template <size_t N, class T=ll, bool=is_integral<T>::value>
struct Choose {
  array<T,N> f,i; Choose() { f[0]=1; rep(j,1,N) f[j] = f[j-1]*j;
    i[N-1]=f[N-1].inv(); for(int j=N; --j;) i[j-1] = i[j]*j; }
  T operator()(int n, int k) const { return f[n] * i[k] * i[n-k]; }
};
template <size_t N, class T>
struct Choose<N,T,true> {
  array<T,N> f; Choose() { f[0]=1; rep(j,1,N) f[j] = f[j-1]*j; }
  T operator()(int n, int k) const { return f[n] / f[k] / f[n-k]; }
};

