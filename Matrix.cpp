#define _T template <typename T>
_T class Matrix; _T Matrix<T> make_diag(int s, T val); _T class Matrix { vector<vector<T>> mat; public: vector<T>& operator[] (int i) { return mat[i]; } 
  const vector<T>& operator[] (int i) const { return mat[i]; } int N() const { return mat.size(); } int M() const { return mat.size() ? mat[0].size() : 0; }
  Matrix() {} Matrix(int n, int m, T val=T()) : mat(n, vector<T>(m, val)) { } Matrix<T>& operator*=(const Matrix<T>& b) { times(b); return *this; }
  Matrix<T>  operator* (const Matrix<T>& b) { Matrix ans = *this; return ans *= b; }
  void times(const Matrix<T>& b, T mod=T()) { vector<vector<T>> ans(N(), vector<T>(b.M()));
    forx(i, N()) forx(j, b.M()) forx(k, M()) { ans[i][j] += mat[i][k] * b[k][j]; if (mod != T()) ans[i][j] %= mod; } mat.swap(ans); } 
  Matrix<T> pow(ll power, T mod=T()) { Matrix<T> ans = make_diag(N(), T(1)), temp = *this;
    for ( ; power; power >>= 1, temp.times(temp, mod)) if (power & 1) ans.times(temp, mod); return ans; }
}; _T Matrix<T> make_diag(int s, T val) { Matrix<T> ans(s,s); forx(i,s) ans[i][i] = val; return ans; }
#undef _T
