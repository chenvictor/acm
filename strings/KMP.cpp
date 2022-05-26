/**
 * Description: KMP prefix function/automaton
 * Source: https://cp-algorithms.com/string/prefix-function.html
 * Time: O(n)
 *
 * pi[0] = 0
 * pi[i] = length of longest proper prefix+suffix of s[0...i]
 **/
vi pi(const string& s) {
  vi p(sz(s));
  rep(i,1,sz(s)) {
    int j=p[i-1];
    while(j&&s[i]!=s[j]) j=p[j-1];
    p[i]=j+(s[i]==s[j]);
  }
  return p;
}
/**
 * state is #chars matched (initial 0)
 * aut[i][k] is transition
 **/
template <int ALPHA, char F>
vector<array<int,ALPHA>> automaton(string s) {
  s += "#";
  vi p = pi(s);
  vector<array<int,ALPHA>> aut(sz(s));
  rep(i,0,sz(s)) {
    rep(c,0,ALPHA) {
      if (i > 0 && F + c != s[i])
        aut[i][c] = aut[p[i-1]][c];
      else
        aut[i][c] = i + (F + c == s[i]);
    }
  }
  return aut;
}

