template <int N, int ALPHA, char F> // N ∼ 2*maxlen+10
struct SuffixTree {
  static int toi(char c) { return c - F; }
  string a; // v = cur node, q = cur position
  int t[N][ALPHA],l[N],r[N],p[N],s[N],v=0,q=0,m=2;
  void ukkadd(int i, int c) { suff:
    if (r[v]<=q) {
      if (t[v][c]==-1) { t[v][c]=m; l[m]=i;
        p[m++]=v; v=s[v]; q=r[v]; goto suff; }
      v=t[v][c]; q=l[v];
    }
    if (q==-1 || c==toi(a[q])) q++; else {
      l[m+1]=i; p[m+1]=m; l[m]=l[v]; r[m]=q;
      p[m]=p[v]; t[m][c]=m+1; t[m][toi(a[q])]=v;
      l[v]=q; p[v]=m; t[p[m]][toi(a[l[m]])]=m;
      v=s[p[m]]; q=l[m];
      while (q<r[m]) { v=t[v][toi(a[q])]; q+=r[v]-l[v]; }
      if (q==r[m]) s[m]=v; else s[m]=m+2;
      q=r[v]-(q-r[m]); m+=2; goto suff;
    }
  }
  SuffixTree(string a) : a(a) {
    fill(r,r+N,a.size());
    memset(s, 0, sizeof s);
    memset(t, -1, sizeof t);
    fill(t[1],t[1]+ALPHA,0);
    s[0] = 1; l[0] = l[1] = -1; r[0] = r[1] = p[0] = p[1] = 0;
    rep(i,0,sz(a)) ukkadd(i, toi(a[i]));
  }
  pii search(const string& x) {
    int cur=0,pos=0;
    for(char c : x) {
      if (pos == r[cur]) {
        cur=t[cur][toi(c)];
        if (cur == -1) return {-1,-1};
        pos=l[cur];
      }
      if (a[pos++] != c)
        return {-1,-1};
    }
    return {cur,pos};
  }
  pii to(pii cp, char x) {
    auto [c,p] = cp;
    if (p == r[c]) {
      c=t[c][toi(x)];
      if (c==-1) return {-1,-1};
      p=l[c];
    }
    if (a[p++] != x)
      return {-1,-1};
    return {c,p};
  }
};

