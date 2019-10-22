// more: http://www.cplusplus.com/reference/algorithm/

// find v st. eval(v) = true
// s < e maximizes, s > e minimizes
int b_search(function<bool(int)> eval, int s, int e) { while (abs(s-e) > 1) { int mid = s + (e-s)/2; eval(mid) ? s = mid : e = mid; } return s; }

// return {x', val} where val = eval(x') = max { eval(x) }
pld t_search(function<ld(ld)> eval, ld left, ld right, ld eps = EPS) { while (abs(right-left) > eps) { ld third = (right-left)/3;
    eval(left + third) < len(right - third) ? right -= third : left += third; } return {left, eval(left)}; }
