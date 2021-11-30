template <size_t N=0, class T=int>
struct Graph: public arr<T,N> {
  template <bool directed=0, class...Args> void add_edge(int u, int v, Args... args) {
    (*this)[u].emplace_back(v, args...);
    if (directed) return;
    (*this)[v].emplace_back(u, args...);
  }
};

