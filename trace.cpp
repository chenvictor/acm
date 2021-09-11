/* DEBUG */

#if (DEBUG && !defined(ONLINE_JUDGE))
template <class T> void _print(const T& t) { cerr << t << " "; }
template <class T> void _print(const vector<T>& t) {
  cerr << "[ "; for (auto it : t) cerr << it << " "; cerr << "]"; }
template <class TT, size_t... I>
void _print(const TT& tup, typename std::index_sequence<I...>) {
  (..., (cerr << get<I>(tup) << ", ")); }
template <class... T> void _print(tuple<T...>& t) {
  _print(t, index_sequence_for<T...>()); }
#define trace(x)  { cerr << ">> Line " << __LINE__ << ": " #x " = "; _print(x); cerr << nl; }
#define debug if(1)
#else
#define trace(...)	{}
#define debug if(0)
#endif

