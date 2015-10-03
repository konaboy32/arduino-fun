@echo off
set PROJECT_HOME=%USERPROFILE%\Documents\Arduino
set COMPILE=C:\arduino165\arduino_debug --verify

rem -----------------------------------------------------------------------------------
rem set SOURCE=%PROJECT_HOME%\lcd_hello\lcd_hello.ino
set SOURCE=%PROJECT_HOME%\beep\beep.ino
rem -----------------------------------------------------------------------------------

rem rmdir %PROJECT_HOME%\build /s /q
rem mkdir %PROJECT_HOME%\build

%COMPILE% %SOURCE%
pause