namespace DateTime {
  const int D = 365;
  const int mSize[12] =   { 31, 28, 31, 30,  31,  30,  31,  31,  30,  31,  30,  31 };
  const int mPrefix[13] = {  0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
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
  const map<string, int> dayIndex = { {"Monday", 0}, {"Tuesday", 1}, {"Wednesday", 2}, {"Thursday", 3}, {"Friday", 4}, {"Saturday", 5}, {"Sunday", 6} };
  const string dayString[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
  // Returns the index of a weekday, 0 = Monday, 1 = Tuesday, ... 6 = Sunday
  int dayToIndex(string& s) { auto it = dayIndex.find(s); assert(it != dayIndex.end()); return it->ss; }
  string indexToDay(int idx) { assert(0 <= idx && idx < 7); return dayString[idx]; }
} using namespace DateTime;

