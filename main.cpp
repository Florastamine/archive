#include <iostream>

#if __cplusplus >= 201103L 
    #define constexpr constexpr 
#else 
    #define constexpr const 
#endif 

int main(int argc, const char **argv)
{
    constexpr std::string s("The quick brown fox jumps over the lazy dog");

    std::cout << s.c_str();

    return 0;
}
