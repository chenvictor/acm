#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define TD typedef
#define forx(i,n) for(int i = 0; i < (n); ++i)
#define forxr(i,n) for(int i = (n)-1; i >= 0; --i)
TD long long ll; TD long double ld; TD pair<int,int> pii; TD pair<ll,ll> pll; TD vector<int> VI; TD vector<bool> VB; TD vector<ll> VL;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

class StringHash { const int m; VI p; public:
  StringHash(int pr = 53, int m = 998802743, int lim = 1e6+50) : m(m), p(1, pr) {
    do { p.push_back(p.back() * pr % m); } while (p.back() != pr && p.size() < lim); }
  ll operator()(string const& s) { ll v = 0; forx(i,s.size()) { v = (v + (s[i] - 'a' + 1) * p[i]) % m; } return v; }
};

int main() {
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  StringHash hasher;

  string a = "helloworldsapaoke";
  string b = "hflloworldsapapke";
  cout << hasher(a) << nl;
  cout << hasher(b) << nl;

  return 0;
}

