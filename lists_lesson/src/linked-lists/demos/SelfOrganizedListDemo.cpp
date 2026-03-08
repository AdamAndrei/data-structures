#include "linked-lists/demos/SelfOrganizedListDemo.h"
#include "linked-lists/self-organized-list/SelfOrganizedListComparer.h"
#include "linked-lists/self-organized-list/SelfOrganizedList.h"
#include <iostream>
#include <random>


using Entry = SelfOrganizedListComparer<int>::Entry;

// Helper: build entries with random probabilities
static std::vector<Entry> makeRandomEntries(int N, std::mt19937 &rng)
{
    std::uniform_int_distribution<int> randA(1, 100000);
    std::vector<int> a(N);
    for (int &x : a)
        x = randA(rng);
    double sum = 0.0;
    for (int x : a)
        sum += x;
    std::vector<Entry> entries(N);
    for (int i = 0; i < N; i++)
        entries[i] = {i + 1, a[i] / sum};
    return entries;
}

// Helper: pk = 1/2^k
static std::vector<Entry> makeDecreasingEntries(int N)
{
    std::vector<Entry> entries(N);
    double sum = 0.0;
    for (int k = 0; k < N - 1; k++)
    {
        entries[k] = {k + 1, 1.0 / std::pow(2.0, k + 1)};
        sum += entries[k].probability;
    }
    entries[N - 1] = {N, 1.0 - sum};
    return entries;
}

// Helper: pk = 2k / (N*(N+1))
static std::vector<Entry> makeIncreasingEntries(int N)
{
    double denom = (double)N * (N + 1);
    std::vector<Entry> entries(N);
    for (int k = 0; k < N; k++)
        entries[k] = {k + 1, 2.0 * (k + 1) / denom};
    return entries;
}

void demoSelfOrganizedList()
{
    const int N = 1000;
    const int NUM_SEARCHES = 100000;
    std::mt19937 rng(42);

    SelfOrganizedListComparer<int>(makeRandomEntries(N, rng), rng, NUM_SEARCHES,
                                   "Random probabilities")
        .showResults();
    SelfOrganizedListComparer<int>(makeDecreasingEntries(N), rng, NUM_SEARCHES,
                                   "Decreasing probabilities (1/2^k)")
        .showResults();
    SelfOrganizedListComparer<int>(makeIncreasingEntries(N), rng, NUM_SEARCHES,
                                   "Increasing probabilities (proportional to k)")
        .showResults();
}
