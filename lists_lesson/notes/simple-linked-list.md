# Simple Linked List

This folder contains four linked list variants, each building on the same basic idea: nodes connected by pointers. They share a common interface (`insertFront`, `insertBack`, `remove`, `contains`, etc.) but differ in how nodes are linked and what constraints they impose.

---

## SinglyLinkedList.h

The most basic linked list. Each node holds a value and a single `next` pointer.

```
head -> [A] -> [B] -> [C] -> nullptr
```

**Node structure:**
```cpp
struct node {
    T value;
    node *next;
};
```

The list only keeps track of `head`. This means operations that need the last element (like `insertBack`, `removeBack`, `back()`) must traverse the whole list — O(n).

**Key design choices:**
- `insertFront` is O(1): just point the new node at the current head, then update head.
- `insertBefore` / `insertAfter` traverse from head looking for the target value, then splice in the new node.
- `remove` uses a trailing pointer pattern: walk with `p`, check `p->next->value`, so you can rewire `p->next` without needing a `prev` pointer.
- `removeBack` uses the same pattern — stop when `current->next->next == nullptr`.
- `update` replaces **all** occurrences of the old value (unlike the doubly linked version which stops at the first).
- `clear` just calls `removeFront` in a loop.
- `back()` traverses to the last node on every call.

**`operator<<` output:**
```
A -> B -> C -> nullptr
```

---

## DoublyLinkedList.h

Each node has both `next` and `prev` pointers, which makes backward traversal and deletion easier — no need to track a trailing pointer.

```
nullptr <-> [A] <-> [B] <-> [C] <-> nullptr
```

**Node structure:**
```cpp
struct node {
    T value;
    node *prev;
    node *next;
};
```

The list still only stores `head` (no tail pointer), so `insertBack` and `removeBack` still traverse to the end — O(n).

**Key design choices:**
- Uses private helpers to reduce duplication: `find(val)` returns the node pointer; `insertAfter(val, node*)`, `insertBefore(val, node*)`, and `removeNode(node*)` do the actual pointer work. The public overloads just call `find` then delegate.
- `removeNode` handles all four cases of unlinking a node: it is the head, it has a prev, it has a next, or neither. Clean and reusable.
- `update` only replaces the **first** match (finds the node, updates value in place). The list stays valid as long as the new value doesn't violate any ordering — but since this list is unordered, that's fine.
- `contains` just checks if `find` returns non-null.

**`operator<<` output:**
```
nullptr <-> A <-> B <-> C <-> nullptr
```

---

## CircularLinkedList.h

A singly-linked list where the last node points back to the first — there is no `nullptr` at the end. Instead of `head`, the list stores a `tail` pointer.

```
tail->next points to front (head)
[A] -> [B] -> [C] -> (back to A)
        ^tail
```

Storing `tail` instead of `head` is the key insight: you can reach both ends in O(1) — `tail` is the back, `tail->next` is the front.

**Node structure:** Same as singly — only a `next` pointer. The circularity is maintained by always keeping `tail->next` pointing at the front.

**Key design choices:**
- `insertFront`: new node points to `tail->next` (current front), then `tail->next` = new node. O(1).
- `insertBack`: new node splices between `tail` and `tail->next`, then `tail` advances to the new node. O(1).
- All traversals use a `do { ... } while (p != tail->next)` loop because you must process at least one node before checking the stop condition (the list wraps around).
- `removeFront` handles the one-node case separately (where `tail->next == tail`) to avoid a dangling `tail`.
- `removeBack` must walk to find the second-to-last node to update `tail` — O(n).
- Private helper `removeNext(node *n)` deletes `n->next` and rewires `n->next = n->next->next`. Used in `removeFront` and `remove`.

**`josephus(int p)`** — unique to this class. Simulates the Josephus problem: starting from the front, every p-th person is eliminated until one remains. Uses the circular structure naturally — just keep stepping `j = j->next` in a loop without worrying about end-of-list.

**`operator<<` output:**
```
A -> B -> C -> (back to front)
```

---

## OrderedLinkedList.h

A singly-linked list that maintains elements in sorted order at all times. Uses a comparator template parameter to determine the ordering.

```cpp
template <typename T, typename Compare = std::less<T>>
```

By default it sorts ascending. You can pass a custom comparator (e.g. `std::greater<T>`) for descending.

**Key design choices:**
- There is no `insertFront` / `insertBack` / `insertAfter` / `insertBefore` — only `insert(val)`. Position is always decided by the comparator, not the caller.
- `insert` walks until it finds the first node where `val < node->next->value` (i.e., `cmp(val, p->next->value)` is true), then splices in there. This keeps the list sorted in one pass — O(n).
- `remove` uses the comparator to early-exit: if `cmp(val, p->next->value)` is true, the value can't be further right, so it stops. This is an optimization over a plain linear scan.
- `contains` also uses the comparator to short-circuit: if `cmp(val, current->value)` is true, we've gone past where val would be, so return false early.
- `update` is implemented as `remove(oldVal)` + `insert(newVal)` — simple and correct, the new value gets inserted in its proper sorted position.
- Constructors: default uses `Compare{}` (default-constructed comparator); the explicit constructor takes a custom comparator instance, useful when the comparator has state.
