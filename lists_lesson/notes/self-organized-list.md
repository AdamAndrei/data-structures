# Self-Organized List

A self-organized list is an unsorted linked list that **rearranges itself based on access patterns**. The idea is that frequently searched elements move closer to the front over time, reducing the average number of comparisons needed per search.

This folder contains two files: the list itself and a benchmarking utility to compare heuristics.

---

## SelfOrganizedList.h

A singly-linked list with a `search` method that accepts a heuristic to control how the list reorganizes itself after each successful find.

**Node structure:** Standard singly-linked node — `value` + `next`.

**Heuristic enum:**
```cpp
enum class Heuristic {
    None,         // plain linear search, no reordering
    MoveToFront,  // move found element to the front
    Transpose     // swap found element one position toward the front
};
```

**Public interface:**

| Method | Description |
|--------|-------------|
| `insertBack(val)` | Append to the end (used to build the list) |
| `removeFront()` | Remove the first element |
| `search(val, h)` | Search for val using heuristic h; returns comparison count or -1 |
| `clear()` | Remove all elements |

**How each heuristic works:**

### None — `searchNone`
Plain linear scan from `head`. Counts comparisons and returns the count on a match, or -1 if not found. The list is never modified.

### MoveToFront — `searchMoveToFront`
Walks with a `previous` + `current` pointer pair. On a match:
- Unlinks `current` from its position (`previous->next = current->next`)
- Points `current->next` at `head`
- Sets `head = current`

If the element is already at the front (`previous == nullptr`), nothing moves. This is an aggressive heuristic — a single access rockets the element to position 1.

### Transpose — `searchTranspose`
Walks with three pointers: `prevPrevious`, `previous`, `current`. On a match:
- Swaps `current` with `previous` (moves it one step closer to the front)
- Handles the edge case where `previous` is the head (sets `head = current`)
- Uses `prevPrevious` to rewire the node before `previous`

This is a conservative heuristic — elements gradually bubble toward the front proportional to how often they are accessed, rather than jumping immediately to position 1. Less volatile than MoveToFront when access patterns are noisy.

**Return value:** All three search methods return the **number of comparisons** made, not a boolean. This lets you measure the cost of each search and compare heuristics empirically. Returns -1 on miss.

---

## SelfOrganizedListComparer.h

A benchmarking utility that runs all heuristics on the same data and reports average search time per query in microseconds.

**Setup:**
```cpp
struct Entry {
    T value;
    double probability;  // how often this value should be searched
};
```

You provide a list of `Entry` values with probabilities that sum to 1.0. The comparer uses a Mersenne Twister RNG (`std::mt19937`) to generate a sequence of search targets drawn from those probabilities, then times each heuristic against that same sequence.

**Key methods:**

- `generateTarget()` — samples a value from the `entries_` distribution using a uniform random draw and a cumulative probability scan. Elements with higher probability are selected more often.
- `makeList(bool sorted)` — builds a `SelfOrganizedList<T>` from entries. If `sorted=true`, entries are pre-sorted by probability descending (highest frequency first) — this is the theoretical optimum baseline. If `false`, inserted in original order.
- `timeHeuristic(list, h, targets)` — runs `list.search(target, h)` for every target, measures wall-clock time with `std::chrono::high_resolution_clock`, and returns average microseconds per search.
- `run()` — builds four lists (None, MoveToFront, Transpose, Sorted) and times each. Returns a `result` struct with the four averages.
- `showResults()` — calls `run()` and prints a formatted table to stdout.

> **Note:** There is a bug in `run()` — all four `timeHeuristic` calls use `listNone` instead of each list's own copy (`listMTF`, `listTranspose`, `listSorted` are built but never used). This means MoveToFront and Transpose are timed on a list that was already mutated by the previous heuristic run, and the "Sorted" result is actually just a second run of `None` on the same list.

**What the comparison shows conceptually (when working correctly):**

| Strategy | Avg comparisons | Characteristics |
|----------|----------------|-----------------|
| None | High | No learning, always linear |
| MoveToFront | Low (fast to adapt) | Best for repeated identical queries |
| Transpose | Medium (slow to adapt) | More stable, better for shifting patterns |
| Pre-sorted | Theoretical minimum | Not dynamic, requires known distribution upfront |
