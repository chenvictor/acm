template <class T> struct matrix {
  int r, c; vector<T> b;
  matrix(int n, int m) : r(n), c(m), b(n*m) { }
  T& operator()(int i, int j) { return b[i*c+j]; }
  matrix operator*(matrix& o) const {
    assert(c == o.r); matrix ret(r, o.c);
    forx(i, r) forx(j, o.c) forx(k, o.c) ret(i, j) += b[i*c+k] * o(k, j);
    return ret;
  }
};

