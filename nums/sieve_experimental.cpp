#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,e) for(int i = s; i < (e); ++i)
using ll = long long; using ld = long double;
using pii = pair<int,int>; using pll = pair<ll, ll>;
using vi = vector<int>; using vl = vector<ll>;
const char nl = '\n';
const ll LINF = 0x3f3f3f3f3f3f3f3fll; const int INF = (int)LINF;
const ld EPS = 1e-9, PI = acos(-1.0L);
#define ff first
#define ss second
#define all(c) begin(c),end(c)
#define SZ(c) int((c).size())

/* BOOK CODE */

namespace siv {
  // See https://codeforces.com/blog/entry/54090
  const int N = 1e7;
  vi prime;
  int f[N];
  int c[N], g[N];
  // if prime
  //   f[i] = 0
  // otherwise
  //   f[i] = min prime factor
  //   c[i] = max power f^c divides i
  //   g[i] = value of multiplicative function
  // value of g(p^k)
  int calc(int p, int k=1) {
    return 1;
  }
  bool comp(int i, int p) {
//    int cip = i%p ? 1 : c[i]+1;
//    g[i*p] = g[i] / calc(p, cip-1) * calc(p, cip);
//    c[i*p] = cip;
    return i%p == 0;
  }
  void build() {
    for (int i=2; i<N; ++i) {
      if (!f[i]) {
        prime.push_back(i);
//        g[i] = calc(i), c[i] = 1;
      }
      for (int p : prime) {
        if (i*p >= N) break;
        f[i*p] = p;
        if (comp(i,p)) break;
      }
    }
  }
}

/* REAL CODE */

void code() {
  siv::build();
  cerr << siv::f[5] << nl;
  cerr << siv::f[10] << nl;
}

/* MAIN */

int main() { // Emily <3
  atexit([]{ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(12);
  code();
  return 0;
}

