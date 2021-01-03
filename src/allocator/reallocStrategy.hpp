#pragma once

#include <cstdint>
#include <vector>
#include <new>
#include <assert.h>

/*!
    @brief Expand strategy
    thanks - sergey-bulanov76 
    https://github.com/azbyx/
*/

void test_array_strategy(std::uint8_t *memmory, std::size_t countBlock, std::size_t size_block)
{
    for (std::size_t i = 0; i < countBlock; ++i)
    {
        printf("adrees block %lu = %p\n", i, memmory + i * size_block);
    }

    printf("\n");

    for (std::size_t i = 0; i < countBlock; ++i)
    {
        printf("adrees block %lu = %p\n", i, *(reinterpret_cast<uint8_t **>(memmory + i * size_block)));
    }
}
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
    struct pointer_wrapper;

    /*!
        @brief create linked list with size = countBlock 
    */
    pointer_wrapper *add_list()
    {
        static_assert(countBlock > 1 && "wrong countBlock");
        static_assert(sizeof(T) >= sizeof(T *) && "type size must be greater then pointer");

        pointer_wrapper *list = static_cast<pointer_wrapper *>(::operator new(sizeof(T) * countBlock));

        for (std::size_t i = 0; i < countBlock - 1; i++)
        {
            *(reinterpret_cast<pointer_wrapper **>(list + i * sizeof(T))) = (list + (i + 1) * sizeof(T));
        }

        *(reinterpret_cast<pointer_wrapper **>(list + (countBlock - 1) * sizeof(T))) = nullptr;

        return list;
    }

    struct pointer_wrapper
    {
        pointer_wrapper *next;
    };

    std::vector<pointer_wrapper *> v_pointer;

    pointer_wrapper *pointer_free;

    /*   void test_init()
    {
        for (std::size_t i = 0; i < countBlock; ++i)
        {
            printf("block %lu have adress = %p\n", i, pointer_free + i * sizeof(T));
        }

        printf("\n");

        for (std::size_t i = 0; i < countBlock; ++i)
        {
            printf("block %lu have adress = %p\n", i, *(reinterpret_cast<void **>(pointer_free + i * sizeof(T))));
        }
    }
    */
};

template <typename T, std::size_t countBlock>
T *realloc_strategy<T, countBlock>::allocate(std::size_t n)
{
    assert(n == 1 && "allocate only one object");

    /* end of memmory */
    if (pointer_free == nullptr)
    {
        pointer_free = add_list();
        v_pointer.push_back(pointer_free);
    }

    auto out = pointer_free;
    pointer_free = pointer_free.next;

    return out;
}

template <typename T, std::size_t countBlock>
void realloc_strategy<T, countBlock>::deallocate(T *ptr, std::size_t n)
{
    pointer_wrapper *dealloc_ptr = reinterpret_cast<pointer_wrapper *>(ptr);
    dealloc_ptr->next = pointer_free;
    pointer_free = dealloc_ptr;
}

template <typename T, std::size_t countBlock>
realloc_strategy<T, countBlock>::~realloc_strategy()
{
    for (auto ptr : v_pointer)
    {
        ::operator delete(ptr);
    }
}