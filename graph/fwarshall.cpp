// All-pairs shortest path
// d - distances
// wIdx - index to retrieve edge weights from data array
// returns true if negative weight cycle exists
bool fWarshall(Graph& graph, vector<VL>& d, int wIdx=0) { d.assign(graph.N(), VL(graph.N(), LINF));
  forx (u, graph.N()) { d[u][u] = 0; for (Edge e : graph.getAdjEdge(u)) d[u][e.nodeFrom(u)] = e[wIdx]; }
  forx (k, graph.N()) forx (i, graph.N()) forx (j, graph.N()) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  forx (i, graph.N()) if (d[i][i] < 0) return true;; return false;
}
