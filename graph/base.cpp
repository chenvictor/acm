struct Graph {
  class Edge { Graph* owner; const int idx; public: const int u, v; Edge() : owner(0), idx(-1), u(-1), v(-1) { } Edge(Graph* owner, int idx, int u, int v) :
  owner(owner), idx(idx), u(u), v(v) { } ll& operator[](int i) { return owner->getEdgeData(idx, i); } ll operator[](int i) const { return owner->getEdgeData(idx, i); }
  int nodeFrom(int f) const { return f^u^v; } }; TD vector<Edge> VE;
  class EdgeIt { VI* adj; VE* edge_list; public: EdgeIt(VI* adj, VE* edge_list) : adj(adj), edge_list(edge_list) {}
  class Iterator { VI* adj; VE* edge_list; int idx; public: Iterator(VI* adj, VE* edge_list, int idx=0) : adj(adj), edge_list(edge_list), idx(idx) {}
  bool operator == (const Iterator& b) const { return adj == b.adj && idx == b.idx; } bool operator != (const Iterator& b) const { return !(*this == b); }
  Iterator operator ++() { auto temp = *this; ++idx; return temp; } Edge& operator *() { return (*edge_list)[(*adj)[idx]]; } };
  Iterator begin() const { return Iterator(adj, edge_list); } Iterator end() const { return Iterator(adj, edge_list, adj->size()); } };
  class NodeIt { EdgeIt it; int u; public: NodeIt(VI* adj, VE* edge_list, int u) : it(adj, edge_list), u(u) {} class Iterator { EdgeIt::Iterator iter; int u;
  public: Iterator(EdgeIt::Iterator iter, int u) : iter(iter), u(u) { } bool operator == (const Iterator& b) const { return iter == b.iter && u == b.u; }
  bool operator != (const Iterator& b) const { return !(*this == b); } Iterator operator ++() { auto temp = *this; ++iter; return temp; }
  int operator *() { return (*iter).nodeFrom(u); } }; Iterator begin() const { return Iterator(it.begin(), u); } Iterator end() const { return Iterator(it.end(), u); } };
  Graph(int N, int D=0) : edge_list(0), adj_list(N), edge_data(0), dimens(D) { edge_list.reserve(N); edge_data.reserve(D*N); }
  Edge& add_edge(int u, int v, bool undirected=true, initializer_list<ll> data = { }) { int i = edge_list.size(); adj_list[u].push_back(i);
  if (undirected) { adj_list[v].push_back(i);} edge_list.emplace_back(this, i, u, v); i = edge_data.size(); edge_data.resize(i+dimens); for (ll val : data)
  { edge_data[i++] = val; } return edge_list.back(); } ll& getEdgeData(int eIdx, int dIdx) { static ll dummy; return (dIdx < 0 || dIdx >= dimens)
      ? dummy : edge_data[eIdx*dimens + dIdx]; } ll N() const { return adj_list.size(); } ll M() const { return edge_list.size(); } ll D() const { return dimens; }
  const VI& getAdjVec(int u) const { return adj_list[u]; } EdgeIt getAdjEdge(int u) { return EdgeIt(&adj_list[u], &edge_list); }
  NodeIt getAdjNode(int u) { return NodeIt(&adj_list[u], &edge_list, u); } const VE& edges() const { return edge_list; }
  int degree(int u) const { return adj_list[u].size(); } Edge& getEdge(int i) { return edge_list[i]; } Edge& operator[](int i) { return edge_list[i]; }
  Graph transpose() const { Graph ret(N(), D()); for (const Edge& e : edges()) { Edge& temp = ret.add_edge(e.v, e.u, false); forx(i,D()) temp[i] = e[i]; } return ret; }
private: VE edge_list; vector<VI> adj_list; VL edge_data; const int dimens; }; typedef Graph::Edge Edge;
