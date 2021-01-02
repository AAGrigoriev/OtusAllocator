#pragma once

#include <assert.h>
#include <cstdint>

/*!
    @brief Strategy without allocation 
*/
template <typename T, std::size_t countBlock>
class array_staregy
{
public:
    array_staregy()
    {
        std::size_t chunkCount = (countBlock / sizeof(T)) - 1; // ошибка 
        for (std::size_t i = 0; i < chunkCount; ++i)
        {
            std::uint8_t *chunkPtr = memmory + (i * sizeof(T));
            *(reinterpret_cast<std::uint8_t **>(chunkPtr)) = chunkPtr + sizeof(T);
        }
        *(reinterpret_cast<std::uint8_t **>(&memmory[chunkCount * sizeof(T)])) = nullptr;
        head = memmory;
    }
    ~array_staregy() = default;

    T *allocate(std::size_t n = 1)
    {
        assert(head != nullptr && "end of memmory in array_staregy");
        assert(n == 1 && "allocate only one object");

        T *out = reinterpret_cast<T *>(head);

        head = *(reinterpret_cast<std::uint8_t **>(head))
    }

    void deallocate(T *ptr, std::size_t n = 1)
    {
        *(reinterpret_cast<std::uint8_t **>(ptr)) = head;
        head = reinterpret_cast<std::uint8_t*>(ptr);
    }

private:
    std::uint8_t memmory[countBlock]; //countBlock * sizeof T подправить 
    std::uint8_t *head;
};