@echo off
chcp 65001 >nul
cd /d "%~dp0"
echo ============================================
echo   Compiling and running: %1
echo ============================================
echo.
g++ -std=c++17 -Wall -g "%~1" -o "%~n1.exe"
if errorlevel 1 (
    echo.
    echo [FAILED] Compile error. Read the red messages above.
    echo.
    pause
    exit /b 1
)
echo [OK] Compile success. Running...
echo --------------------------------------------
"%~n1.exe"
echo --------------------------------------------
echo.
echo [Done] Program finished.
pause