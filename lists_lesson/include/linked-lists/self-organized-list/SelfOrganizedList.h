#pragma once

template <typename T>
class SelfOrganizedList
{
public:
    enum class Heuristic
    {
        None,
        MoveToFront,
        Transpose
    };

    SelfOrganizedList() : head(nullptr), size(0) {}
    ~SelfOrganizedList() { this->clear(); }

    void clear();
    bool isEmpty() const { return this->head == nullptr; }

    void insertBack(const T &val);
    void removeFront();

    int search(const T &val, Heuristic h = Heuristic::None);

private:
    struct node
    {
        T value;
        node *next;
        explicit node(T v) : value(v), next(nullptr) {}
    };

    node *head;
    int size;
    int searchNone(const T &val) const;
    int searchMoveToFront(const T &val);
    int searchTranspose(const T &val);
};

template <typename T>
void SelfOrganizedList<T>::clear()
{
    while (!isEmpty())
        this->removeFront();
}

template <typename T>
void SelfOrganizedList<T>::insertBack(const T &val)
{
    node *element = new node(val);
    if (this->isEmpty())
    {
        this->head = element;
        return;
    }
    node *current = this->head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = element;
}

template <typename T>
void SelfOrganizedList<T>::removeFront()
{
    if (this->isEmpty())
        return;
    node *tmp = this->head;
    this->head = this->head->next;
    delete tmp;
    this->size--;
}

template <typename T>
int SelfOrganizedList<T>::search(const T &val, Heuristic h)
{
    switch (h)
    {
    case Heuristic::MoveToFront:
        return this->searchMoveToFront(val);
    case Heuristic::Transpose:
        return this->searchTranspose(val);
    default:
        return this->searchNone(val);
    }
}

template <typename T>
int SelfOrganizedList<T>::searchNone(const T &val) const
{
    int comparisons = 0;
    for (node *current = this->head; current != nullptr; current = current->next)
    {
        ++comparisons;
        if (current->value == val)
            return comparisons;
    }

    return -1;
}

template <typename T>
int SelfOrganizedList<T>::searchMoveToFront(const T &val)
{
    int comparisons = 0;
    node *previous = nullptr;
    node *current = this->head;
    while (current != nullptr)
    {
        ++comparisons;
        if (current->value == val)
        {
            if (previous != nullptr)
            {
                previous->next = current->next;
                current->next = this->head;
                this->head = current;
            }
            return comparisons;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}

template <typename T>
int SelfOrganizedList<T>::searchTranspose(const T &val)
{
    int comparisons = 0;
    node *prevPrevious = nullptr;
    node *previous = nullptr;
    node *current = this->head;

    while (current != nullptr)
    {
        ++comparisons;
        if (current->value == val)
        {
            if (previous != nullptr)
            {
                if (prevPrevious != nullptr)
                    prevPrevious->next = current;
                else
                    this->head = current;
                previous->next = current->next;
                current->next = previous;
            }
            return comparisons;
        }
        prevPrevious = previous;
        previous = current;
        current = current->next;
    }

    return -1;
}
