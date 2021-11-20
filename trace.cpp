/* DEBUG */

#if (DEBUG && !defined(ONLINE_JUDGE))
template<typename T> void _print(const T& t) { cerr << t; }
template<typename Head, typename... Tail> void _print(Head h, Tail... t) { _print(h); cerr << ","; _print(t...); }
template<typename F, typename S> void _print(const pair<F,S> &p) { cerr << "("; _print(p.ff, p.ss); cerr << ")"; }
template <typename... T> void _print(tuple<T...>& t) { cerr << "<"; apply([](auto&&... args){ _print(args...); }, t); cerr << ">"; }
#define trace(...) cerr << ">> Line " << __LINE__ << ": " #__VA_ARGS__ " = "; \
  _print(__VA_ARGS__); cerr << endl
#define ifdebug if(1)
#else
#define trace(...)
#define ifdebug if(0)
#endif

