template <int SZ>
struct HLD {
  int sz[SZ], in[SZ], nx[SZ], out[SZ], t;
  void build(Graph& g, int root=0) {
    t = 0;
    dfs_sz(g, root);
    dfs_hld(g, root);
  }
  void dfs_sz(Graph& g, int v, int p=-1) {
    sz[v] = 1;
    for (int &u : g[v]) {
      if (u == p) continue;
      dfs_sz(g,u,v);
      sz[v] += sz[u];
      if (sz[u] > sz[g[v][0]]) {
        swap(u, g[v][0]);
      }
    }
  }
  void dfs_hld(Graph& g, int v, int p=-1) {
    in[v] = t++;
    for (int u : g[v]) {
      if (u == p) continue;
      nx[u] = (u == g[v][0] ? nx[v] : v);
      dfs_hld(g,u,v);
    }
    out[v] = t;
  }
  // v is ancestor of u?
  bool is_ancestor(int v, int u) {
    return in[v] <= in[u] && out[v] >= out[u];
  }
};

