#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define TD typedef
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD long long ll; TD long double ld; TD pair<int,int> pii; TD pair<ll, ll> pll; TD vector<int> VI; TD vector<bool> VB; TD vector<ll> VL;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second


namespace Nums {
// iterate over digits of a number, from right to left
  #define for_digits(d, number) for (ll _=(number); _; ) for (int d = _%10; _; d=(_/=10)%10)
// b^e % mod
  ll modpow(ll b, int e, int mod) { ll res = 1; for (; e>0; e>>=1, b=b*b%mod) { if (e&1) res = res*b % mod; } return res; }
// nCr
  ll nCr(ll n, ll r) {
    if (r>n) return 0;
    if (r<<1>n) r=n-r;
    if (!r) return 1;
    ll res=n;
    for (int i = 2; i <= r; ++i) {
      res = res * (n-i+1) / i;
    } return res;
  }
// solves: ax + by = gcd(a,b)
// return: { gcd, x, y };
// source: https://en.wikibooks.org/wiki/Algorithm_Implementation/Mathematics/Extended_Euclidean_algorithm#Iterative_algorithm_3
  template <typename T>
  tuple<T,T,T> egcd(T a, T b) {
    T gcd = b, x = 0, y = 1, x_ = 1, y_ = 0;
    while (a) {
      b = gcd / a;
      swap(gcd, a); a %= gcd;
      swap(y, y_); y_ -= b * y;
      swap(x, x_); x_ -= b * x;
    }
    return {gcd, x, y};
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  cerr << "Time: " <<  (ld)clock() / CLOCKS_PER_SEC << nl;
  return 0;
}

