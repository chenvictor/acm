namespace m {
  using T = int;
  const T sent = INF; //-INF and max for max stack
  T cmp(T a, T b) {
    return min(a,b);
  }
  struct stack {
    std::stack<T> d, s;
    stack() {
      d.push(sent); s.push(sent);
    }
    void push(T v) {
      d.push(v);
      s.push(cmp(v, s.top()));
    }
    void pop() { s.pop(); d.pop(); }
    T top() const { return d.top(); }
    T get() const { return s.top(); }
    size_t size() const { return s.size()-1; }
  };
  struct queue {
    stack in, out;
    void _flush() {
      if (out.size() == 0) while (in.size())
        out.push(in.top()), in.pop();
    }
    void push(T v) { in.push(v); }
    void pop() { _flush(); out.pop(); }
    T get() { return cmp(in.get(), out.get()); }
    T front() { _flush(); return out.top(); }
    size_t size() const { return in.size() + out.size(); }
  };
}

