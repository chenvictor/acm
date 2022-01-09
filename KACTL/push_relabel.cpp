/**
 * Max-flow in O(V^2\sqrt E)
 * To obtain the actual flow, look at positive values only.
 * Source: KACTL w/ minor tweaks
 **/
struct PushRelabel {
	struct Edge {
		int d, r;
		ll f, c;
	};
	vector<vector<Edge>> g;
	vl ex;
	vector<Edge*> cur;
	vector<vi> hs; vi H;
	PushRelabel(int n) : g(n), ex(n), cur(n), hs(2*n), H(n) {}
	void addEdge(int s, int t, ll cap, ll rcap=0) {
		if (s == t) return;
		g[s].push_back({t, sz(g[t]), 0, cap});
		g[t].push_back({s, sz(g[s])-1, 0, rcap});
	}
	void addFlow(Edge& e, ll f) {
		if (!f) return;
		auto& [ed,er,ef,ec] = e;
		auto& [bd,br,bf,bc] = g[ed][er];
		if (!ex[ed]) hs[H[ed]].push_back(ed);
		ef += f; ec -= f; ex[ed] += f;
		bf -= f; bc += f; ex[bd] -= f;
	}
	ll calc(int s, int t) {
		int v = sz(g); H[s] = v; ex[t] = 1;
		vi co(2*v); co[0] = v-1;
		rep(i,0,v) cur[i] = g[i].data();
		for (Edge& e : g[s]) addFlow(e, e.c);
		for (int hi = 0;;) {
			while (hs[hi].empty()) if (!hi--) return -ex[s];
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ex[u] > 0)  // discharge u
				if (cur[u] == g[u].data() + sz(g[u])) {
					H[u] = INF;
					for (Edge& e : g[u])
						if (e.c && H[u] > H[e.d]+1)
							H[u] = H[e.d]+1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						rep(i,0,v) if (hi < H[i] && H[i] < v)
							--co[H[i]], H[i] = v + 1;
					hi = H[u];
				} else if (cur[u]->c && H[u] == H[cur[u]->d]+1)
					addFlow(*cur[u], min(ex[u], cur[u]->c));
				else ++cur[u];
		}
	}
  // true <=> v is on the source side of min-cut
	bool leftOfMinCut(int v) { return H[v] >= sz(g); }
};

