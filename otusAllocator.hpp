#include "buffer.hpp"
#include <array>
#include <assert.h>

/* Аллакатор для структур данных одинакового размера и создаваемых по 1 */

template <typename T, std::size_t memmoryCapacity>
struct Light_Pool_Allocator
{
    using value_type = T;

    constexpr Light_Pool_Allocator();

    template <typename U, std::size_t N>
    Light_Pool_Allocator(const Light_Pool_Allocator<U, N> &);

    T *allocate(std::size_t n);

    void deallocate(T *p, std::size_t n);

private:

    constexpr void rec_init(std::uint32_t chunkIndex, std::uint32_t chunkCount)
    {
        if (chunkIndex < chunkCount)
        {
            std::uint8_t *chunkPtr = memmory + (chunkIndex * sizeof(T));
            *(reinterpret_cast<uint8_t **>(chunkPtr)) = chunkPtr + sizeof(T);
            rec_init(++chunkIndex, chunkCount);
        }
    }

    std::uint8_t memmory[memmoryCapacity];
    std::uint8_t *head;
};

template <typename T, std::size_t memmoryCapacity>
constexpr Light_Pool_Allocator<T, memmoryCapacity>::Light_Pool_Allocator()
{
    static_assert(sizeof(T) >= 8 && "type size must be greater then pointer on 64 bit");
    static_assert(memmoryCapacity % sizeof(T) == 0 && "Total memmory must be multiple of size T");

    constexpr std::uint32_t chunkCount = (memmoryCapacity / sizeof(T)) - 1;
    constexpr std::uint32_t startChunkIndex = 0;
    rec_init(startChunkIndex, chunkCount);

    *(reinterpret_cast<std::uint8_t **>(&memmory[chunkCount * sizeof(T)])) = nullptr;
    head = memmory;
}

template <typename T, std::size_t memmoryCapacity>
T *Light_Pool_Allocator<T, memmoryCapacity>::allocate(std::size_t n)
{
    assert(head != nullptr && "end of memmory in Light_Pool_Allocator");

    assert(n == 1 && "allocate only one object");

    T *out = reinterpret_cast<T *>(head);

    head = *(reinterpret_cast<uint8_t **>(head));

    return out;
}

template <typename T,std::size_t memmoryCapacity>
void Light_Pool_Allocator<T,memmoryCapacity>::deallocate(T *p, std::size_t n)
{
    assert( n == 1 && "allocate only one object");

    *(reinterpret_cast<T**>(p)) = head;
    head = p;
}


template <class T, class U, std::size_t N>
constexpr bool operator==(const Light_Pool_Allocator<T, N> &, const Light_Pool_Allocator<U, N> &) noexcept
{
    return false;
}

template <class T, class U, std::size_t N>
constexpr bool operator!=(const Light_Pool_Allocator<T, N> &, const Light_Pool_Allocator<U, N> &) noexcept
{
    return true;
}