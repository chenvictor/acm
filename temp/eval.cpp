#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,e) for(int i = s; i < (e); ++i)
using ll = long long; using ld = long double;
using pii = pair<int,int>; using pll = pair<ll, ll>;
using vi = vector<int>; using vl = vector<ll>;
const char nl = '\n';
const ll LINF = 0x3f3f3f3f3f3f3f3fll; const int INF = (int)LINF;
const ld EPS = 1e-9, PI = acos(-1.0L);
#define ff first
#define ss second
#define all(c) begin(c),end(c)
#define sz(c) int(c.size())
#define SELF (*this)
template <typename T, typename Cmp = less<T>>
using heap = priority_queue<T,vector<T>,Cmp>;
template <class T, size_t N=0>
using arr = typename conditional<N,array<T,N>,vector<T>>::type;

// pair i/o
template <typename...T> istream& operator>>(istream& is, pair<T...>& v) { return is >> v.ff >> v.ss; }
template <typename...T> ostream& operator<<(ostream& os, const pair<T...>& v) { return os << v.ff << " " << v.ss; }
// tuple i/o
template <typename...T> istream& operator>>(istream& is, tuple<T&...> t) { return apply([&](auto&&... a) { ((is >> a), ...); }, t), is; }
template <typename...T> ostream& operator<<(ostream& os, const tuple<T...>& t) { return apply([&](auto&& f, auto&&... r) { os << f; ((os << " " << r), ...); }, t), os; }

#if (DEBUG && !defined(ONLINE_JUDGE))
#define trace(...) cerr << make_tuple(">> Line",__LINE__,#__VA_ARGS__,"=",__VA_ARGS__,"<<") << endl
#define ifdebug if(1)
#else
#define trace(...)
#define ifdebug if(0)
#endif

/* BOOK CODE */

/* REAL CODE */

namespace Expression {
  using T = int;
  struct Parser {
    stringstream ss;
    bool bad_divide=0;
    static int precedence(char op) {
      switch(op) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case ')': return INF;
      }
      trace(op);
      assert(false);
    }
    T calc(char op, T a, T b) {
      switch(op) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/':
          if (b != 0 && a%b == 0) {
            return a/b;
          }
      }
      return INF;
    }
    Parser(const string& s): ss(s) {
      trace(s);
    }
    T eval() {
      return rec(parse_primary());
    }
    T rec(T lhs, int min_precedence=0) {
      trace(lhs,min_precedence);
      if (ss.peek() != EOF) {
        char op,lookahead = (char)ss.peek();
        if (lookahead == ')') {
          ss.ignore();
          return lhs;
        }
        while (precedence(lookahead) >= min_precedence) {
          ss >> op;
          trace(op);
          T rhs = parse_primary();
          trace(rhs);
          lookahead = char(ss.peek());
            // TODO right associativity
          while (precedence(lookahead) > precedence(op)) {
            if (lookahead == ')') {
              ss.ignore();
              break;
            }
            rhs = rec(rhs, precedence(op) + (precedence(lookahead) > precedence(op)));
            lookahead = char(ss.peek());
          }
          lhs = calc(op, lhs, rhs);
        }
      }
      return lhs;
    }
    T parse_primary() {
      if (ss.peek() == '(') {
        ss.ignore();
        return rec(parse_primary(),0);
      }
      T val; ss >> val; return val;
    }
  };
}

void code() {
  cout << Expression::Parser("11+1").eval() << nl;
}

/* MAIN CODE */

int main() { // Emily <3
  atexit([]{ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(12);
  code();
  return 0;
}

