#ifndef __GAMEDATA__
#define __GAMEDATA__

#include "basics.h"

struct GameData
{
	ushort weight; 	// used to create treemap
	string data;	// actual data

	inline GameData::GameData(const string& _data = "", int _weight = 0)
		: weight(_weight), data(_data)
	{
	}

	static GameData GameData::checkFormat(const string& _line)
	{
		int posSep = _line.find("|");

		if (posSep != string::npos && isnum(_line.substr(0, posSep)))
			return GameData(_line.substr(posSep + 1), atoi(_line.substr(0, posSep).c_str()));

		return GameData();		// dummy value, empty string
	}

	inline string GameData::toString()
	{
		return weight + "|" + data;
	}

	inline bool GameData::operator==(const GameData& _data)
	{
		return weight == _data.weight && data == _data.data;
	}

	inline bool GameData::operator!=(const GameData& _data)
	{
		return !(local == _data);
	}
};

//inline bool GameData::operator<(const GameData& right)
//{
//	return weight < right.weight;
//}

inline bool operator<(const GameData & left, const GameData & right) {
	return left.weight < right.weight;
}


#endif // !__GAMEDATA__
