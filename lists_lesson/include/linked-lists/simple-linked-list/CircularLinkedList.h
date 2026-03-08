#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class CircularLinkedList
{
public:
    CircularLinkedList() : tail(nullptr), size(0) {}
    ~CircularLinkedList() { clear(); }

    void insertFront(const T &val);
    void insertBack(const T &val);
    void insertAfter(const T &val, const T &before);
    void insertBefore(const T &val, const T &after);

    void remove(const T &val);
    void removeFront();
    void removeBack();
    void clear();

    void update(const T &oldVal, const T &newVal);

    bool isEmpty() const { return this->tail == nullptr; }
    int getSize() const { return size; }
    bool contains(const T &val) const;

    const T &front() const;
    const T &back() const;

    void josephus(int p);

    friend std::ostream &operator<<(std::ostream &os, const CircularLinkedList<T> &l)
    {
        if (l.isEmpty())
        {
            os << "[empty]";
            return os;
        }
        node *p = l.tail->next;
        do
        {
            os << p->value;
            if (p->next != l.tail->next)
                os << " -> ";
            p = p->next;
        } while (p != l.tail->next);
        os << " -> (back to front)";
        return os;
    }

private:
    struct node
    {
        T value;
        node *next;
        node(const T &v) : value(v), next(nullptr) {}
    };

    node *tail;
    int size;

    void removeNext(node *n);
};

template <typename T>
void CircularLinkedList<T>::insertFront(const T &val)
{
    node *elem = new node(val);
    if (isEmpty())
    {
        elem->next = elem;
        this->tail = elem;
    }
    else
    {
        elem->next = this->tail->next;
        this->tail->next = elem;
    }
    this->size++;
}

template <typename T>
void CircularLinkedList<T>::insertBack(const T &val)
{
    if (isEmpty())
    {
        this->insertFront(val);
        return;
    }

    node *elem = new node(val);
    elem->next = this->tail->next;
    this->tail->next = elem;
    this->tail = elem;
    size++;
}

template <typename T>
void CircularLinkedList<T>::insertAfter(const T &val, const T &before)
{
    if (isEmpty())
        return;
    node *p = this->tail->next;
    do
    {
        if (p->value == before)
        {
            node *elem = new node(val);
            elem->next = p->next;
            p->next = elem;
            if (p == this->tail)
                this->tail = elem;
            size++;
            return;
        }
        p = p->next;
    } while (p != this->tail->next);
}

template <typename T>
void CircularLinkedList<T>::insertBefore(const T &val, const T &after)
{
    if (isEmpty())
        return;

    if (this->tail->next->value == after)
    {
        insertFront(val);
        return;
    }

    node *p = this->tail->next;
    while (p->next != this->tail->next && p->next->value != after)
        p = p->next;

    if (p->next->value != after)
        return;

    node *elem = new node(val);
    elem->next = p->next;
    p->next = elem;
    size++;
}

template <typename T>
void CircularLinkedList<T>::remove(const T &val)
{
    if (isEmpty())
        return;

    if (this->tail->next->value == val)
    {
        removeFront();
        return;
    }

    node *p = this->tail->next;
    while (p->next != this->tail->next && p->next->value != val)
        p = p->next;

    if (p->next->value != val)
        return;

    if (p->next == this->tail)
        this->tail = p;

    removeNext(p);
}

template <typename T>
void CircularLinkedList<T>::removeFront()
{
    if (isEmpty())
        return;
    if (this->tail->next == this->tail)
    {
        delete this->tail;
        this->tail = nullptr;
        size--;
        return;
    }
    removeNext(this->tail);
}

template <typename T>
void CircularLinkedList<T>::removeBack()
{
    if (isEmpty())
        return;
    if (this->tail->next == this->tail)
    {
        delete this->tail;
        this->tail = nullptr;
        size--;
        return;
    }

    node *current = this->tail->next;
    while (current->next != this->tail)
        current = current->next;

    current->next = this->tail->next;
    delete this->tail;
    this->tail = current;

    this->size--;
}

template <typename T>
void CircularLinkedList<T>::clear()
{
    while (!this->isEmpty())
    {
        this->removeFront();
    }
}

template <typename T>
void CircularLinkedList<T>::update(const T &oldVal, const T &newVal)
{
    if (isEmpty())
        return;
    node *p = this->tail->next;
    do
    {
        if (p->value == oldVal)
            p->value = newVal;
        p = p->next;
    } while (p != this->tail->next);
}

template <typename T>
bool CircularLinkedList<T>::contains(const T &val) const
{
    if (isEmpty())
        return false;
    node *p = this->tail->next;
    do
    {
        if (p->value == val)
            return true;
        p = p->next;
    } while (p != this->tail->next);
    return false;
}

template <typename T>
const T &CircularLinkedList<T>::front() const
{
    if (isEmpty())
        throw std::underflow_error("front on empty list");
    return this->tail->next->value;
}

template <typename T>
const T &CircularLinkedList<T>::back() const
{
    if (isEmpty())
        throw std::underflow_error("back on empty list");
    return this->tail->value;
}

template <typename T>
void CircularLinkedList<T>::josephus(int p)
{
    if (isEmpty())
        return;

    node *j = this->tail->next;   // start at front
    while (j != j->next)          // more than one node remains
    {
        for (int i = 0; i < p - 1; i++)
            j = j->next;          // advance p-1 steps; j is now before the victim

        this->tail = j;
        std::cout << "Removing " << j->next->value << " | ";
        removeNext(j);
        std::cout << *this << std::endl;
        j = this->tail->next;     // move to new front for next round
    }
    std::cout << "Winner: " << j->value << std::endl;
}

template <typename T>
void CircularLinkedList<T>::removeNext(node *n)
{
    node *tmp = n->next;
    n->next = tmp->next;
    delete tmp;
    size--;
}
