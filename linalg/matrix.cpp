template <class T, class p=valarray<T>>
struct matrix : public p {
  using value_type = T;
  int n,m;
  matrix(int r, int c): p(r*c), n(r), m(c) {}
  matrix(int d=0): matrix(d,d) {}
  T& operator()(int i, int j) { return SELF[i*m+j]; }
  const T& operator()(int i, int j) const { return SELF[i*m+j]; }
  // A*B
  matrix operator*(const matrix& B) const {
    assert(m == B.n);
    matrix R(n,B.m);
    rep(k,0,n) rep(i,0,m) rep(j,0,B.m) R(i,j) += SELF(i,k)*B(k,j);
    return R;
  }
  // A*x
  valarray<T> operator*(const valarray<T>& x) const {
    assert(m == sz(x));
    valarray<T> res(n);
    rep(i,0,n) rep(j,0,m) res[i] += SELF(i,j)*x[j];
    return res;
  }
  // A^T
  matrix transpose() const {
    matrix t(m,n);
    rep(i,0,m) rep(j,0,n) t(i,j) = SELF(j,i);
    return t;
  }
};

