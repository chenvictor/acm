/**
 * dynamic prefix sum
 * Point update, query of range [0, x)
 * tested on: https://codeforces.com/gym/100246
 * O(lg(n)**d)
 **/
template <class T, class D, class ...Args>
struct BIT {
  using SUB = BIT<T,Args...>;
  vector<SUB> s;
  BIT(int n, Args... ns): s(n, SUB(ns...)) {}
  void add(int x, Args... xs, T v) {
    for (; x<sz(s); x |= x+1) s[x].add(xs..., v);
  }
  T query(int x, Args... xs) {
    T res=0;
    for (; x; x &= x-1) res += s[x-1].query(xs...);
    return res;
  }
};

template <class T>
struct BIT<T,int> {
	vector<T> s;
	BIT(int n): s(n) { }
  void add(int x, T v) {
    for (; x<sz(s); x |= x+1) s[x] += v;
  }
  T query(int x) {
    T res=0;
    for (; x; x &= x-1) res += s[x-1];
    return res;
  }
};

