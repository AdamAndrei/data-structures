# Queue

This folder contains two queue implementations: a basic `Queue` and two priority queue variants.

---

## Queue.h

A queue is a **FIFO** (First In, First Out) data structure. Elements enter at the back and leave from the front. Think of a line of people — first to arrive is first to be served.

Unlike the Stack which only needs `head`, this list keeps both `first` (front) and `last` (back) pointers so both `enqueue` and `dequeue` are O(1).

```
front [first]                [last] back
  [A] -> [B] -> [C] -> [D] -> nullptr
enqueue adds here --------^
dequeue removes from here ^--- (first)
```

**Node structure:**
```cpp
struct node {
    T value;
    node *next;
};
```

**Public interface:**

| Method | Description |
|--------|-------------|
| `enqueue(val)` | Add to the back |
| `dequeue()` | Remove and return the front element |
| `front()` | Read the front element without removing it |
| `clear()` | Remove all elements |
| `isEmpty()` / `getSize()` | State checks |

**Key design choices:**

- `enqueue` appends to `last->next` then advances `last`. If the list is empty, both `first` and `last` point to the new node. O(1).
- `dequeue` removes from `first` and advances it. Crucially, if after removal `first` becomes `nullptr`, `last` is also set to `nullptr` — otherwise you'd have a dangling `last` pointer. Throws on empty. O(1).
- `clear` avoids calling `dequeue` (which returns a value we don't need) — it directly walks `first` via a `tmp` pointer and deletes each node. Slightly more efficient than reusing `dequeue`.

**`operator<<` output:**
```
front [ A, B, C, D ] back
```

---

## PriorityQueue.h

A priority queue where elements are served in priority order (lower number = higher priority). Uses an **array of `Queue<T>` buckets**, one per priority level.

```cpp
template <typename T, int P>   // P = number of priority levels
```

```
queues[0] (highest priority): [A] -> [B]
queues[1]:                    [C]
queues[2] (lowest priority):  [D] -> [E]
```

**State:**
- `queues[P]` — fixed-size array of Queue objects, one per priority level
- `firstQ` — index of the highest-priority non-empty queue (-1 if empty)
- `lastQ` — index of the lowest-priority non-empty queue (-1 if empty)
- `maxSize` — optional capacity limit (stored but not enforced in the current code)

**Key design choices:**

- `enqueue(val, priority)` validates the priority is in range, then delegates to `queues[priority].enqueue(val)`. Updates `firstQ` / `lastQ` if the new priority is outside the current range. O(1).
- `dequeue` removes from `queues[firstQ]`. If that bucket becomes empty, it scans forward from `firstQ+1` to find the next non-empty bucket to update `firstQ`. Worst case O(P), but P is a compile-time constant so it's effectively O(1) in practice.
- `peek` just calls `front()` on `queues[firstQ]`. O(1).
- Elements of the same priority are served in FIFO order within their bucket (because each bucket is a plain `Queue`).

> **Note:** There is a bug in `enqueue` — it always calls `this->queues->enqueue(val)` (enqueues into `queues[0]`) instead of `this->queues[priority].enqueue(val)`. The priority tracking logic (`firstQ`/`lastQ`) is correct, but all elements land in bucket 0 regardless of the priority passed.

---

## SortedPriorityQueue.h

An alternative priority queue that maintains a **single sorted linked list** instead of an array of buckets. Nodes are kept sorted by priority (highest first = lowest number first) at all times.

Each node stores its priority alongside the value:

```cpp
struct node {
    T value;
    int priority;
    node *next;
};
```

```
first (front, highest priority)           last (back)
[val=A, pri=0] -> [val=B, pri=1] -> [val=C, pri=3] -> nullptr
```

**Key design choices:**

- `enqueue(val, priority)` inserts in sorted order: walks until it finds the first node with a lower priority (`current->priority < priority`), then splices in. O(n) insertion, but dequeue is O(1).
- **Bounded capacity** (`maxSize`): if the queue is full and the new element lands before the `last` node, the last node is dropped to make room — the queue keeps only the highest-priority elements. If the new element would go at the end and the queue is full, it is silently discarded. `increaseSize(n)` lets you grow the capacity.
- `dequeue` removes `first` (always the highest-priority node). Resets `last` to `nullptr` if the list becomes empty. O(1).
- `front()` returns `first->value`. O(1).

**Comparison with PriorityQueue:**

| | `PriorityQueue<T,P>` | `SortedPriorityQueue<T>` |
|---|---|---|
| Priority levels | Fixed at compile time (`P`) | Any integer |
| Enqueue | O(1) | O(n) |
| Dequeue | O(P) worst case | O(1) |
| Capacity limit | Stored, not enforced | Enforced, drops lowest priority |
