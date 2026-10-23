@echo off
rem Day6 multi-file run script - double click to compile and run
cd /d "%~dp0"

echo === compiling all .cpp in this folder ===
g++ -std=c++17 -Wall -g *.cpp -o app.exe
if errorlevel 1 (
    echo.
    echo [ERROR] compile failed - see messages above
    pause
    exit /b 1
)

echo === running app.exe ===
echo.
app.exe

echo.
echo === program finished ===
pause
