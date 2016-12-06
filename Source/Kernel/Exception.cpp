/*
 * Copyright (c) 2016, Florastamine
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <Exception.hpp> 

namespace Hotland {
    namespace Error {
        const char *ErrorDescriptionTable[] = {
            "Operation successful", 
            "Operation failed (generic failure)", 
            "Current task is busy", 
            "The specified file couldn't be found", 
            "The specified file couldn't be opened: Permission denied", 
            "Bad file format", 
            "The file you're trying to open is already exists", 
            "The file you're trying to open is already exists and it is not empty", 
            "Out of memory", 
            "Parameter out of range", 
            "Bad parameter format"
        };

        const char *Get(ErrorList nCode) 
        {
            return ErrorDescriptionTable[nCode];
        }
    }
}
