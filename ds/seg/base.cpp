template <class T, int K, int N=1<<K>
struct segtree {
#define IN  (l <= s && e <= r)
#define OUT (r <= s || e <= l)
#define MID ((s+e)/2)
#define LEN (e-s)
#define L (i*2)
#define R (L+1)
  array<T,2*N> t;
  T& operator[](int i) { return t[i+N]; }
  void build(int i=1, int s=0, int e=N) {
    if (LEN==1) return;
    build(L, s, MID);
    build(R, MID, e);
    t[i].merge(t[L],t[R]);
  }
  void flush(int i=1, int s=0, int e=N) {
    if (LEN==1) return;
    t[i].prop(t[L],t[R],s,e);
    flush(L,s,MID);
    flush(R,MID,e);
  }
  T query(int l, int r) {
    function<T(int,int,int)> go = [&](int i, int s, int e) {
      if (OUT) return T{};
      if (IN) return t[i];
      t[i].prop(t[L],t[R],s,e);
      return T{}.merge(go(L,s,MID),go(R,MID,e));
    };
    return go(1,0,N);
  }
  template<class F, typename...A>
  void update(F& f, int l, int r, A... args) {
    function<void(int,int,int)> go = [&](int i, int s, int e) {
      if (OUT) return;
      if (IN && f(t[i],s,e,args...)) return;
      t[i].prop(t[L],t[R],s,e);
      go(L,s,MID);
      go(R,MID,e);
      t[i].merge(t[L],t[R]);
    };
    go(1,0,N);
  }
  /* Binary search: first index r where range [l, r] satisfies f, or r=N if not possible */
  template<class F, typename...A>
  int find(F& f, int l, A...args) {
    function<pair<int,T>(int,int,int,T)> go = [&](int i, int s, int e, T acc) -> pair<int,T> {
      if (e <= l) return {N, {}};
      T cur = T{}.merge(acc, t[i]);
      if (!f(cur, args...)) return {N,cur};
      if (LEN==1) return {s, cur};
      t[i].prop(t[L],t[R],s,e);
      auto left = go(L, s, MID, acc);
      return left.ff != N ? left : go(R,MID,e,left.ss);
    };
    return go(1,0,N,{}).ff;
  }
};

