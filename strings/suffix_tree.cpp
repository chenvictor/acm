struct SuffixTree {
  static const int ALPHA = 26+1;
  int toi(char c) {
    return c - 'A';
  }
	const string a;
  const int n;
  vector<array<int,ALPHA>> t;
  VI l,r,p,s;
	int v=0,q=0,m=2;
	void ukkadd(int i, int c) { suff:
		if (r[v]<=q) {
			if (t[v][c]==-1) { t[v][c]=m;  l[m]=i;
				p[m++]=v; v=s[v]; q=r[v];  goto suff; }
			v=t[v][c]; q=l[v];
		}
		if (q==-1 || c==toi(a[q])) q++; else {
			l[m+1]=i;  p[m+1]=m;  l[m]=l[v];  r[m]=q;
			p[m]=p[v];  t[m][c]=m+1;  t[m][toi(a[q])]=v;
			l[v]=q;  p[v]=m;  t[p[m]][toi(a[l[m]])]=m;
			v=s[p[m]];  q=l[m];
			while (q<r[m]) { v=t[v][toi(a[q])];  q+=r[v]-l[v]; }
			if (q==r[m])  s[m]=v;  else s[m]=m+2;
			q=r[v]-(q-r[m]);  m+=2;  goto suff;
		}
	}
	SuffixTree(const string& a) : a(a), n(2*a.size()+10), t(n), l(n), r(n,n), p(n), s(n) {
    forx(i,n) fill(t[i].begin(), t[i].end(), -1);
    fill(t[1].begin(), t[1].end(), 0);
		s[0] = 1; l[0] = l[1] = -1; r[0] = r[1] = 0;
		forx(i,a.size()) ukkadd(i, toi(a[i]));
	}
};
