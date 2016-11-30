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

package.path = package.path .. ";./BuildTool"
package.cpath = package.cpath .. ";./" 

require("imgui") 
require("vars") 

function love.load(args)
    love.window.setTitle(window_title)

    love.window.setMode(0, 0, {})
    __window_max_width, __window_max_height = love.graphics.getDimensions()

    love.window.setMode(window_width, window_height, {
        fullscreen = false,
        vsync = false,
        msaa = 0,
        resizable = false,
        x = (__window_max_width - window_width) / 2,
        y = (__window_max_height - window_height) / 2
    })
end 

function love.update(dt)
end 

function love.textinput(t)
    imgui.TextInput(t)
end

function love.keypressed(key)
    imgui.KeyPressed(key)
end

function love.keyreleased(key)
    imgui.KeyReleased(key)
end

function love.mousemoved(x, y)
    imgui.MouseMoved(x, y)
end

function love.mousepressed(x, y, button)
    imgui.MousePressed(button)
end

function love.mousereleased(x, y, button)
    imgui.MouseReleased(button)
end

function love.wheelmoved(x, y)
    imgui.WheelMoved(y)
end 

local RenderToolchainUI = function ()
    if __toolchain_type == 1 then -- Linux (native) 
        imgui.Text("Linux (native)")
    elseif __toolchain_type == 2 then -- Windows (with Microsoft Visual Studio)
        imgui.Text("Windows (with Microsoft Visual Studio)")
    elseif __toolchain_type == 3 then -- Windows (with MinGW/MinGW-W64) 
        _, __mingw_root_buffer = imgui.InputText("MinGW root", __mingw_root_buffer, __mingw_root_buffer_length) 
    elseif __toolchain_type == 4 then -- Windows (with MSYS2+MinGW) 
        _, __msys2_root_buffer = imgui.InputText("MSYS2 root", __msys2_root_buffer, __msys2_root_buffer_length) 
    else 
    end 
end  

