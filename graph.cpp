#include <bits/stdc++.h>
using namespace std;
#define CM ,
#define TD(a,b) typedef a b
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9, PI = acos(-1);
#define forx(i,n) for(ll i = 0; i < (ll) (n); ++i)
#define ff first
#define ss second

class Edge {
  ll d[1]; public: int u, v; Edge() { }
  Edge(int u, int v) : u(u), v(v) { }
  ll& operator[](int i) { return d[i]; }
  int operator()(int f) { return f ^ u ^ v; }
};
class Graph {
  public:
  private: 
    vector<Edge> edge_list; //edges
    vector<VI> adj_list; //adj_list[i] contains the indices of the edges
  public:
    Graph(int N) : edge_list(0), adj_list(N) {}
    // Add an edge to the graph, 'undirected' will add the edge both ways
    void addEdge(Edge& e, bool undirected=true) {
      adj_list[e.u].push_back(edge_list.size());
      if (undirected)
        adj_list[e.v].push_back(edge_list.size());
      edge_list.emplace_back(e);
    }
    ll N() { return adj_list.size(); }
    ll M() { return edge_list.size(); }
    Edge& operator[](int i) { return edge_list[i]; }
    VI& getEdges(int u) { return adj_list[u]; }
};

// Single Source Shortest Path, no negative weights
// s = source node
// d = 
void dijkstra(Graph& graph, int s, VL& d, int wIdx=0) {
  d.resize(graph.N(), LINF);
  d[s] = 0;
  VB seen(graph.N(), false);
  priority_queue<pii, vector<pii>, less<pii>> pq;
  pq.push({0, s});
  int v; Edge e;
  while(!pq.empty()) {
    s = pq.top().second;
    pq.pop();
    if (seen[s]) continue;
    seen[s] = true;
    for (const int& i : graph.getEdges(s)) {
      e = graph[i];
      v = e(s);
      if (d[v] > d[s] + e[wIdx]) {
        d[v] = d[s] + e[wIdx];
        pq.push({d[v], v});
      }
    }
  }
}

// All-pairs shortest path
// d - distances
// wIdx - index to retrieve edge weights from data array
// returns true if negative weight cycle exists
bool fWarshall(Graph& graph, vector<VL>& d, int wIdx=0) {
  d.resize(graph.N(), VL(graph.N(), LINF));
  int v; Edge e;
  forx (u, graph.N()) {
    d[u][u] = 0; // dist to self is 0
    for (const int& i : graph.getEdges(u)) {
      e = graph[i];
      v = e(u);
      d[u][v] = e[wIdx];
    }
  }
  forx (k, graph.N())
    forx (i, graph.N())
      forx (j, graph.N())
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  forx (i, graph.N())
    if (d[i][i] < 0) return true;
  return false;
}

// Single Source Shortest Path w/ negative weights
// s - source node
// d - distances
// wIdx - index to retrieve edge weights from
// returns true if negative weight cycle exists
bool bFord(Graph& graph, int s, VL& d, int wIdx=0) {
  d.resize(graph.N(), LINF);
  d[s] = 0; Edge e;
  forx (i, graph.N()) {
    forx (j, graph.M()) {
      e = graph[j];
      if (d[e.v] > d[e.u] + e[wIdx]) {
        if (i == graph.N() - 1) return true;
        d[e.v] = d[e.u] + e[wIdx];
      }
    }
  }
  return false;
}

void printV (VL& d) {
  forx(i, d.size()) {
    cout << " ";
    if (d[i] >= LINF) cout << "*";
    else cout << d[i];
  } cout << nl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  Graph graph(10);
  int wIdx = 0;
  Edge e(0, 1);
  e[wIdx] = 3;
  graph.addEdge(e);
  e.u = 1; e.v = 4; e[wIdx] = 2;
  graph.addEdge(e);
  e.u = 0; e.v = 4; e[wIdx] = 6;
  graph.addEdge(e);
  VL d;
  dijkstra(graph, 0, d, wIdx);
  cout << "dijkstra:" << nl;
  printV(d);
  d.clear();
  bFord(graph, 0, d, wIdx);
  cout << "bellman ford:" << nl;
  printV(d);
  vector<VL> d2;
  fWarshall(graph, d2, wIdx);
  cout << "floyd warshall:" << nl;
  forx (i, d2.size()) {
    printV(d2[i]);
  }
  return 0;
}
