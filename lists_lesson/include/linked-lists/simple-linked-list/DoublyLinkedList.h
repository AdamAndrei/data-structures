#pragma once
#include <iostream>

template <typename T>
class DoublyLinkedList
{
public:
    DoublyLinkedList() : head(nullptr), size(0) {}
    ~DoublyLinkedList() { clear(); };

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

    friend std::ostream &operator<<(std::ostream &os, const DoublyLinkedList<T> &l)
    {
        node *p = l.head;
        os << "nullptr <-> ";
        while (p)
        {
            os << p->value;
            if (p->next)
                os << " <-> ";
            p = p->next;
        }
        os << " <-> nullptr";
        return os;
    }

private:
    struct node
    {
        T value;
        node *prev;
        node *next;
        node(const T &v) : value(v), prev(nullptr), next(nullptr) {}
    };

    node *head;
    int size;

    node *find(const T &val) const;
    void insertAfter(const T &val, node *beforeNode);
    void insertBefore(const T &val, node *afterNode);
    void removeNode(node *toDelete);
};

template <typename T>
typename DoublyLinkedList<T>::node *DoublyLinkedList<T>::find(const T &val) const
{
    node *current = this->head;
    while (current != nullptr)
    {
        if (current->value == val)
            return current;
        current = current->next;
    }
    return nullptr;
}

template <typename T>
void DoublyLinkedList<T>::insertBefore(const T &val, node *afterNode)
{
    if (isEmpty())
        return;

    if (afterNode == this->head)
    {
        this->insertFront(val);
        return;
    }

    node *element = new node(val);
    element->prev = afterNode->prev;
    element->next = afterNode;
    afterNode->prev->next = element;
    afterNode->prev = element;
    this->size++;
}

template <typename T>
void DoublyLinkedList<T>::insertAfter(const T &val, node *beforeNode)
{
    node *element = new node(val);
    element->prev = beforeNode;
    element->next = beforeNode->next;

    if (beforeNode->next != nullptr)
        beforeNode->next->prev = element;

    beforeNode->next = element;
    this->size++;
}

template <typename T>
void DoublyLinkedList<T>::removeNode(node *toDelete)
{
    if (toDelete == nullptr)
        return;
    if (toDelete->prev != nullptr)
        toDelete->prev->next = toDelete->next;
    else
        this->head = toDelete->next;

    if (toDelete->next != nullptr)
        toDelete->next->prev = toDelete->prev;

    delete toDelete;
    this->size--;
}

template <typename T>
void DoublyLinkedList<T>::insertFront(const T &val)
{
    node *element = new node(val);
    element->next = this->head;
    if (!this->isEmpty())
    {
        this->head->prev = element;
    }
    this->head = element;
    this->size++;
}

template <typename T>
void DoublyLinkedList<T>::insertBack(const T &val)
{
    if (this->isEmpty())
    {
        this->insertFront(val);
        return;
    }

    node *current = this->head;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    node *element = new node(val);
    current->next = element;
    element->prev = current;
    this->size++;
}

template <typename T>
void DoublyLinkedList<T>::insertAfter(const T &val, const T &before)
{
    if (this->isEmpty())
        return;

    node *beforeNode = this->find(before);
    if (beforeNode != nullptr)
        this->insertAfter(val, beforeNode);
}

template <typename T>
void DoublyLinkedList<T>::insertBefore(const T &val, const T &after)
{
    if (this->isEmpty())
        return;

    node *afterNode = this->find(after);
    if (afterNode == nullptr)
        return;

    this->insertBefore(val, afterNode);
}

template <typename T>
void DoublyLinkedList<T>::remove(const T &val)
{
    this->removeNode(this->find(val));
}

template <typename T>
void DoublyLinkedList<T>::removeFront()
{
    this->removeNode(this->head);
}

template <typename T>
void DoublyLinkedList<T>::removeBack()
{
    if (this->isEmpty())
        return;
    node *current = this->head;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    this->removeNode(current);
}

template <typename T>
void DoublyLinkedList<T>::clear()
{
    while (!isEmpty())
        this->removeFront();
}

template <typename T>
void DoublyLinkedList<T>::update(const T &oldVal, const T &newVal)
{
    node *toUpdate = this->find(oldVal);
    if (toUpdate == nullptr)
        return;

    toUpdate->value = newVal;
}

template <typename T>
bool DoublyLinkedList<T>::contains(const T &val) const
{
    return this->find(val) != nullptr;
}

template <typename T>
const T &DoublyLinkedList<T>::front() const
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot get front element of an empty list!");
    return this->head->value;
}

template <typename T>
const T &DoublyLinkedList<T>::back() const
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