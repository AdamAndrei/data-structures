#pragma once
#include "Queue.h"

template <typename T, int P>
class PriorityQueue
{
public:
    PriorityQueue() : firstQ(-1), lastQ(-1), size(0), maxSize(-1) {}
    ~PriorityQueue() { this->clear(); }
    explicit PriorityQueue(int maxSize) : firstQ(-1), lastQ(-1), size(0), maxSize(maxSize) {}

    void clear();

    void enqueue(const T &val, int priority);
    T dequeue();

    const T &peek() const;

    bool isEmpty() const { return firstQ == -1; }
    int getSize() const { return this->size; }

private:
    Queue<T> queues[P];
    int firstQ;
    int lastQ;
    int size;
    int maxSize;
};

template <typename T, int P>
void PriorityQueue<T, P>::enqueue(const T &val, int priority)
{
    if (priority < 0 || priority >= P)
        throw std::underflow_error("Invalid priority");
    this->queues->enqueue(val);
    this->size++;

    if (this->firstQ == -1 || priority < this->firstQ)
        this->firstQ = priority;
    if (this->lastQ == -1 || priority > this->lastQ)
        this->lastQ = priority;
}

template <typename T, int P>
T PriorityQueue<T, P>::dequeue()
{
    if (this->isEmpty())
        throw std::underflow_error("Remove on empty priority queue!");

    T val = this->queues[this->firstQ].dequeue();
    this->size--;

    if (this->queues[firstQ].isEmpty())
    {
        if (this->firstQ == this->lastQ)
            this->firstQ = this->lastQ = -1;
        else
        {
            for (int i = this->firstQ + 1; i <= lastQ; i++)
            {
                if (!this->queues[i].isEmpty())
                {
                    this->firstQ = i;
                    break;
                }
            }
        }
    }
    return val;
}

template <typename T, int P>
const T &PriorityQueue<T, P>::peek() const
{
    if (this->isEmpty())
        throw std::underflow_error("Cannot get front of empty queue!");
    return this->queues[this->firstQ].peek();
}
