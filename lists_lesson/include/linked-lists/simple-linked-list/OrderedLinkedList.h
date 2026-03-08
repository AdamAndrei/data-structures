#pragma once
#include <iostream>
#include <stdexcept>
#include <functional>

template <typename T, typename Compare = std::less<T>>
class OrderedLinkedList
{
public:
    OrderedLinkedList() : head(nullptr), size(0), cmp(Compare{}) {}
    explicit OrderedLinkedList(Compare cmp) : head(nullptr), size(0), cmp(cmp) {}
    ~OrderedLinkedList() { clear(); }

    void insert(const T &val);

    void remove(const T &val);
    void removeFront();
    void removeBack();
    void clear();

    void update(const T &oldVal, const T &newVal);

    bool isEmpty() const { return this->head == nullptr; }
    int getSize() const { return this->size; }

    bool contains(const T &val) const;
    const T &front() const;
    const T &back() const;

    friend std::ostream &operator<<(std::ostream &os, const OrderedLinkedList<T, Compare> &l)
    {
        node *p = l.head;
        while (p)
        {
            os << p->value;
            if (p->next)
                os << " -> ";
            p = p->next;
        }
        os << " -> nullptr";
        return os;
    }

private:
    struct node
    {
        T value;
        node *next;
        node(const T &v) : value(v), next(nullptr) {}
    };

    node *head;
    int size;
    Compare cmp;
};

template <typename T, typename Compare>
void OrderedLinkedList<T, Compare>::insert(const T &val)
{
    node *element = new node(val);
    if (this->isEmpty() || this->cmp(val, this->head->value))
    {
        element->next = this->head;
        this->head = element;
        this->size++;
        return;
    }

    node *p = this->head;
    while (p->next != nullptr && !this->cmp(val, p->next->value))
    {
        p = p->next;
    }

    element->next = p->next;
    p->next = element;
    this->size++;
}

template <typename T, typename Compare>
void OrderedLinkedList<T, Compare>::remove(const T &val)
{
    if (this->isEmpty())
        return;

    if (this->head->value == val)
    {
        this->removeFront();
        return;
    }

    node *p = this->head;
    while (p->next != nullptr && !this->cmp(val, p->next->value) && p->next->value != val)
    {
        p = p->next;
    }

    if (p->next == nullptr || p->next->value != val)
        return;
    node *tmp = p->next;
    p->next = p->next->next;
    delete tmp;
    this->size--;
}

template <typename T, typename Compare>
void OrderedLinkedList<T, Compare>::removeFront()
{
    if (this->isEmpty())
        return;

    node *tmp = this->head;
    this->head = this->head->next;
    delete tmp;
    this->size--;
}

template <typename T, typename Compare>
void OrderedLinkedList<T, Compare>::removeBack()
{
    if (this->isEmpty())
        return;

    if (this->head->next == nullptr)
    {
        this->removeFront();
        return;
    }

    node *current = this->head;
    while (current->next->next != nullptr)
    {
        current = current->next;
    }

    node *toDelete = current->next;
    current->next = nullptr;
    delete toDelete;
    this->size--;
}

template <typename T, typename Compare>
void OrderedLinkedList<T, Compare>::clear()
{
    while (!this->isEmpty())
    {
        removeFront();
    }
}

template <typename T, typename Compare>
void OrderedLinkedList<T, Compare>::update(const T &oldVal, const T &newVal)
{
    if (this->isEmpty())
        return;

    this->remove(oldVal);
    this->insert(newVal);
}

template <typename T, typename Compare>
bool OrderedLinkedList<T, Compare>::contains(const T &val) const
{
    if (this->isEmpty())
        return false;

    node *current = this->head;
    while (current != nullptr && !this->cmp(val, current->value))
    {
        if (current->value == val)
            return true;
        current = current->next;
    }

    return false;
}

template <typename T, typename Compare>
const T &OrderedLinkedList<T, Compare>::front() const
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot get front element of an empty list!");
    return this->head->value;
}

template <typename T, typename Compare>
const T &OrderedLinkedList<T, Compare>::back() const
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot get last element of an empty list!");
    node *current = this->head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    return current->value;
}
