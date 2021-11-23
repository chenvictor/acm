template <typename T, int K=17>
struct segtree {
#define IN  (l <= s && e <= r)
#define OUT (r <= s || e <= l)
#define MID ((s+e)/2)
#define L (i*2)
#define R (i*2+1)
  constexpr static int N = 1 << K;
  array<T,2*N> t;
  T& operator[](int i) { return t[i+N]; }
  void build(int i=1, int s=0, int e=N) {
    if (s+1==e) return;
    build(L, s, MID);
    build(R, MID, e);
    t[i].merge(t[L], t[R], e-s);
  }
  T query(int l, int r, int i=1, int s=0, int e=N) {
    if (IN) return t[i];
    T ans;
    if (OUT) return ans;
    t[i].prop(t[L], t[R], e-s);
    ans.merge(query(l, r, L, s, MID), query(l, r, R, MID, e), e-s);
    return ans;
  }
  template<typename Op, typename...A>
  void upd(int l, int r, int i, int s, int e, A...args) {
    if (OUT) return;
    if (IN && Op::calc(t[i], args..., e-s)) return;
    t[i].prop(t[L], t[R], e-s);
    upd<Op>(l, r, L, s, MID, args...);
    upd<Op>(l, r, R, MID, e, args...);
    t[i].merge(t[L], t[R], e-s);
  }
  template<typename Op, typename...A>
  void update(int l, int r, A...args){
    upd<Op>(l,r,1,0,N,args...);
  }

  // testing
  template<typename F, typename...A>
  void upd2(const F&& f, int l, int r, int i, int s, int e, A...args) {
    if (OUT) return;
    if (IN && f(t[i], args..., e-s)) return;
    t[i].prop(t[L], t[R], e-s);
    upd2(f, l, r, L, s, MID, args...);
    upd2(f, l, r, R, MID, e, args...);
    t[i].merge(t[L], t[R], e-s);
  }
  template<typename F, typename...A>
  void update2(const F&& f, int l, int r, A... args) {
    upd2(f,l,r,1,0,N,args...);
  }
};

struct Data {
  Data() {
    /* default null node value USED IN QUERIES so initialize!!! */
  }
  Data(int val) {
  }
  void merge(const Data& l, const Data& r, int len) {

  }
  /* update operations
   * - len=1 at leaf, must return true
   * - return false for seg beats
   */
  struct todo {
    static bool calc(Data& t, int len) {
      return true;
    }
  };
  // function struct version, seg.update<inc>(l,r,v);
  // slightly faster?
  struct inc {
    static bool calc(Data& t, ll v, int len) {
      return true;
    }
  };
  // static func version, seg.update2(increment, l,r,v);
  static bool increment(Data& t, ll v, int len) {
    return true;
  }
  void prop(Data& l, Data& r, int len) {
    /* optional lazy prop */
  }
};

