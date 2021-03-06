class BigInt { typedef unsigned int uint; typedef unsigned long long ull; static const int I_SIZE = 8*sizeof(uint); int sgn; vector<uint> mag;
  uint& operator[] (int i) { if (i >= size()) mag.resize(i+1, 0); return mag[i]; } uint operator[] (int i) const { return (i < mag.size()) ? mag[i] : 0; }
  int cmpMag(const BigInt& b) const { ll diff = size() - b.size(); for (int i = size()-1; i >= 0 && !diff; --i) diff = (ll)(*this)[i] - b[i];; return getSign(diff); }
  int cmp(const BigInt& b) const { if (!sgn) return -b.sgn;; if (!b.sgn || sgn ^ b.sgn) return sgn;; return sgn * cmpMag(b); }
  void addMag(const BigInt& b) { ull x = 0; for (int i=0; i < max(b.size(), size()) || x; ++i, x >>= I_SIZE) (*this)[i] = (x += (ull)(*this)[i] + b[i]); }
  void subMag(const BigInt& b) { bool carry = false; ll x = 0; for (int i=0; i < max(b.size(), size()) || x; ++i, x >>= I_SIZE) {
    x += (ll)(*this)[i] - b[i] - carry; if ((carry = x < 0)) ++x += UINT_MAX; (*this)[i] = x; } tc(); }
  int size() const { return mag.size(); } void tc() { while (mag.size() && !mag.back()) mag.pop_back(); if (mag.empty()) sgn = 0; }
  char toChar(int radix=10, bool upper=false) const { int val = toInt(); assert(val < radix); return val + ((val < 10) ? '0' : (upper ? 'A' : 'a')-10); }
  template <typename T> static inline char getSign(T x) { return (x < 0) ? -1 : x > 0; } void fastFromString10(string s) { int temp = 0, end = (s[0] == '-');
    BigInt base = 1; for (int i = s.length()-1, b = 1; i >= end; --i) { temp += b * (s[i] - '0'); if (b == 1e9) { *this += (base * temp); base *= 1000000000;
    temp = 0, b = 1; } else { b *= 10; } } *this += base * temp; if (end) sgn *= -1; } string fastToString10() const { const BigInt radix = 1000000000;
    BigInt abs = absolute(); string ans; do { auto p = abs.divide(radix); int val = p.ss.toInt(); forx(i,9) { ans += ((val % 10) + '0'); val /= 10; } abs.swap(p.ff);
    } while (abs.toBool()); while (ans.size() > 1 && ans.back() == '0') { ans.pop_back(); } if (sgn < 0) ans += '-';; reverse(ans.begin(), ans.end()); return ans; }
  public: BigInt() : sgn(0), mag(0) {} BigInt(string s, int radix=10) { fromString(s,radix); } BigInt(int x) : sgn(getSign(x)), mag(1, abs((ll)x)) { }
  char sign() const { return sgn; } void clear() { mag.clear(); sgn = 0; } void swap(BigInt& b) { std::swap(sgn, b.sgn); mag.swap(b.mag); }
  BigInt negate() const { BigInt ans = *this; ans.sgn *= -1; return ans; } BigInt absolute() const { return ((sgn < 0) ? negate() : *this); }
  BigInt operator - () const { return negate(); } BigInt operator + () const { BigInt ans = (*this); return ans; }
  int popcount() const { int tot = 0; for (uint v : mag) { tot += __builtin_popcount(v); } return tot; }
  int bitcount() const { return sgn ? (mag.size() * I_SIZE - __builtin_clz(mag.back())) : -1; }
  int ctz(bool pop1 = false) const { if (pop1) return I_SIZE * (mag.size() - 1) + __builtin_ctz(mag.back());; if (!sgn) return -1;;
    for (int ans = 0, i = mag.size()-1; ; --i, ans += I_SIZE) if (mag[i]) return ans += __builtin_ctz(mag[i]); }
  BigInt lastnbits(int n) { BigInt ans = *this; const int full = ((n-1) / I_SIZE)+1, semi = n % I_SIZE;
    if (full > 0) { ans.mag.resize(full); ans.mag.back() &= ((1 << semi) - 1); } else { ans.clear(); } ans.tc(); return ans; }
  inline static int fromChar(char c) { return (c<'a')?(c<'A'?c-'0':c-'A'):c-'a'; } void fromString(string s, int radix=10) { if (radix == 10) { fastFromString10(s);
    return; } BigInt bigRadix(radix); clear(); for (int i = (s[0]=='-'); i < s.length(); ((*this) *= bigRadix) += fromChar(s[i]), ++i);; sgn = s[0]=='-' ? -1 : 1; tc(); }
  int toInt() const { assert(canInt()); return (sgn < 0) ? -(*this)[0] : (*this)[0]; } bool canInt() const { return *this >= INT_MIN && *this <= INT_MAX; }
  bool toBool() const { return sgn; }
  string toString(int radix=10, bool upper=false) const { if (radix == 10 && canInt()) { return to_string(toInt()); } if (radix == 10) return fastToString10();
    BigInt bigRadix(radix), abs = absolute(); string ans; do { auto p = abs.divide(bigRadix); ans += (p.ss.toChar(radix, upper)); abs.swap(p.ff); }
    while (abs.sgn); if (sgn < 0) ans += '-';; reverse(ans.begin(), ans.end()); return ans; }
  friend istream& operator>>(istream& in, BigInt& x) { string s; in >> s; x.fromString(s); return in; }
  friend ostream& operator<<(ostream& out, const BigInt& x) { return out << x.toString(); }
  BigInt& operator>>=(int shift) { if (shift < 0) return operator<<=(-shift);; if (sgn) { const int full = shift / I_SIZE, semi = shift % I_SIZE, sz = mag.size();
    for(int i = full; i < sz; ++i) (*this)[i-full] = ((ull)(*this)[i] | ((ull)(*this)[i+1] << I_SIZE)) >> semi;; mag.resize(sz-full); tc(); } return *this; }
  BigInt& operator<<=(int shift) { if (shift < 0) return operator>>=(-shift); if (sgn) { const int full = shift / I_SIZE, semi = shift % I_SIZE, sz = mag.size();
    ull val = ((ull)mag.back()) << semi; if (val >> I_SIZE) (*this)[sz+full] = val >> I_SIZE;; for (int i = sz-1; i > 0; --i) { (val <<= I_SIZE) |= (((ull) (*this)[i-1])
    << semi); (*this)[full+i] = val >> I_SIZE; } (*this)[full] = val; fill(mag.begin(), mag.begin()+full, 0); tc(); } return *this; }
  BigInt& operator&=(const BigInt& b) { forx (i, size()) (*this)[i] &= b[i];; tc(); return *this; }
  BigInt& operator|=(const BigInt& b) { forx (i, max(size(),b.size())) (*this)[i] |= b[i];; return *this; }
  BigInt& operator^=(const BigInt& b) { forx (i, max(size(),b.size())) (*this)[i] ^= b[i];; tc(); return *this; }
  BigInt& operator +=(const BigInt& b) { if (b.sgn) { if (sgn) { if (sgn == b.sgn) { addMag(b); } else { switch(cmpMag(b)) { case 0: clear(); break;
    case 1: subMag(b); break; case -1: BigInt temp = b; swap(temp); subMag(temp); } } } else { (*this) = b; } } return *this; }
  BigInt& operator -=(const BigInt& b) { if (b.sgn) { if (sgn) { if (sgn == b.sgn) { switch(cmpMag(b)) { case 0: clear(); break; case 1: subMag(b); break;
    case -1: BigInt temp = -b; swap(temp); subMag(temp); } } else { addMag(b); } } else { (*this) = -b; } } return *this; } 
  BigInt& operator *=(const BigInt& b) { if (&b == this) { throw "Cannot *= itself. Use BigInt.square() instead!"; } if (!sgn || !b.sgn) { clear(); return *this; }
    if (popcount() == 1) { BigInt temp = b; swap(temp); sgn *= temp.sgn; return *this <<= temp.ctz(true); }
    if (b.popcount() == 1) { sgn *= b.sgn; return *this <<= b.ctz(true); } BigInt a; swap(a); sgn = a.sgn * b.sgn; ull x = 0, t=0; bool carry = false;
    forx(i, a.size()) { for(int j = 0; j < b.size() || x || carry; ++j) { x += (*this)[i+j]; carry = __builtin_add_overflow(x, (ull)a[i]*b[j], &t);
    (*this)[i+j] = x = t; x >>= I_SIZE; x += ((ull)carry) << I_SIZE; } } return *this; }
  pair<BigInt,BigInt> divide(const BigInt& b) { if (canInt() && b.canInt()) { int x = toInt(), y = b.toInt(); if (x == INT_MIN && y == -1) {
    auto ans = make_pair(BigInt(INT_MAX), BigInt(0)); ++ans.ff; return ans; } int q = x / y; return make_pair(BigInt(q), BigInt(x-q*y)); }
    else { if (b.popcount() == 1) { int cnt = b.ctz(true); BigInt temp = *this; BigInt R = temp.lastnbits(cnt); temp.sgn *= b.sgn; return make_pair(temp >> cnt, R); }
    switch(cmpMag(b)) { case -1: return make_pair(BigInt(0), *this); case 0: return make_pair(BigInt(sgn * b.sgn), BigInt(0)); }
    BigInt lo = 0, hi = (absolute()+1), mid, res; int cmp = 1; while((lo < hi-1) && cmp) { mid = (lo+hi) >> 1; res = b*mid; cmp = cmpMag(res);
    switch (cmp) { case 1: lo.swap(mid); break; case -1: hi.swap(mid); break; case 0: hi.swap(mid); lo = hi++; break; } } lo.sgn *= (sgn * b.sgn); res = lo*b;
    BigInt rem = *this - res; return make_pair(lo, rem); } }
  BigInt& operator /=(const BigInt& b) { return *this = divide(b).ff; } BigInt& operator %=(const BigInt& b) { return *this = divide(b).ss; }
#define _op(op) bool operator op (const BigInt& rhs) const { return cmp(rhs) op 0; }
_op(<) _op(<=) _op(==) _op(!=) _op(>) _op(>=)
#undef _op
#define _op(op, op2, T) BigInt operator op (T b) const { BigInt ans=*this; return ans op2 b; }
  _op(&, &=, const BigInt&); _op(|, |=, const BigInt&); _op(^,^=,const BigInt&); _op(>>,>>=,int); _op(<<,<<=,int); _op(&,&=,int); _op(|,|=,int); _op(^,^=,int);
#undef _op
#define _op(op, op2) BigInt operator op (const BigInt& b) const { BigInt copy = *this; return copy op2 b; }
  _op(+, +=); _op(-, -=); _op(*, *=); _op(/, /=); _op(%, %=);
#undef _op
#define _op(op) BigInt& operator op (int b) { BigInt temp(b); return (*this) op temp; }
  _op(+=); _op(-=); _op(*=); _op(/=); _op(%=);
#undef _op
#define _op(op, op2) BigInt operator op (int b) const { BigInt ans = *this; return ans op2 b; }
  _op(+, +=); _op(-, -=); _op(*, *=); _op(/, /=); _op(%, %=);
#undef _op
  BigInt& operator++() { return (*this) += 1; } BigInt& operator--() { return (*this) -= 1; } BigInt operator++(int) { BigInt copy = *this; *this += 1; return copy; }
  BigInt operator--(int) { BigInt copy = *this; *this -= 1; return copy; } BigInt square() { if (!sgn) return *this; return (*this) * (*this); }
  BigInt pow(int exp) { BigInt ans(1), base(*this); for (; exp > 0; exp >>= 1, base = base.square()) if (exp & 1) ans *= base; return ans; }
};

