#pragma once

#include <cstdint>
#include <vector>
#include <new>
#include <assert.h>

/*!
    @brief Expand strategy
    idea author - sergey-bulanov76 
    https://github.com/azbyx/custom_allocator
*/

template <typename T, std::size_t countBlock>
class realloc_strategy
{
public:
    realloc_strategy() noexcept
    {
        pointer_free = add_list();
        v_pointer.push_back(pointer_free);
    }

    realloc_strategy(const realloc_strategy &otther) = delete;
    realloc_strategy(realloc_strategy &&other) = delete;

    T *allocate(std::size_t n);

    void deallocate(T *ptr, std::size_t n = 1);

    ~realloc_strategy();

private:
    /*!
    @brief create linked list with size = countBlock 
    */
    pointer_wrapper *add_list()
    {
        static_assert(countBlock > 1 && "wrong countBlock");
        static_assert(sizeof(T) >= sizeof(T *) && "type size must be greater then pointer");

        pointer_wrapper *list = ::operator new(sizeof(T) * countBlock);

        for (std::size_t i = 0; i < countBlock - 1; i++)
        {
            *(list + i * sizeof(T)) = (list + (i + 1) * sizeof(T));
        }

        *(list + (countBlock - 1) * sizeof(T)) = nullptr;

        return list;
    }

    struct pointer_wrapper
    {
        pointer_wrapper *next;
    };

    std::vector<pointer_wrapper *> v_pointer;

    pointer_wrapper *pointer_free;
};

template <typename T, std::size_t countBlock>
T *realloc_strategy<T, std::size_t countBlock>::allocate(T *ptr, std::size_t n = 1)
{
    assert(n == 1 && "allocate only one object");

    /* end of memmory */
    if (pointer_free == nullptr)
    {
        pointer_free = add_list();
        v_pointer.push_back(pointer_free);
    }

    auto ptr = pointer_free;
    pointer_free = pointer_free.next;

    return out;
}

template <typename T, std::size_t countBlock>
void realloc_strategy<T, std::size_t countBlock>::deallocate(T *ptr, std::size_t n = 1)
{
    auto dealloc_ptr = reinterpret_cast<pointer_wrapper *>(ptr);
    dealloc_ptr.next = pointer_free;
    pointer_free = dealloc_ptr;
}

template <typename T, std::size_t countBlock>
realloc_strategy<T, std::size_t countBlock>::~realloc_strategy()
{
    for (auto ptr : v_pointer)
    {
        ::operator delete(ptr);
    }
}