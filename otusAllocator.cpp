#include <iostream>
#include <map>

#include "otusAllocator.hpp"

int main()
{
    Light_Pool_Allocator<double, 256> alloc;

    std::map<int,int,std::less<>,Light_Pool_Allocator<std::pair<const int,int>,1000>> my_map;

    return 0;
}