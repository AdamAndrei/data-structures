# Stack

## Stack.h

A stack is a **LIFO** (Last In, First Out) data structure. The last element pushed is the first one popped. Think of a stack of plates — you always add and remove from the top.

This implementation is a singly-linked list under the hood, with `head` acting as the top of the stack.

```
top (head)
 |
[C] -> [B] -> [A] -> nullptr
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
| `push(val)` | Add to the top |
| `pop()` | Remove and return the top element |
| `peek()` | Read the top element without removing it |
| `clear()` | Remove all elements |
| `isEmpty()` | True if no elements |
| `getSize()` | Number of elements |

**Key design choices:**

- `push` is identical to `insertFront` in a singly linked list: point the new node at the current head, then update head. O(1).
- `pop` saves the value before deleting the node, then returns it. Throws `std::underflow_error` if empty. O(1).
- `peek` just returns `head->value` without any structural change. O(1).
- `clear` reuses `pop` in a loop — the simplest correct implementation.
- All three core operations are O(1), which is the main advantage of the linked-list stack over an array-based one (no resizing needed).

**`operator<<` output:**
```
C -> B -> A -> nullptr   (top is on the left)
```
