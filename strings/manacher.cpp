/**
 * Description: O(n) max length palindrome
 * P[2i]   = centered at s[i]        (odd)
 * P[2i+1] = centered at s[i]-s[i+1] (even)
 *
 * For max palindrome:
    int i = max_element(all(len))-len.begin();
    s.substr(i/2-(len[i]-1)/2, len[i])
 **/
vi manacher(const string& s) {
  vi P(sz(s)*2-1);
  for (int i = P[0] = 1,d,l,r; i+2 < 2*sz(s); i += d) {
    int& p = P[i]; l = (i - p - 1)/2, r = (i + p + 1)/2;
    while(0 <= l && r < sz(s) && s[l] == s[r]) --l, ++r, p += 2;
    for(d = 1; P[i-d] < p-d; P[i+d] = P[i-d], ++d);;
    P[i+d] = p-d;
  }
  return P;
}

