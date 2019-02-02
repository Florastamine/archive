@echo off 
call ICommon.bat 

for /f "delims=" %%f in (.\DeleteTargetListSafe) do (
    %RECURSIVE_DELETE_FILES% %%f  
)
