/**
 * Single Source Shortest Path w/ negative weights
 * returns {dist, neg_cycle?}
 * if neg_cycle? => at least some node v in each cycle has dist[v] = ~LINF
 **/
pair<vl,bool> bellman_ford(const vector<vector<pii>>& g, int s) {
  const int n = sz(g);
  bool neg=0;
  vl d(n, LINF); d[s] = 0;
  rep(i,1,n)
  rep(u,0,n) {
    if (d[u] == LINF) continue;
    for (auto [v,w] : g[u]) {
      d[v] = min(d[v], d[u] + w);
    }
  }
  rep(u,0,n) {
    if (d[u] == LINF) continue;
    for (auto [v,w] : g[u]) {
      if (d[v] > d[u] + w) {
        d[v] = ~LINF;
        neg = 1;
      }
    }
  }
  return {d,neg};
}

