#if 1
template <class T> void _print(T v) { cerr << v; } void _err(istream_iterator<string> it) { (void)it; }
template <class A, class B> void _print(pair<A,B> v) { cerr << "("; _print(v.ff); cerr << ","; _print(v.ss); cerr << ")"; }
template <class T, class... Args> void _err(istream_iterator<string> it, T a, Args... args) { cerr << '\t' << *it << " = "; _print(a); _err(++it, args...); }
#define trace(...)  { cerr << "Line " << __LINE__ << ":"; string _s = #__VA_ARGS__; replace(_s.begin(), _s.end(), ',', ' ');       \
  stringstream _ss(_s); _err(istream_iterator<string>(_ss), __VA_ARGS__); cerr << nl; }
#define debug if(1)
#else
#define trace(...)	{}
#define debug if(0)
#endif
