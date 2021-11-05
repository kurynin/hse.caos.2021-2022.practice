#include <iostream>
#include <string>

// ...
const char* hello;
extern "C" void print_hello_length();

int main()
{
    std::string s;

    // считывание за раз целой текстовой строки произвольного размера
    while(std::getline(std::cin, s)) {
        hello = s.c_str();
        print_hello_length();
    }
    return 0;
}
