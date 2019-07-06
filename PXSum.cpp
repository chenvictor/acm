template <typename T>
class PXSum {
  // Prefix Sum: push all data first, then call queries
  vector<T> data; public: PXSum() { }
  template <typename F>
    PXSum(vector<F>& d) { const int n = d.size(); data.resize(n); if (n) { data[0] = d[0]; for (int i = 1; i < n; ++i) { data[i] = d[i] + data[i-1]; } } }
  template <typename F>
    void push(F val) { data.push_back(data.size() ? val + data.back() : val); }
  size_t size() const { return data.size(); }
  // val[i]
  T query(int i) const { return (i ? data[i] - data[i-1] : data[0]); }
  // sum[l, r)
  T query(int l, int r) const {
    if (l == r) return T(0);
    return l ? (data[r-1] - data[l-1]) : data[r-1]; }
};
