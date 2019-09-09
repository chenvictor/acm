class KMP {
  VI fail; string p;
  public:
    KMP (string pattern) : fail(pattern.size()+1), p(pattern) { for(int i=0, j=-1; ; ++i, ++j) {
    fail[i] = j; if (i == p.size()) { break; } while (j >= 0 && p[i] != p[j]) j = fail[j]; } }
    // return offset from begin to matches in increasing order.
    // optionally returns partial matches at end of string
    VI match(string::iterator begin, string::iterator end, bool partial=false) {
      VI ans; for (int i=0,j=0; ; ++i, ++j) {
        if (j == p.size()) ans.push_back(i-j), j = fail[j];
        if (i == end - begin) { if (j && partial) { ans.push_back(i-j); } break; }
        while (j >= 0 && begin[i] != p[j]) j = fail[j];
      } return ans;
    }
};
