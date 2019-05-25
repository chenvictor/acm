#include <bits/stdc++.h>
using namespace std;
#define CM ,
#define TD(a,b) typedef a b
#define forx(i,n) for(int i = 0; i < n; ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9; const ld PI = acos(-1);
#define ff first
#define ss second

class Rational {
	ll n, d;
	void reduce() {
		ll gcd = __gcd(n, d);
		n /= gcd;
		d /= gcd;
	}
	public:
	Rational(ll num=0, ll den=1, bool reduced=false) : n(num), d(den) {
    if (!reduced) reduce();
  }
	ld getVal() {
		return (ld) n / d;
	}
  ll num() const { return n; }
  ll den() const { return d; }
  friend ostream& operator<<(ostream& out, const Rational& r) {
    return out << r.n << "/" << r.d;
  }
#define _cop(op) bool operator op(const Rational& b) const
	_cop(==) { return n==b.n && d==b.d; }
	_cop(<) { return n*b.d < d*b.n; }
	_cop(>) { return b < *this; }
	_cop(<=) { return !(*this > b); }
	_cop(>=) { return !(*this < b); }
	_cop(!=) {	return !(*this==b); }
#undef _cop
// Arithmetic operators
#define _rop(op) Rational operator op(const Rational& b)
  _rop(*) {
    ll g1 = __gcd(n, b.den()), g2 = __gcd(d, b.num());
    return Rational(n/g1*b.num()/g2, b.den()/g1*d/g2, true);
  }
  _rop(/) {
    ll g1 = __gcd(n, b.num()), g2 = __gcd(d, b.den());
    return Rational(n/g1*b.den()/g2, b.num()/g1*d/g2, true);
  }
  _rop(+) {
    ll g = __gcd(d, b.den());
    return Rational(b.den()/g*n + d/g*b.num(),d/g*b.den(),true);
  }
#undef _rop
};

int main() {
	// Testing
	cout << setprecision(6) << fixed;
	Rational test(6,2);
  cout << test << nl;
  cout << test.getVal() << nl;
  Rational t2(5,6);
  cout << t2 << nl;
  Rational t3 = test * t2;
  cout << t3 << nl;
  cout << t2 / test << nl;
  cout << t3 + test << nl;
	return 0;
}
