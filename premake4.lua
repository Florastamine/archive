solution "Hotland"

configurations {
    "Debug", 
    "Release"
}

project "Hotland" 
language "C++"
kind "WindowedApp"
files {
    "**.cpp",
    "**.hpp", 
    "**.c", 
    "**.h"
} 

configuration "Debug" 
buildoptions {
    "-Wall",
    "-std=c++03"
}

configuration "Release" 
buildoptions {
    "-Ofast", 
    "-std=c++03"
}