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

#include <boost/variant.hpp> 

#include "../../Source/Kernel/Compatibility/CXXCompatibility.hpp" 

#include <stdint.h> // Somehow Visual Studio Code slashes a line under the inclusion of <cstdint>, 
                    // So I have to resort back to <stdint.h>. For uint32_t. 
#include <string> 

#define HOTLAND_DEFINE_CONSTANT_VARIABLE_BASE_TYPE(TypeID) \
    template <int nType> struct CTypeName { \
        static const std::string &GetName() { \
            static std::string tName("Unknown type"); \
            return tName; \
        } \
    }; 

#define HOTLAND_DEFINE_CONSTANT_VARIABLE_TYPE(TypeID, TypeValue) \
    template <> struct CTypeName<TypeID> { \
        static const std::string &GetName() { \
            static std::string tName(TypeValue); \
            return tName; \
        }; \
    }; 

#define HOTLAND_DEFINE_CONSTANT_VARIABLE_CASE(cType) \
    case cType : { \
        m_typeName = CTypeName<cType>::GetName(); \
        break; \
    }

namespace Hotland { 
    enum 
    {
        TYPE_INT, 
        TYPE_LONG, 
        TYPE_FLOAT, 
        TYPE_DOUBLE 
    }; 

    HOTLAND_DEFINE_CONSTANT_VARIABLE_BASE_TYPE();
    HOTLAND_DEFINE_CONSTANT_VARIABLE_TYPE(TYPE_INT, "Integer type");
    HOTLAND_DEFINE_CONSTANT_VARIABLE_TYPE(TYPE_LONG, "Long type");
    HOTLAND_DEFINE_CONSTANT_VARIABLE_TYPE(TYPE_FLOAT, "Float type");
    HOTLAND_DEFINE_CONSTANT_VARIABLE_TYPE(TYPE_DOUBLE, "Double type"); 

    class HOTLAND_API Variable {
        public: 
            Variable() : 
                m_typeID(TYPE_INT), 
                m_typeName(CTypeName<TYPE_INT>::GetName()), 
                m_ID(reinterpret_cast<uint32_t>(this)), 
                m_name() 
            {
            }

            Variable(int cType) 
            {
                m_typeID = cType;

                switch(m_typeID = cType, cType) {
                    HOTLAND_DEFINE_CONSTANT_VARIABLE_CASE(TYPE_INT);
                    HOTLAND_DEFINE_CONSTANT_VARIABLE_CASE(TYPE_LONG);
                    HOTLAND_DEFINE_CONSTANT_VARIABLE_CASE(TYPE_FLOAT);
                    HOTLAND_DEFINE_CONSTANT_VARIABLE_CASE(TYPE_DOUBLE);
                }

                m_ID = reinterpret_cast<uint32_t>(this); 
            }

            Variable(const Variable &V)
            {
                if(this != &V) {
                    m_typeID = V.m_typeID;
                    m_typeName = V.m_typeName;
                    m_typeContainer = V.m_typeContainer;
                }
            }

            Variable(Variable &&) = default;

            ~Variable()
            {
            } 

            inline auto operator=(const Variable &V) -> Variable & 
            {
                if(this != &V) {
                    m_typeID = V.m_typeID;
                    m_typeName = V.m_typeName;
                    m_typeContainer = V.m_typeContainer;
                }

                return *this;
            }

            inline auto operator==(const Variable &V) const -> bool { return IsConvertible(V); } 

            inline auto IsConvertible(const Variable &V) const -> bool { return m_typeID == V.m_typeID; }

            inline auto GetTypeID() const -> int { return m_typeID; }

            inline auto GetTypeName() const -> std::string { return m_typeName; } 

            inline auto GetID() const -> uint32_t { return m_ID; }

            inline auto GetName() const -> std::string { return m_name; }

            inline auto SetName(const char *s) -> void { m_name = std::string(s); } 

            inline auto SetName(const std::string &s) -> void { m_name = s; } 
        private:
            boost::variant<
                int,         // TYPE_INT 
                long,        // TYPE_LONG 
                float,       // TYPE_FLOAT 
                double       // TYPE_DOUBLE 
            > m_typeContainer; 

            std::string m_name;
            uint32_t    m_ID;

            std::string m_typeName; 
            int         m_typeID;
    }; 
}

