template <bool UNDIRECTED=true>
struct EulerWalk {
  // Source: KACTL, refactor needed
  struct V {
    vector<pii> outs; // (dest, edge index)
    int indeg = 0;
  };
  vector<V> nodes;
  int nedges = 0;
  EulerWalk(int n): nodes(n) {}
  void add_edge(int u, int v) {
    nodes[u].outs.emplace_back(v, nedges);
    ++nodes[v].indeg;
    if (UNDIRECTED) {
      nodes[v].outs.emplace_back(u, nedges);
      ++nodes[u].indeg;
    }
    ++nedges;
  }
  vi solve(int src) {
    int c = 0;
    for (auto& n : nodes) c += abs(n.indeg - sz(n.outs));
    if (c > 2) return {};
    vector<vector<pii>::iterator> its;
    for (auto& n : nodes)
      its.push_back(n.outs.begin());
    vector<bool> eu(nedges);
    vi ret, s = {src};
    while(!s.empty()) {
      int x = s.back();
      auto& it = its[x], end = nodes[x].outs.end();
      while(it != end && eu[it->second]) ++it;
      if(it == end) { ret.push_back(x); s.pop_back(); }
      else { s.push_back(it->first); eu[it->second] = true; }
    }
    if(sz(ret) != nedges+1)
      ret.clear(); // No Eulerian cycles/paths.
    // else, non-cycle if ret.front() != ret.back()
    reverse(all(ret));
    return ret;
  }
};

