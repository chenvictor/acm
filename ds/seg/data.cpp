struct Data {
  Data(int val) { }
  /* default null node value USED IN QUERIES so initialize!!! */
  Data() { }
  /* merge logic */
  Data(const Data& l, const Data& r) { merge(l,r); }
  void merge(const Data& l, const Data& r) {
  }
  /* update operations => len=1 at leaf, must return true
   * false to recurse to child nodes */
  struct update {
    static bool calc(Data& t, int s, int e) {
      return true;
    }
  };
  void prop(Data& l, Data& r, int s, int e) {
    /* optional lazy prop */
  }
  /* search operations => ok return true if condition is satisfied */
  struct find {
    static bool ok(const Data& t) {
      return true;
    }
  };
};

