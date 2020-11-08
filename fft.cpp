// Ref kactl and http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
namespace FFT {
  using T = double;
  using cx = complex<T>;
  using vt = vector<T>;
  using vx = vector<cx>;
  vi bitrev(int n, int L) { vi rev(n); rep(i,1,n) rev[i] = (rev[i/2] | (i & 1) << L) / 2; return rev; }

  vx roots(int n) {
    vx rt(n); rt[0] = rt[1] = 1;
    for (int k = 2; k < n; k*=2) {
      cx x = polar((T)1, (T)PI/k);
      rep (i,k,2*k) rt[i] = i&1 ? rt[i/2]*x : rt[i/2];
    }
    return rt;
  }

  void fft(vx& a, const vx& rt) {
    int n = a.size();
    for (int k = 1; k < n; k *= 2)
      for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
#if 1
        // apparently slower?
        cx z = rt[j+k] * a[i+j+k];
#else
        // apparently 25% faster?
        auto x = (T*)&rt[j+k], y = (T*)&a[i+j+k];
        cx z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);
#endif
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
  }

  vt conv(const vt& a, const vt& b) {
    if (a.empty() || b.empty()) return {};
    const int r = a.size()+b.size()-1, L = 32-__builtin_clz(r), n = 1 << L;
    vt res(r); vi rev = bitrev(n, L);
    vx in(n), out(n), rt = roots(n);
    rep(i,0,max(a.size(), b.size())) in[rev[i]] = {a[i], b[i]};
    fft(in, rt);
    for (cx& x : in) x *= x;
    rep(i,0,n) out[rev[i]] = in[-i & (n - 1)] - conj(in[i]);
    fft(out, rt);
    rep(i,0,r) res[i] = imag(out[i]) / (4 * n);
    return res;
  }
}

