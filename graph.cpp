// INITIALIZATION:
// Graph(N,D)
//    constructs a graph with 'N' nodes and Edge dimension 'D', ie. edges can hold 'D' long long data values
// add_edge(u,v, [undirected], [data])
//    adds an edge from 'u' to 'v' (undirected by default) and with the optionally given intial edge data values
//
// Edge:
//   operator[i] returns the ith data value associated with this edge (by reference)
//   nodeFrom(f) returns the node that would be reached from node 'f' via this edge.
// 
// USAGE:
// Graph algorithms will take in a graph, relevant inputs (eg. source and target node) as well as data indices. eg. wIdx, cIdx
// These indicate which index the edge data is stored in. eg. wIdx=0 means edge weights will be accessed using Edge[0];
struct Graph {
  class Edge { Graph* owner; const int idx; public: const int u, v; Edge() : owner(0), idx(-1), u(-1), v(-1) { } Edge(Graph* owner, int idx, int u, int v) :
    owner(owner), idx(idx), u(u), v(v) { } ll& operator[](int i) { return owner->getEdgeData(idx, i); }
    int nodeFrom(int f) const { return f^u^v; } }; TD vector<Edge> VE;
  class EdgeIt { VI* adj; VE* edge_list; public: EdgeIt(VI* adj, VE* edge_list) : adj(adj), edge_list(edge_list) {}
    class Iterator { VI* adj; VE* edge_list; int idx; public: Iterator(VI* adj, VE* edge_list, int idx=0) : adj(adj), edge_list(edge_list), idx(idx) {}
    bool operator == (const Iterator& b) const { return adj == b.adj && idx == b.idx; } bool operator != (const Iterator& b) const { return !(*this == b); }
    Iterator operator ++() { auto temp = *this; ++idx; return temp; } Edge& operator *() { return (*edge_list)[(*adj)[idx]]; } };
    Iterator begin() const { return Iterator(adj, edge_list); } Iterator end() const { return Iterator(adj, edge_list, adj->size()); } };
  class NodeIt { EdgeIt it; int u; public: NodeIt(VI* adj, VE* edge_list, int u) : it(adj, edge_list), u(u) {} class Iterator { EdgeIt::Iterator iter; int u;
    public: Iterator(EdgeIt::Iterator iter, int u) : iter(iter), u(u) { } bool operator == (const Iterator& b) const { return iter == b.iter && u == b.u; }
    bool operator != (const Iterator& b) const { return !(*this == b); } Iterator operator ++() { auto temp = *this; ++iter; return temp; }
    int operator *() { return (*iter).nodeFrom(u); } }; Iterator begin() const { return Iterator(it.begin(), u); }
    Iterator end() const { return Iterator(it.end(), u); } };

  Graph(int N, int D=0) : edge_list(0), adj_list(N), edge_data(0), dimens(D) { edge_list.reserve(N); edge_data.reserve(D*N); }
  Edge& add_edge(int u, int v, bool undirected=true, initializer_list<ll> data = { }) {
    int i = edge_list.size();
    adj_list[u].push_back(i);
    if (undirected)
      adj_list[v].push_back(i);
    edge_list.emplace_back(this, i, u, v);
    int j = edge_data.size();
    edge_data.resize(j+dimens);
    for (ll val : data) edge_data[j++] = val;
    return edge_list.back();
  }
  ll& getEdgeData(int eIdx, int dIdx) { static ll dummy; return (dIdx < 0 || dIdx >= dimens) ? dummy : edge_data[eIdx*dimens + dIdx]; }
  // Number of nodes and edges, and dimension of each edge respectively
  ll N() const { return adj_list.size(); }
  ll M() const { return edge_list.size(); }
  ll D() const { return dimens; }
  // AdjVec is the edge indices
  VI& getAdjVec(int u) { return adj_list[u]; }
  EdgeIt getAdjEdge(int u) { return EdgeIt(&adj_list[u], &edge_list); }
  NodeIt getAdjNode(int u) { return NodeIt(&adj_list[u], &edge_list, u); }
  VE& edges() { return edge_list; }
  // Degree of a node (for directed graph, out degree)
  int degree(int u) const { return adj_list[u].size(); }
  Edge& getEdge(int i) { return edge_list[i]; }
  Edge& operator[](int i) { return edge_list[i]; }
  // returns true if u's only neighbor is p
  bool isLeaf(int u, int p) const { return adj_list[u].size() == 1 && edge_list[adj_list[u][0]].nodeFrom(u) == p; }
private: VE edge_list; vector<VI> adj_list; VL edge_data; const int dimens; }; typedef Graph::Edge Edge;

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

// Finds the diameter of a tree graph
// @param g     the graph
// @param i     the node to use as the root
int tree_diameter(Graph& g, int i = 0) {
  // ff is the diameter so far (which could be the branch)
  // ss is the longest branch
  function<pii(int,int)> helper = [&](int u, int p) {
    if (g.isLeaf(u,p)) return make_pair(0,0);
    int diam = 0; // biggest diameter so far
    int best = 0; // biggest branch so far
    for (int v : g.getAdjNode(u)) {
      if (v == p) continue;
      pii temp = helper(v, u);
      diam = max(diam, temp.ff);
      diam = max(diam, best + temp.ss + 1);
      best = max(best, temp.ss + 1);
    }
    return make_pair(diam, best);
  };
  return helper(i, -1).ff;
}

// Single Source Shortest Path, no negative weights
// s = source node
// d = distances
void dijkstra(Graph& graph, int s, VL& d, int wIdx=0) {
  d.assign(graph.N(), LINF); d[s] = 0; VB seen(graph.N(), false); priority_queue<pii, vector<pii>, less<pii>> pq;
  pq.push({0, s}); int v; while(!pq.empty()) { s = pq.top().second; pq.pop(); if (seen[s]) continue;; seen[s] = true;
  for (Edge e : graph.getAdjEdge(s)) { v = e.nodeFrom(s); if (d[v] > d[s] + e[wIdx]) { d[v] = d[s] + e[wIdx]; pq.push({d[v], v}); } } }
}

// All-pairs shortest path
// d - distances
// wIdx - index to retrieve edge weights from data array
// returns true if negative weight cycle exists
bool fWarshall(Graph& graph, vector<VL>& d, int wIdx=0) { d.assign(graph.N(), VL(graph.N(), LINF));
  forx (u, graph.N()) { d[u][u] = 0; for (Edge e : graph.getAdjEdge(u)) d[u][e.nodeFrom(u)] = e[wIdx]; }
  forx (k, graph.N()) forx (i, graph.N()) forx (j, graph.N()) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  forx (i, graph.N()) if (d[i][i] < 0) return true;; return false;
}

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

void topoSort (Graph& graph, VI& ans)  {
  VB visited(graph.N(), false); stack<int> st;
  function<void(int u)> helper = [&](int u) { visited[u] = true; for (int v : graph.getAdjNode(u)) if (!visited[v]) helper(v); st.push(u); };
  forx (i, graph.N()) { if (!visited[i]) helper(i); } ans.resize(graph.N()); int i = 0; while (!st.empty()) { ans[i++] = st.top(); st.pop(); }
}
