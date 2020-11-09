#include <memory>
#include <new>

namespace slist
{
template <typename T, typename Allocator = std::allocator<T>>
class sForwardList
{
private:
    struct Node
    {
        T data;
        Node *next;
    };

    class Iterator : public std::iterator<std::input_iterator_tag, T>
    {
        friend class sForwardList;

    public:

        Iterator(const Iterator &iter) : m_node(iter.m_node) {}

        bool operator==(const Iterator &other) const { return m_node == other.m_node; }

        bool operator!=(const Iterator &other) const { return m_node != other.m_node; }

        typename Iterator::reference operator*() const { return m_node->data; }

        //typename Iterator::pointer operator->() const {return &node->data;}

        Iterator &operator++()
        {
            m_node = m_node->next;
            return *this;
        }

    private:

        explicit Iterator(Node *node) : m_node(node) {}

        Node *m_node;
    };

    Node *m_head = nullptr;

public:

    using iterator = Iterator;

    iterator begin()
    {
        return iterator(m_head);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    const iterator begin() const
    {
        return iterator(m_head);
    }

    const iterator end() const
    {
        return iterator(nullptr);
    }

    void addTail(T &t);

    void remove();

    const T &get_head() const;

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
const T &sForwardList<T, Allocator>::get_head() const
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

}