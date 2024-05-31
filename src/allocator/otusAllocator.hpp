#pragma once

#include <assert.h>

/*!
    @brief Allocator
*/

namespace simple_allocator
{
    template <typename T, std::size_t countBlock, template <class, std::size_t> class Strategy>
    struct Simple_Allocator
    {
        using value_type = T;

        Simple_Allocator() = default;

        template <typename U>
        struct rebind
        {
            using other = Simple_Allocator<U, countBlock, Strategy>;
        };

        template <typename U>
        Simple_Allocator(const Simple_Allocator<U, countBlock, Strategy> &) {}

        T *allocate(std::size_t n);

        template <typename U, typename... Args>
        void construct(U *ptr, Args &&... args)
        {
            new (ptr) U(std::forward<Args>(args)...);
        }

        void deallocate(T *ptr, std::size_t n = 1);

        template <typename U>
        void destroy(U *ptr)
        {
            ptr->~U();
        }

    private:
        Strategy<T, countBlock> alloc_strategy;
    };

    template <typename T, std::size_t countBlock, template <class, std::size_t> class Strategy>
    T *Simple_Allocator<T, countBlock, Strategy>::allocate(std::size_t n)
    {
        return alloc_strategy.allocate(n);
    }

    template <typename T, std::size_t countBlock, template <class, std::size_t> class Strategy>
    void Simple_Allocator<T, countBlock, Strategy>::deallocate(T *p, std::size_t n)
    {
        alloc_strategy.deallocate(p, n);
    }

    // template <typename U, typename... Args>
    //void Light_Pool_Allocator<U, Args>::construct(U *ptr, Args &&... args)
    //{
    //            new (ptr) U(std::forward<Args>(args)...);
    //}

    //    template <typename U>
    //   void Light_Pool_Allocator<U>::destroy(U *ptr)
    //   {
    //      ptr->~U();
    //   }

    template <class T, class U, std::size_t N, template <class, std::size_t> class Strategy>
    constexpr bool operator==(const Simple_Allocator<T, N, Strategy> &, const Simple_Allocator<U, N, Strategy> &) noexcept
    {
        return false;
    }

    template <class T, class U, std::size_t N, template <class, std::size_t> class Strategy>
    constexpr bool operator!=(const Simple_Allocator<T, N, Strategy> &, const Simple_Allocator<U, N, Strategy> &) noexcept
    {
        return true;
    }

} // namespace simple_allocator