@echo off 
SET MAKETOOL=..\tools\premake\release\premake5.exe

rem %MAKETOOL% --arch=x86 --to=vs2013\x86 vs2013
%MAKETOOL% --arch=x64 --to=vs2013\x64 vs2013

rem %MAKETOOL% --arch=x86 --to=vs2012\x86 vs2012
rem %MAKETOOL% --arch=x64 --to=vs2012\x64 vs2012

rem vs2008 project generation commented because the project uses many new features introduced in c++11
rem %MAKETOOL% --arch=x86 --to=vs2008\x86 vs2008
rem %MAKETOOL% --arch=x64 --to=vs2008\x64 vs2008

pause