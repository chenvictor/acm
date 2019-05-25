#include <bits/stdc++.h>
using namespace std;
#define CM ,
#define TD(a,b) typedef a b
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9; const ld PI = acos(-1);
#define ff first
#define ss second

#define _T template <typename T>
_T class Matrix; _T Matrix<T> diag(int s, T val); _T class Matrix {
  vector<vector<T>> mat;
  public:
  vector<T>& operator[] (int i) { return mat[i]; } 
  const vector<T>& operator[] (int i) const { return mat[i]; }
  int N() const { return mat.size(); }
  int M() const { return mat.size() ? mat[0].size() : 0; }
  Matrix() {}
  Matrix(int n, int m, T val=T()) : mat(n, vector<T>(m, val)) { }
  // Math stuff
  Matrix<T>& operator*=(const Matrix<T>& b) {
    assert(M() == b.N()); // remove assertion?
    vector<vector<T>> ans(N(), vector<T>(b.M()));
    forx(i, N()) forx(j, b.M()) forx(k, M()) ans[i][j] += mat[i][k] * b[k][j];
    mat.swap(ans);
    return *this;
  }
  Matrix<T> operator*(const Matrix<T>& b) {
    Matrix ans = *this;
    return ans *= b;
  }
  Matrix<T> pow(ll power) {
    assert(N() == M()); //only for square matrix
    //max power is 63? ask Rahim
    Matrix<T> ans = diag(N(), T(1));
    for (ll i = 62; i > -1; --i) {
      ans *= ans;
      if ((1ll << i) & power) {
        ans *= (*this);
      }
    }
    return ans;
  }
  Matrix<T> v_pow(ll power) {
    assert(N() == M());
    //let's perform squaring
    Matrix<T> ans = diag(N(), T(1)); //initial answer is identity matrix
    Matrix<T> temp = *this;
    for ( ; power > 0; power >>= 1, temp *= temp) {
      if (power & 1) ans *= temp;
    }
    return ans;
  }
}; _T Matrix<T> diag(int s, T val) { Matrix<T> ans(s,s); forx(i,s) ans[i][i] = val; return ans; }
#undef _T

template <typename T>
void printM(Matrix<T> m) {
  cout << "Dimens: " << m.N() << "x" << m.M() << nl;
  forx(i, m.N()) {
    forx(j, m.M()) {
      cout << m[i][j] << "\t";
    }
    cout << nl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3  
  srand(256);
  Matrix<int> fib(10,10);
  forx(i,10) forx(j,10) {
    fib[i][j] = rand() % 10000007;
  }
  //Rahim's implementation seems pretty slow?
  //
  const bool rahim = false;
  forx(i, 128) {
    if (rahim)
      fib.pow(i);
    else
      fib.v_pow(i);
  }
  cout << clock() << nl;
  return 0;
}

