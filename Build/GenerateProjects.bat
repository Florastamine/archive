@echo off 
call PremakeCommon.bat 

%INVOKE_PREMAKE% clean 
%INVOKE_PREMAKE% --cc=gcc --os=linux --platform=x32 gmake 
%INVOKE_PREMAKE% codeblocks 
%INVOKE_PREMAKE% vs2012 
%INVOKE_PREMAKE% xcode4 
