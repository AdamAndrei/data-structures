#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class Queue
{
public:
    Queue() : first(nullptr), last(nullptr), size(0) {}
    ~Queue() { this->clear(); }

    void clear();
    bool isEmpty() const { return this->first == nullptr; }
    int getSize() const { return this->size; }

    void enqueue(const T &val);
    T dequeue();

    const T &front() const;

    friend std::ostream &operator<<(std::ostream &os, const Queue<T> &q)
    {
        node *p = q.first;
        os << "front [ ";
        while (p)
        {
            os << p->value;
            if (p->next)
                os << ", ";
            p = p->next;
        }
        os << " ] back";
        return os;
    }

private:
    struct node
    {
        T value;
        node *next;
        node(const T &v) : value(v), next(nullptr) {}
    };
    node *first;
    node *last;
    int size;
};

template <typename T>
void Queue<T>::clear()
{
    while (!this->isEmpty())
    {
        node* tmp = this->first->next;
        delete this->first;
        this->first = tmp;
    }
}

template <typename T>
void Queue<T>::enqueue(const T &val)
{
    node *element = new node(val);
    if (this->isEmpty())
        this->first = this->last = element;
    else
    {
        this->last->next = element;
        this->last = element;
    }

    this->size++;
}

template <typename T>
T Queue<T>::dequeue()
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot dequeue on empty queue!");

    node *toDelete = this->first;
    T valToReturn = this->first->value;

    this->first = this->first->next;
    if (this->first == nullptr)
        this->last = nullptr;

    delete toDelete;
    this->size--;
    return valToReturn;
}

template <typename T>
const T &Queue<T>::front() const
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot get the first element on empty queue!");

    return this->first->value;
}
