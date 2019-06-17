#include <bits/stdc++.h>
using namespace std;
#define CM ,
#define TD(a,b) typedef a b
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9, PI = acos(-1);
#define forx(i,n) for(ll i = 0; i < (ll) (n); ++i)
#define ff first
#define ss second

struct Graph { 
  class Edge { int sz; union { ll* d; ll d0; };
    void dalloc(int s) { if (s == sz) return;; if (sz > 1) free(d);; if (s <= 1) d0 = 0; else d = (ll*) malloc(s*sizeof(*d)); sz = s; }
    public: int u, v; Edge() : sz(0), d(NULL) { } Edge(int u, int v, int s=0) : sz(0), d(NULL), u(u), v(v) { dalloc(s); if (sz > 1) fill(d, d+sz, 0ll); }
    ~Edge() { if (sz > 1) free(d); } Edge(const Edge& b) : sz(0) { *this = b; } Edge& operator =(const Edge& ref) {
    dalloc(ref.sz); u = ref.u; v = ref.v; if (sz <= 1) d0 = ref.d0; else copy(ref.d, ref.d+sz, d);; return *this; }
    ll& operator[](int i) { return (sz <= 1 ? d0 : d[i]); } int operator()(int f) const { return f ^ u ^ v; } }; typedef vector<Edge> VE;
  class EdgeIt { VI* adj; VE* edge_list; public: EdgeIt(VI* adj, VE* edge_list) : adj(adj), edge_list(edge_list) {}
    class Iterator { VI* adj; VE* edge_list; int idx; public: Iterator(VI* adj, VE* edge_list, int idx=0) : adj(adj), edge_list(edge_list), idx(idx) {}
    bool operator == (const Iterator& b) const { return adj == b.adj && idx == b.idx; } bool operator != (const Iterator& b) const { return !(*this == b); }
    Iterator operator ++() { auto temp = *this; idx++; return temp; } Edge& operator *() { return (*edge_list)[(*adj)[idx]]; } };
    Iterator begin() const { return Iterator(adj, edge_list); } Iterator end() const { return Iterator(adj, edge_list, adj->size()); } };
  class NodeIt { VI* adj; VE* edge_list; int u; public: NodeIt(VI* adj, VE* edge_list, int u) : adj(adj), edge_list(edge_list), u(u) {}
    class Iterator { VI* adj; VE* edge_list; int u,idx; public: Iterator(VI* adj, VE* edge_list, int u, int idx=0) : adj(adj), edge_list(edge_list), u(u), idx(idx) {}
    bool operator == (const Iterator& b) const { return adj == b.adj && idx == b.idx && u == b.u; } bool operator != (const Iterator& b) const { return !(*this == b); }
    Iterator operator ++() { auto temp = *this; idx++; return temp; } int operator *() { return (*edge_list)[(*adj)[idx]](u); } };
    Iterator begin() const { return Iterator(adj, edge_list, u); } Iterator end() const { return Iterator(adj, edge_list, u, adj->size()); } };
  Graph(int N, int D=0) : edge_list(0), adj_list(N), dimens(D) { edge_list.reserve(N); }
  int add_edge(int u, int v, bool undirected=true) { adj_list[u].push_back(edge_list.size()); if (undirected) adj_list[v].push_back(edge_list.size());
    edge_list.emplace_back(Edge(u, v, dimens)); return edge_list.size() - 1; }
  ll N() const { return adj_list.size(); } ll M() const { return edge_list.size(); } ll D() const { return dimens; }
  VI& getAdjVec(int u) { return adj_list[u]; }
  VE& edges() { return edge_list; } int out_degree(int u) { return adj_list[u].size(); }
  Edge& operator[](int i) { return edge_list[i]; } EdgeIt getAdjEdge(int u) { return EdgeIt(&adj_list[u], &edge_list); }
  NodeIt getAdjNode(int u) { return NodeIt(&adj_list[u], &edge_list, u); }
  // returns true if u's only neighbor is p
  bool isLeaf(int u, int p) const { return adj_list[u].size() == 1 && edge_list[adj_list[u][0]](u) == p; }
private: VE edge_list; vector<VI> adj_list; const int dimens; }; typedef Graph::Edge Edge;

// g      -> the graph
// SCC[u] <- the scc node u belongs to in reverse topo order (0,1,...num-1)
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
    //check leaf
    if (g.isLeaf(u,p)) {
      return make_pair(0,0);
    }
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
  for (Edge e : graph.getAdjEdge(s)) { v = e(s); if (d[v] > d[s] + e[wIdx]) { d[v] = d[s] + e[wIdx]; pq.push({d[v], v}); } } }
}

// All-pairs shortest path
// d - distances
// wIdx - index to retrieve edge weights from data array
// returns true if negative weight cycle exists
bool fWarshall(Graph& graph, vector<VL>& d, int wIdx=0) { d.assign(graph.N(), VL(graph.N(), LINF));
  forx (u, graph.N()) { d[u][u] = 0; for (Edge e : graph.getAdjEdge(u)) d[u][e(u)] = e[wIdx]; }
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

void printV (VL& d) {
  forx(i, d.size()) {
    cout << " ";
    if (d[i] >= LINF) cout << "*";
    else cout << d[i];
  } cout << nl;
}

int main() {
  //ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  
  Edge a(0, 1, 2);
  cout << a[0] << nl;
  cout << a[1] << nl;
  a[0] = 5;
  a[1] = -2;
  Edge b(a);
  function <void(void)> stat = [&](){
    cout << "a[0]=" << a[0] << nl;
    cout << "a[1]=" << a[1] << nl;
    cout << "b[0]=" << b[0] << nl;
    cout << "b[1]=" << b[1] << nl;
  };
  stat();
  b[1] = 3;
  a[0] = 999;
  stat();
  Edge c(0, 1, 5);
  c[0] = 999;
  c[1] = 993;
  c[4] = 121;
  cout << "c4=" << c[4] << nl;
  c = b;
  stat();
  cout << c[0] << " " << c[1] << nl;
  c = b;
  b = a;
  Edge d(c);
  d[0] = a[1];


  return 0;
}
