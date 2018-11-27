#include <Python.h>
#include <osdefs.h>
#include <internal/pystate.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#ifdef __APPLE__
#include <libproc.h>
#endif

static int py_wstat(const wchar_t* path, struct stat *buf)
{
    int err;
    char *fname;
    fname = _Py_EncodeLocaleRaw(path, NULL);
    if (fname == NULL)
    {
        errno = EINVAL;
        return -1;
    }
    err = stat(fname, buf);
    PyMem_Free(fname);
    return err;
}

static int is_file(wchar_t* filename)
{
    struct stat buf;
    if (py_wstat(filename, &buf) != 0)
        return 0;
    if (!S_ISREG(buf.st_mode))
        return 0;
    return 1;
}

static int is_dir(wchar_t* filename)
{
    struct stat buf;
    if (py_wstat(filename, &buf) != 0)
        return 0;
    if (!S_ISDIR(buf.st_mode))
        return 0;
    return 1;
}

static _PyInitError eval_full_path_of_executable(wchar_t** result)
{
    wchar_t* exe_path_w = NULL;
#ifdef _WIN32
    wchar_t buffer[MAXPATHLEN + 1];
    wchar_t reparsed_path[MAXPATHLEN + 1];
    DWORD attr;
    DWORD size;
    DWORD (WINAPI* GetFinalPathNameByHandleW_Ptr)(HANDLE, LPWSTR, DWORD, DWORD);
    HANDLE fh_exe;
    size = GetModuleFileNameW(NULL, buffer, MAXPATHLEN);
    if (size == 0)
        return _Py_INIT_ERR("Cannot eval path of executable: got 0 from GetModuleFileNameW");
    if (size  > MAXPATHLEN)
        size = MAXPATHLEN;
    buffer[size] = 0;
    GetFinalPathNameByHandleW_Ptr = (DWORD (WINAPI *)(HANDLE, LPWSTR, DWORD, DWORD))GetProcAddress(GetModuleHandle("kernel32"), "GetFinalPathNameByHandleW");
    if (GetFinalPathNameByHandleW_Ptr)
    {
        attr = GetFileAttributesW(buffer);
        if (attr == INVALID_FILE_ATTRIBUTES)
            return _Py_INIT_ERR("Cannot eval path of executable: got INVALID_FILE_ATTRIBUTES from GetFileAttributesW");
        if (attr & FILE_ATTRIBUTE_REPARSE_POINT)
        {
            fh_exe = CreateFileW(buffer, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (fh_exe == INVALID_HANDLE_VALUE)
                return _Py_INIT_ERR("Cannot eval path of executable: got INVALID_HANDLE_VALUE from CreateFileW");
            size = (*GetFinalPathNameByHandleW_Ptr)(fh_exe, reparsed_path, MAX_PATH, 0);
            if (size == 0)
            {
                CloseHandle(fh_exe);
                return _Py_INIT_ERR("Cannot eval path of executable: got 0 from GetFinalPathNameByHandleW");
            }
            CloseHandle(fh_exe);
            if (size > MAX_PATH)
              size = MAX_PATH;
            reparsed_path[size] = 0;
            if (wcsncmp(L"\\\\?\\", reparsed_path, 4) == 0)
                wcsncpy(buffer, &reparsed_path[4], MAX_PATH - 3);
            else
                wcsncpy(buffer, reparsed_path, MAX_PATH + 1);
        }
    }
    exe_path_w = PyMem_RawMalloc((wcslen(buffer) + 1) * sizeof(wchar_t));
    wcscpy(exe_path_w, buffer);
#else
    char exe_path[MAXPATHLEN + 1];
#ifdef __APPLE__
    int size = proc_pidpath(getpid(), exe_path, MAXPATHLEN);
#else
    int size = readlink("/proc/self/exe", exe_path, MAXPATHLEN);
#endif
    if (size < 0)
        size = 0;
    exe_path[size] = 0;
    exe_path_w = Py_DecodeLocale(exe_path, NULL);
#endif
    *result = exe_path_w;
    return _Py_INIT_OK();
}

static _PyInitError eval_dirname_of_this_dso(wchar_t** result)
{
    wchar_t* dso_path = NULL;
    int i;
#ifdef _WIN32
    extern HANDLE PyWin_DLLhModule;
    wchar_t buffer[MAXPATHLEN + 1];
    if (PyWin_DLLhModule == NULL)
    {
        return _Py_INIT_ERR("Cannot eval dirname of dso: HANDLE PyWin_DLLhModule is NULL");
    }
    GetModuleFileNameW(PyWin_DLLhModule, buffer, MAXPATHLEN);
    i = (int)wcslen(buffer);
    for (; i >= 0; --i)
    {
        if (buffer[i] == '\\')
        {
            buffer[i + 1] = 0;
            break;
        }
    }
    dso_path = PyMem_RawMalloc((wcslen(buffer) + 1) * sizeof(wchar_t));
    wcscpy(dso_path, buffer);
#else
    Dl_info dl;
    memset(&dl, 0, sizeof(dl));
    int ret = dladdr((void*)eval_dirname_of_this_dso, &dl);
    if (!ret || !dl.dli_fname || (dl.dli_fname[0] != '/'))
    {
        return _Py_INIT_ERR("Cannot eval dirname of dso: bad result in dladdr()");
    }

    dso_path = Py_DecodeLocale(dl.dli_fname, NULL);
    i = (int)wcslen(dso_path);
    for (; i >= 0; --i)
    {
        if (dso_path[i] == '/')
        {
            dso_path[i + 1] = 0;
            break;
        }
    }
#endif
    *result = dso_path;
    return _Py_INIT_OK();
}

_PyInitError _PyPathConfig_Calculate(_PyPathConfig* config, const _PyCoreConfig* core_config)
{
    _PyInitError err;
    int i;
    wchar_t* dso_dir_path = NULL;
    wchar_t* prog_path = NULL;
    wchar_t stdlib_zip_fname[32];
    wchar_t stdlib_dname[32];
    wchar_t stdlib_zip_path[MAXPATHLEN + 1];
    wchar_t stdlib_dir_path[MAXPATHLEN + 1];
    int have_stdlib_zip = 0;
    int have_stdlib_dir = 0;
    int have_py_home = 0;
    int have_env_path = 0;
    int have_modules_dir = 0;
    wchar_t modules_path[MAXPATHLEN + 1];
    size_t search_path_len = 0;
    wchar_t delim[2] = {DELIM, 0};
    wchar_t sepstr[2] = {SEP, 0};
    wchar_t* new_search_path = NULL;
    wchar_t* prefix = NULL;

    err = eval_dirname_of_this_dso(&dso_dir_path);
    if (_Py_INIT_FAILED(err))
        goto failed;

    err = eval_full_path_of_executable(&prog_path);
    if (_Py_INIT_FAILED(err))
        goto failed;

    prefix = _PyMem_RawWcsdup(prog_path);
    i = (int)wcslen(prefix);
    for (; i > 0; --i)
    {
        if (prefix[i - 1] == SEP)
        {
            prefix[i - 1] = 0;
            break;
        }
    }

    if (core_config->module_search_path_env && core_config->module_search_path_env[0] != 0)
    {
        have_env_path = 1;
    }

    swprintf(stdlib_zip_fname, 32, L"python%d%d.zip", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    wcscpy(stdlib_zip_path, dso_dir_path);
    wcscat(stdlib_zip_path, stdlib_zip_fname);
    have_stdlib_zip = is_file(stdlib_zip_path);

    if (!have_stdlib_zip)
    {
        swprintf(stdlib_dname, 32, L"python%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
        wcscpy(stdlib_dir_path, dso_dir_path);
        wcscat(stdlib_dir_path, stdlib_dname);
        have_stdlib_dir = is_dir(stdlib_dir_path);
    }

    if (!have_stdlib_zip && !have_stdlib_dir)
    {
        if (core_config->home && core_config->home[0])
            have_py_home = is_dir(core_config->home);
    }

    wcscpy(modules_path, prefix);
    wcscat(modules_path, sepstr);
    wcscat(modules_path, L"modules");
    have_modules_dir = is_dir(modules_path);

    if (have_stdlib_zip)
    {
        search_path_len += 1 + wcslen(stdlib_zip_path);
    }
    if (have_stdlib_dir)
    {
        search_path_len += 1 + wcslen(stdlib_dir_path);
    }
    if (have_py_home)
    {
        search_path_len += 1 + wcslen(core_config->home);
    }
    if (have_modules_dir)
    {
        search_path_len += 1 + wcslen(modules_path);
    }
    if (have_env_path)
    {
        search_path_len += 1 + wcslen(core_config->module_search_path_env);
    }
    if (core_config->nmodule_search_path > 0)
    {
        for (i = 0; i < core_config->nmodule_search_path; ++i)
        {
            search_path_len += 1 + wcslen(core_config->module_search_paths[i]);
        }
    }

    new_search_path = (wchar_t*)PyMem_RawMalloc(search_path_len * sizeof(wchar_t));
    if (new_search_path == NULL)
    {
        err = _Py_INIT_NO_MEMORY();
        goto failed;
    }
    new_search_path[0] = 0;

    if (have_stdlib_zip)
    {
        if (new_search_path[0])
            wcscat(new_search_path, delim);
        wcscat(new_search_path, stdlib_zip_path);
    }
    if (have_stdlib_dir)
    {
        if (new_search_path[0])
            wcscat(new_search_path, delim);
        wcscat(new_search_path, stdlib_dir_path);
    }
    if (have_py_home)
    {
        if (new_search_path[0])
            wcscat(new_search_path, delim);
        wcscat(new_search_path, core_config->home);
    }
    if (have_modules_dir)
    {
        if (new_search_path[0])
            wcscat(new_search_path, delim);
        wcscat(new_search_path, modules_path);
    }
    if (have_env_path)
    {
        if (new_search_path[0])
            wcscat(new_search_path, delim);
        wcscat(new_search_path, core_config->module_search_path_env);
    }
    if (core_config->nmodule_search_path > 0)
    {
        for (i = 0; i < core_config->nmodule_search_path; ++i)
        {
            if (new_search_path[0])
                wcscat(new_search_path, delim);
            wcscat(new_search_path, core_config->module_search_paths[i]);
        }
    }

    dso_dir_path[wcslen(dso_dir_path) - 1] = 0;

    config->module_search_path = new_search_path;
    config->program_full_path = prog_path;
    config->prefix = prefix;
#ifdef _WIN32
    config->dll_path = dso_dir_path;
#else
    config->exec_prefix = _PyMem_RawWcsdup(prefix);
    PyMem_RawFree(dso_dir_path);
#endif
    return _Py_INIT_OK();

failed:
    PyMem_RawFree(dso_dir_path);
    PyMem_RawFree(prog_path);
    PyMem_RawFree(prefix);
    return err;
}

#ifdef _WIN32
int _Py_CheckPython3()
{
    return 0;
}
#endif
