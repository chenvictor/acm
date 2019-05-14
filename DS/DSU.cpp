class DSU {
	vector<int> p, s; int c;
	public:
		DSU (int n) : p(n), s(n, 1) { c = n; for(int i = 0; i < n; ++i) p[i] = i; }
		int find(int x) { return (p[x] == x) ? p[x] : p[x] = find(p[x]); }
		int size(int x) { return s[find(x)]; } int count() { return c; }
		void join(int x, int y) {
			if (find(x) == find(y)) return;; if (s[p[x]] > s[p[y]]) swap(p[x], p[y]);
			p[p[x]] = p[y]; s[p[y]] += s[p[x]]; c--;
		}
};
