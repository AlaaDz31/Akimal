#pragma once
#include "../../Utils/basics.h"
#include "../../bin/Options Loading/ini.h"

struct Localization {
	string yes;
	string no;
	string not_valid;
	string won;
	string guess;
	string ask_animal;
	string ask_question;
	string keep;
	Localization(string, string, string, string, string, string, string, string);
};

Localization::Localization(
	string _yes,
	string _no,
	string _not_valid,
	string _won,
	string _guess,
	string _ask_animal,
	string _ask_question,
	string _keep
) : no(_no), yes(_yes), not_valid(_not_valid), won(_won), guess(_guess), ask_animal(_ask_animal), ask_question(_ask_question), keep(_keep) {};



Localization get_Locale_From(string locale, string file) {
	return Localization(
		getKey(locale, "yes", file),
		getKey(locale, "no", file),
		getKey(locale, "not_valid", file),
		getKey(locale, "won", file),
		getKey(locale, "guess", file),
		getKey(locale, "ask_animal", file),
		getKey(locale, "ask_question", file),
		getKey(locale, "keep", file)
		);
}