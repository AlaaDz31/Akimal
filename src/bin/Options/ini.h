#pragma once
#include <fstream>
#include <Windows.h>
#include "../../Utils/basics.h"

string getKey(string block, string key, string file)
{
	char tmp[100];
	GetPrivateProfileString(block.c_str(), key.c_str(), "", tmp, 100, file.c_str());
	return string(tmp);
}

void setKey(string block, string key, string newValue, string file)
{
	WritePrivateProfileString(block.c_str(), key.c_str(), newValue.c_str(), file.c_str());
}