class Graph {
  vector<VI> adj; public: Graph(int n=0) : adj(n) { }
  void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
  const VI& operator[](int u) const { return adj[u]; }
};
