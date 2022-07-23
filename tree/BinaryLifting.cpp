/**
 * Binary Lifting
 **/
template <int K, int N=1<<K>
struct BinaryLifting {
  int dep[N], bin[N][K];
  int sum[N][K]; // optional, path sum queries
  void init(int sz, int root) {
    fill(bin[0], bin[sz], -1);
    dep[root] = 0;
    sum[root][0] = 0; // optional
  }
  void add_leaf(int p, int v, int w) {
    dep[v] = dep[p]+1;
    for(int k=0; p != -1; p=bin[p][k++]) {
      bin[v][k] = p;
      sum[v][k] = w; w += sum[p][k]; // optional
    };
  }
  int up(int u, int d) {
    rep(i,0,K) if (d>>i&1) {
      u = bin[u][i];
    }
    return u;
  }
  // optional: path up query
  int sum_up(int u, int d) {
    int res=0;
    rep(i,0,K) if (d>>i&1) {
      res += sum[u][i];
      u = bin[u][i];
    }
    return res;
  }
  int operator()(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    u = up(u,dep[u]-dep[v]);
    if (u == v) return u;
    for (int j=K;j--;)
      if (bin[u][j] != bin[v][j]) {
        u = bin[u][j];
        v = bin[v][j];
      }
    return bin[u][0];
  }
};

