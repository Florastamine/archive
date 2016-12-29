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
    enum { IN, OUT }; 

    class /* HOTLAND_API */ Node { 
        public: 
            virtual auto IsEmpty() const -> bool = 0; 
            virtual auto Get() const -> std::vector<Variable> = 0;
            virtual auto Push(const Variable &) -> void = 0;
            virtual auto Pop() -> void = 0;
            virtual auto Size() const -> std::vector<Variable>::size_type = 0;
            virtual auto Join() -> void = 0; 

            inline auto GetName() const -> std::string { return m_name; } 
            inline auto GetID() const -> uint32_t { return m_ID; } 

            inline auto SetName(const char *s) -> void { m_name = std::string(s); }
            inline auto SetName(const std::string &s) -> void { m_name = s; } 
        protected:
            std::string m_name;
            uint32_t    m_ID;
    };

    class HOTLAND_API INode : public virtual Node {
        public:
            inline auto IsEmpty() const -> bool { return !(this->m_listIn.size()); } 

            inline auto Push(const Variable &V) -> void { (this->m_listIn).push_back(V); } 

            inline auto Pop() -> void { (this->m_listIn).pop_back(); }

            inline auto Size() const -> std::vector<Variable>::size_type { return m_listIn.size(); } 

            inline auto Get() const -> std::vector<Variable> { return m_listIn; }

            inline auto Join() -> void {}
        protected:
            std::vector<Variable> m_listIn;
    }; 

    class HOTLAND_API ONode : public virtual Node {
        public:
            inline auto IsEmpty() const -> bool { return !(this->m_listOut.size()); } 

            inline auto Push(const Variable &V) -> void { (this->m_listOut).push_back(V); }

            inline auto Pop() -> void { (this->m_listOut).pop_back(); } 

            inline auto Size() const -> std::vector<Variable>::size_type { return m_listOut.size(); } 

            inline auto Get() const -> std::vector<Variable> { return m_listOut; }

            inline auto Join() -> void {} 
        protected:
            std::vector<Variable> m_listOut;
    };

    #define TERNARY_STATEMENT(c, s, t) \
        do { \
            if ((c) == true) { s; } \
            else { t; } \
        } while(false) 

    class HOTLAND_API IONode : public INode, public ONode { 
        public: 
            inline auto IsEmpty() const -> bool { return ((this->m_listIn).size() <= 0) && ((this->m_listOut).size() <= 0); } 

            inline auto Push(const Variable &V) -> void { TERNARY_STATEMENT(m_mode == IN, INode::Push(V), ONode::Push(V));  }

            inline auto Pop() -> void { TERNARY_STATEMENT(m_mode == IN, INode::Pop(), ONode::Pop()); }

            inline auto Size() const -> std::vector<Variable>::size_type { return INode::Size() + ONode::Size(); }  

            inline auto Get() const -> std::vector<Variable> { return (m_mode == IN ? INode::Get() : ONode::Get()); }

            inline auto Join() -> void {}

            inline auto GetRWMode() -> int { return m_mode; } 

            inline auto SetRWMode(const int &i) -> void { m_mode = i; }
        private: 
            // 
            int m_mode;
    }; 

    // RendererNode is just a INode with a fixed bunch of input slots which correspond to different 
    // properties of a typical material: ambient, reflective/gloss, emissive, and such. This is the ending 
    // node in the node graph and it's used for rendering the final result. 
    class HOTLAND_API RendererNode : public INode {
        public: 
            enum 
            {
                AMBIENT,   // Should be a float? 
                ALBEDO,    // Ditto 
                EMISSIVE,  // Should be a vec4()? Or vec3() in exchange for the absence of alpha? 
                SPECULAR,  // Ditto? 
                DIFFUSE    // Ditto. 
            };  
        private: 
    }; 
}
