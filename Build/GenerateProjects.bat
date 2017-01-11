@echo off 
call ICommon.bat 

%INVOKE_PREMAKE% clean 

rem Batch is a retarded language  
for /f "delims=" %%f in (.\BuildTargetList) do (
    IF "%%f" == "gmake" (
        %INVOKE_PREMAKE% --cc=gcc --os=linux --platform=x32 %%f
    ) ELSE (
	%INVOKE_PREMAKE% %%f 

	IF "%%f" == "vs2012" ( 
		rename Hotland.sln Hotland_VS2012.sln 
	)

	IF "%%f" == "vs2013" (
		rename Hotland.sln Hotland_VS2013.sln
	)

	IF "%%f" == "vs2015" (
		rename Hotland.sln Hotland_VS2015.sln
	)
    )
) 
