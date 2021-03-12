// Single Source Shortest Path w/ negative weights
// neg set to true if neg cycle exists
vl bFord(const vector<pii>& g, int s, bool& neg) {
  const int sz = g.size();
  vl d(sz, LINF); d[s] = 0;
  rep(i,1,n) rep(u,0,sz) {
    if (d[u] == LINF) continue;
    for (pii& e : g[u]) {
      int v,w; tie(v,w) = e;
      d[v] = min(d[v], d[u] + w);
    }
  }
  rep(u,0,sz) {
    if (d[u] == LINF) continue;
    for (pii& e : g[u]) {
      int v,w; tie(v,w) = e;
      if (d[v] > d[u] + w) {
        neg = 1; return d;
      }
    }
  }
  return d;
}

