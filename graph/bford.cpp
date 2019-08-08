// Single Source Shortest Path w/ negative weights
// s - source node
// d - distances
// wIdx - index to retrieve edge weights from
// returns true if negative weight cycle exists
bool bFord(Graph& graph, int s, VL& d, int wIdx=0) {
  d.assign(graph.N(), LINF); d[s] = 0; forx (i, graph.N()) for (Edge e : graph.edges())
  if (d[e.v] > d[e.u] + e[wIdx]) { if (i == graph.N() - 1) return true;; d[e.v] = d[e.u] + e[wIdx]; }
  return false;
}
