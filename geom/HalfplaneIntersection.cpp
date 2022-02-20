namespace HPI {
  // Source: https://cp-algorithms.com/geometry/halfplane-intersection.html
  // - https://open.kattis.com/problems/bigbrother
  const St inf = 1e9;
  struct HP {
    Pt p,pq; St a;
    HP() {}
    HP(const Pt &x, const Pt& y): p(x), pq(y-x){
      a = atan2(imag(pq),real(pq));
    }
    bool out(const Pt& r) const {
      return cp(pq,r-p)<EPS;
    }
    bool operator<(const HP& e) const {
      if (abs(a-e.a)<EPS) return out(e.p);
      return a<e.a;
    }
    bool operator==(const HP& e) const {
      return a==e.a;
    }
  };
  Pt inter(const HP& s, const HP& t) {
    return s.p + s.pq*cp(t.p-s.p,t.pq)/cp(s.pq,t.pq);
  }
  vector<Pt> solve(vector<HP>& h) {
    // optional bounding box
      Pt bb[] = {{inf,inf},{-inf,inf},{-inf,-inf},{inf,-inf},{inf,inf}};
      rep(i,0,4) h.emplace_back(bb[i],bb[i+1]);
    sort(all(h));
    h.erase(unique(all(h)), h.end());
    deque<HP> dq;
    int n=0;
#define CLEAN(l,hp,i,op) while(n>l && hp.out(inter(dq[i],dq[i+1]))) {dq.op(); --n;}
    for(auto& hp : h) {
      CLEAN(1,hp,n-2,pop_back);
      CLEAN(1,hp,0,pop_front);
      dq.push_back(hp); ++n;
    }
    CLEAN(2,dq[0],n-2,pop_back);
    CLEAN(2,dq.back(),0,pop_front);
    if (n<3) return {};
    vector<Pt> res(n);
    res[0] = inter(dq.back(),dq[0]);
    rep(i,1,n) {
      res[i] = inter(dq[i],dq[i-1]);
    }
    return res;
  }
};

