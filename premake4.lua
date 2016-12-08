solution "Hotland"

configurations {
    "Debug", 
    "Release"
}

project "Hotland" 
language "C++"
kind "WindowedApp"
files {
    "**.ipp", 
    "**.cpp",
    "**.hpp", 
    "**.c", 
    "**.h"
} 

configuration "Debug" 
buildoptions {
    "-Og", -- https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html 
    "-Wall", 
    "-std=gnu++11", 
    "-I\"./Source/3rd/\"",
    "-I\"./Source/Kernel/\"",
    "-I\"./Source/Kernel/IO/\"", 
    "-I\"./Source/Kernel/Platform/\"",
    "-I\"./Source/Kernel/Compatibility\""
}

configuration "Release" 
buildoptions {
    "-Ofast", 
    "-Wall", 
    "-std=gnu++11", 
    "-I\"./Source/3rd/\"", 
    "-I\"./Source/Kernel/\"",   
    "-I\"./Source/Kernel/IO/\"", 
    "-I\"./Source/Kernel/Platform/\"",  
    "-I\"./Source/Kernel/Compatibility\""
}
