struct input {
  string s;
  input(const string& v): s(v) {}
  input() {
    getline(cin, s);
    while(cin.peek() == nl) cin.ignore();
  }
  struct tokens {
    vector<input> t;
    template <class T>
    vector<T> map() { return vector<T>(all(t)); }
    void check_size(int s) {
      if (s != sz(t)) {
        cerr << "cannot unpack " << sz(t) << " tokens to " << s << " values" << endl;
        exit(1);
      }
    }
    template <class T, size_t S>
    array<T,S> unpack() {
      check_size(S);
      auto v = map<T>();
      array<T,S> res{};
      copy(all(v), res.begin());
      return res;
    }
    template <class...T>
    tuple<T...> unpack() {
      tuple<T...> res;
      check_size(tuple_size_v<tuple<T...>>);
      int i=0; apply([&](auto&&... a) { ((a = T(t[i++])), ...); }, res);
      return res;
    }
    operator vector<string>() { return map<string>(); }
  };
  template <class D=char>
  tokens split(const D& delim=' ') {
    tokens t{};
    size_t cur = 0, nx;
    while ((nx = s.find(delim, cur)) != string::npos) {
      if (cur != nx) t.t.emplace_back(s.substr(cur, nx-cur));
      cur = nx+1;
    }
    t.t.emplace_back(s.substr(cur));
    return t;
  }
  operator string() const { return s; }
  template <class T>
  explicit operator T() const {
    stringstream ss(s);
    T t; ss >> t;
    if (ss.fail() || !ss.eof()) {
      cerr << "failed to parse token '" << s << "' as " << typeid(T).name() << endl;
      exit(1);
    }
    return t;
  }
  void print() {
    cout << s << nl;
  }
  friend ostream& operator<<(ostream& os, const input& i) { return os << i.s; }
};

