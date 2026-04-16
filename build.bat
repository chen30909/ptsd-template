@echo off
if exist build (
    echo [INFO] build is exist , skip it
) else (
    echo [INFO] build is not exist, do cmake option Debug
    cmake -DCMAKE_BUILD_TYPE=Debug -B build
)
echo build the project now
cmake --build build
echo finish compile , run ./build/Debug/2025OOPL_PROJECT.exe
pause
