template <size_t K, class P=ld, class T=double> struct FFT {
  /**
   * 1<<K = max size
   * P = double for speed
   * ref kactl and http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
   **/
  constexpr static int N = 2<<K;
  using C = complex<T>;
  using vd = vector<T>;
  using vx = vector<C>;
  array<complex<P>, N> R;
  array<C,N> rt;
  FFT() {
    rt[1] = R[1] = 1;
    for (int k=2; k<N; k*=2) {
      auto x = polar((P)1, (P)PI/k);
      for(int i=k; i < 2*k; i+=2) {
        rt[i] = R[i] = R[i/2];
        rt[i+1] = R[i+1] = R[i/2]*x;
      }
    }
  }
  C mul(const C& a, const C& b) {
    // return a*b; /* slower */
    return C(a.real()*b.real() - a.imag()*b.imag(), a.real()*b.imag() + a.imag()*b.real());
  }
  void fft(vx& a) {
    for (int k = 1; k < sz(a); k *= 2)
      for (int i = 0; i < sz(a); i += 2 * k) rep(j,0,k) {
        C z = mul(rt[j+k], a[i+j+k]);
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
  }
  vd conv(const vd& a, const vd& b) {
    const int r = sz(a)+sz(b)-1;
    if (r<0) return {};
    vd res(r);
    const int L = 32 - __builtin_clz(r);
    static int rev[N], n=0;
    if (n != 1<<L) {
      n = 1<<L;
      rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    }
    vx in(n), out(n);
    rep(i,0,sz(a)) in[rev[i]].real(a[i]);
    rep(i,0,sz(b)) in[rev[i]].imag(b[i]);
    fft(in);
    for(auto& x : in) x*=x;
    rep(i,0,n) out[i] = in[-rev[i] & (n - 1)] - conj(in[rev[i]]);
    fft(out);
    rep(i,0,sz(res)) res[i] = imag(out[i]) / (4*n);
    return res;
  }
};

