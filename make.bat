@echo off
set PROJECT_HOME=%USERPROFILE%\Documents\Arduino
set COMPILE=C:\arduino165\arduino_debug --verify

rem -----------------------------------------------------------------------------------
set source=%PROJECT_HOME%\lcd_hello\lcd_hello.ino
rem -----------------------------------------------------------------------------------

rem rmdir %PROJECT_HOME%\build /s /q
rem mkdir %PROJECT_HOME%\build

%compile% %source%
pause