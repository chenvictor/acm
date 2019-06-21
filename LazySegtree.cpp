#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define CM ,
#define TD(a,b) typedef a b
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

template <typename T, typename L=T> class Segtree {
  int n; vector<T> data;
  vector<L> lazy; VB lazy_bit;
  function<T(T,T)> merge;
	void build() { for (int i = n - 1; i > 0; --i) data[i] = merge(data[i<<1], data[i<<1|1]); }
	public:
		Segtree(int n, function<T(T,T)> f) : n(n), data(2*n), merge(f) { build(); }
		Segtree(int n, T val, function<T(T,T)> f) : n(n), data(2*n, val), merge(f) { build(); }
		Segtree(vector<T>& init, function<T(T,T)> f) : n(init.size()), data(2*n), merge(f) {
			copy(init.begin(), init.end(), data.begin() + n); build(); }
    // query idx
		T query(int idx) { return data[n+idx]; }
    // query range [l, r)
    T query(int l, int r) {
      throw "Not implemented";
    }
    // update idx
		void update(int idx, T value) { for (data[idx += n] = value; idx > 1; idx >>= 1) data[idx>>1] = merge(data[idx], data[idx^1]); }
    // update range [l, r)
    void update(int l, int r, T value) {
      throw "Not implemented";
    }
    // query the range [l,r)
		T query(int l, int r) {
      assert(r >= l); if (l==r) return T();; if (l==--r) return get(l);;
		 	T resl, resr; bool initl = false, initr = false;
			for (l += n, r += (n+1); l < r; l >>= 1, r >>= 1) {
				if (l&1) resl = initl ? merge(resl, data[l++]) : (initl = true, data[l++]);
				if (r&1) resr = initr ? merge(data[--r], resr) : (initr = true, data[--r]);
			} if (!initl) return resr;; if (!initr) return resl;; return merge(resl, resr);
		}
};

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3  
  
  
  cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl;
  return 0;
}
