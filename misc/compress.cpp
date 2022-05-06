/**
 * Compress in-place, returns reverse mapping
 **/
vi compress(vi& vec) {
  vi mp = vec;
  sort(all(mp));
  mp.erase(unique(all(mp)), mp.end());
  for (int& v : vec) v = int(lower_bound(all(mp), v)-mp.begin());
  return mp;
}

