class DSU {
  vector<int> p; int c;
  public:
    DSU (int n) : p(n, -1), c(n) { }
    int find(int x) { return (p[x] < 0) ? x : p[x] = find(p[x]); }
    ll size(int x) { return -p[find(x)]; }
    int count() { return c; }
    void join(int x, int y) { if ((x = find(x)) == (y = find(y))) return;; if (p[x] < p[y]) swap(x, y); p[y] += p[x]; p[x] = y; c--; }
};
