template <typename T, int K>
struct segtree {
#define IN  (l <= s && e <= r)
#define OUT (r <= s || e <= l)
#define MID (s+(e-s)/2)
#define LEN (e-s)
#define L (i*2)
#define R (i*2+1)
  constexpr static int N = 1 << K;
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
  T query(int l, int r, int i=1, int s=0, int e=N) {
    if (IN) return t[i]; else if (OUT) return T();
    t[i].prop(t[L],t[R],s,e);
    return T(query(l, r, L, s, MID), query(l, r, R, MID, e));
  }
  template<typename Op, typename...A>
  void upd(int l, int r, int i, int s, int e, A...args) {
    if (OUT || (IN && Op::calc(t[i],args...,s,e))) return;
    t[i].prop(t[L],t[R],s,e);
    upd<Op>(l, r, L, s, MID, args...);
    upd<Op>(l, r, R, MID, e, args...);
    t[i].merge(t[L],t[R]);
  }
  template<typename Op, typename...A>
  void update(int l, int r, A...args){ upd<Op>(l,r,1,0,N,args...); }
  /* Binary search - first index r where range [l, r] has value >= lim */
  template<typename Find, typename...A>
  pair<int,T> find(int l, int i, int s, int e, T acc, A...args) {
    if (e <= l) return {N, T()};
    T cur(acc, t[i]);
    const bool ok = Find::ok(cur, args...);
    if (!ok || LEN==1) return {ok ? s : N, cur};
    t[i].prop(t[L],t[R],s,e);
    auto left = find<Find>(l, L, s, MID, acc, args...);
    if (Find::ok(left.ss, args...)) return left;
    return find<Find>(l, R, MID, e, left.ss, args...);
  }
  template<typename Find, typename...A>
  pair<int,T> find(int l, A...args) { return find<Find>(l,1,0,N,T(),args...); }
};

