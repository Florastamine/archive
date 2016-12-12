@echo off 
call ICommon.bat 

%INVOKE_PREMAKE% clean 

rem Batch is a retarded language  
for /f "delims=" %%f in (.\BuildTargetList) do (
    if %%f == "gmake" (
        %INVOKE_PREMAKE% --cc=gcc --os=linux --platform=x32 %%f
    ) ELSE (
        %INVOKE_PREMAKE% %%f
    )
) 
