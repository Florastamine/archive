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

#include "NodeGraph.hpp" 

static auto Get42Line() -> std::string { static const std::string line('_', 42); return line; }

inline auto operator<<(std::ostream &stream, const Hotland::Variable &V) -> std::ostream & 
{
    stream << Get42Line() << '\n'; 
    stream << "Variable [" << &V << "]'s contents:\n"; 
    stream << "Real name: [" << V.GetName() << "]; Unique ID: " << V.GetID() << "]\n"; 
    stream << "Underlying type name: [" << V.GetTypeName() << "]; Underlying type ID: [" << V.GetTypeID() << "]\n"; 
    stream << Get42Line() << '\n'; 
    stream << std::flush;

    return stream;
}

inline auto operator<<(std::ostream &stream, const Hotland::Node &N) -> std::ostream & 
{
    stream << Get42Line() << '\n'; 
    stream << "Node [" << &N << "]'s contents:\n"; 
    stream << "Real name: [" << N.GetName() << "]; Unique ID: " << N.GetID() << "]\n"; 
    stream << "Number of INODES - ONODES:" << N.GetINodeSize() << '-' << N.GetONodeSize() << '\n';
    stream << Get42Line() << '\n'; 
    stream << std::flush; 

    return stream; 
}
