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
#define elif                    else if
#define catch_exception(ex)		catch (const exception& ex)
#define emptylist_exception		out_of_range ("List is empty!")
#define keynotfound_exception	exception("Key was not found")
#define outofrange_exception	out_of_range ("Index is out of range!")
#define unexcepted_exception	exception ("An unexcepted exception has occurred!")
#define local					(*this)

#define MAX_SIZE(t)				(pow (2, 8 * sizeof (t)) - 1)
#define MIN_SIZE(t)				(-pow (2, 8 * sizeof (t)) + 1)
#define TEMP(t)					template<class t>
#define GENERIC_TEMP			TEMP(T)
#define CLS						system("cls")
#define PAUSE					system("pause")
#define PAUSEN					system("pause>nul")
#define END_MAIN				PAUSEN; return 0
#define FLUSH_IN				fflush(stdin)
#define FLUSH_OUT				fflush(stdout)
#define ENDL					cout << endl
#define endll					endl << endl
#define ENDLL					cout << endll
#define SET_TIME				srand(time(NULL))
#define typeof(v)				typeid(v).name()

// gets and returns a simple variable in input with check
#define insertCheck (minV, maxV, s, e, v)	cout << s; while (cin >> v && v < minV || v > maxV) cout << e << endl << "Retry: "

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

#endif /*__BASICS__*/