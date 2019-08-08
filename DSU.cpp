class DSU { VI p; int c; public: DSU (int n) : p(n, -1), c(n) { }
  // Get representative of x
  int find(int x) { return (p[x] < 0) ? x : p[x] = find(p[x]); }
  // Get size of set containg x
  int size(int x) { return -p[find(x)]; }
  // Get # of disjoint sets
  int count() { return c; }
  // Joins sets containing x, y
  void join(int x, int y) { if ((x = find(x)) == (y = find(y))) return; if (p[x] < p[y]) swap(x, y); p[y] += p[x]; p[x] = y; c--; }
};
