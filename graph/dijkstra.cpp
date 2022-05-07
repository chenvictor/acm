// Single Source Shortest Path, no negative weights
// s = source node
template <typename Tw, typename Td=Tw>
vector<Td> dijkstra(const vector<vector<pair<int,Tw>>>& adj, vi src) {
  using V = pair<Td,int>;
  vector<Td> ans(sz(adj), -1);
  heap<V,greater<V>> pq;
  for(int s : src) pq.emplace(0,s);
  while(sz(pq)) {
    auto [d, v] = pq.top(); pq.pop();
    if (ans[v] != -1) continue;
    ans[v] = d;
    for (auto [u, e] : adj[v])
      pq.emplace(d+e,u);
  }
  return ans;
}

