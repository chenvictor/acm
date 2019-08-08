// g      -> the graph
// SCC[u] <- the scc node u belongs to in reverse topo order [0,1,...num)
// num    <- the number of SCCs
void getSCC(Graph& g, VI& SCC, int& num) {
  VI low(g.N()), vis(g.N()); SCC.assign(g.N(), -1); stack<int> verts; int time = num = 0;
  function<void(int)> helper = [&](int u) { low[u] = vis[u] = ++time; verts.push(u);
    for (int v : g.getAdjNode(u)) { if (!vis[v]) helper(v);; if (SCC[v] == -1) low[u] = min(low[u], low[v]); }
    if (vis[u] <= low[u]) { int v; do { v = verts.top(); verts.pop(); SCC[v] = num; } while (v != u); ++num; } };
  forx(i, g.N()) if (!vis[i]) helper(i);
}
