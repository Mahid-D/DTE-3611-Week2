#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

#include "subset_sum.cpp"
#include "knapsack.cpp"
#include "tsp_held_karp.cpp"

int main() {
    // Subset Sum benchmark
    vector<int> nums;
    int valArr[] = {3, 34, 4, 12, 5, 2};
    nums.assign(valArr, valArr + 6);
    int target = 9;

    auto start = high_resolution_clock::now();
    bool subsetResult = subsetSum(nums, target);
    auto end = high_resolution_clock::now();
    cout << "Subset Sum (" << target << "): " << (subsetResult ? "YES" : "NO") << endl;
    cout << "Time: " << duration_cast<microseconds>(end - start).count() << " µs\n";

    // Knapsack benchmark
    int vArr[] = {60, 100, 120};
    int wArr[] = {10, 20, 30};
    vector<int> values(vArr, vArr + 3);
    vector<int> weights(wArr, wArr + 3);
    int capacity = 50;

    start = high_resolution_clock::now();
    int maxVal = knapsack(values, weights, capacity);
    end = high_resolution_clock::now();
    cout << "\nKnapsack Max Value: " << maxVal << endl;
    cout << "Time: " << duration_cast<microseconds>(end - start).count() << " µs\n";

    // TSP benchmark
    int distArr[5][5] = {
        {0,10,15,20,10},
        {10,0,35,25,15},
        {15,35,0,30,20},
        {20,25,30,0,25},
        {10,15,20,25,0}
    };

    vector< vector<int> > dist(5, vector<int>(5));
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            dist[i][j] = distArr[i][j];

    start = high_resolution_clock::now();
    int tspCost = tspHeldKarp(dist);
    end = high_resolution_clock::now();
    cout << "\nTSP Held-Karp Cost: " << tspCost << endl;
    cout << "Time: " << duration_cast<microseconds>(end - start).count() << " µs\n";

    return 0;
}
