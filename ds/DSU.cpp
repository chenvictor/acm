struct DSU {
  vi p;
  DSU (int n) : p(n, -1) { }
  int find(int x) {
    return (p[x] < 0) ? x : p[x] = find(p[x]);
  }
  int size(int x) { return -p[find(x)]; }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  bool join(int x, int y) {
    if ((x = find(x)) == (y = find(y))) return 0;
    if (p[x] < p[y]) swap(x, y);
    p[y] += p[x]; p[x] = y;
    return 1;
  }
};

