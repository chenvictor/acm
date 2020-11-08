template <typename T> class PXSum {
  vector<T> d; public: PXSum() : d(1) { }
  template <class It> void build(It begin, It end) { d.resize(1); while (begin != end) push(*begin++); }
  void push(T val) { d.push_back(val + d.back()); }
  // sum[l, r)
  T query(int l, int r) const { return d[r] - d[l]; }
};
