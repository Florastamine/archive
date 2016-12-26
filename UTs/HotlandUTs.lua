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

local UTBase = require("./HotlandUTsBase") 

solution("HotlandUTs") 

for i = 1, #UTBase, 1 do 
    project(UTBase[i]) 
        language("C++") 
        kind("WindowedApp") 

        location(UTBase[i] .. '_' .. _ACTION) 
        targetdir(tostring(UTBase[i] .. '_' .. _ACTION .. "/Binaries"))  

        files({
            tostring(UTBase[i] .. ".cpp"), 
            "../Source/**.cpp", 
            "../Source/**.hpp"
        })

        excludes({"../Source/main.cpp"})

        includedirs({
            "../Source/3rd/boost", 
            "../Source/3rd/cereal/include", 
            "../Source/3rd/EASTL/include", 
            "../Source/3rd/EASTL/source", 
            "../Source/3rd/EASTL/test/packages/EABase/include/Common", 
            "../Source/3rd/EASTL/test/packages/EAStdC/include", 
            "../Source/3rd/EASTL/test/packages/EAAssert/include", 
            "../Source/3rd/rapidjson/include", 

            "../Source", 
            "./3rd"
        }) 

        libdirs({
            -- 
        }) 

        configurations({
            "Debug", 
            "Release" 
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
end 
