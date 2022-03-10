using pt = complex<ld>;
using pol = vector<pt>;
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
// dist(const pt& a, const pt& b) ==> abs(a-b)
bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
int sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }
#define CMP(x,y) (const pt& a, const pt& b) { return x(a)<x(b)-EPS || (x(a)<=x(b)+EPS && y(a)<y(b)-EPS); }
bool cmp_lex   CMP(real,imag)
bool cmp_lex_i CMP(imag,real)
istream& operator>>(istream& is, pt& p) { ld x,y; is >> x >> y; p.real(x); p.imag(y); return is; }
ostream& operator<<(ostream& os, const pt& p) { return os << real(p) << " " << imag(p); }

