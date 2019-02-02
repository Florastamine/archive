@echo off 
call ICommon.bat  

for /f "delims=" %%f in (.\BuildTargetList) do (
    %RECURSIVE_DELETE_DIRECTORY% %%f 
)

%RECURSIVE_DELETE_DIRECTORY% Hotland.xcworkspace 

for /f "delims=" %%f in (.\DeleteTargetList) do ( 
    %RECURSIVE_DELETE_FILES% %%f 
) 
