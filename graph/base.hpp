template <class T=int, class p=vector<vector<T>>>
struct Graph: public p {
  using p::p;
  template <class...Args> void add_edge(int u, int v, Args... args) {
    SELF[u].emplace_back(v, args...);
    SELF[v].emplace_back(u, args...);
  }
};

