#include <memory>
#include <new>

template <typename T, typename Allocator = std::allocator<T>>
class sForwardList
{
private:
    struct Node
    {
        T data;
        Node *next;
    };

    Node *m_head = nullptr;

public:
    void addTail(T &t);

    void remove();

    const T &get_head();

    ~sForwardList();
};

template <typename T, typename Allocator>
void sForwardList<T, Allocator>::addTail(T &t)
{
    try
    {
        Node *node = new Node{t, nullptr};
        node->next = m_head;
        m_head = node;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << e.what() << '\n';
    }
}

template <typename T, typename Allocator>
void sForwardList<T, Allocator>::remove()
{
    if (m_head != nullptr)
    {
        Node *next = m_head->next;

        delete m_head;

        m_head = next;
    }
}

template <typename T, typename Allocator>
const T &sForwardList<T, Allocator>::get_head()
{
    return m_head->data;
}

template <typename T, typename Allocator>
sForwardList<T, Allocator>::~sForwardList()
{
    while (m_head)
    {
        remove();
    }
}
