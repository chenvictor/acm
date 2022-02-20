/**
 * Bipartite matching in O(VE)
 * g: left side neighbors
 * n: right side size
 * returns a mapping of right node => left node, or -1 if unmatched
 * source: KACTL
 **/
template <class G>
vi dfs_matching(const G& g, int n) {
  vi btoa(n,-1); vector<bool> vis(n);
  function<bool(int)> dfs = [&](int j) {
    if (btoa[j] == -1) return 1;
    vis[j] = 1; int di = btoa[j];
    for (int e:g[di]) if(!vis[e] && dfs(e)) return btoa[e]=di,1;
    return 0;
  };
  rep(i,0,sz(g)) {
    trace(i);
    fill(all(vis), 0);
    for(int j:g[i]) if(dfs(j)) {
      btoa[j] = i; break;
    }
  }
  return btoa;
}

