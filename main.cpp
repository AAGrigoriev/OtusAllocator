#include <iostream>
#include <map>

#include "otusAllocator.hpp"
#include "simpleList.hpp"

using namespace simple_allocator;
using namespace slist;

int main()
{
    sForwardList<double> list;

    std::map<int, int, std::less<>, Light_Pool_Allocator<std::pair<const int, int>, 1000>> my_map;

    my_map[0] = 3;
    my_map[6] = 50;

    return 0;
}