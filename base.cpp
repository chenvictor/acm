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
#define TESTCASES(t) int t=0,_TC; cin >> _TC; while(t++<_TC)
template <typename T, typename Cmp = less<T>>
using heap = priority_queue<T,vector<T>,Cmp>;

// tuple i/o
template <typename...T> istream& operator>>(istream& is, tuple<T&...> t) { return apply([&](auto&&... a) { ((is >> a), ...); }, t), is; }
template <typename...T> ostream& operator<<(ostream& os, const tuple<T...>& t) { return apply([&](auto&& f, auto&&... r) { os << f; ((os << " " << r), ...); }, t), os; }
// pair i/o
template <typename...T> istream& operator>>(istream& is, pair<T&...>& v) { return is >> v.ff >> v.ss; }
template <typename...T> ostream& operator<<(ostream& os, const pair<T...>& v) { return os << v.ff << " " << v.ss; }

#if (DEBUG && !defined(ONLINE_JUDGE))
template<typename T> void _print(const T& t) { cerr << t; }
template<typename Head, typename... Tail> void _print(Head h, Tail... t) { _print(h); cerr << ","; _print(t...); }
#define trace(...) cerr << ">> Line " << __LINE__ << ": " #__VA_ARGS__ " = "; _print(__VA_ARGS__); cerr << endl
#define ifdebug if(1)
#else
#define trace(...)
#define ifdebug if(0)
#endif

/* BOOK CODE */

/* REAL CODE */

void code() {

}

/* MAIN CODE */

int main() { // Emily <3
  atexit([]{ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(12);
  code();
  return 0;
}
