#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,e) for(int i = s; i < (e); ++i)
using ll = long long; using ld = long double;
using pii = pair<int,int>; using pll = pair<ll, ll>;
using vi = vector<int>; using vl = vector<ll>;
const char nl = '\n';
const ll LINF = 0x3f3f3f3f3f3f3f3fll; const int INF = (int)LINF;
const ld EPS = 1e-9, PI = acos(-1.0L);
#define ff first
#define ss second
#define all(c) begin(c),end(c)
#define sz(c) int(c.size())
template <typename T, typename Cmp = less<T>>
using heap = priority_queue<T,vector<T>,Cmp>;
template <class T, size_t N=0>
using arr = typename conditional<N,array<T,N>,vector<T>>::type;

// tuple i/o
template <typename...T> istream& operator>>(istream& is, tuple<T&...> t) { return apply([&](auto&&... a) { ((is >> a), ...); }, t), is; }
template <typename...T> ostream& operator<<(ostream& os, const tuple<T...>& t) { return apply([&](auto&& f, auto&&... r) { os << f; ((os << " " << r), ...); }, t), os; }
// pair i/o
template <typename...T> istream& operator>>(istream& is, pair<T&...>& v) { return is >> v.ff >> v.ss; }
template <typename...T> ostream& operator<<(ostream& os, const pair<T...>& v) { return os << v.ff << " " << v.ss; }

#if (DEBUG && !defined(ONLINE_JUDGE))
#define trace(...) cerr << make_tuple(">> Line",__LINE__,#__VA_ARGS__,"=",__VA_ARGS__,"<<") << endl
#define ifdebug if(1)
#else
#define trace(...)
#define ifdebug if(0)
#endif

/* BOOK CODE */

const int base=1000000000;

template <size_t N>
struct bigint {
  constexpr static int BASE = 1e9;
  using bi = bigint;
  int len=0; array<int,N> data;
  bigint() { }
	bigint(int x) { for(;x>0;x/=base) data[len++]=x%base; }
  bigint(const string& s) {

  }
	int &operator[](int i) { return data[i]; }
	int operator[](int i) const { return (i<len)*data[i]; }
  friend istream& operator>>(istream& is, bi &x) {
    static string s; is >> s; x=s; return is;
  }
  friend ostream& operator<<(ostream&output, const bi &x) {
    output<<(x.len==0?0:x[x.len-1]);
    for(int i=x.len-2;i>=0;i--)
      for(int j=base/10;j>0;j/=10)
        output<<x[i]/j%10;
    return output;
  }
};

//int compare(const bigint &a,const bigint &b) {
//	int i;
//	if(a.len!=b.len)return a.len>b.len?1:-1;
//
//	for(i=a.len-1;i>=0&&a[i]==b[i];i--);
//	if(i<0)return 0;
//	return a[i]>b[i]?1:-1;
//}
//bool operator==(const bigint &a,const bigint &b) { return compare(a,b)==0; }
//bool operator!=(const bigint &a,const bigint &b) { return compare(a,b)!=0; }
//bool operator>(const bigint &a,const bigint &b) { return compare(a,b)>0; }
//bool operator<(const bigint &a,const bigint &b) { return compare(a,b)<0; }
//bool operator>=(const bigint &a,const bigint &b) { return compare(a,b)>=0; }
//bool operator<=(const bigint &a,const bigint &b) { return compare(a,b)<=0; }
//
//bigint operator+(const bigint &a,const bigint &b) {
//	bigint c; int i,x=0;
//
//	for(i=0;i<a.len||i<b.len||x>0;i++) {
//		if(i<a.len)x+=a[i];
//		if(i<b.len)x+=b[i];
//		c[i]=x%base;
//		x/=base;
//	}
//
//	c.len=i;
//	return c;
//}
//
//bigint operator-(const bigint &a,const bigint &b) {
//	bigint c; int x=0; c.len=a.len;
//
//	for(int i=0;i<c.len;i++) {
//		c[i]=a[i]-x;
//		if(i<b.len)c[i]-=b[i];
//
//		if(c[i]<0) x=1,c[i]+=base;
//		else x=0;
//	}
//	while(c.len>0&&c[c.len-1]==0)c.len--;
//	return c;
//}
//
//bigint operator*(const bigint &a,const int b) {
//	int i; if(b==0)return 0; bigint c; long long x=0;
//
//	for(i=0;i<a.len||x>0;i++) {
//		if(i<a.len)x+=(long long)(a[i])*b;
//		c[i]=x%base;
//		x/=base;
//	}
//
//	c.len=i;
//	return c;
//}
//
//bigint operator*(const bigint &a,const bigint &b) {
//	if(b.len==0)return 0;
//  bigint c;
//	for(int i=0;i<a.len;i++) {
//		long long x=0;
//		for(int j=0;j<b.len||x>0;j++) {
//			if(j<b.len)x+=(long long)(a[i])*b[j];
//			if(i+j<c.len)x+=c[i+j];
//
//			if(i+j>=c.len)
//				c[c.len++]=x%base;
//			else
//				c[i+j]=x%base;
//			x/=base;
//		}
//	}
//
//	return c;
//}
//
//bigint operator/(const bigint &a,const int b) {
//	bigint c;
//	long long x=0;
//
//	for(int i=a.len-1;i>=0;i--) {
//		x=x*base+a[i];
//		c[i]=x/b;
//		x%=b;
//	}
//
//	c.len=a.len;
//	while(c.len>0&&c[c.len-1]==0)c.len--;
//
//	return c;
//}
//
//bigint operator/(const bigint &a,const bigint &b) {
//	bigint c,x=0;
//	int l,r,mid;
//
//	for(int i=a.len-1;i>=0;i--) {
//		x=x*base+a[i];
//		l=0;
//		r=base-1;
//
//		while(l<=r) {
//			mid=(l+r)>>1;
//
//			if(compare(b*mid,x)<=0) l=mid+1;
//			else r=mid-1;
//		}
//
//		c[i]=r; x=x-b*r;
//	}
//
//	c.len=a.len;
//	while(c.len>0&&c[c.len-1]==0)c.len--;
//	return c;
//}
//
//bigint operator%(const bigint &a,const bigint &b) {
//	bigint temp;
//	temp=a/b;
//	temp=a-b*temp;
//
//	return temp;
//}


/* REAL CODE */

void code() {

}

/* MAIN CODE */

int main() { // Emily <3
  atexit([]{ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(12);
  code();
  return 0;
}

