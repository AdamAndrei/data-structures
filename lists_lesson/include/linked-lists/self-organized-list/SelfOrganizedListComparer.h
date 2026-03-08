#pragma once
#include "linked-lists/self-organized-list/SelfOrganizedList.h"
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>

template <typename T>
class SelfOrganizedListComparer
{
public:
    struct Entry
    {
        T value;
        double probability;
    };

    SelfOrganizedListComparer(std::vector<Entry> entries, std::mt19937 &rng, int numberOfSearches, std::string label) : entries_(std::move(entries)), rng_(rng), numberOfSearches_(numberOfSearches), label_(std::move(label)) {}

    void showResults();

private:
    using Heuristic = typename SelfOrganizedList<T>::Heuristic;
    struct result
    {
        double avgTimeNone;
        double avgTimeMTF;
        double avgTimeTranspose;
        double avgTimeSorted;
    };

    std::vector<Entry> entries_;
    std::mt19937 &rng_;
    int numberOfSearches_;
    std::string label_;

    T generateTarget() const;
    result run() const;
    SelfOrganizedList<T> makeList(bool sorted) const;
    double timeHeuristic(SelfOrganizedList<T> &list, Heuristic h, const std::vector<T> &targets) const;
};

template <typename T>
void SelfOrganizedListComparer<T>::showResults()
{
    result r = run();
    std::cout << "\n=== " << label_ << " ===\n";
    std::cout << "  None       : " << r.avgTimeNone << " µs/search\n";
    std::cout << "  MoveToFront: " << r.avgTimeMTF << " µs/search\n";
    std::cout << "  Transpose  : " << r.avgTimeTranspose << " µs/search\n";
    std::cout << "  Sorting    : " << r.avgTimeSorted << " µs/search\n";
}

template <typename T>
T SelfOrganizedListComparer<T>::generateTarget() const
{
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double probe = dist(rng_);
    double s = 0.0;

    for (const Entry &e : this->entries_)
    {
        s += e.probability;
        if (probe < s)
            return e.value;
    }

    return this->entries_.back().value;
}

template <typename T>
typename SelfOrganizedListComparer<T>::result SelfOrganizedListComparer<T>::run() const
{
    std::vector<T> targets(this->numberOfSearches_);
    for (T &target : targets)
        target = this->generateTarget();
    auto listNone = this->makeList(false);
    auto listMTF = this->makeList(false);
    auto listTranspose = this->makeList(false);
    auto listSorted = this->makeList(false);

    return {
        this->timeHeuristic(listNone, Heuristic::None, targets),
        this->timeHeuristic(listNone, Heuristic::MoveToFront, targets),
        this->timeHeuristic(listNone, Heuristic::Transpose, targets),
        this->timeHeuristic(listNone, Heuristic::None, targets),
    };
}

template <typename T>
SelfOrganizedList<T> SelfOrganizedListComparer<T>::makeList(bool sorted) const
{
    SelfOrganizedList<T> list;
    if (sorted)
    {
        std::vector<const Entry *> entryPtrs;
        for (const Entry &e : this->entries_)
            entryPtrs.push_back(&e);
        std::sort(entryPtrs.begin(), entryPtrs.end(),
                  [](const Entry *a, const Entry *b)
                  { return a->probability > b->probability; });
        for (const Entry *e : entryPtrs)
            list.insertBack(e->value);
    }
    else
    {
        for (const Entry &e : this->entries_)
            list.insertBack(e.value);
    }
    return list;
}

template <typename T>
double SelfOrganizedListComparer<T>::timeHeuristic(SelfOrganizedList<T> &list, Heuristic h, const std::vector<T> &targets) const
{
    auto t0 = std::chrono::high_resolution_clock::now();
    for (const T &target : targets)
        list.search(target, h);
    auto t1 = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::micro>(t1 - t0).count() / targets.size();
}
