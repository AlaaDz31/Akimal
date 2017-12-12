#pragma once

#include <map>
#include <string>
#include <Windows.h>
#include "basics.h"

using namespace std;

class Localization
{
	using _map = map<string, string>;
	using init = initializer_list<pair<string,string>>;

public:
	Localization() = default;
	Localization(const init& _list)
	{
		for (auto a : _list)
			addEntry(a);
	}
	~Localization() = default;

	void addEntry(const pair<string, string>& _pair) { loc_map.insert(_pair); }

private:
	_map loc_map;
};

pair<string, string> getKey(string section, string key, string file)
{
	char tmp[100];
	GetPrivateProfileString(section.c_str(), key.c_str(), "", tmp, 100, file.c_str());
	return { key,tmp };
}

void setKey(string section, string key, string newValue, string file)
{
	WritePrivateProfileString(section.c_str(), key.c_str(), newValue.c_str(), file.c_str());
}

Localization get_locale(string _locale, string _sourceFile)
{
	return {
		getKey(_locale, "yes", _sourceFile),
		getKey(_locale, "no", _sourceFile),
		getKey(_locale, "not_valid", _sourceFile),
		getKey(_locale, "won", _sourceFile),
		getKey(_locale, "guess", _sourceFile),
		getKey(_locale, "ask_animal", _sourceFile),
		getKey(_locale, "ask_question", _sourceFile),
	};
}

Localization locale = get_locale(getKey("options", "locale", ".\Options.ini").second, ".\Locales.ini");

inline bool PositiveAnswer(std::string clause, Localization locale)
{
	toLowerCase(clause);
	return (clause == "y" || clause == "yes" || clause == "s" || clause == "si");
}

inline bool NegativeAnswer(std::string clause, Localization locale)
{
	toLowerCase(clause);
	return (clause == "n" || clause == "no");
}