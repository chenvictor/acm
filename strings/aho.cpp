// https://github.com/kth-competitive-programming/kactl/blob/master/content/strings/AhoCorasick.h
// 1. Aho::insert() strings
// 2. Aho::build()
// root is node 0
template <int K=26>
struct Aho {
  struct Node {
    int back, nx[K], cnt = 0, s, end = -1;
    //  ^suffix link ^# matches  ^ longest match ending at this node
    Node(int v) { fill(all(nx), v); }
  };
  int sz = 0; vector<Node> N = {-1}; vi backp;
  Aho(int rs=0) {
    N.reserve(rs);
    backp.reserve(rs);
  }
  // backp[i] is the longest suffix of string i, -1 if none
  // returns terminal node of added string
  int insert(const string& s) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int& m = go(n,c);
      if (m == -1) { n = m = sz(N); N.emplace_back(-1); }
      else n = m;
    }
    if (N[n].end == -1) N[n].s = sz;
    backp.push_back(N[n].end);
    N[n].end = sz++;
    N[n].cnt++;
    return n;
  }
  void build() {
    N[0].back = sz(N);
    N.emplace_back(0);
    for (queue<int> q({0}); q.size(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      rep(i,0,K) {
        int &ed = N[n].nx[i], y = N[prev].nx[i];
        if (ed == -1) {
          ed = y;
        } else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].s])
            = N[y].end;
          N[ed].cnt += N[y].cnt;
          q.push(ed);
        }
      }
    }
    N[0].back = 0; N.pop_back();
  }
  int& go(int i, char c) {
    // TODO change base
    return N[i].nx[c - 'a'];
  }
  vi find(const string& word) {
    int i=0;
    vi res; // ll count = 0;
    for(char c : word) {
      i = go(i,c);
      res.push_back(N[i].end);
      // count += N[i].cnt;
    }
    return res;
  }
  // returns all matches starting at each pos, shortest first
  // findAll type operations NsqrtN ONLY IF STRINGS DISTINCT
  vector<vi> findAll(vector<string>& pat, const string& word) {
    vi r = find(word);
    vector<vi> res(sz(word));
    rep(i,0,sz(word)) {
      int ind = r[i];
      while (ind != -1) {
        res[i - pat[ind].size() + 1].push_back(ind);
        ind = backp[ind];
      }
    }
    return res;
  }
};

