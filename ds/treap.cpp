namespace treap {
  struct node; using ptr = node*;
  const struct T {
    int cnt, val;
    T() {
      // nill node initialization
    }
    T(int v): cnt(1) {
      val = v;
    }
  } nill;
#define t_of(x) (x ? x->t : nill)
  struct node {
    ptr l=0,r=0; int y; T t;
    template <typename V>
    node(V&& v=0): y(rand()), t(v) { }
    ~node() { delete l; delete r; }
  };
  ptr calc(ptr p) {
    // custom merge logic
    auto& t = p->t, tl = t_of(p->l), tr = t_of(p->r);
    t.cnt = tl.cnt + tr.cnt + 1;
    t.sum = tl.sum + tr.sum + t.val;
    return p;
  }
  /* lazy operations */
  void push(ptr p) {
    // if (!p) return;
    // auto& t = p->t;
  }
  // returns [0, k), [k, end)
  tuple<ptr,ptr> split(ptr p, int k) {
    static ptr t;
    if (!p) return {0,0};
    push(p);
    // p->x >= k for lower_bound(k)
    auto lt = t_of(p->l);
    if (lt.cnt >= k) {
      tie(t,p->l) = split(p->l, k);
      return {t, calc(p)};
    }
    // comment out
    k -= lt.cnt+1;
    tie(p->r,t) = split(p->r, k);
    return {calc(p), t};
  }
  ptr merge(ptr l, ptr r) {
    if (!l) return r;
    if (!r) return l;
    if (l->y > r->y) {
      push(l);
      l->r = merge(l->r, r);
      return calc(l);
    } else {
      push(r);
      r->l = merge(l, r->l);
      return calc(r);
    }
  }
  template <typename F>
  void visit(ptr p, const F& f) {
    if(!p) return;
    push(p);
    visit(p->l, f);
    f(p);
    visit(p->r, f);
  }
  /* optional, multi merge/split */
  template<class A, class... Args>
  A merge(A l, A r, Args... rest) {
    return merge(merge(l,r), rest...);
  }
  // [0, k), [k, k2), [k3, k4), ...
  template<class... Args>
  auto split(ptr p, int k, Args... rest) {
    auto [l, r] = split(p, rest...);
    return tuple_cat(split(l, k), make_tuple(r));
  }
}

