/**
 * Calculates SCCs, numbered in reverse topological order
 * @returns {c: i => ssc id, # components}
 * adapted from KACTL
 **/
template <class G>
pair<vi,int> ssc(const G& g) {
  int n=sz(g),t=0,nc=0,x;
  vi c(n,-1),l(n),z; vi vs; // optional, set of vertices in component
  function<int(int)> dfs = [&](int v) {
    int lo=l[v]=++t; z.push_back(v);
    for (int u:g[v]) if (c[u]<0)
      lo=min(lo, l[u] ?: dfs(u));
    if (lo==l[v]) {
      do {
        x = z.back(); z.pop_back();
        c[x] = nc;
        vs.push_back(x); // optional
      } while (x != v);
      // optional, do something with vs
      vs.clear(); // optional
      nc++;
    }
    return l[v]=lo;
  };
  rep(i,0,n) if (c[i]<0) dfs(i);
  return {c,nc};
}
