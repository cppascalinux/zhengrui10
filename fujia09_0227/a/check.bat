@echo off
:loop
gen.exe
a.exe
bf.exe 
fc a.out bf.out
if not errorlevel 1 goto loop
pause