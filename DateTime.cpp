namespace DateTime {
  static const int D = 365;
  static const int mSize[12] =   { 31, 28, 31, 30,  31,  30,  31,  31,  30,  31,  30,  31 };
  static const int mPrefix[13] = {  0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
  class Date {
    // No leap years, months and dates are 1 based
    int m, d; void parseInt(int i) { assert(0 <= i && i < D); for(m=0; i >= mPrefix[m]; ++m); d = i - mPrefix[m-1] + 1; }
    public:
    Date() : m(1), d(1) { }
    // A date from the month m, and date d
    Date(int m, int d) : m(m), d(d) { assert(1 <= m && m <= 12); assert(1 <= d && d <= mSize[m-1]); }
    // A date from its integer value, compatible with toInt()
    Date(int i) { parseInt(i); }
    // converts a date to a 0 based integer representation
    // returns the number of days past Jan 1st, year optional
    int toInt() const { return mPrefix[m-1] + d - 1; }
    // return the number of days past 'b' this date is.
    // b comes STRICTLY before THIS, so if b == THIS, the result is 365!
    int daysPast(Date b) const { int ans = toInt() - b.toInt(); if (ans <= 0) { ans += 365; } return ans; }
    int getMonth() const { return m; }
    int getDay() const { return d; }
#define _op(o) bool operator o (const Date& d) const { return toInt() o d.toInt(); }
  _op(<); _op(<=); _op(>); _op(>=); _op(==); _op(!=);
#undef _op
    Date& operator+=(int offset) { parseInt((toInt()+offset) % D); return *this; }
    Date& operator-=(int offset) { parseInt(((toInt()-offset) % D + D) % D); return *this; }
    Date  operator+(int offset) { Date cpy = *this; return cpy += offset; }
    Date  operator-(int offset) { Date cpy = *this; return cpy -= offset; }
  };
} using namespace DateTime;
