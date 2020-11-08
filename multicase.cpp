#include <bits/stdc++.h>
using namespace std;
void fileio(const char* in, const char* out) {
  if (fopen(in, "r")) { assert(freopen(in, "r", stdin) && freopen(out, "w", stdout)); }
}
#define rep(i,s,e) for(int i = s; i < (e); ++i)
using ll = long long; using ld = long double; using pii = pair<int,int>; using pll = pair<ll, ll>; using vi = vector<int>;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1.0L);
#define ff first
#define ss second
#define all(c) c.begin(),c.end()

void deal(int TC) {
  (void) TC;

}

int main() { // Emily <3
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(12);
  int T; cin >> T;
  for (int i = 1; i <= T; ++i) deal(i);
  return 0;
}
