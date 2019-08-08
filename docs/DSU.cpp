class DSU {
  vector<int> p; // p[i] is the parent of elem 'i' if >= 0. Otherwise, if 'i' is the parent, it is the negative size of the set
  int c; //the number of disjoint sets
  public: DSU (int n) : p(n, -1), c(n) { }
  int find(int x) {
    //while x has a parent, go up, and apply path compression
    return (p[x] < 0) ? x : p[x] = find(p[x]);
  }
  int size(int x) { return -p[find(x)]; }
  int count() { return c; }
  void join(int x, int y) {
    if ((x = find(x)) == (y = find(y))) return;
    if (p[x] < p[y]) swap(x, y); //p[y] < p[x]
    // since they are negative sizes, set(x) is smaller than set(y),
    // merge set(x) onto set(y)
    p[y] += p[x]; // update set(y)'s size
    p[x] = y;     // point set(x) to set(y)
    c--;          // decrement the count of disjoint sets
  }
};
