#pragma once

#include <array>
#include <assert.h>

/* Аллакатор для структур данных одинакового размера и создаваемых по 1 */

namespace simple_allocator
{
    template <typename T, std::size_t memmoryCapacity>
    struct Light_Pool_Allocator
    {
        using value_type = T;

        Light_Pool_Allocator();

        template <typename U>
        struct rebind
        {
            using other = Light_Pool_Allocator<U, memmoryCapacity>;
        };

        template <typename U, std::size_t N>
        Light_Pool_Allocator(const Light_Pool_Allocator<U, N> &) {}

        T *allocate(std::size_t n);

        template <typename U, typename... Args>
        void construct(U *ptr, Args &&... args)
        {
            std::cout << __PRETTY_FUNCTION__ << std::endl;

            new (ptr) U(std::forward<Args>(args)...);
        }

        void deallocate(T *ptr, std::size_t n = 1);

        template <typename U>
        void destroy(U *ptr)
        {
            std::cout << __PRETTY_FUNCTION__ << std::endl;

            ptr->~U();
        }

    private:
    
        void rec_init()
        {
            constexpr std::size_t chunkCount = (memmoryCapacity / sizeof(T)) - 1;
            for (std::size_t i = 0; i < chunkCount; ++i)
            {
                std::uint8_t *chunkPtr = memmory + (i * sizeof(T));
                *(reinterpret_cast<std::uint8_t **>(chunkPtr)) = chunkPtr + sizeof(T);
            }
            *(reinterpret_cast<std::uint8_t **>(&memmory[chunkCount * sizeof(T)])) = nullptr;
            head = memmory;
        }

        std::uint8_t memmory[memmoryCapacity];
        std::uint8_t *head;
    };

    template <typename T, std::size_t memmoryCapacity>
    Light_Pool_Allocator<T, memmoryCapacity>::Light_Pool_Allocator()
    {
        static_assert(sizeof(T) >= 8 && "type size must be greater then pointer on 64 bit");
        static_assert(memmoryCapacity % sizeof(T) == 0 && "Total memmory must be multiple of size T");

        rec_init();
    }

    template <typename T, std::size_t memmoryCapacity>
    T *Light_Pool_Allocator<T, memmoryCapacity>::allocate(std::size_t n)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;

        assert(head != nullptr && "end of memmory in Light_Pool_Allocator");

        assert(n == 1 && "allocate only one object");

        T *out = reinterpret_cast<T *>(head);

        head = *(reinterpret_cast<uint8_t **>(head));

        return out;
    }

    template <typename T, std::size_t memmoryCapacity>
    void Light_Pool_Allocator<T, memmoryCapacity>::deallocate(T *p, std::size_t n)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;

        assert(n == 1 && "deallocate only one object");

        *(reinterpret_cast<std::uint8_t **>(p)) = head;
        head = reinterpret_cast<std::uint8_t *>(p);
    }

    // template <typename U, typename... Args>
    //void Light_Pool_Allocator<U, Args>::construct(U *ptr, Args &&... args)
    //{
    //            new (ptr) U(std::forward<Args>(args)...);
    // }

    //    template <typename U>
    //   void Light_Pool_Allocator<U>::destroy(U *ptr)
    //   {
    //      ptr->~U();
    //  }

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

} // namespace simple_allocator