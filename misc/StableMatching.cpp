/**
 * Gale Shapley stable matching
 * https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm
 * O(nm)
 * 0. StableMatching(n = #men, m = #women) n <= m
 * 1. initialize prefs (0-indexed, list of most to least preferred)
 *    - men    => pri[id] = {...}
 *    - women: => addWoman(id, {...})
 * 2. calc()
 * 3. match[i] = woman i's man (-1 => unmatched)
 *    mit[i]   = man i's woman
 **/
struct StableMatching {
  vector<vi> pri, p;
  vi mit, match;
  StableMatching(int n, int m): pri(n),p(m,vi(n)),mit(n,-1),match(m,-1) {
    assert(n <= m);
  }
  void addWoman(int id, const vi& pref) {
    rep(i,0,sz(pref)) p[id][pref[i]] = i;
  }
  void calc() {
    queue<int> pro;
    rep(i,0,sz(pri)) pro.push(i);
    while(sz(pro)) {
      int id = pro.front(); pro.pop();
      while(1) {
        int to = pri[id][++mit[id]];
        int& opp = match[to];
        if (opp == -1) {
          opp = id;
          break;
        } else if (p[to][opp] > p[to][id]) {
          pro.push(opp);
          opp = id;
          break;
        }
      }
    }
  }
};

