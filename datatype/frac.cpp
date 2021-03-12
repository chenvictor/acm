struct frac {
	ll num, den;
	frac(ll n=0, ll d=1): num(n), den(d) {
    assert(den != 0);
    if (den < 0) { num = -num, den = -den; }
    reduce();
  }
  frac& reduce() { ll g = gcd(num, den); num /= g, den /= g; return *this; }
  ld value() const { return ld(num)/den; }
  friend ostream& operator<<(ostream& out, const frac& r) {
    return out << r.num << "/" << r.den;
  }
  // COMPARISON:   a CMP b   <=>   a.cmp(b) CMP 0
  ll cmp(const frac& o) const { return num * o.den - den * o.num; }
  // TRANSFORM
  frac inv() const { return frac(den,num); }
  frac operator-() const {return frac(-num,den); }
  // MATH
  frac& operator *=(const frac& b) { num *= b.num, den *= b.den; return reduce(); }
  frac& operator -=(const frac& b) { num = cmp(b), den *= b.den; return reduce(); }
  frac& operator /=(const frac& b) { return *this *= b.inv(); }
  frac& operator +=(const frac& b) { return *this -= -b; }
  frac operator * (const frac& b) const { return frac(*this) *= b; }
  frac operator / (const frac& b) const { return frac(*this) /= b; }
  frac operator + (const frac& b) const { return frac(*this) += b; }
  frac operator - (const frac& b) const { return frac(*this) -= b; }
};

