vector<pt> cxc(pt c1, ld r1, pt c2, ld r2) {
  ld dq = norm(c1-c2), rq=r1*r1-r2*r2;
  pt c = (c1+c2)+(c2-c1)*rq/dq; c*=.5;
  ld dt=2*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if (dt < -EPS) return {};
  if (dt < EPS) return {c};
  dt=sqrt(dt)/2/dq;
  pt d = (c2-c1)*pt(0,1)*dt;
  return {c+d, c-d};
}
