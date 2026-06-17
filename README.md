# Postfix Calculator — Stack Implementations

A small C++ project that builds the core engine of a **postfix (Reverse Polish Notation) calculator**: the stack. The interesting part is that the same stack is implemented **three different ways**, so you can compare how the choice of underlying storage affects the design — while the public interface stays identical.

This was built as a data-structures exercise (DSA Project 1).

---

## What is a postfix calculator?

Postfix notation writes the operator *after* its operands. Instead of `3 + 4`, you write `3 4 +`.

It's evaluated with a stack:

1. Read tokens left to right.
2. If the token is a number, **push** it onto the stack.
3. If it's an operator, **pop** the top two numbers, apply the operator, and **push** the result back.
4. When the input ends, the single value left on the stack is the answer.

Example — `5 1 2 + 4 * + 3 -` evaluates to `14`.

Every stack in this project exposes exactly the operations needed to do this: `push`, `pop`, and the four arithmetic operators (`add`, `subtract`, `multiply`, `divide`), plus helpers to inspect and print the stack.

---

## The three implementations

| File(s) | Class | Storage | Key idea |
|---|---|---|---|
| `stack_a.h/.cpp` | `Stack_A` | Fixed-size array (`int[1024]`) | Simplest; capacity is capped at 1024. |
| `stack_b.h/.cpp` | `Stack_B` | Dynamic (heap) array | Doubles capacity when full, halves it when mostly empty. No fixed limit. |
| `stack_c.h/.cpp` | `Stack_C` | Doubly-linked list | Backed by a `List` of `Node`s with sentinel ends. Grows one node at a time. |

The linked-list version is supported by two helper classes:

- **`node.h/.cpp` (`Node`)** — a single list element holding an `int value` and `next`/`prev` pointers.
- **`list.h/.cpp` (`List`)** — a doubly-linked list framed by two **sentinel** (dummy) nodes: `[X]<->[7]<->[3]<->[X]`. The sentinels mean insert and delete never need special cases for the empty list or the ends.

### Shared interface

All three stack classes provide:

```cpp
void push(int data);                 // push a value
int  pop();                          // pop and return the top value
int  get_element_from_top(int idx);  // peek, counting from the top (0 = top)
int  get_element_from_bottom(int idx);// peek, counting from the bottom (0 = bottom)
void print_stack(bool top_or_bottom);// print all elements (false = bottom→top, true = top→bottom)
int  add();                          // pop two, push (a + b)
int  subtract();                     // pop two, push (a - b)
int  multiply();                     // pop two, push (a * b)
int  divide();                       // pop two, push (a / b), floored
int  get_size();                     // number of elements
// plus get_stack() to access the underlying storage
```

---

## A design detail worth knowing: floored division

`divide()` does **not** behave like plain C++ integer division. C++ truncates toward zero (`-7 / 2 == -3`), but this project rounds **toward negative infinity** instead (`-7 / 2 == -4`), matching the way Python's `//` operator works. This is done with a small correction after the division:

```cpp
if (quotient <= 0 && dividend % divisor != 0) {
    quotient--;
}
```

This is a deliberate choice, not a bug — it keeps division consistent for negative numbers.

### Operand order

For the non-commutative operators (`subtract`, `divide`), the order matches postfix expectations: the value pushed **first** is the left operand. So `5 3 -` gives `5 - 3 = 2`, and `6 2 /` gives `6 / 2 = 3`.

---

## Error handling

The operations throw `std::runtime_error` on invalid use:

- `"Stack Full"` — pushing past 1024 on `Stack_A`.
- `"Empty Stack"` — popping an empty stack.
- `"Not Enough Arguments"` — an operator called with fewer than two values.
- `"Divide by Zero Error"` — dividing by zero.
- `"Index out of range"` — peeking past the ends.

---

## Project structure

```
.
├── node.h / node.cpp        # list element (Stack_C)
├── list.h / list.cpp        # doubly-linked list with sentinels (Stack_C)
├── stack_a.h / stack_a.cpp  # fixed-size array stack
├── stack_b.h / stack_b.cpp  # dynamic array stack
├── stack_c.h / stack_c.cpp  # linked-list stack
├── .gitignore
└── README.md
```

> Note: this repo contains the stack classes themselves, not a `main()` driver. To run them, write a small program that includes the header you want and calls into it (see below).

---

## Building and using it

There's no entry point yet, so you supply one. For example, create `main.cpp`:

```cpp
#include <iostream>
#include "stack_a.h"

int main() {
    Stack_A s;
    s.push(3);
    s.push(4);
    std::cout << s.add() << std::endl;   // prints 7
    return 0;
}
```

Compile it together with the matching `.cpp` file(s):

```bash
# Array stack
g++ -std=c++17 main.cpp stack_a.cpp -o calc

# Dynamic-array stack
g++ -std=c++17 main.cpp stack_b.cpp -o calc

# Linked-list stack (needs node.cpp and list.cpp too)
g++ -std=c++17 main.cpp stack_c.cpp list.cpp node.cpp -o calc

./calc
```

---

## What I learned building this

- The same abstract data type (a stack) can sit on top of very different storage, and the trade-offs (fixed vs. dynamic capacity, contiguous memory vs. pointer-chasing) are real and visible in the code.
- Sentinel nodes make linked-list edge cases much cleaner to write.
- Amortized resizing (doubling/halving) is what lets the dynamic array feel "unlimited" without reallocating on every push.

---

## Possible next steps

- Add a `main()` that reads a full postfix expression from input and evaluates it end to end.
- Add unit tests covering the edge cases (empty stack, division by zero, negative floored division).
- Make the stacks templated (`Stack<T>`) so they work with types other than `int`.
