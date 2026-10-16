@echo off
chcp 65001 >nul
cd /d "%~dp0"
echo ============================================
echo   Compiling and running day1\p1.cpp
echo ============================================
echo.
g++ -std=c++17 -Wall -g "day1\p1.cpp" -o "day1\p1.exe"
if errorlevel 1 (
    echo.
    echo [FAILED] Compile error.
    echo.
    pause
    exit /b 1
)
echo [OK] Compile success. Running...
echo --------------------------------------------
"day1\p1.exe"
echo --------------------------------------------
echo.
echo [Done]
pause