#if (DEBUG && !defined(ONLINE_JUDGE))
template <class T>
void _prt(T v) { cerr << v; }
template <class A, class B>
void _prt(pair<A,B>& v) { cerr << "("; _prt(v.ff); cerr << ","; _prt(v.ss); cerr << ")"; }
template <class E>
void _prt(vector<E>& vec) { cerr << "["; for(E& v:vec) _prt(v), cerr << " "; cerr << "]"; }
template <class T, class... Args> void _prt(T a, Args... args) {
  _prt(a); cerr << nl; _prt(args...); }
#define trace(...)  { cerr << "Line " << __LINE__ << nl; _prt(__VA_ARGS__); cerr << nl; }
#define debug if(1)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define trace(...)	{}
#define debug if(0)
#define eprintf(...) {}
#endif

