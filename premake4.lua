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
    "-Wall", 
    "-std=gnu++11", 
    "-I\"./Source/3rd/\""
}

configuration "Release" 
buildoptions {
    "-Ofast", 
    "-Wall", 
    "-std=gnu++11", 
    "-I\"./Source/3rd/\""
}
