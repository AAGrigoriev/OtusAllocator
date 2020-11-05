#include <cstdint>

template<std::size_t N>
struct buffer
{
    uint8_t  memmory[N];
    uint8_t* head = nullptr;
};