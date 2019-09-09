template <typename T> class PXSum {
  vector<T> data; public: PXSum() : data(1) { }
  template <typename F> void push(F val) { data.push_back(val + data.back()); }
  size_t size() const { return data.size()-1; }
  // val[i]
  T value(int i) const { return data[i+1] - data[i]; }
  // sum[l, r)
  T query(int l, int r) const { return (l == r) ? T(0) : (data[r] - data[l]); }
};
