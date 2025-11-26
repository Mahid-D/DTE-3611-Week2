# Network Flow Algorithms in C++

This project implements classical network flow algorithms in modern C++ (C++20), including:

- **Ford-Fulkerson** (maximum flow)
- **Edmonds-Karp** (maximum flow using BFS for shortest augmenting paths)
- **Goldberg-Tarjan** (minimum-cost flow using successive shortest path approach)

The code demonstrates a small test graph and prints the computed max flows and min-cost flows.

---

## Requirements

- C++20 compatible compiler (`clang++` recommended)
- Standard C++ libraries (no external dependencies required)

---

## Compilation and Execution

You can compile and run the project in two ways:

### 1. Direct compilation and execution

```bash
clang++ -std=c++20 main.cpp -o main
./main
```
