#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

#ifndef TableSets
#define TableSets

/*     TABLE PART       */

struct TableSet
{
	unsigned char HORIZONTAL;
	unsigned char VERTICAL;
	unsigned char UP_RIGHT;
	unsigned char UP_LEFT;
	unsigned char SEP_LEFT;
	unsigned char SEP_RIGHT;
	unsigned char DOWN_RIGHT;
	unsigned char DOWN_LEFT;
	unsigned char SEP_UP;
	unsigned char SEP_DOWN;
	unsigned char CROSS;
};
TableSet D_LINE = { 205,186,201,187,185,204,200,188,202,203,206 };
TableSet HYB1 = { 196, 186, 214, 183, 182, 199, 211,189,207, 209, 215 };
TableSet DEFAULT_SET = D_LINE;

/*      GRAPH PART     */

struct GraphSet
{
	unsigned char HORIZONTAL;
	unsigned char VERTICAL;
	unsigned char UP_A;
	unsigned char RIGHT_A;
	unsigned char CROSS;
};

GraphSet GRAPH1 = { 196,179,'^', '>', 197 };
GraphSet D_GRAPH = GRAPH1;

const int DEF_INT[] = { INT_MIN };




#endif
