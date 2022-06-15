struct V {
  // TODO data
  V& merge(const V& l, const V& r) {
    return SELF;
  }
  /* update operations: LEN=1 at leaf, must return true
   * false to recurse to child nodes */
  static bool update(V& t, int s, int e, int v) {
    return 1;
  }
  /* optional lazy prop */
  void prop(V& l, V& r, int s, int e) {
  }
  /* search operation: return true if condition is satisfied */
  static bool find(const V& t) {
    return 0;
  }
};

