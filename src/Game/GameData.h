#pragma once
#include "../Utils/basics.h"

struct GameData {
	ushort weight; 	//used to create treemap
	string data;	//actual data

	GameData(string);
	bool operator>(GameData right);
};

GameData::GameData(string _data) : weight(0), data(_data) {}

inline bool GameData::operator>(GameData right){
	return weight>right.weight;
}
