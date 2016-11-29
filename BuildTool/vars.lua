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

window_width, window_height = 640, 600   

version = "Alpha"
l2d_version_major, l2d_version_minor, l2d_version_rev, l2d_version_name = love.getVersion()
window_title = string.format("Herbal %s (%s, Love2D %d.%d.%d %s)", version, _VERSION, l2d_version_major, l2d_version_minor, l2d_version_rev, l2d_version_name)

__window_max_width, __window_max_height = 0, 0 

__built_target_buffer, __built_target_buffer_length = "./", 257
__msys2_root_buffer, __msys2_root_buffer_length = "./", 257 
__mingw_root_buffer, __mingw_root_buffer_length = "./", 257 
__built_cmake_buffer, __built_cmake_buffer_length = "./", 257 

__begin_configuring_pressed = false
__begin_reparse_configuration = false 
__begin_save_configuration = false 

__is_build_64bit, __is_build_angelscript, __is_build_lua, __is_build_luajit, __is_build_luajit_alm = false, false, false, false, false
__is_build_luajit_safe, __is_build_network, __is_build_physics, __is_build_nav, __is_build_mt, __is_build_2d = false, false, false, false, false, false
__is_build_tools, __is_build_samples, __is_build_package, __is_build_profiling, __is_build_static_vcruntime, __is_build_w32console = false, false, false, false, false, false 
__is_build_docs, __is_build_pch, __is_build_lua_rawscript = false, false, false     

__database_type = 1  
__target_type = 1 
__lib_type = 1 
__toolchain_type = 1

__conf_name = "herbal.conf" 
__script_name = "out."
