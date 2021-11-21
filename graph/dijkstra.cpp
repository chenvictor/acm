// Single Source Shortest Path, no negative weights
// s = source node
template <typename T, typename T2=T>
vector<T2> dijkstra(const vector<vector<pair<int,T>>>& adj, int s=0) {
  using V = pair<T2,int>; vector<T2> res(sz(adj), -1); vector<bool> vis(sz(adj));
  heap<V,greater<V>> pq; pq.emplace(0, s);
  while(pq.size()) {
    auto [d, v] = pq.top(); pq.pop();
    if (vis[v]) continue;
    vis[v] = 1;
    res[v] = d;
    for (auto [u, e] : adj[v]) {
      pq.emplace(d+e,u);
    }
  }
  return res;
}

