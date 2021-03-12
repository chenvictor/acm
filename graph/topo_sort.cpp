vi topo(const vector<vi>& g)  {
  vi ans; vector<bool> vis(g.size());
  function<void(int)> helper = [&](int u) {
    vis[u] = 1; for (int v : g[u]) if (!vis[v]) helper(v); ans.push_back(u);
  };
  rep(i,0,g.size()) { if (!vis[i]) helper(i); }
  reverse(all(ans));
  return ans;
}

