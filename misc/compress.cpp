// compress an array or vector of integers in place
// returns the reverse mapping
template <class Iter>
map<int,int> compress(Iter begin, Iter end) {
  map<int,int> rev;
  for(Iter it = begin; it != end; ++it) rev[*it] = 0;
  int idx = 0;
  for (auto& it : rev) { it.ss = idx++; }
  for(Iter it = begin; it != end; ++it) *it = rev[*it];
  return rev;
}