function love.draw()
    imgui.NewFrame() 

    imgui.SetNextWindowSize(window_width, window_height)
    imgui.SetNextWindowPos(0, 0)

    imgui.Begin(window_title)
        if imgui.CollapsingHeader("General configuration") then 
            _, __built_target_buffer = imgui.InputText("Built target folder", __built_target_buffer, __built_target_buffer_length)  
            _, __built_cmake_buffer = imgui.InputText("CMake location/path", __built_cmake_buffer, __built_cmake_buffer_length)
        end 

        if imgui.CollapsingHeader("Toolchain") then 
            imgui.Text("Toolchain type:")
            _, __toolchain_type = imgui.Combo("TT", __toolchain_type, {
                "Linux (native)",
                "Windows (with Microsoft Visual Studio)", 
                "Windows (with MinGW/MinGW-W64)",
                "Windows (with MSYS2+MinGW/MinGW-W64)"
            }, 4);
            
            RenderToolchainUI()
        end 

        if imgui.CollapsingHeader("Target configuration") then 
            _, __target_type = imgui.Combo("TC", __target_type, {
                "Linux (I'll generate a bash (.sh) script)", 
                "Windows (I'll generate a batch (.bat) script)"
            }, 2); 
        end 

        if imgui.CollapsingHeader("Build options") then 
            _, __is_build_64bit = imgui.Checkbox("Build 64-bit targets (URHO3D_64BIT)", __is_build_64bit) 

            _, __is_build_network = imgui.Checkbox("Networking support (URHO3D_NETWORK)", __is_build_network) 

            _, __is_build_physics = imgui.Checkbox("Physics(*) support (URHO3D_PHYSICS)", __is_build_physics)
            imgui.Text("(*) Physics support through Bullet.")

            _, __is_build_nav = imgui.Checkbox("Navigation support (URHO3D_NAVIGATION)", __is_build_nav)

            _, __is_build_2d = imgui.Checkbox("2D(*) support (URHO3D_URHO2D)", __is_build_2d) 
            imgui.Text("(*) 2D support includes both rendering and physics.")

            _, __is_build_mt = imgui.Checkbox("MT support (URHO3D_THREADING)", __is_build_mt) 

            _, __is_build_profiling = imgui.Checkbox("Profiling support (URHO3D_PROFILING)", __is_build_profiling) 

            _, __is_build_pch = imgui.Checkbox("Enable PCH(*) support (URHO3D_PCH)", __is_build_pch)
            imgui.Text("(*) PCH: Precompiled header.")

            _, __is_build_gnu11 = imgui.Checkbox("Enable C++11(*) support (URHO3D_C++11)", __is_build_gnu11) 
            imgui.Text("C++11 (URHO3D_C++11) would also be enabled if one of the following configurations were selected: ")
            imgui.Text("- URHO3D_ANGELSCRIPT on web and Android/ARM platforms with aarch64, or")
            imgui.Text("- URHO3D_DATABASE_ODBC on all platforms.") 

            imgui.Text("Library type")
            _, __lib_type = imgui.Combo("LT", __lib_type, {
                "Static (.a on Linux, and .lib on Windows)", 
                "Dynamic (.so on Linux, and .dll on Windows)"
            }, 2)

            if imgui.CollapsingHeader("AngelScript") then  
                _, __is_build_angelscript = imgui.Checkbox("AngelScript(*) support (URHO3D_ANGELSCRIPT), ", __is_build_angelscript)
                imgui.Text("(*) AngelScript is required by the built-in scene editor.")
            end 

            if imgui.CollapsingHeader("Lua/LuaJIT") then 
                _, __is_build_lua = imgui.Checkbox("Lua support (URHO3D_LUA)", __is_build_lua)
                _, __is_build_luajit = imgui.Checkbox("LuaJIT support (URHO3D_LUAJIT)", __is_build_luajit)
                _, __is_build_luajit_alm = imgui.Checkbox("LuaJIT amalgamated build(*) (URHO3D_LUAJIT_AMALG)", __is_build_luajit_alm)
                imgui.Text("(*) Quoting from http://luajit.org/install.html:") 
                imgui.Text([[
The build system has a special target for an amalgamated build, i.e. make amalg. 
This compiles the LuaJIT core as one huge C file and allows GCC to generate faster 
and shorter code. Alas, this requires lots of memory during the build. This may 
be a problem for some users, that's why it's not enabled by default. But it shouldn't 
be a problem for most build farms. 
It's recommended that binary distributions use this target for their LuaJIT builds.
                ]])

                _, __is_build_luajit_safe = imgui.Checkbox("C++ wrapper safety checks(*) for Lua/LuaJIT (URHO3D_SAFE_LUA)", __is_build_luajit_safe) 
                imgui.Text("(*) This can be slow.")   

                _, __is_build_lua_rawscript = imgui.Checkbox("Prefer loading raw script files over the ones in Urho3D's cache. (URHO3D_LUA_RAW_SCRIPT_LOADER)", __is_build_lua_rawscript) 
                imgui.Text("(*) This can be useful for debugging purposes, but has less performance than just loading from the resource cache.")
            end 

            if imgui.CollapsingHeader("Rendering") then 
                _, __is_build_gl = imgui.Checkbox("OpenGL(*) support (URHO3D_OPENGL)", __is_build_gl) 
                _, __is_build_d3d11 = imgui.Checkbox("Direct3D11(**) support (URHO3D_D3D11)", __is_build_d3d11)
                imgui.Text("(*) Selecting OpenGL on any platform will override Direct3D, and vice versa.")  
                imgui.Text("(**) Building on Windows with both OpenGL and Direct3D11 unselected will default to Direct3D9.")
                imgui.Text("     Selecting both OpenGL and Direct3D11 will default to OpenGL on non-Windows platforms, and ")
                imgui.Text("     Direct3D11/Direct3D9 on Windows platform.")
            end 

            if imgui.CollapsingHeader("Database") then 
                _, __database_type = imgui.Combo("DT", __database_type, {
                    "OBDC (*)",
                    "SQLite"
                }, 2) 

                if __database_type == 1 then 
                    imgui.Text("OBDC requires vendor-specific ODBC driver.") 
                end 
            end 

            if imgui.CollapsingHeader("Windows-specific settings") then 
                _, __is_build_static_vcruntime = imgui.Checkbox("Prefer static C/C++ runtime libraries(*) (URHO3D_STATIC_RUNTIME)", __is_build_static_vcruntime)
                imgui.Text("(*) Use static C/C++ runtime libraries and eliminate the need for runtime DLLs installation. (VS only)")

                _, __is_build_w32console = imgui.Checkbox("Prefer main() over WinMain() to set up a console for logging purposes. (URHO3D_WIN32_CONSOLE)", __is_build_w32console) 
            end 

            if imgui.CollapsingHeader("Extras") then 
                _, __is_build_samples = imgui.Checkbox("Build samples (URHO3D_SAMPLES)", __is_build_samples)

                _, __is_build_tools = imgui.Checkbox("Build development tools(*) (URHO3D_TOOLS)", __is_build_tools)
                imgui.Text("(*) Include everything in Source/Tools/.")

                _, __is_build_extras = imgui.Checkbox("Build extra tools(*) (URHO3D_EXTRAS)", __is_build_extras)
                imgui.Text("(*) OgreBatchConverter")

                _, __is_build_package = imgui.Checkbox("Enable packaging of resources (URHO3D_PACKAGING)", __is_build_package)

                _, __is_build_docs = imgui.Checkbox("Build documentation (URHO3D_DOCS)", __is_build_docs)
            end  
        end 

        if imgui.CollapsingHeader("Post-build") then 
            _, __is_strip_bin = imgui.Checkbox("Strip symbols from binaries(*) (gcc only)", __is_strip_bin)
            imgui.Text("(*) Only binaries produced by GCC (gcc/g++/...) can have their symbols stripped. On ")
            imgui.Text("Windows platforms and binaries are built using MSVC, symbols are stored in (a) separate")
            imgui.Text(".pdb (files).") 
        end 

        __begin_reparse_configuration = imgui.Button("Reparse configuration file (" .. __conf_name .. ")") 
        __begin_save_configuration = imgui.Button("Save current configuration to " .. __conf_name)
        __begin_configuring_pressed = imgui.Button("Begin configuring and generating " .. __script_name)
    imgui.End()

    imgui.Render()
end 
