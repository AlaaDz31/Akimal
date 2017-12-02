#pragma once
#include "..\..\lib\basics.h"

struct GameData
{
	ushort weight; 	// used to create treemap
	string data;	// actual data

	GameData (string, int = 0);

	string toString ();

	bool operator>(const GameData&);
};

inline GameData::GameData (string _data, int weight)
	: weight (0), data (_data)
{
}

inline string GameData::toString ()
{
	return weight + "|" + data;
}

inline bool GameData::operator>(const GameData& right)
{
	return weight > right.weight;
}
