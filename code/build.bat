@echo off

ctime -begin dbc.ctm

set CommonCompilerFlags=-Wall -Wextra -std=c99 -g
set CommonCompilerFlags=-DDEBUG=1 %CommonCompilerFlags%
set CommonLinkerFlags=

REM TODO - can we just build both with one exe?

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

del *.pdb > NUL 2> NUL

REM 64-bit build
REM Optimization switches /wO2
echo WAITING FOR PDB > lock.tmp
gcc %CommonCompilerFlags% ..\code\dbc.c %CommonLinkerFlags% -o ..\build\dbc.exe
set LastError=%ERRORLEVEL%
del lock.tmp
popd

ctime -end dbc.ctm %LastError%
