# DTE-3611: Algorithm Design — Week 2

## Topic
**Algorithmic Complexity and Dynamic Programming**

This repository contains implementations of Week 2 exercises focusing on NP-hard and NP-complete problems solved with dynamic programming (DP).  
Algorithms included are **Subset Sum**, **0/1 Knapsack**, and **Traveling Salesman Problem (TSP)** using the Held–Karp approach.

---

## Implemented Algorithms

### 1. Subset Sum
- **Goal:** Determine if a subset of numbers sums to a target value.  
- **Approach:** Bottom-up DP table.  
- **Input Example:** `{3, 34, 4, 12, 5, 2}`, target = 9  
- **Output:** YES  
- **Time Complexity:** O(n × S)  

### 2. 0/1 Knapsack
- **Goal:** Maximize total value within a weight limit.  
- **Approach:** DP table storing optimal subproblem solutions.  
- **Input Example:** `values = {60, 100, 120}`, `weights = {10, 20, 30}`, capacity = 50  
- **Output:** Max Value = 220  
- **Time Complexity:** O(n × W)  

### 3. Traveling Salesman Problem (Held–Karp)
- **Goal:** Find the minimal cost tour visiting all cities once and returning to the start.  
- **Approach:** DP with bitmasking to represent visited city subsets.  
- **Input Example:** 5-city distance matrix  
- **Output:** Min Cost = 95  
- **Time Complexity:** O(n² × 2ⁿ)  

---

## How to Compile & Run

Open a terminal in the repository folder and execute:

```bash
# Compile using C++17 standard
g++ -std=c++17 benchmarks.cpp -o benchmarks

# Run benchmarks
./benchmarks
