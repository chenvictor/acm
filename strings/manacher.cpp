// even palin btwn s[i],s[i+1]: P[2*i+1]
VI find_pals(const string& s) {
  VI P(s.size()*2-1);
  for (int i = P[0] = 1,d,l,r; i+2 < 2*(int)s.length(); i += d) {
    int& p = P[i]; l = (i - p - 1)/2, r = (i + p + 1)/2;
    for(;0 <= l && r < s.size() && s[l] == s[r]; --l, ++r, p += 2);
    for(d = 1; P[i-d] < p-d; P[i+d] = P[i-d], ++d);; P[i+d] = p-d; }
  return P;
}
