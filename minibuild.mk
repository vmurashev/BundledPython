#pragma build output-wsl='output/wsl'
#pragma os:all native model=auto
#pragma os:windows nasm executable='C:\NASM\nasm.exe'

#pragma os:windows toolset module=msvs version=2008
#pragma os:windows toolset module=msvs version=2015

#pragma os:windows toolset module=mingw package='C:\mingw-w64\i686-5.4.0-win32-dwarf-rt_v5-rev0\mingw32' arch=x86
#pragma os:windows toolset module=mingw package='C:\mingw-w64\x86_64-5.4.0-win32-seh-rt_v5-rev0\mingw64' arch=x86_64

#pragma os:linux toolset module=mingw package='~/x-tools/x86_64-w64-mingw32' prefix=x86_64-w64-mingw32- arch=x86,x86_64

#pragma os:linux toolset module=xtools package='~/x-tools/i686-unknown-linux-gnu'        prefix=i686-unknown-linux-gnu-        arch=x86
#pragma os:linux toolset module=xtools package='~/x-tools/x86_64-unknown-linux-gnu'      prefix=x86_64-unknown-linux-gnu-      arch=x86_64
#pragma os:linux toolset module=xtools package='~/x-tools/arm-unknown-linux-gnueabi'     prefix=arm-unknown-linux-gnueabi-     arch=arm
#pragma os:linux toolset module=xtools package='~/x-tools/aarch64-unknown-linux-gnueabi' prefix=aarch64-unknown-linux-gnueabi- arch=arm64

#pragma os:macosx toolset module=clang
