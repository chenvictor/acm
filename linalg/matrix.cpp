template <class T, class row=vector<T>, class p=vector<row>>
struct matrix : public p {
  using p::p;
  matrix(int a, int b, T v={}) : p(a, row(b,v)) {}
  int n() const { return int(p::size()); };
  int m() const { return p::empty() ? 0 : sz(SELF[0]); }
  // access
  T& operator()(int i, int j) { return SELF[i][j]; }
  const T& operator()(int i, int j) const { return SELF[i][j]; }
  // A*B
  matrix operator*(const matrix& B) const {
    assert(m() == B.n());
    matrix R(n(),B.m());
    rep(k,0,n()) rep(i,0,m()) rep(j,0,B.m()) R(i,j) += SELF(i,k)*B(k,j);
    return R;
  }
  // A*x
  row operator*(const row& x) const {
    assert(m() == sz(x));
    row res(n());
    rep(i,0,n()) rep(j,0,m()) res[i] += SELF(i,j)*x[j];
    return res;
  }
  // A^T
  matrix transpose() const {
    matrix t(m(),n());
    rep(i,0,m) rep(j,0,n) t(i,j) = SELF(j,i);
    return t;
  }
  static matrix diag(int n, T&& v=1) {
    matrix I(n,n);
    rep(i,0,n) I(i,i)=v;
    return I;
  }
};

