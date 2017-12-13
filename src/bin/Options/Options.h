#pragma once
#include "..\..\Utils\basics.h"

struct GameOptions
{
	std::string path;
	std::string splash_art;
	std::string menu_art;
	std::string log_file;
	bool log_enabled;

	GameOptions(std::string, std::string, bool);
	GameOptions(std::string, std::string, std::string, std::string, bool);
};

GameOptions::GameOptions(std::string _path, std::string _log_file, bool _log_enabled)
	: path(_path), log_file(_log_file), log_enabled(_log_enabled)
{
}

GameOptions::GameOptions(std::string _path, std::string _splash_art, std::string _menu_art, std::string _log_file, bool _log_enabled)
	: path(_path), splash_art(_splash_art), menu_art(_menu_art), log_file(_log_file), log_enabled(_log_enabled)
{
}