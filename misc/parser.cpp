template <class T=int>
struct Parser {
  stringstream ss;
  Parser(const string& s): ss(s) {}
  using OP = tuple<int,function<T(T,T)>>; // {precedence, func}
  map<char,OP> ops = {
    {'+', OP{1,[](T a, T b){ return a+b; }}},
    {'-', OP{1,[](T a, T b){ return a-b; }}},
    {'*', OP{2,[](T a, T b){ return a*b; }}},
    {'/', OP{2,[](T a, T b){ return a/b; }}},
  };
  int npre() {
    auto it = ops.find((char)ss.peek());
    return it == ops.end() ? -1 : get<int>(it->ss);
  }
  T rec(T lhs, int min_precedence=0) {
    while (npre() >= min_precedence) {
      auto& [pre,calc] = ops[(char)ss.get()];
      T rhs = parse_primary();
        // TODO right associativity
      while (npre() > pre) {
        rhs = rec(rhs, pre + (npre() > pre));
      }
      lhs = calc(lhs, rhs);
    }
    return lhs;
  }
  T parse_primary() {
    // unary minus
    if (ss.peek() == '-') {
      ss.ignore();
      return -parse_primary();
    }
    T val;
    if (ss.peek() == '(') {
      ss.ignore(), val=eval(), ss.ignore();
    } else
      ss >> val;
    return val;
  }
  T eval() { return rec(parse_primary()); }
};

