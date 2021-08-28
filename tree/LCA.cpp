/**
 * LCA with binary jumping
 * Usage:
 *  1. LCA(#nodes)
 *  2. build(graph [, root])
 *  3. lca(u, v)
 */
struct LCA {
  vi d; // depth
  vector<vi> bin;
  inline int anc(int v, int k) {
    return (k < sz(bin[v])) ? bin[v][k] : -1;
  }
  LCA(int n) : d(n), bin(n) { }
  void build(const vector<vi>& g, int u = 0, int p = -1) {
    for (int v : g[u]) {
      if (v == p) continue;
      add_node(v, u);
    }
  }
  // Add 'v' as a child of 'p'
  void add_node(int v, int p) {
    d[v] = d[p]+1;
    bin[v].push_back(p);
    for (int k = 0; anc(p, k) != -1; ++k)
      bin[v].push_back(p = anc(p, k));
  }
  int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    for (int i=0, l=d[u]-d[v]; l; ++i, l >>= 1) {
      if (l & 1) u = anc(u, i);
    }
    if (u == v) return u;
    for (int j = sz(bin[v]); j--;)
      if (anc(u, j) != anc(v, j)) {
        u = anc(u, j);
        v = anc(v, j);
      }
    return anc(u, 0);
  }
};

