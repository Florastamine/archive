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

#include "Variable.hpp" 

namespace Hotland {
    struct Connector {
        Connector(const Variable &vIn = nullptr, const Variable &vOut = nullptr) : m_vIn(vIn), m_vOut(vOut) 
        {
        }

        Connector(const Connector &C)
        {
            if(this != &C) {
                this->m_vIn = C.m_vIn;
                this->m_vOut = C.m_vOut;
            }
        }

        Connector(Connector &&) = default;

        inline auto operator=(const Connector &C) -> Connector & 
        {
            if(this != &C) {
                this->m_vIn = C.m_vIn;
                this->m_vOut = C.m_vOut;
            }

            return *this;
        }

        ~Conector()
        {
        }

        inline auto Connect(const Variable &V1, const Variable &V2) -> void 
        {
            if(IsSameType(vIn, vOut)) {
                m_vIn = &vIn;
                m_vOut = &vOut;
            }
        } 

        inline auto Execute() -> void 
        {
            if(IsSameType() && IsConnected()) {
                *m_vIn = *m_vOut;
            }
        }

        inline auto IsConnected() const -> bool { return (m_vIn != nullptr) && (m_vOut != nullptr); } 
        inline auto IsSameType(const Variable &V1, const Variable &V2) const -> bool { return V1.GetVariant.type() == V2.GetVariant().type(); }

        private: 
            Variable *m_vIn;
            Variable *m_vOut;
    }; 
}
