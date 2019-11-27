template <class T, class Compare = greater<T>>
class PQ { Compare cmp; VI c; vector<pair<int, T>> km;
  inline int& elem(int i) { return c[i-1]; }
  inline int& idx(int i) { return km[i].ff; }
  inline T& pri(int i) { return km[i].ss; }
  inline bool swp(int i, int j) {
    int &x = elem(i), &y = elem(j); if (cmp(pri(x), pri(y))) return false;
    swap(x, y), idx(x) = i, idx(y) = j; return true; }
  void h_up(int i) { for (int p = i/2; i > 1 && swp(p, i); i = p, p/=2); }
  void h_dn(int i) { for (int ch = i*2; ch <= c.size(); i = ch, ch*=2) {
    if (ch < c.size() && cmp(pri(elem(ch|1)), pri(elem(ch)))) { ch |= 1; }
    if (!swp(i, ch)) break; } }
  public: PQ(int n) : km(n) { c.reserve(n); }
  pair<int, T> top() { int i = c.at(0); return {i,pri(i)}; }
  bool empty() const { return c.empty(); }
  size_t size() const { return c.size(); }
  void push(int key, const T& priority) {
    bool go_up = cmp(priority, pri(key)); int& i = idx(key); pri(key) = priority;
    if (i) go_up ? h_up(i) : h_dn(i); else c.push_back(key), h_up(i = c.size()); }
  void pop() { swp(c.size(), 1); idx(c.back()) = 0; c.pop_back(); h_dn(1); }
};
