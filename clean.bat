@ECHO OFF
REM /P prompts
CLS
ECHO "+---------------------------------------------------+"
ECHO "|             Cleaning up SRC directory             |"
ECHO "|                                                   |"
ECHO "| Version 0.1                               by De   |"
ECHO "+---------------------------------------------------+"
del /s *.o
del /s *.obj
del /s *.exe
del /s *.ncb
del /s *.ilk
del /s *.idb
del /s *.nch
del /s *.suo
del /s *.ddb
del /s *.pdb
del /s *.tlog
del /s *.ipch
del /s *.sdf
del /s *.map
del /s *.gcda
del /s *.gcno
del /s *.gcd
del /s *.xml
del /s *.html
del /s *.VC.db
ECHO "+---------------------------------------------------+"
ECHO "|                  R  E  A  D  Y   !                |"
ECHO "+---------------------------------------------------+"
@ECHO ON
