/**
 * Range Queries of idempotent operations (e.g. min/max)
 * Time: O(nlogn) build, O(1) per query
 * Source: KACTL w/ minor tweaks
 **/
template<class T, class Cmp=less<>> struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw], Cmp());
		}
	}
	T query(int a, int b, T&& empty) {
    assert(a <= b);
    if (a == b) return empty;
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)], Cmp());
	}
};

