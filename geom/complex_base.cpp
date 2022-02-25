using St = ld;
using Pt = complex<St>;
St cp(const Pt& a, const Pt& b) { return imag(conj(a)*b); }
St dp(const Pt& a, const Pt& b) { return real(conj(a)*b); }

struct cmp_lex {
  bool operator()(const Pt& a, const Pt& b) const {
    return a.real()<b.real()-EPS
      ||  (a.real()<=b.real()+EPS && a.imag()<b.imag()-EPS);
  }
};

