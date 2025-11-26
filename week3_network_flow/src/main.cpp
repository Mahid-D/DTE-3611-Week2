#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

// ------------------- Graph Definitions -------------------
struct Edge {
  int from, to, capacity, flow;
};

class Graph {
public:
  int n;
  std::vector<std::vector<int>

              >
      adj;
  std::vector<Edge> edges;

  Graph(int nodes) : n(nodes), adj(nodes) {}

  void add_edge(int from, int to, int capacity) {
    Edge e1 = {from, to, capacity, 0};
    Edge e2 = {to, from, 0, 0}; // reverse edge
    adj[from].push_back(edges.size());
    edges.push_back(e1);
    adj[to].push_back(edges.size());
    edges.push_back(e2);
  }
};

// ------------------- Ford-Fulkerson -------------------
int dfs(Graph &g, int v, int t, int f, std::vector<bool> &visited) {
  if (v == t)
    return f;
  visited[v] = true;
  for (int id : g.adj[v]) {
    Edge &e = g.edges[id];
    if (!visited[e.to] && e.capacity > e.flow) {
      int pushed = dfs(g, e.to, t, std::min(f, e.capacity - e.flow), visited);
      if (pushed > 0) {
        e.flow += pushed;
        g.edges[id ^ 1].flow -= pushed;
        return pushed;
      }
    }
  }
  return 0;
}

int ford_fulkerson(Graph &g, int s, int t) {
  int flow = 0;
  while (true) {
    std::vector<bool> visited(g.n, false);
    int pushed = dfs(g, s, t, std::numeric_limits<int>::max(), visited);
    if (pushed == 0)
      break;
    flow += pushed;
  }
  return flow;
}

// ------------------- Edmonds-Karp -------------------
int edmonds_karp(Graph &g, int s, int t) {
  int flow = 0;

  while (true) {
    std::vector<int> parent_edge(g.n, -1);
    std::queue<int> q;
    q.push(s);
    parent_edge[s] = -2;

    while (!q.empty() && parent_edge[t] == -1) {
      int u = q.front();
      q.pop();
      for (int id : g.adj[u]) {
        Edge &e = g.edges[id];
        if (parent_edge[e.to] == -1 && e.capacity > e.flow) {
          parent_edge[e.to] = id;
          q.push(e.to);
        }
      }
    }

    if (parent_edge[t] == -1)
      break;

    int pushed = std::numeric_limits<int>::max();
    for (int cur = t; cur != s;) {
      int id = parent_edge[cur];
      pushed = std::min(pushed, g.edges[id].capacity - g.edges[id].flow);
      cur = g.edges[id].from;
    }

    for (int cur = t; cur != s;) {
      int id = parent_edge[cur];
      g.edges[id].flow += pushed;
      g.edges[id ^ 1].flow -= pushed;
      cur = g.edges[id].from;
    }

    flow += pushed;
  }

  return flow;
}

// ------------------- Goldberg-Tarjan (Successive Shortest Path)
// -------------------
struct CostEdge {
  int from, to, capacity, flow, cost;
};

struct MinCostGraph {
  int n;
  std::vector<std::vector<int>

              >
      adj;
  std::vector<CostEdge> edges;

  MinCostGraph(int nodes) : n(nodes), adj(nodes) {}

  void add_edge(int from, int to, int capacity, int cost) {
    CostEdge e1 = {from, to, capacity, 0, cost};
    CostEdge e2 = {to, from, 0, 0, -cost};
    adj[from].push_back(edges.size());
    edges.push_back(e1);
    adj[to].push_back(edges.size());
    edges.push_back(e2);
  }
};

// Bellman-Ford to find shortest path
bool bellman_ford(MinCostGraph &g, int s, int t, std::vector<int> &parent,
                  std::vector<int> &parent_edge) {
  int n = g.n;
  std::vector<int> dist(n, std::numeric_limits<int>::max());
  dist[s] = 0;
  parent.assign(n, -1);
  parent_edge.assign(n, -1);

  for (int i = 0; i < n - 1; ++i) {
    for (int u = 0; u < n; ++u) {
      if (dist[u] == std::numeric_limits<int>::max())
        continue;
      for (int id : g.adj[u]) {
        CostEdge &e = g.edges[id];
        if (e.capacity > e.flow && dist[e.to] > dist[u] + e.cost) {
          dist[e.to] = dist[u] + e.cost;
          parent[e.to] = u;
          parent_edge[e.to] = id;
        }
      }
    }
  }

  return parent[t] != -1;
}

int goldberg_tarjan_min_cost(Graph &g_orig, int s, int t) {
  MinCostGraph g(g_orig.n);
  for (auto &e : g_orig.edges) {
    if (e.capacity > 0)
      g.add_edge(e.from, e.to, e.capacity, 1); // cost = 1 for each edge
  }

  int flow = 0;
  std::vector<int> parent, parent_edge;
  while (bellman_ford(g, s, t, parent, parent_edge)) {
    int pushed = std::numeric_limits<int>::max();
    for (int cur = t; cur != s; cur = parent[cur]) {
      int id = parent_edge[cur];
      pushed = std::min(pushed, g.edges[id].capacity - g.edges[id].flow);
    }

    for (int cur = t; cur != s; cur = parent[cur]) {
      int id = parent_edge[cur];
      g.edges[id].flow += pushed;
      g.edges[id ^ 1].flow -= pushed;
    }

    flow += pushed;
  }

  return flow;
}

// ------------------- Helper: Build Test Graph -------------------
Graph build_test_graph() {
  Graph g(4);
  g.add_edge(0, 1, 100);
  g.add_edge(1, 2, 50);
  g.add_edge(2, 3, 100);
  return g;
}

// ------------------- Main -------------------
int main() {
  Graph g1 = build_test_graph();
  int ff = ford_fulkerson(g1, 0, 3);
  std::cout << "Ford-Fulkerson max flow: " << ff << std::endl;

  Graph g2 = build_test_graph();
  int ek = edmonds_karp(g2, 0, 3);
  std::cout << "Edmonds-Karp max flow: " << ek << std::endl;

  Graph g3 = build_test_graph();
  int gt = goldberg_tarjan_min_cost(g3, 0, 3);
  std::cout << "Goldberg-Tarjan min-cost flow: " << gt << std::endl;

  return 0;
}
