#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class Stack
{
public:
    Stack() : head(nullptr), size(0) {}
    ~Stack() { this->clear(); };

    void push(const T &val);
    T pop();
    const T &peek() const;

    void clear();

    bool isEmpty() const { return this->head == nullptr; }
    int getSize() const { return this->size; }

    friend std::ostream &operator<<(std::ostream &os, const Stack<T> &l)
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
void Stack<T>::push(const T &val)
{
    node *element = new node(val);

    element->next = this->head;
    this->head = element;
    this->size++;
}

template <typename T>
T Stack<T>::pop()
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot pop an empty list!");
    node *toDelete = this->head;
    T valToReturn = this->head->value;

    this->head = this->head->next;
    delete toDelete;
    this->size--;
    return valToReturn;
}

template <typename T>
const T &Stack<T>::peek() const
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot peek an empty list!");

    return this->head->value;
}

template <typename T>
void Stack<T>::clear()
{
    while (!this->isEmpty())
    {
        this->pop();
    }
}
