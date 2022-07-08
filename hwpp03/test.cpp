#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

//=================================================================================================
// a dummy exception class, keep this implementation
class InvalidDateException : public invalid_argument
{
public:
  InvalidDateException ( )
    : invalid_argument ( "invalid date or format" )
  {
  }
};
//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base & ( * date_format ( const char * fmt ) ) ( ios_base & x )
{
  return [] ( ios_base & ios ) -> ios_base & { return ios; };
}
//=================================================================================================
class CDate
{
protected:
  time_t rawtime;
  struct tm timeinfo;
  char separator;
  short int daysInMonth[13] = {69, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

public:
  CDate(short int year, short int month, short int day)
  {
   if(month < 1 || month > 12) throw InvalidDateException();

   short int dInMo = getNODays(year, month);

   if(day > dInMo || day < 1) throw InvalidDateException();
  
   this->timeinfo = {0};

   this->timeinfo.tm_year = year - 1900;
   this->timeinfo.tm_mon = month - 1;
   this->timeinfo.tm_mday = day;

   this->rawtime = mktime(&this->timeinfo);

   this->timeinfo.tm_year = year;
   this->timeinfo.tm_mon = month;
   this->timeinfo.tm_mday = day;

   separator = '-';
  }

  friend ostream & operator << (ostream & out, const CDate & date);
  friend bool operator >> (istream & in, CDate & date);

  CDate & operator++();
  CDate & operator--();
  CDate operator++(int);
  CDate operator--(int);
  CDate operator+(int);
  CDate operator-(int);
  CDate operator+(CDate &);
  int operator-(CDate &);

  bool operator==(CDate &);
  bool operator!=(CDate &);
  bool operator<=(CDate &);
  bool operator>=(CDate &);
  bool operator< (CDate &);
  bool operator> (CDate &);

private:
  bool isLeap(short int year)
  {
    if(year % 4 != 0) return 0;
    if(year % 400 == 0) return 1;
    if(year % 100 == 0) return 0;
    return 1;
  }
  
  short int getNODays(short int year, short int month)
  {
    short int ret = daysInMonth[month];

    if(month == 2 && isLeap(year)) ret += 1;

    return ret;
  }
};

ostream & operator << (ostream & out, const CDate & date)
{
  out << date.timeinfo.tm_year << date.separator 
      << setw(2) << setfill('0') << date.timeinfo.tm_mon << date.separator
      << setw(2) << setfill('0') << date.timeinfo.tm_mday;
  
  return out;
}

bool operator >> (istream & in, CDate & date)
{
  char tmpO, tmpT;
  short int year, month, day;

  in >> year >> tmpO >> month >> tmpT >> day;

  if(tmpO != '-' || tmpT != '-') 
  {
    in.setstate(ios::failbit);
    return 0;
  }
  if(month < 1 || month > 12)
  {
    in.setstate(ios::failbit);
    return 0;
  }

  short int dInMo = date.getNODays(year, month);

  if(day > dInMo || day < 1)
  {
    in.setstate(ios::failbit);
    return 0;
  }
  
  date.timeinfo.tm_year = year;
  date.timeinfo.tm_mon = month;
  date.timeinfo.tm_mday = day;

  return 1;
}

bool isLeap(short int year)
  {
    if(year % 4 != 0) return 0;
    if(year % 400 == 0) return 1;
    if(year % 100 == 0) return 0;
    return 1;
  }

short int daysInMonthFun(short int year, short int month)
{
  short int daysInMonth[13] = {69, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  short int ret = daysInMonth[month];
  if(month == 2 && isLeap(year)) ret += 1;

  return ret;
}

CDate CDate::operator++(int)
{
  short int dInMo = daysInMonthFun(timeinfo.tm_year, timeinfo.tm_mon);
  
  CDate ret = *this;

  timeinfo.tm_mday++;

  if((timeinfo.tm_mday) > dInMo)
  {
    timeinfo.tm_mday = 1;
    timeinfo.tm_mon++;

    if(timeinfo.tm_mon == 13)
    {
      timeinfo.tm_mon = 1;
      timeinfo.tm_year++;
    }
  }

  struct tm tmp = timeinfo;

  tmp.tm_year -= 1900;
  tmp.tm_mon -= 1;

  rawtime = mktime(&tmp);

  return ret;
}

CDate CDate::operator--(int)
{
  CDate ret = *this;

  timeinfo.tm_mday--;

  if((timeinfo.tm_mday) == 0)
  {
    timeinfo.tm_mon--;

    if(timeinfo.tm_mon == 0)
    {
      timeinfo.tm_mon = 12;
      timeinfo.tm_year--;
    }

    timeinfo.tm_mday = daysInMonthFun(timeinfo.tm_year, timeinfo.tm_mon);
  }

  struct tm tmp = timeinfo;

  tmp.tm_year -= 1900;
  tmp.tm_mon -= 1;

  rawtime = mktime(&tmp);

  return ret;
}

CDate & CDate::operator++()
{
  short int dInMo = daysInMonthFun(timeinfo.tm_year, timeinfo.tm_mon);
  
  timeinfo.tm_mday++;

  if((timeinfo.tm_mday) > dInMo)
  {
    timeinfo.tm_mday = 1;
    timeinfo.tm_mon++;

    if(timeinfo.tm_mon == 13)
    {
      timeinfo.tm_mon = 1;
      timeinfo.tm_year++;
    }
  }

  struct tm tmp = timeinfo;

  tmp.tm_year -= 1900;
  tmp.tm_mon -= 1;

  rawtime = mktime(&tmp);

  return *this;
}

CDate & CDate::operator--()
{  
  timeinfo.tm_mday--;

  if((timeinfo.tm_mday) == 0)
  {
    timeinfo.tm_mon--;

    if(timeinfo.tm_mon == 0)
    {
      timeinfo.tm_mon = 12;
      timeinfo.tm_year--;
    }

    timeinfo.tm_mday = daysInMonthFun(timeinfo.tm_year, timeinfo.tm_mon);
  }

  struct tm tmp = timeinfo;

  tmp.tm_year -= 1900;
  tmp.tm_mon -= 1;

  rawtime = mktime(&tmp);

  return *this;
}

CDate CDate::operator + (int days)
{
  CDate ret = *this;

  for(int i = 0; i < days; i++)
  {
     ret = ++ret;
  }

  return ret;
}

CDate CDate::operator - (int days)
{
  CDate ret = *this;

  for(int i = 0; i < days; i++)
  {
     ret = --ret;
  }

  return ret;
}

int CDate::operator - (CDate & date)
{
  time_t ret = this->rawtime - date.rawtime;

  return ret / 86400;
}

bool CDate::operator == (CDate & date)
{
  return (this->rawtime == date.rawtime);
}

bool CDate::operator != (CDate & date)
{
  return (this->rawtime != date.rawtime);
}

bool CDate::operator > (CDate & date)
{
  return (this->rawtime > date.rawtime);
}

bool CDate::operator >= (CDate & date)
{
  return (this->rawtime >= date.rawtime);
}

bool CDate::operator < (CDate & date)
{
  return (this->rawtime < date.rawtime);
}

bool CDate::operator <= (CDate & date)
{
  return (this->rawtime <= date.rawtime);
}

#ifndef __PROGTEST__
int main ( void )
{
  ostringstream oss;
  istringstream iss;

  CDate a ( 2000, 1, 2 );
  CDate b ( 2010, 2, 3 );
  CDate c ( 2004, 2, 10 );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2000-01-02" );
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2010-02-03" );
  oss . str ("");
  oss << c;
  assert ( oss . str () == "2004-02-10" );
  a = a + 1500;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2004-02-10" );
  b = b - 2000;
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2004-08-13" );
  assert ( b - a == 185 );
  assert ( ( b == a ) == false );
  assert ( ( b != a ) == true );
  assert ( ( b <= a ) == false );
  assert ( ( b < a ) == false );
  assert ( ( b >= a ) == true );
  assert ( ( b > a ) == true );
  assert ( ( c == a ) == true );
  assert ( ( c != a ) == false );
  assert ( ( c <= a ) == true );
  assert ( ( c < a ) == false );
  assert ( ( c >= a ) == true );
  assert ( ( c > a ) == false );
  a = ++c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-11" );
  a = --c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-10" );
  a = c++;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-11" );
  a = c--;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-10" );
  iss . clear ();
  iss . str ( "2015-09-03" );
  assert ( ( iss >> a ) );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-09-03" );
  a = a + 70;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-11-12" );

  CDate d ( 2000, 1, 1 );
  try
  {
    CDate e ( 2000, 32, 1 );
    assert ( "No exception thrown!" == nullptr );
  }
  catch ( ... )
  {
  }
  iss . clear ();
  iss . str ( "2000-12-33" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-11-31" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-02-29" );
  assert ( ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );
  iss . clear ();
  iss . str ( "2001-02-29" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );
 /*

  //-----------------------------------------------------------------------------
  // bonus test examples
  //-----------------------------------------------------------------------------
  CDate f ( 2000, 5, 12 );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  oss . str ("");
  oss << date_format ( "%Y/%m/%d" ) << f;
  assert ( oss . str () == "2000/05/12" );
  oss . str ("");
  oss << date_format ( "%d.%m.%Y" ) << f;
  assert ( oss . str () == "12.05.2000" );
  oss . str ("");
  oss << date_format ( "%m/%d/%Y" ) << f;
  assert ( oss . str () == "05/12/2000" );
  oss . str ("");
  oss << date_format ( "%Y%m%d" ) << f;
  assert ( oss . str () == "20000512" );
  oss . str ("");
  oss << date_format ( "hello kitty" ) << f;
  assert ( oss . str () == "hello kitty" );
  oss . str ("");
  oss << date_format ( "%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%" ) << f;
  assert ( oss . str () == "121212121212050505200020002000%%%%%" );
  oss . str ("");
  oss << date_format ( "%Y-%m-%d" ) << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-01-1" );
  assert ( ! ( iss >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-1-01" );
  assert ( ! ( iss >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-001-01" );
  assert ( ! ( iss >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-01-02" );
  assert ( ( iss >> date_format ( "%Y-%m-%d" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2001-01-02" );
  iss . clear ();
  iss . str ( "05.06.2003" );
  assert ( ( iss >> date_format ( "%d.%m.%Y" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2003-06-05" );
  iss . clear ();
  iss . str ( "07/08/2004" );
  assert ( ( iss >> date_format ( "%m/%d/%Y" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2004-07-08" );
  iss . clear ();
  iss . str ( "2002*03*04" );
  assert ( ( iss >> date_format ( "%Y*%m*%d" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2002-03-04" );
  iss . clear ();
  iss . str ( "C++09format10PA22006rulez" );
  assert ( ( iss >> date_format ( "C++%mformat%dPA2%Yrulez" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2006-09-10" );
  iss . clear ();
  iss . str ( "%12%13%2010%" );
  assert ( ( iss >> date_format ( "%%%m%%%d%%%Y%%" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2010-12-13" );

  CDate g ( 2000, 6, 8 );
  iss . clear ();
  iss . str ( "2001-11-33" );
  assert ( ! ( iss >> date_format ( "%Y-%m-%d" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "29.02.2003" );
  assert ( ! ( iss >> date_format ( "%d.%m.%Y" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "14/02/2004" );
  assert ( ! ( iss >> date_format ( "%m/%d/%Y" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "2002-03" );
  assert ( ! ( iss >> date_format ( "%Y-%m" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "hello kitty" );
  assert ( ! ( iss >> date_format ( "hello kitty" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "2005-07-12-07" );
  assert ( ! ( iss >> date_format ( "%Y-%m-%d-%m" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "20000101" );
  assert ( ( iss >> date_format ( "%Y%m%d" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-01-01" );
*/
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
