#ifndef __BASICS__
#define __BASICS__

#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <stdexcept>

#define STD						using namespace std
STD;

#define null					""
#define in						:
#define extends                 :

#define catch_exception(ex)		catch (const exception& ex)
#define emptylist_exception		out_of_range ("List is empty!")
#define keynotfound_exception	exception("Key was not found")
#define outofrange_exception	out_of_range ("Index is out of range!")
#define unexcepted_exception	exception ("An unexcepted exception has occurred!")
#define local					(*this)



#define TEMP(t)					template<class t>
#define GENERIC_TEMP			TEMP(T)
#define CLS						system("cls")
#define PAUSE					system("pause")
#define PAUSEN					system("pause>nul")
#define END_MAIN				PAUSEN; return 0


					
					
					






typedef unsigned short			ushort;
typedef unsigned int			uint;
typedef unsigned long			ulong;
typedef unsigned long long		ullong;
typedef unsigned char			uchar;

// returns the mcm between 2 numbers
GENERIC_TEMP T mcm (T x, T y)
{
	if (x == 0 || y == 0)
		return -1;

	for (T m = (max) (x, y); m <= x * y; m += (max) (x, y))
		if (m % x == 0 && m % y == 0)
			return m;
}

// return the MCD between 2 numbers (Euclide)
GENERIC_TEMP T MCD (T x, T y)
{
	if (y == 0)
		return x;
	
	return MCD (y, x % y);
}

// returns n!
inline int fact (const int& n)
{
	if (n == 0)
		return 1;
	else
		return (n * fact (n - 1));
}

GENERIC_TEMP bool outOfRange (T value, T minV, T maxV)
{
	return (value < minV || value > maxV);
}

GENERIC_TEMP bool inRange (T value, T minV, T maxV)
{
	return !outOfRange (value, minV, maxV);
}

inline bool isnum (const string& str)
{
	for (uint i = 0; i < str.size (); i++)
		if (!isdigit (str.at (i)))
			return false;

	return true;
}

#endif /*__BASICS__*/
