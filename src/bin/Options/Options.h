#pragma once
#include "..\..\Utils\basics.h"

struct GameOptions
{
private:
	using string = std::string;

public:
	string path;
	string splash_art;
	string menu_art;
	string def_question;
	string def_correct_ans;
	string def_wrong_ans;

	string log_file;
	bool log_enabled = false;

	GameOptions() = default;														// Default constructor; does not allow to play
	GameOptions(string);															// Constructor with path - Logging is disabled
	GameOptions(string, string, bool);												// Constructor with path - Can enable logging
	GameOptions(string, string, string);											// Constructor with path and arts - Logging is disabled
	GameOptions(string, string, string, string, bool);
	GameOptions(string, string, string, string);
	GameOptions(string, string, string, string, string, bool);
	GameOptions(string, string, string, string, string, string);
	GameOptions(string, string, string, string, string, string, string, bool);
};

