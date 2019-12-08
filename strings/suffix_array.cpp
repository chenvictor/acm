struct SuffixArray {
  const string s;
	VI sa;  //suffix array
  VI inv; //inverse
  VI lcp; //longest common prefix
  //burrow wheeler
  char bwt(int i) const { return sa[i] ? s[sa[i]-1] : ' '; }
  // child table
	SuffixArray(const string& _, int lim = 256) : s(_) {
		int n = s.size() + 1, k = 0, a, b;
		VI x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = inv = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			forx(i,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			forx(i,n) ws[x[i]]++;
			forx(i,lim-1) ws[i+1] += ws[i];
			forxr(i,n) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			forx(i,n-1) a = sa[i], b = sa[i+1], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		forx(i,n-1) rank[sa[i+1]] = i+1;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
    forx(i,n) inv[sa[i]] = i;
	}
};
