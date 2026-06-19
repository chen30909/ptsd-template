@echo off
if exist build (
    echo [INFO] build is exist , skip it
) else (
    echo [INFO] build is not exist, do cmake option Debug
    cmake -DCMAKE_BUILD_TYPE=Debug -B build
)
echo build the project now
cmake --build build --target LINEPOP2
echo finish compile
echo If you use Visual Studio generator, run build\Debug\LINEPOP2.exe
echo If you use MinGW/Ninja generator, run build\LINEPOP2.exe
pause
