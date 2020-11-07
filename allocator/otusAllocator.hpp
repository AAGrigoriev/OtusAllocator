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
        Light_Pool_Allocator(const Light_Pool_Allocator<U, N> &);

        T *allocate(std::size_t n);

        void deallocate(T *p, std::size_t n);

    private:
        std::size_t rec_init()
        {
            constexpr std::size_t chunkCount = (memmoryCapacity / sizeof(T)) - 1;
            std::cout << "chunkCount = " << chunkCount << std::endl;
            std::cout << sizeof(T) << std::endl;
            for (std::size_t i = 0; i < chunkCount; ++i)
            {
                std::uint8_t *chunkPtr = memmory + (i * sizeof(T));
                printf("currentPtr = %p ", chunkPtr);
                *(reinterpret_cast<std::uint8_t **>(chunkPtr)) = chunkPtr + sizeof(T);
                printf(" nextAddres = %p ", *(reinterpret_cast<uint8_t **>(chunkPtr)));
            }
            std::cout << std::endl;
            *(reinterpret_cast<std::uint8_t **>(&memmory[chunkCount * sizeof(T)])) = nullptr;
            printf("\nend memmory = %p ", (reinterpret_cast<std::uint8_t **>(&memmory[chunkCount * sizeof(T)])));
            printf("  end memmory = %p ", *(reinterpret_cast<std::uint8_t **>(&memmory[chunkCount * sizeof(T)])));
            head = memmory;
            return 0;
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
        assert(head != nullptr && "end of memmory in Light_Pool_Allocator");

        assert(n == 1 && "allocate only one object");

        T *out = reinterpret_cast<T *>(head);
        printf("\nAlloc\n");
        printf("address current = %p \n", out);

        head = *(reinterpret_cast<uint8_t **>(head));
        printf("address head = %p \n", head);

        return out;
    }

    template <typename T, std::size_t memmoryCapacity>
    void Light_Pool_Allocator<T, memmoryCapacity>::deallocate(T *p, std::size_t n)
    {
        assert(n == 1 && "allocate only one object");

        *(reinterpret_cast<std::uint8_t **>(p)) = head;
        printf("dealloc \n");
        printf("addres head = %p \n", head);
        printf("addres free = %p \n", p);
        head = reinterpret_cast<std::uint8_t *>(p);
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

} // namespace simple_allocator