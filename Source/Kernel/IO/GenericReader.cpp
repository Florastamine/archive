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

#include <GenericReader.hpp>

#include <cstdio>  

namespace Hotland {
    namespace IO {
        void GenericReader::Open(const std::string &fName, const std::string &fMode)
        {
            if(!m_pInternalBlock)
                m_pInternalBlock = std::fopen(fName.c_str(), "r");
        }

        void GenericReader::Close()
        {
            if(m_pInternalBlock)
                std::fclose(m_pInternalBlock);
        }

        void GenericReader::Write(const std::string &fContent)
        {
            if(m_pInternalBlock)
                std::fwrite(fContent.data(), sizeof fContent[0], fContent.size(), m_pInternalBlock);
        }

        const char *GenericReader::Read(std::size_t bSize)
        {
            if(m_pInternalBlock) {
                char *rBuffer = new char[bSize + 1];

                std::fread(rBuffer, sizeof(char), bSize, m_pInternalBlock);
                rBuffer[bSize] = '\0';

                return reinterpret_cast<const char *>(rBuffer);
            }

            return NULL;
        }

        const char *GenericReader::ReadLine(std::size_t nThreshold) 
        {
            if(m_pInternalBlock) {
                char *c = new char[nThreshold + 1];
                std::fgets(c, nThreshold, m_pInternalBlock);
                c[nThreshold + 1] = '\0';

                return reinterpret_cast<const char *>(c);
            } 

            return NULL;
        } 

        const char *GenericReader::ReadAll(std::size_t nThreshold)
        {
            if(m_pInternalBlock) {
                char *s = new char[nThreshold + 1];
                int i = -1, c = 0;
                
                while((EOF != (c = std::fgetc(m_pInternalBlock))) && (i < (int) nThreshold)) 
                    s[++i] = (char) c;

                s[i + 1] = '\0';
                return reinterpret_cast<const char *>(s);
            } 

            return NULL;
        } 

        const char *GenericReader::ReadChunk(std::size_t nSize)
        {
            return GenericReader::ReadAll(nSize);
        } 

        std::size_t GenericReader::Size() 
        {
            std::size_t s = 0;

            if(m_pInternalBlock) {
                std::rewind(m_pInternalBlock);
                std::fseek(m_pInternalBlock, 0, SEEK_END);

                s = std::ftell(m_pInternalBlock);
                std::rewind(m_pInternalBlock);
            }

            return s;
        }
    }
}
