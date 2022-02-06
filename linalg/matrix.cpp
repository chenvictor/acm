template <class T, class p=valarray<T>>
struct matrix : public p {
  using value_type = T;
  int n,m;
  matrix(int r, int c): p(r*c), n(r), m(c) {}
  matrix(int d=0): matrix(d,d) {}
  T& operator()(int i, int j) { return SELF[i*m+j]; }
  const T& operator()(int i, int j) const { return SELF[i*m+j]; }
  matrix operator*(const matrix& o) const {
    assert(m == o.n);
    matrix R(n,o.m);
    rep(k,0,n) rep(i,0,m) rep(j,0,o.m) R(i,j) += SELF(i,k)*o(k,j);
    return R;
  }
  valarray<T> operator*(const valarray<T>& o) const {
    assert(m == sz(o));
    valarray<T> res(n);
    rep(i,0,n) rep(j,0,m) res[i] += SELF(i,j)*o[j];
    return res;
  }
};

