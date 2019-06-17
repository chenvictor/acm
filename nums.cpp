#include <bits/stdc++.h>
using namespace std;
#define CM ,
#define TD(a,b) typedef a b
#define forx(i,n) for(int i = 0; i < n; ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9; const ld PI = acos(-1);
#define ff first
#define ss second

// Digit utils
// Iterate over digits of a number
namespace Nums {
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
// ax+ by = gcd(a,b)
  template <typename T>
  T egcd(T a, T b, T& x, T& y) {
    if (!a) { x=0, y=1; return b; }
    T tx, ty, t = egcd(b%a, a, tx, ty);
    x = ty - (b/a) * tx; y = tx;
    return t;
  }
};


int main() {
  int x, y;
  cout << egcd(150,90,x, y) << nl;
  cout << x << " " << y << nl;
  return 0;
}
