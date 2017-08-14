@echo off

ctime -begin dbc.ctm

set CommonCompilerFlags=-Wall -Wextra -std=c99 -g -Wno-sign-compare
set CommonCompilerFlags=-DDEBUG=1 %CommonCompilerFlags%
set CommonLinkerFlags=

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

gcc %CommonCompilerFlags% ..\code\dbc.c %CommonLinkerFlags% -o ..\build\dbc_gcc.exe
set LastError=%ERRORLEVEL%
popd

ctime -end dbc.ctm %LastError%
