#pragma once
#include <windows.h>
#include <fstream>
#include "../../Utils/basics.h"

#define DEFAULT_OPTIONSFILE "Options.ini"

string getKey(string block, string key, string file) {
	char tmp[100];
	GetPrivateProfileString(block.c_str(), key.c_str(), "", tmp, 100, file.c_str());
	return string(tmp);
}

void setKey(string block, string key, string newValue, string file) {
	WritePrivateProfileString(block.c_str(), key.c_str(), newValue.c_str(), file.c_str());
}

bool check_file(string file) {
	fstream tmp(file);
	return tmp.good();
}
