namespace bridges {
  // Find bridges in a graph. Handles dup edges
  // If graph is disconnected, call dfs(u) once for each node
  // 1. add edges
  // 2. dfs(1)
  // 3. out contains 1 based indices of bridge edges (may not be in order of insertion)
  const int N = 1e4+5;
  vector<pii> adj[N]; vi out;
  int n = 0; // # edges
  void add_edge(int u, int v) {
    adj[u].emplace_back(v, ++n);
    adj[v].emplace_back(u, n);
  }
  int low[N], tin[N], t=1;
  void dfs(int u = 1, int i=0) {
    if (tin[u]) return;
    tin[u] = low[u] = t++;
    for (auto e : adj[u]) {
      int to, x; tie(to,x) = e;
      if (x == i) continue;
      if (tin[to]) { low[u] = min(low[u], tin[to]); } else {
        dfs(to, x); low[u] = min(low[u], low[to]);
        if (low[to] > tin[u]) out.push_back(x);
      }
    }
  }
}

