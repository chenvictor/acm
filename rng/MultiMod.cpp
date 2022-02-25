/**
 * Multiple values with multiple mods
 * Element-wise + - * operations
 **/
template<int... M> struct MultiMod: array<int,sizeof...(M)> {
  static constexpr size_t SZ = sizeof...(M);
  static constexpr array<int,SZ> MOD = {M...};
#define IMPL(x) MultiMod res; rep(i,0,SZ) res[i] = x % MOD[i]; return res;
  MultiMod operator+ (MultiMod o) const { IMPL( (SELF[i]+o[i])        )}
  MultiMod operator- (MultiMod o) const { IMPL( (SELF[i]+MOD[i]-o[i]) )}
  MultiMod operator* (MultiMod o) const { IMPL( ll(SELF[i])*o[i]      )}
  friend ostream& operator<<(ostream& os, const MultiMod& hv) {
    os << "<"; for (int v : hv) os << " " << v;
    return os << " >";
  }
};

