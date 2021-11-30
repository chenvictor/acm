template <size_t K>
struct LCA {
  constexpr static int N = 1<<K;
  int depth[N], bin[N][K];
  LCA() { memset(bin,-1,sizeof bin); }
  // Add 'v' as a child of 'p'
  void add_node(int v, int p) {
    depth[v] = depth[p]+1;
    int *b = bin[v];
    *b++ = p;
    for (int k = 0; bin[p][k] != -1; ++k)
      *b++ = p = bin[p][k];
  }
  int up(int u, int d) {
    for (int i=0; d; ++i,d/=2) {
      if (d&1) u = bin[u][i];
    }
    return u;
  }
  int operator()(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    u = up(u,depth[u]-depth[v]);
    if (u == v) return u;
    for (int j=K;j--;)
      if (bin[u][j] != bin[v][j]) {
        u = bin[u][j];
        v = bin[v][j];
      }
    return bin[u][0];
  }
};

