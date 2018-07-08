rem If you're using Premake5 or Premake4, replace PREMAKE with the name of the Premake executable of 
rem your choice. Since I originally intended to build Hotland with both Premake4 and Premake5, I leave 
rem the PREMAKE variable to just "premake" without the extra '4' or '5'. 

set "PREMAKE=premake" 
set "INVOKE_PREMAKE=%PREMAKE% --file=Hotland.lua" 
set "RECURSIVE_DELETE_DIRECTORY=rd /s /q" 
set "RECURSIVE_DELETE_FILES=del /a /q /f /f"  
