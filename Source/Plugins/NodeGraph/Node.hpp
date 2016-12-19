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

#include "../../Source/Kernel/Compatibility/CXXCompatibility.hpp" 

#include "Variable.hpp" 

#include <stdint.h>  
#include <vector> 

namespace Hotland { 
    class HOTLAND_API Node {
        public: 
            Node() : 
                m_listIn(), 
                m_listOut(), 
                m_ID(reinterpret_cast<uint32_t>(this)),
                m_name()
            {
            }

            Node(const Node &N)
            {
                if(this != &N) {
                    this->m_listIn = N.m_listIn;
                    this->m_listOut = N.m_listOut;
                    this->m_name = N.m_name;
                    this->m_ID = reinterpret_cast<uint32_t>(this);
                }
            }

            Node(Node &&N) = default;

            ~Node()
            {
            }

            inline auto operator=(const Node &N) -> Node & 
            {
                if(this != &N) {
                    this->m_listIn = N.m_listIn;
                    this->m_listOut = N.m_listOut;
                    this->m_name = N.m_name;
                    this->m_ID = reinterpret_cast<uint32_t>(this);
                }

                return *this;
            }

            inline auto operator==(const Node &N) -> bool 
            {
                return (this->m_listIn == N.m_listIn) && (this->m_listOut == N.m_listOut);
            } 

            inline auto IsEmpty() const -> bool { return ((this->m_listIn).size() == 0) && ((this->m_listOut).size() == 0); }

            inline auto PushIn(const Variable &V) -> void { (this->m_listIn).push_back(V); }

            inline auto PushOut(const Variable &V) -> void { (this->m_listOut).push_back(V); }

            inline auto PopIn() -> void { (this->m_listIn).pop_back(); }

            inline auto PopOut() -> void { (this->m_listOut).pop_back(); }

            inline auto JoinIn() -> void {}

            inline auto JoinOut() -> void {} 

            inline auto GetINodeSize() const -> std::vector<Variable>::size_type { return m_listIn.size(); }

            inline auto GetONodeSize() const -> std::vector<Variable>::size_type { return m_listOut.size(); } 

            inline auto GetName() const -> std::string { return m_name; } 

            inline auto GetID() const -> uint32_t { return m_ID; }

            inline auto SetName(const char *s) -> void { m_name = std::string(s); }

            inline auto SetName(const std::string &s) -> void { m_name = s; } 
        private:
            std::vector<Variable> m_listIn;
            std::vector<Variable> m_listOut; 

            std::string m_name;
            uint32_t    m_ID;
    }; 
}
