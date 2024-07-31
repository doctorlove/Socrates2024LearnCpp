#include <iostream>
#include <cassert>
#include <sstream>
#include <string> 

void show(std::ostream & os, const std::string & words) // no copy!
{
    os << words;
}

void tests()
{
    std::ostringstream oss;
    show(oss, "Hello, world!");
    assert(oss.str() == "Hello, world!");
}

int main()
{
    tests();
    show(std::cout, "Hello, world!\n");
}

