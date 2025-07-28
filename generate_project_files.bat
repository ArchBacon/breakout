@echo off
call external\premake\premake5.exe --file=breakout.build.lua vs2022
IF %ERRORLEVEL% NEQ 0 PAUSE &:: If the output code is not 0, there is probably an error
