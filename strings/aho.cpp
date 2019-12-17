//https://github.com/kth-competitive-programming/kactl/blob/master/content/strings/AhoCorasick.h
struct Aho {
  static const int ALPHA = 26;
    static int toi(char c) {
    return c - 'a';
  }
  struct Node {
    int back, next[ALPHA], start = -1, end = -1, nmatches = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  int sz = 0;
  vector<Node> N = {-1}; VI backp;
  int insert(string& s) {
    assert(!s.empty());
    int j = sz++;
    int n = 0;
    for (char c : s) {
      int& m = N[n].next[toi(c)];
      if (m == -1) { n = m = N.size(); N.emplace_back(-1); }
      else n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    N[n].nmatches++;
    return n;
  }
  void build() {
    N[0].back = N.size();
    N.emplace_back(0);
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      forx(i,ALPHA) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1) ed = y;
        else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
            = N[y].end;
          N[ed].nmatches += N[y].nmatches;
          q.push(ed);
        }
      }
    }
    N[0].back = 0; N.pop_back();
  }
  VI find(string word) {
    int n = 0;
    VI res; // ll count = 0;
    for(char c : word) {
      n = N[n].next[c - first];
      res.push_back(N[n].end);
      // count += N[n].nmatches;
    }
    return res;
  }
  vector<VI> findAll(vector<string>& pat, string word) {
    VI r = find(word);
    vector<VI> res(word.size());
    forx(i,word.size()) {
      int ind = r[i];
      while (ind != -1) {
        res[i - pat[ind].size() + 1].push_back(ind);
        ind = backp[ind];
      }
    }
    return res;
  }
};
