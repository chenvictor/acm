#ifndef NDEBUG
#define trace(var)  {cerr << "Line " << __LINE__ << ": " << #var << "=" << (var) << nl;}
#else
#define trace(var)	{}
#endif
