/**
 * HLD: decompose paths into log segments, and subtree into segment
 * https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 **/
template <size_t N, bool EDGE_VAL> struct HLD {
  vi adj[N];
  array<int,N> p,sz,in,nx,dep; int t;
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void build(int r) {
    p[r] = dep[r] = t = 0;
    dfs_sz(r);
    nx[r] = r;
    dfs_hld(r);
  }
  int dfs_sz(int v) {
    sz[v] = 1;
    for (int& u : adj[v]) {
      p[u] = v;
      dep[u] = dep[v]+1;
      adj[u].erase(find(all(adj[u]), v));
      sz[v] += dfs_sz(u);
      if (sz[u] > sz[adj[v][0]])
        swap(u, adj[v][0]);
    }
    return sz[v];
  }
  void dfs_hld(int v) {
    in[v] = t++;
    rep(i,0,sz(adj[v])) {
      int u=adj[v][i];
      nx[u] = i?u:nx[v];
      dfs_hld(u);
    }
  }
  // v is ancestor of u?
  bool is_ancestor(int v, int u) {
    return in[v] <= in[u] && in[v]+sz[v] >= in[u]+sz[u];
  }
  int lca(int a, int b) {
    for(;nx[a] != nx[b]; b=p[nx[b]]) {
      if(dep[nx[a]] > dep[nx[b]]) swap(a,b);
    }
    if(dep[a] > dep[b]) swap(a,b);
    return a;
  }
  /**
   * calls f on [l,r) segment of subtree/segments of path
   **/
  template <class F>
  void apply_path(int a, int b, F f) {
    for(;nx[a] != nx[b]; b=p[nx[b]]) {
      if(dep[nx[a]] > dep[nx[b]]) swap(a,b);
      f(in[nx[b]],in[b]+1);
    }
    if(dep[a] > dep[b]) swap(a,b);
    f(in[a]+EDGE_VAL, in[b]+1);
  }
  template <class F>
  void apply_subtree(int v, F f) {
    f(in[v]+EDGE_VAL, in[v]+sz[v]);
  }
};

