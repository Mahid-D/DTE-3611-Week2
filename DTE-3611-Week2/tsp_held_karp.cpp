#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int tspHeldKarp(vector< vector<int> >& dist) {
    int n = dist.size();
    int N = 1 << n;
    vector< vector<int> > dp(N, vector<int>(n, INT_MAX / 2));
    dp[1][0] = 0;

    for (int mask = 1; mask < N; mask += 2) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u))) continue;
            for (int v = 0; v < n; ++v) {
                if (mask & (1 << v)) continue;
                dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v],
                                             dp[mask][u] + dist[u][v]);
            }
        }
    }

    int res = INT_MAX;
    for (int i = 1; i < n; ++i)
        res = min(res, dp[N - 1][i] + dist[i][0]);
    return res;
}
