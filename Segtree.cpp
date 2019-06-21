template <typename T> class Segtree {
  int n; vector<T> data;
  function<T(T,T)> merge;    // merge:  T1 is left, T2 is right, return combined T
  function<void(T&,T)> updt; // update: T& 1 is orig, T2 is new
	void build() { for (int i = n - 1; i > 0; --i) data[i] = merge(data[i<<1], data[i<<1|1]); }
	public:
		Segtree(int n, function<T(T,T)> mer, function<void(T&,T)> upd) : n(n), data(2*n), merge(mer), updt(upd) { build(); }
		Segtree(int n, T val, function<T(T,T)> mer, function<void(T&,T)> upd) : n(n), data(2*n, val), merge(mer), updt(upd) { build(); }
		Segtree(vector<T>& init, function<T(T,T)> mer, function<void(T&,T)> upd) : n(init.size()), data(2*n), merge(mer), updt(upd) {
			copy(init.begin(), init.end(), data.begin() + n); build(); }
    // get value at idx
		T query(int idx) { return data[n+idx]; }
    // assign value at idx
		void update(int idx, T value) { for (data[idx += n] = value; idx > 1; idx >>= 1) data[idx>>1] = merge(data[idx], data[idx^1]); }
    // query the range [l,r)
		T query(int l, int r) {
      assert(r >= l); if (l==r) return T();; if (l==--r) return query(l);;
		 	T resl, resr; bool initl = false, initr = false;
			for (l += n, r += (n+1); l < r; l >>= 1, r >>= 1) {
				if (l&1) resl = initl ? merge(resl, data[l++]) : (initl = true, data[l++]);
				if (r&1) resr = initr ? merge(data[--r], resr) : (initr = true, data[--r]);
			} if (!initl) return resr;; if (!initr) return resl;; return merge(resl, resr);
		}
  // Common merge funcs
  static T merge_sum(T a, T b) { return a+b; }
  static T merge_max(T a, T b) { return max(a,b); }
  static T merge_min(T a, T b) { return min(a,b); }
  // Common update funcs
  static void update_set(T& o, T n) { o = n; }
  static void update_add(T& o, T n) { o += n; }
};
