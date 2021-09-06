#include "number_class.h"
#include <iostream>
int main(int argc, char const *argv[])
{
    try {
        N::number a("5", 10);
        std::cout << a << '\n';
        return 0;
    } catch (std::string msg) {
        std::cout << msg << '\n';
        return -1;
    }
}