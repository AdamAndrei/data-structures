#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class SinglyLinkedList
{
public:
    SinglyLinkedList() : head(nullptr), size(0) {}
    ~SinglyLinkedList() { clear(); }

    void insertFront(const T &val);
    void insertBack(const T &val);
    void insertAfter(const T &val, const T &before);
    void insertBefore(const T &val, const T &after);

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

    friend std::ostream &operator<<(std::ostream &os, const SinglyLinkedList<T> &l)
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
};

template <typename T>
void SinglyLinkedList<T>::insertFront(const T &val)
{
    node *element = new node(val);
    element->next = this->head;
    this->head = element;
    this->size++;
}

template <typename T>
void SinglyLinkedList<T>::insertBack(const T &val)
{
    if (this->isEmpty())
    {
        this->insertFront(val);
        return;
    }
    node *element = new node(val);
    node *current = this->head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = element;
    this->size++;
}

template <typename T>
void SinglyLinkedList<T>::insertBefore(const T &val, const T &after)
{
    if (isEmpty())
        return;
    if (this->head->value == after)
    {
        this->insertFront(val);
        return;
    }

    node *p = this->head;
    while (p->next != nullptr && p->next->value != after)
    {
        p = p->next;
    }

    if (p->next == nullptr)
        return;

    node *element = new node(val);
    element->next = p->next;
    p->next = element;
    this->size++;
}

template <typename T>
void SinglyLinkedList<T>::insertAfter(const T &val, const T &before)
{
    if (this->isEmpty())
        return;

    node *current = this->head;
    while (current != nullptr && current->value != before)
    {
        current = current->next;
    }

    if (current == nullptr)
        return;

    node *element = new node(val);
    element->next = current->next;
    current->next = element;
    this->size++;
}

template <typename T>
void SinglyLinkedList<T>::removeFront()
{
    if (this->isEmpty())
        return;

    node *tmp = this->head;
    this->head = this->head->next;
    delete tmp;
    this->size--;
}

template <typename T>
void SinglyLinkedList<T>::removeBack()
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

template <typename T>
void SinglyLinkedList<T>::remove(const T &val)
{
    if (this->isEmpty())
        return;

    if (this->head->value == val)
    {
        this->removeFront();
        return;
    }

    node *p = this->head;
    while (p->next != nullptr && p->next->value != val)
    {
        p = p->next;
    }

    if (p->next == nullptr)
        return;
    node *tmp = p->next;
    p->next = p->next->next;
    delete tmp;
    this->size--;
}

template <typename T>
void SinglyLinkedList<T>::clear()
{
    while (!this->isEmpty())
    {
        removeFront();
    }
}

template <typename T>
void SinglyLinkedList<T>::update(const T &oldVal, const T &newVal)
{
    if (this->isEmpty())
        return;

    node *current = this->head;
    while (current != nullptr)
    {
        if (current->value == oldVal)
            current->value = newVal;
        current = current->next;
    }
}

template <typename T>
bool SinglyLinkedList<T>::contains(const T &val) const
{
    if (this->isEmpty())
        return false;

    node *current = this->head;
    while (current != nullptr)
    {
        if (current->value == val)
            return true;
        current = current->next;
    }

    return false;
}

template <typename T>
const T &SinglyLinkedList<T>::front() const
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot get front element of an empty list!");
    return this->head->value;
}

template <typename T>
const T &SinglyLinkedList<T>::back() const
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
