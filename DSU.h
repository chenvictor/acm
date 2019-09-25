class DSU {
  VI p; int c;
  public: DSU (int n);
  // Get representative of x
  int find(int x);
  // Get size of set containg x
  int size(int x);
  // Get # of disjoint sets
  int count();
  // Joins sets containing x, y
  void join(int x, int y);
};
