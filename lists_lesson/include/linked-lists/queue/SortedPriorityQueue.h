#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class SortedPriorityQueue
{
public:
    SortedPriorityQueue() : first(nullptr), last(nullptr), size(0), maxSize(1) {}
    ~SortedPriorityQueue() { this->clear(); }
    explicit SortedPriorityQueue(int maxSize) : first(nullptr), last(nullptr), size(0), maxSize(maxSize) {}

    void clear();
    bool isEmpty() const { return this->first == nullptr; }
    int getSize() const { return this->size; }
    void increaseSize(int addSize) { this->maxSize += addSize; }

    void enqueue(const T &val, int priority);
    T dequeue();

    const T &front() const;

    friend std::ostream &operator<<(std::ostream &os, const SortedPriorityQueue<T> &q)
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
        int priority;
        node *next;
        node(const T &v, int p) : value(v), priority(p), next(nullptr) {}
    };
    node *first;
    node *last;
    int size;
    int maxSize;
};

template <typename T>
void SortedPriorityQueue<T>::clear()
{
    while (!this->isEmpty())
    {
        node *tmp = this->first->next;
        delete this->first;
        this->first = tmp;
    }
}

template <typename T>
void SortedPriorityQueue<T>::enqueue(const T &val, int priority)
{
    node *element = new node(val, priority);

    node *previous = nullptr;
    node *current = this->first;

    while (current != nullptr && current->priority >= priority)
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        if (this->size < this->maxSize)
        {
            if (this->isEmpty())
                this->first = this->last = element;
            else
            {
                this->last->next = element;
                this->last = element;
            }
            this->size++;
        }
        else
            delete element;
        return;
    }

    element->next = current;

    if (previous == nullptr)
        this->first = element;
    else
        previous->next = element;

    if (this->size < this->maxSize)
        this->size++;
    else
    {
        node *p = element;
        while (p->next != this->last)
            p = p->next;
        delete this->last;
        this->last = p;
        this->last->next = nullptr;
    }
}

template <typename T>
T SortedPriorityQueue<T>::dequeue()
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot dequue an empty queue!");
    node *toDelete = this->first;
    this->first = this->first->next;
    if (this->first == nullptr)
        this->last = nullptr;
    T val = toDelete->value;
    delete toDelete;
    this->size--;
    return val;
}

template <typename T>
const T &SortedPriorityQueue<T>::front() const
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot get first element of empty queue!");
    return this->first->value;
}
