#ifndef __GAMEDATA__
#define __GAMEDATA__

#include "..\Utils\basics.h"

struct GameData
{
	ushort weight; 	// used to create treemap
	string data;	// actual data

	static GameData checkFormat (const string&);	// checks whether a string can be casted to GameData obj

	GameData (const string& = "", int = 0);

	string toString ();

	bool operator<(const GameData&);
	bool operator==(const GameData&);
	bool operator!=(const GameData&);
};

inline GameData::GameData (const string& _data, int _weight)
	: weight (_weight), data (_data)
{
}

GameData GameData::checkFormat (const string& _line)
{
	int posSep = _line.find ('|');

	if (isnum (_line.substr (0, posSep)))
		return GameData (_line.substr (posSep + 1), atoi (_line.substr (0, posSep).c_str ()));

	return GameData ();		// dummy value, empty string
}

inline string GameData::toString ()
{
	return weight + "|" + data;
}

inline bool GameData::operator<(const GameData& right)
{
	return weight < right.weight;
}

inline bool GameData::operator==(const GameData& _data)
{
	return weight == _data.weight && data == _data.data;
}

inline bool GameData::operator!=(const GameData& _data)
{
	return !(local == _data);
}

#endif // !__GAMEDATA__
