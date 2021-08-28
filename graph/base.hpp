struct Graph: public vector<vi> {
  void add_edge(int u, int v) {
    (*this)[u].push_back(v);
    (*this)[v].push_back(u);
  }
};

