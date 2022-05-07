template <class T=int, bool directed=0, class p=vector<vector<T>>>
struct Graph: public p {
  using p::p;
  template <class...Args> void add_edge(int u, int v, Args... args) {
    (*this)[u].emplace_back(v, args...);
    if (directed) return;
    (*this)[v].emplace_back(u, args...);
  }
};

