struct Trie {
  typedef int Data;
  typedef string::iterator itt;
  static int toi(char c) {
    return c-'a';
  }
  map<int,Trie> child;
  Data data;
  bool end;
  Trie* insert(itt b, itt e) {
    Trie* cur = this;
    while (b!=e) cur = &cur->child[toi(*b++)];
    cur->end = 1;
    return cur;
  }
  Trie* find(itt b, itt e) {
    Trie* cur = this;
    while (b!=e) if (!(cur = cur->next(*b++))) return 0;
    return cur->end ? cur : 0;
  }
  Trie* next(char c) {
    auto it = child.find(toi(c));
    return it == child.end() ? 0 : &it->ss;
  }
};
