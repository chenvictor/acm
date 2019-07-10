#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define CM ,
#define TD(a,b) typedef a b
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

class ModInt {
  ll val; static const int MOD = -1; static_assert(MOD > 0ll, "Modulus not set!");
  int modInverse(int a) { // simplified extended GCD, onl solving for x
    int b = MOD, x = 0, x_ = 1, q; while (a != 0) { q = b / a; swap(b, a); a %= b;
    swap(x, x_); x_ -= q * x; } assert(b == 1); return (x %= MOD) < 0 ? (x + MOD) : x; }
  public: ModInt() : val(0) { } ModInt(int v) : val(v) { if ((val %= MOD) < 0) val += MOD; }
    ModInt& operator += (const ModInt& b) { if ((val += b.val) >= MOD) val -= MOD; return *this; }
    ModInt& operator -= (const ModInt& b) { if ((val -= b.val) < 0) val += MOD; return *this; }
    ModInt& operator *= (const ModInt& b) { val = (val*b.val) % MOD; return *this; }
    ModInt& operator /= (const ModInt& b) { if (((val *= modInverse(b.val)) %= MOD) < 0) val += MOD; return *this; }
#define _op(op) ModInt& operator op (int b) { ModInt w(b); return *this op w; }
    _op(+=); _op(-=); _op(*=); _op(/=);
#undef _op
#define _op(op, btype, op2) ModInt operator op (btype b) const { ModInt ans = *this; return ans op2 b; }
    _op(+, const ModInt&, +=); _op(-, const ModInt&, -=); _op(*, const ModInt&, *=); _op(/, const ModInt&, /=);
    _op(+, int, +=); _op(-, int, -=); _op(*, int, *=); _op(/, int, /=);
#undef _op
    operator int() const { assert(0 <= val && val < MOD); return val; }
};

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3  
  ModInt x = 200;
  cout << x << nl;
  x /= 10;
  cout << x << nl;
  x /= 7;
  cout << x << nl;
  x *= 7;
  cout << x << nl;
  
  cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl;
  return 0;
}
