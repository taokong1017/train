#include <iostream>
#include <type_traits>

#define unused(data) ((void)data)

namespace Test {
namespace Enable {
    template<bool B, typename T = void>
    struct enable_if {};
 
    template<class T>
    struct enable_if<true, T> { typedef T type; };
}

namespace TypeTest {
    // the partial specialization of A is enabled via a template parameter
    template<typename T, typename Enable = void>
    struct A {
        A(){std::cout << "A(void)\n";}
    };
 
    // specialization for floating point types
    template<typename T>
    struct A<T, typename Test::Enable::enable_if<std::is_floating_point<T>::value>::type> {
        A(){std::cout << "A(float)\n";}
    };
}

}

int main(int argc, char** argv)
{
    Test::TypeTest::A<int> int_test;
    Test::TypeTest::A<float> float_test;
    
    return 0;
}