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

	GameOptions() = default;																	// Default constructor; does not allow to play
	GameOptions(string, string = "", bool = false);												// Constructor with path - Can enable log_enabled
	GameOptions(string, string, string, string, string, string, string = "", bool = false);		// Constructor with complete initialization
};

// Set file path and eventaully log options
inline GameOptions::GameOptions(string _path, string _log_file, bool _log_enabled)
	: path(_path), log_file(_log_file), log_enabled(_log_enabled)
{
}

// Complete setter
inline GameOptions::GameOptions(string _path, string _splash_art, string _menu_art,
								string _def_question, string _def_correct_ans, string _def_wrong_ans,
								string _log_file, bool _log_enabled)

	: path(_path), splash_art(_splash_art), menu_art(_menu_art),
	def_question(_def_question), def_correct_ans(_def_correct_ans), def_wrong_ans(_def_wrong_ans),
	log_file(_log_file), log_enabled(_log_enabled)
{
}
