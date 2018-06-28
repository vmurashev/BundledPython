#include <Python.h>
#include <osdefs.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#ifdef __APPLE__
#include <libproc.h>
#endif

static char EMPTY_STR[1] = {0};
static char prog_path[MAXPATHLEN+1] = {0};
static char prog_dir_path[MAXPATHLEN+1] = {0};
static char* module_search_path = NULL;
static int calculated = 0;

static char* prefix = EMPTY_STR;
static char* exec_prefix = EMPTY_STR;


static int is_full_path(const char* path)
{
#ifdef _WIN32
    char letter = 0;
    char anchor = 0;
    if (path && path[0] && path[1])
    {
        letter = path[0];
        letter &= ~0x20;
        anchor = path[1];
    }
    if (anchor == ':' && 'A' <= letter && letter <= 'Z')
    {
      return 1;
    }
    return 0;
#else
    if (path && path[0] == '/')
    {
        return 1;
    }
    return 0;
#endif
}


static void eval_full_path_of_executable()
{
    char* sep = NULL;
#ifdef _WIN32
    wchar_t buffer[MAXPATHLEN + 1];
    wchar_t reparsed_path[MAXPATHLEN + 1];
    DWORD attr;
    DWORD size;
    DWORD (WINAPI* GetFinalPathNameByHandleW_Ptr)(HANDLE, LPWSTR, DWORD, DWORD);
    HANDLE fh_exe;
#endif
    char* preset_progpath = Py_GetProgramName();
    if (is_full_path(preset_progpath))
    {
        strcpy(prog_path, preset_progpath);
        goto eval_dir_path;
    }
#ifdef _WIN32
    size = GetModuleFileNameW(NULL, buffer, MAXPATHLEN);
    if (size == 0)
        Py_FatalError("Cannot eval path of executable: got 0 from GetModuleFileNameW");
    if (size  > MAXPATHLEN)
        size = MAXPATHLEN;
    buffer[size] = 0;
    GetFinalPathNameByHandleW_Ptr = (DWORD (WINAPI *)(HANDLE, LPWSTR, DWORD, DWORD))GetProcAddress(GetModuleHandle("kernel32"), "GetFinalPathNameByHandleW");
    if (GetFinalPathNameByHandleW_Ptr)
    {
        attr = GetFileAttributesW(buffer);
        if (attr == INVALID_FILE_ATTRIBUTES)
            Py_FatalError("Cannot eval path of executable: got INVALID_FILE_ATTRIBUTES from GetFileAttributesW");
        if (attr & FILE_ATTRIBUTE_REPARSE_POINT)
        {
            fh_exe = CreateFileW(buffer, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (fh_exe == INVALID_HANDLE_VALUE)
                Py_FatalError("Cannot eval path of executable: got INVALID_HANDLE_VALUE from CreateFileW");
            size = (*GetFinalPathNameByHandleW_Ptr)(fh_exe, reparsed_path, MAX_PATH, 0);
            if (size == 0)
            {
                CloseHandle(fh_exe);
                Py_FatalError("Cannot eval path of executable: got 0 from GetFinalPathNameByHandleW");
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
    WideCharToMultiByte(CP_ACP, 0, buffer, -1, prog_path, MAXPATHLEN+1, NULL, NULL);
#else
#ifdef __APPLE__
    int size = proc_pidpath(getpid(), prog_path, MAXPATHLEN);
#else
    int size = readlink("/proc/self/exe", prog_path, MAXPATHLEN);
#endif
    if (size < 0)
        size = 0;
    prog_path[size] = 0;
#endif

eval_dir_path:
    strcpy(prog_dir_path, prog_path);
#ifdef _WIN32
    sep = strrchr(prog_dir_path, '\\');
#else
    sep = strrchr(prog_dir_path, '/');
#endif
    if (sep == NULL)
        Py_FatalError("Cannot eval dirname of executable: path separator not found");
    sep++;
    *sep = 0;
}


#ifdef Py_ENABLE_SHARED

static int is_file(const char* filename)
{
    struct stat buf;
    if (stat(filename, &buf) != 0)
        return 0;
    if (!S_ISREG(buf.st_mode))
        return 0;
    return 1;
}

static int is_dir(const char* filename)
{
    struct stat buf;
    if (stat(filename, &buf) != 0)
        return 0;
    if (!S_ISDIR(buf.st_mode))
        return 0;
    return 1;
}

static void eval_dirname_of_this_dso(char* dso_path)
{
    int i;
#ifdef _WIN32
    extern HANDLE PyWin_DLLhModule;
    wchar_t buffer[MAXPATHLEN + 1];
#endif
    dso_path[0] = 0;
#ifdef _WIN32
    if (PyWin_DLLhModule == NULL)
    {
        Py_FatalError("Cannot eval dirname of dso: HANDLE PyWin_DLLhModule is NULL");
    }
    GetModuleFileNameW(PyWin_DLLhModule, buffer, MAXPATHLEN);
    i = (int)(wcslen(buffer));
    for (; i >= 0; --i)
    {
        if (buffer[i] == '\\')
        {
            buffer[i + 1] = 0;
            break;
        }
    }
    WideCharToMultiByte(CP_ACP, 0, buffer, -1, dso_path, MAXPATHLEN+1, NULL, NULL);
#else
    Dl_info dl;
    memset(&dl, 0, sizeof(dl));
    int ret = dladdr((void*)eval_dirname_of_this_dso, &dl);
    if (!ret || !dl.dli_fname || (dl.dli_fname[0] != '/'))
    {
        Py_FatalError("Cannot eval dirname of dso: bad result in dladdr()");
    }
    strcpy(dso_path, dl.dli_fname);
    i = (int)(strlen(dso_path));
    for (; i >= 0; --i)
    {
        if (dso_path[i] == '/')
        {
            dso_path[i + 1] = 0;
            break;
        }
    }
#endif
}

static void calculate_path(void)
{
    char dso_dir_path[MAXPATHLEN + 1];
    char stdlib_zip_fname[32];
    char stdlib_dname[32];
    char stdlib_zip_path[MAXPATHLEN + 1];
    char stdlib_dir_path[MAXPATHLEN + 1];
    int have_stdlib_zip = 0;
    int have_stdlib_dir = 0;
    int have_py_home = 0;
    int have_env_path = 0;
    int have_modules_dir = 0;
    const char* py_home = NULL;
    const char* envpath = NULL;
    char modules_path[MAXPATHLEN + 1];
    size_t search_path_len = 0;
    char delim[2] = {DELIM, 0};

    eval_full_path_of_executable();
    eval_dirname_of_this_dso(dso_dir_path);
    envpath = Py_GETENV("PYTHONPATH");
    if (envpath && envpath[0] != 0)
    {
        have_env_path = 1;
    }

    snprintf(stdlib_zip_fname, 32, "python%d%d.zip", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    strcpy(stdlib_zip_path, dso_dir_path);
    strcat(stdlib_zip_path, stdlib_zip_fname);
    have_stdlib_zip = is_file(stdlib_zip_path);

    if (!have_stdlib_zip)
    {
        snprintf(stdlib_dname, 32, "python%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
        strcpy(stdlib_dir_path, dso_dir_path);
        strcat(stdlib_dir_path, stdlib_dname);
        have_stdlib_dir = is_dir(stdlib_dir_path);
    }

    if (!have_stdlib_zip && !have_stdlib_dir)
    {
        py_home = Py_GetPythonHome();
        if (py_home && py_home[0])
            have_py_home = is_dir(py_home);
    }

    strcpy(modules_path, prog_dir_path);
    strcat(modules_path, "modules");

    have_modules_dir = is_dir(modules_path);

    if (have_stdlib_zip)
    {
        search_path_len += 1 + strlen(stdlib_zip_path);
    }
    if (have_stdlib_dir)
    {
        search_path_len += 1 + strlen(stdlib_dir_path);
    }
    if (have_py_home)
    {
        search_path_len += 1 + strlen(py_home);
    }
    if (have_modules_dir)
    {
        search_path_len += 1 + strlen(modules_path);
    }
    if (have_env_path)
    {
        search_path_len += 1 + strlen(envpath);
    }

    module_search_path = (char*) malloc(search_path_len);
    module_search_path[0] = 0;

    if (have_stdlib_zip)
    {
        if (module_search_path[0])
            strcat(module_search_path, delim);
        strcat(module_search_path, stdlib_zip_path);
    }
    if (have_stdlib_dir)
    {
        if (module_search_path[0])
            strcat(module_search_path, delim);
        strcat(module_search_path, stdlib_dir_path);
    }
    if (have_py_home)
    {
        if (module_search_path[0])
            strcat(module_search_path, delim);
        strcat(module_search_path, py_home);
    }
    if (have_modules_dir)
    {
        if (module_search_path[0])
            strcat(module_search_path, delim);
        strcat(module_search_path, modules_path);
    }
    if (have_env_path)
    {
        if (module_search_path[0])
            strcat(module_search_path, delim);
        strcat(module_search_path, envpath);
    }

    calculated = 1;
}

#else

static void calculate_path(void)
{
    int have_env_path = 0;
    const char* envpath = NULL;
    eval_full_path_of_executable();
    envpath = Py_GETENV("PYTHONPATH");
    if (envpath && envpath[0] != 0)
    {
        have_env_path = 1;
    }
    if (have_env_path)
    {
        module_search_path = (char*) malloc(1 + strlen(envpath));
        module_search_path[0] = 0;
        strcat(module_search_path, envpath);
    }
    else
    {
        module_search_path = EMPTY_STR;
    }
    calculated = 1;
}

#endif /*Py_ENABLE_SHARED*/


/* External interface */

char* Py_GetPath(void)
{
    if (!calculated)
        calculate_path();
    return module_search_path;
}

char* Py_GetPrefix(void)
{
    if (!calculated)
        calculate_path();
    return prefix;
}

char* Py_GetExecPrefix(void)
{
    if (!calculated)
        calculate_path();
    return exec_prefix;
}

char* Py_GetProgramFullPath(void)
{
    if (!calculated)
        calculate_path();
    return prog_path;
}
