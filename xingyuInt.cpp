#include <bits/stdc++.h>
using namespace std;
#define CM ,
#define TD(a,b) typedef a b
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

#define DEBUG 1
#if     DEBUG
#define trace(var)  {cerr << "Line " << __LINE__ << ": " << #var << "=" << var << nl;}
#else
#define trace(var)	{}
#endif
const int base=1000000000;
const int maxn=500;

class bigint
{
public:
	int len;
	int data[maxn+10];
	
	bigint():len(0){}	
	bigint(const bigint &x):len(x.len) { memcpy(data,x.data,len*sizeof(int)); }
	
	bigint(int x):len(0) { for(;x>0;x/=base) data[len++]=x%base; }
	
	bigint &operator=(const bigint &x) { len=x.len; memcpy(data,x.data,len*sizeof*data); return *this; }

	int &operator[](int i) { return data[i]; }

	int operator[](int i) const { return i<len?data[i]:0; }
};

int compare(const bigint &a,const bigint &b) {
	int i;
	if(a.len!=b.len)return a.len>b.len?1:-1;
	
	for(i=a.len-1;i>=0&&a[i]==b[i];i--);
	if(i<0)return 0;
	return a[i]>b[i]?1:-1;
}
bool operator==(const bigint &a,const bigint &b) { return compare(a,b)==0; }
bool operator!=(const bigint &a,const bigint &b) { return compare(a,b)!=0; }
bool operator>(const bigint &a,const bigint &b) { return compare(a,b)>0; }
bool operator<(const bigint &a,const bigint &b) { return compare(a,b)<0; }
bool operator>=(const bigint &a,const bigint &b) { return compare(a,b)>=0; }
bool operator<=(const bigint &a,const bigint &b) { return compare(a,b)<=0; }

bigint operator+(const bigint &a,const bigint &b) {
	bigint c; int i,x=0;
	
	for(i=0;i<a.len||i<b.len||x>0;i++) {
		if(i<a.len)x+=a[i];
		if(i<b.len)x+=b[i];
		c[i]=x%base;
		x/=base;
	}
	
	c.len=i;
	return c;
}

bigint operator-(const bigint &a,const bigint &b) {
	bigint c; int x=0; c.len=a.len;
	
	for(int i=0;i<c.len;i++) {
		c[i]=a[i]-x;
		if(i<b.len)c[i]-=b[i];
		
		if(c[i]<0) x=1,c[i]+=base;
		else x=0;
	}
	while(c.len>0&&c[c.len-1]==0)c.len--;
	return c;
}

bigint operator*(const bigint &a,const int b) {
	int i; if(b==0)return 0; bigint c; long long x=0;
	
	for(i=0;i<a.len||x>0;i++) {
		if(i<a.len)x+=(long long)(a[i])*b;
		c[i]=x%base;
		x/=base;
	}
	
	c.len=i;
	return c;
}

bigint operator*(const bigint &a,const bigint &b) {
	if(b.len==0)return 0;
  bigint c;
	for(int i=0;i<a.len;i++) {
		long long x=0;
		for(int j=0;j<b.len||x>0;j++) {
			if(j<b.len)x+=(long long)(a[i])*b[j];
			if(i+j<c.len)x+=c[i+j];
			
			if(i+j>=c.len)
				c[c.len++]=x%base;
			else
				c[i+j]=x%base;
			x/=base;
		}
	}
	
	return c;
}

bigint operator/(const bigint &a,const int b) {
	bigint c;
	long long x=0;
	
	for(int i=a.len-1;i>=0;i--) {
		x=x*base+a[i];
		c[i]=x/b;
		x%=b;
	}
	
	c.len=a.len;
	while(c.len>0&&c[c.len-1]==0)c.len--;
	
	return c;
}

bigint operator/(const bigint &a,const bigint &b) {
	bigint c,x=0;
	int l,r,mid;
	
	for(int i=a.len-1;i>=0;i--) {
		x=x*base+a[i];
		l=0;
		r=base-1;
		
		while(l<=r) {
			mid=(l+r)>>1;
			
			if(compare(b*mid,x)<=0) l=mid+1;
			else r=mid-1;
		}
		
		c[i]=r; x=x-b*r;
	}
	
	c.len=a.len;
	while(c.len>0&&c[c.len-1]==0)c.len--;
	return c;
}

bigint operator%(const bigint &a,const bigint &b) {
	bigint temp;
	temp=a/b;
	temp=a-b*temp;
	
	return temp;
}

istream&operator>>(istream&input,bigint &x) {
	char c;
	
	for(x=0;input>>c;) {
		x=x*10+(c-'0');
		if(input.peek()<=' ')break;
	}	
	return input;
}

ostream&operator<<(ostream&output,const bigint &x) {
	output<<(x.len==0?0:x[x.len-1]);
	
	for(int i=x.len-2;i>=0;i--)
		for(int j=base/10;j>0;j/=10)
			output<<x[i]/j%10;
			
	return output;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3  
  bigint a, b;
  cout << "Enter num" << endl;
  cin >> a;
  cout << "Enter num" << endl;
  cin >> b;
  bigint c;
  c = a+b;
  c = a-b;
  c = a/b;
  c = a%b;
  c = a*b;
  cerr << (ld) clock() / CLOCKS_PER_SEC << nl;
  return 0;
}


