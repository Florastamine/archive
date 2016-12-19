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

#include <Variable.hpp> 

#define HOTLAND_DEFINE_CONSTANT_VARIABLE_CASE(cType) \
    case cType : { \
        this->m_typeName = CTypeName<cType>::GetName(); \
        break; \
    }

namespace Hotland {
    void Variable::SetVariableDefaults(int cType) 
    {
        this->m_typeID = cType;

        switch(cType) {
            HOTLAND_DEFINE_CONSTANT_VARIABLE_CASE(TYPE_INT);
            HOTLAND_DEFINE_CONSTANT_VARIABLE_CASE(TYPE_LONG);
            HOTLAND_DEFINE_CONSTANT_VARIABLE_CASE(TYPE_FLOAT);
            HOTLAND_DEFINE_CONSTANT_VARIABLE_CASE(TYPE_DOUBLE);
        } 

        SetVariableID();
    }

    void Variable::SetVariableID()
    {
        this->m_ID = reinterpret_cast<uint32_t>(this); 
    }

    Variable::Variable(int cType)
    {
        SetVariableDefaults(cType);
    } 

    Variable::~Variable()
    {
    }

    Variable::Variable(const Variable &V) 
    {
        if(this != &V) {
            this->m_typeID = V.m_typeID;
            this->m_typeName = V.m_typeName;
            this->m_typeContainer = V.m_typeContainer;
        }
    } 

    int Variable::GetType() const 
    {
        return this->m_typeID;
    }

    bool Variable::IsConvertible(const Variable &V) const 
    {
        return this->m_typeID == V.m_typeID;
    }

    std::string Variable::GetName() const 
    {
        return this->m_typeName; 
    }  

    uint32_t Variable::GetID() const
    {
        return this->m_ID;
    }
}
