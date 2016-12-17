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

#include <string>
#include <vector> 

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

namespace Hotland { 
    enum 
    {
        TYPE_INT, 
        TYPE_LONG, 
        TYPE_FLOAT, 
        TYPE_DOUBLE 
    }; 

    HOTLAND_DEFINE_CONSTANT_VARIABLE_BASE_TYPE(void);
    HOTLAND_DEFINE_CONSTANT_VARIABLE_TYPE(TYPE_INT, "Integer type");
    HOTLAND_DEFINE_CONSTANT_VARIABLE_TYPE(TYPE_LONG, "Long type");
    HOTLAND_DEFINE_CONSTANT_VARIABLE_TYPE(TYPE_FLOAT, "Float type");
    HOTLAND_DEFINE_CONSTANT_VARIABLE_TYPE(TYPE_DOUBLE, "Double type");

    class HOTLAND_API Variable {
        public:
            Variable(int cType = TYPE_INT);
            Variable(const Variable &V);
            Variable(const Variable &&V);

            ~Variable();

            inline Variable &operator=(const Variable &V)
            {
                if(this != &V) {
                    this->m_typeID = V.m_typeID;
                    this->m_typeName = V.m_typeName;
                    this->m_typeContainer = V.m_typeContainer;
                }

                return *this;
            }

            inline bool operator==(const Variable &V) const 
            {
                return IsConvertible(V);
            }

            int GetType() const;
            bool IsConvertible(const Variable &V) const; 
            std::string GetName() const; 
        private:
            boost::variant<
                int,         // TYPE_INT 
                long,        // TYPE_LONG 
                float,       // TYPE_FLOAT 
                double       // TYPE_DOUBLE 
            > m_typeContainer; 

            int         m_typeID;
            std::string m_typeName; 

            void SetVariableDefaults(int cType);
    }; 

    class HOTLAND_API Node {
        public:
            Node();
            Node(const Node &N);
            Node(const Node &&N);

            ~Node();

            Node &operator=(const Node &N); 

            bool IsEmpty() const;
            void ConnectIn(const Node &N, int nIFrom, int nITo);
            void ConnectOut(const Node &N, int nIFrom, int nITo);

            void PushIn(const Variable &V);
            void PushOut(const Variable &V);

            void PopIn();
            void PopOut();
        private:
            std::vector<Variable> m_listIn;
            std::vector<Variable> m_listOut;
    }; 
}
