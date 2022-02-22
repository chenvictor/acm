/**
 * 2D Grid traversal neighbors   0,0 → y
 * starting EAST going cc-wise    ↓
 *                                x
 **/
template <int D=4> constexpr initializer_list<pii>
  Grid = {{0,1},{-1,0},{0,-1},{1,0}};
template <> constexpr initializer_list<pii>
  Grid<8> = {{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1}};

