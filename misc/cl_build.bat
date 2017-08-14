@echo off

ctime -begin dbc.ctm

REM set CommonCompilerFlags=-Od -MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo -Oi -W4 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -wd4996 -wd4204 -FC -Z7
set CommonCompilerFlags=-Od -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo -Oi -W4 -wd4996 -wd4204 -Z7 -DWIN32
set CommonCompilerFlags=-DDEBUG=0 %CommonCompilerFlags%
set CommonLinkerFlags= -incremental:no -opt:ref

REM TODO - can we just build both with one exe?

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

del *.pdb > NUL 2> NUL

REM 64-bit build
REM Optimization switches /wO2
echo WAITING FOR PDB > lock.tmp
cl %CommonCompilerFlags% ..\code\dbc.c -Fmwin32_dbc.map /link %CommonLinkerFlags%
set LastError=%ERRORLEVEL%
del lock.tmp
popd

ctime -end dbc.ctm %LastError%
