class Rational {
	ll n, d; void reduce() { ll gcd = __gcd(n, d); n /= gcd; d /= gcd; } public:
	Rational(ll num=0, ll den=1, bool reduced=false) : n(num), d(den) { if (!reduced) reduce(); }
	ld value() const { return (ld) n / d; } ll num() const { return n; } ll den() const { return d; }
  friend ostream& operator<<(ostream& out, const Rational& r) { return out << r.n << "/" << r.d; }
#define _(op) bool operator op(Rational b) const
	_(==) { return n==b.n && d==b.d; } _(!=) { return !(*this==b); } _(<) { return n*b.d < d*b.n; }
	_(>) { return b < *this; } _(<=) { return !(*this > b); } _(>=) { return !(*this < b); }
#undef _
#define _(op) Rational& operator op (Rational b)
  Rational inverse() const { return Rational((n < 0 ? -d : d), (n < 0 ? -n : n), true); }
  Rational operator -  () const { return Rational(-n, d, true); } _(/=) { return *this *= b.inverse(); } _(-=) { return *this += -b; }
  _(*=) { ll g1 = __gcd(n, b.den()), g2 = __gcd(d, b.num()); n = n / g1 * b.num() / g2; d = b.den() / g1 * d / g2; return *this; }
  _(+=) { ll g = __gcd(d, b.den()); n = b.den()/g*n + d/g*b.num(); d = d / g * b.den(); return *this; }
#undef _
#define _(op) Rational& operator op (ll b)
  _(*=) { return *this *= Rational(b); } _(/=) { return *this *= Rational(1, b); } _(+=) { n += d*b; return *this; } _(-=) { return *this += -b; }
#undef _
#define _(op, T, op2) Rational operator op(T b) const { Rational ans = *this; return ans op2 b; }
  _(*, Rational, *=); _(/, Rational, /=); _(+, Rational, +=); _(-, Rational, -=); _(*, ll, *=); _(/, ll, /=); _(+, ll, +=); _(-, ll, -=);
#undef _
};
