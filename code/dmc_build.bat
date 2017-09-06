@ECHO OFF
CLS
ECHO Compiling with profiling (-gt)
dmc -gt -g -p -r -w- -x -wc -A -Ar dbc.c -o ..\build\dbc_dmc.exe
@ECHO ON