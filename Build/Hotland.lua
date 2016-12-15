--[[
Copyright (c) 2016, Florastamine

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
]]-- 

solution("Hotland") 

project("Hotland") 
    language("C++") 
    kind("WindowedApp") -- Kind of the project. We'll be using WindowedApp for now. 

    location(_ACTION) -- Location of the generated project files for a specific platform when invoking Premake. 
                      -- For example, it's the location of the generated VS2012 solution when calling 
                      -- "premake4 vs2012".  
    targetdir(tostring(_ACTION .. "/Binaries")) -- Where the binaries will be built, we'll be using the "Binaries" folder 
                                                -- inside the project folder for now.   

    files({ -- Files to be included in the project.  
        "../**.ipp", 
        "../**.hpp", 
        "../**.cpp", 
        "../**.c", 
        "../*.h",
        "../*.inl"
    }) 

    excludes({ -- Files to be excluded out of the project. 
        -- 
    })

    includedirs({
        "../Source/3rd/boost", 
        "../Source/3rd/cereal/include", 
        "../Source/3rd/EASTL/include", 
        "../Source/3rd/EASTL/source", 
        "../Source/3rd/EASTL/test/packages/EABase/include/Common", 
        "../Source/3rd/EASTL/test/packages/EAStdC/include", 
        "../Source/3rd/EASTL/test/packages/EAAssert/include", 
        "../Source/3rd/rapidjson/include", 

        "../Source/Kernel",
        "../Source/Kernel/IO",
        "../Source/Kernel/Platform",
        "../Source/Kernel/Compatibility" 
    }) 

    libdirs({
        -- 
    })

    configurations({
        "Debug", 
        "Release", 
        "With_DLL_Debug",
        "With_DLL_Release"  
    }) 
    
    configuration("Debug") 
        configuration("gmake") 
            buildoptions({
                "-Og", -- https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html 
                "-Wall", 
                "-std=gnu++11", 
                "-DEASTL_DLL=1", 
                "-DEA_PLATFORM_MINGW=1"
            })

        configuration("vs*") 
            buildoptions({
                -- "/std:c++11",  
                "/Od",  
                "/RTC", 
                "/sdl", 
                "/Wall" 
            }) 

            defines({"DEBUG"})

    configuration("Release") 
        configuration("gmake") 
            buildoptions({
                "-Ofast", 
                "-Wall", 
                "-std=gnu++11", 
                "-DEASTL_DLL=1"
            })

        configuration("vs*") 
            buildoptions({ 
                -- "/Ox",
                -- "/O1",  
                -- "/Wall" 
            })

            defines({
                "_CRT_SECURE_NO_WARNINGS",  
                "_SCL_SECURE_NO_WARNINGS", 
                "_ALLOW_KEYWORD_MACROS", -- Because we've re-defined nullptr to NULL inside Source/Kernel/Compatibility/CXXCompatibility.hpp 
                                         -- to be able to compile with C++03-conformed compilers, this macro exists to shut the MSVC 
                                         -- compiler up about redefining macros. 
                "NDEBUG" 
            }) 
