#pragma once

#ifndef __BASICS__
#define __BASICS__

#include <algorithm>
#include <cstdio>
#include <conio.h>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>

#define STD						using namespace std

#define null					""
#define in						:
#define catch_exception(ex)		catch (const std::exception& ex)
#define emptylist_exception		std::out_of_range ("List is empty!")
#define keynotfound_exception	std::exception("Key was not found")
#define outofrange_exception	std::out_of_range ("Index is out of range!")
#define unexcepted_exception	std::exception ("An unexcepted exception has occurred!")

#define MAX_SIZE(t)				(pow (2, 8 * sizeof (t)) - 1)
#define MIN_SIZE(t)				(-pow (2, 8 * sizeof (t)) + 1)
#define CLS						std::system("cls")
#define PAUSE					std::system("pause")
#define _PAUSE(str)				printf_s(str); _getch()
#define ENPAUSE					_PAUSE("Press any key to continue. . .")
#define PAUSEN					std::system("pause>nul")
#define END_MAIN				PAUSEN; return 0
#define FLUSH_IN				std::fflush(stdin)
#define FLUSH_OUT				std::fflush(stdout)
#define ENDL					std::cout << std::endl
#define endll					std::endl << std::endl
#define ENDLL					std::cout << endll
#define SET_TIME				srand(time(nullptr))
#define typeof(v)				typeid(v).name()

#ifndef local
#define local					(*this)
#endif /*local*/

typedef unsigned short			ushort;
typedef unsigned int			uint;
typedef unsigned long			ulong;
typedef unsigned long long		ullong;
typedef unsigned char			uchar;

// returns the mcm between 2 numbers
template<class T>
T mcm(T x, T y)
{
	if (x == 0 || y == 0)
		return -1;

	for (T m = (max) (x, y); m <= x * y; m += (max) (x, y))
		if (m % x == 0 && m % y == 0)
			return m;
}

// returns the MCD between 2 numbers (Euclid's algorithm)
template<class T>
T MCD(T x, T y)
{
	if (y == 0)
		return x;

	return MCD(y, x % y);
}

// returns n!
inline int fact(const int& n)
{
	if (n == 0)
		return 1;
	else
		return (n * fact(n - 1));
}

template<class T>
inline bool outOfRange(T value, T minV, T maxV)
{
	return (value < minV || value > maxV);
}

template<class T>
inline bool inRange(T value, T minV, T maxV)
{
	return !outOfRange(value, minV, maxV);
}

inline bool isnum(const std::string& str)
{
	for (uint i = 0; i < str.size(); i++)
		if (!isdigit(str.at(i)))
			return false;

	return true;
}

inline void LowerCase(std::string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

inline void UpperCase(std::string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
}

inline bool PositiveAnswer(std::string clause)
{
	LowerCase(clause);
	return (clause == "y" || clause == "yes" || clause == "s" || clause == "si");
}

inline bool NegativeAnswer(std::string clause)
{
	LowerCase(clause);
	return (clause == "n" || clause == "no");
}
#endif // !__BASICS__
