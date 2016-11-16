@echo off

echo -------
echo -------

set Wildcard=*.h *.cpp *.inl *.c

echo TODOS:
findstr -s -n -i -l "TODO" %Wildcard%

echo -------
echo -------
