#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define TD typedef
#define forx(i,n) for(int i = 0; i < (n); ++i)
#define forxr(i,n) for(int i = n; i--;)
TD long long ll; TD long double ld; TD pair<int,int> pii; TD pair<ll,ll> pll; TD vector<int> VI; TD vector<bool> VB; TD vector<ll> VL;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

#define all(a) a.begin(), a.end()

struct SuffixArray {
  const string s;
	VI sa;
  VI inv;
  VI lcp;
  VI bwt;
	SuffixArray(const string& _, int lim = 256) : s(_) {
		int n = s.size() + 1, k = 0, a, b;
		VI x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = inv = bwt = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			forx(i,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			forx(i,n) ws[x[i]]++;
			forx(i,lim-1) ws[i+1] += ws[i];
			forxr(i,n) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			forx(i,n-1) a = sa[i], b = sa[i+1], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		forx(i,n-1) rank[sa[i+1]] = i+1;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
    //calc inverse
    forx(i,n) inv[sa[i]] = i;
	}
  void debug() {
    cerr << "initial string: " << s << nl;
    cerr << "i\tsa\tinv\tlcp\tbwt\tsuffix\n";
    forx(i,s.size()+1) {
      cerr << i << '\t' << sa[i] << '\t' << inv[i] << '\t' << lcp[i] << '\t' << bwt[i] << '\t' << string(s.begin() + sa[i], s.end()) << "$\n";
    }
  }
};

int main() {
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(12);
  // Emily <3
  string s;
  cin >> s;
  SuffixArray sx(s);
  sx.debug();
  
  return 0;
}
