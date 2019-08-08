// Single Source Shortest Path, no negative weights
// s = source node
// d = distances
void dijkstra(Graph& graph, int s, VL& d, int wIdx=0) {
  d.assign(graph.N(), LINF); d[s] = 0; VB seen(graph.N(), false); priority_queue<pii, vector<pii>, less<pii>> pq;
  pq.push({0, s}); int v; while(!pq.empty()) { s = pq.top().second; pq.pop(); if (seen[s]) continue;; seen[s] = true;
  for (Edge e : graph.getAdjEdge(s)) { v = e.nodeFrom(s); if (d[v] > d[s] + e[wIdx]) { d[v] = d[s] + e[wIdx]; pq.push({d[v], v}); } } }
}
