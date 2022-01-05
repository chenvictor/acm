namespace karatsuba {
  template <class V, class P=typename V::value_type*>
  V multiply(const V& a, const V& b) {
    function<void(P,P,P,int)> divconq = [&divconq](P x, P y, P res, int n) {
      if (n <= 32) {
        rep(i,0,n) rep(j,0,n) res[i+j] += x[i]*y[j];
        return;
      }
      const int h = n/2;
      V temp(2*n-2); auto x0y0 = &temp[0], mid = &temp[n-1];
      divconq(x+h,y+h,res+n,h);
      divconq(x,y,x0y0,h);
      rep(i,0,h) x[i] += x[h+i];
      rep(i,0,h) y[i] += y[h+i];
      divconq(x,y,mid,h);
      rep(i,0,h) x[i] -= x[h+i];
      rep(i,0,h) y[i] -= y[h+i];
      rep(i,0,n-1) {
        res[i] += x0y0[i];
        res[i+h] += mid[i] - x0y0[i] - res[i+n];
      }
    };
    const int N = 1<<(32-__builtin_clz(max({sz(a),sz(b),1})-1));
    V v(2*N); copy(all(a), v.begin()); copy(all(b), v.begin()+N);
    V res(2*N-1);
    divconq(&v[0],&v[N],&res[0],N);
    while(sz(res) && res.back() == 0) res.pop_back();
    return res;
  }
}

