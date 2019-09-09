// Single Source Shortest Path w/ negative weights
// s - source node
// d - distances
// wIdx - index to retrieve edge weights from
// returns true if negative weight cycle exists
bool bFord(const Graph& graph, int s, VL& d, int wIdx=0) { d.assign(graph.N(), LINF); d[s] = 0;
  forx (i, graph.N() - 1) for (const Edge& e : graph.edges()) if (d[e.u] != LINF) d[e.v] = min(d[e.v], d[e.u] + e[wIdx]);
  for (const Edge& e : graph.edges()) { if (d[e.u] != LINF && d[e.v] > d[e.u] + e[wIdx]) return true; } return false; }

// Single Source/Target Shortest Path w/ negative weights
// s - source
// t - target
// wIdx - index to retrieve edge weights from
// returns min weight path from s to t if it exists. otherwise, LINF
ll bFordSingleTarget(const Graph& graph, int s, int t, int wIdx=0) { VL r(graph.N(), LINF), d(graph.N(), LINF); r[t] = d[s] = 0;
  forx(i, graph.N() - 1) for (const Edge& e : graph.edges()) {
    if (r[e.v] != LINF) r[e.u] = min(r[e.u], r[e.v] + e[wIdx]);
    if (d[e.u] != LINF) d[e.v] = min(d[e.v], d[e.u] + e[wIdx]); }
  for (const Edge& e : graph.edges()) { if (d[e.u] != LINF && d[e.v] > d[e.u] + e[wIdx] && r[e.u] != LINF) return LINF; } return d[t];
}
