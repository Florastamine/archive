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

#pragma once 

#include <string> 

#include "../Compatibility/CXXCompatibility.hpp"

#include "ReadWriteBase.hpp" 

namespace Hotland {
    namespace IO {
        class HOTLAND_API GenericReader : public ReadWriteBase {
            public:
                GenericReader() : ReadWriteBase() {}
                ~GenericReader() {} 

                void Open(const std::string &fName, const std::string &fMode = std::string());
                void Close();

                void Write(const std::string &fContent);
                const char *Read(std::size_t bSize); 

                const char *ReadLine(std::size_t nThreshold = 512); 
                const char *ReadAll(std::size_t nThreshold = 65536); 
                const char *ReadChunk(std::size_t nSize = 1024); 

                std::size_t Size(int nMultiplier = 1);

                std::FILE *Get() const;
            private:
        };
    }
}