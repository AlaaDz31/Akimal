#include <sstream>
#include "Options Loading\ini.h"
#include "../Game/Localization/Localization.h"
#include "../Game/Akimal.h"

int main() {
	string menu_art;

	string opt = getKey("options", "save", "./Options.ini");

	Localization locale = get_Locale_From(getKey("options", "locale", "./Options.ini"), "./Locales.ini");

	cout << locale.ask_animal;

	//getting ascii art
	{
		ifstream splashscreen("Title_splashscreen.txt");
		cout << splashscreen.rdbuf() << endl;
		splashscreen.close();
		PAUSEN; CLS;
		ifstream menu_screen("menu_text.txt");
		stringstream tmpSS;
		tmpSS << menu_screen.rdbuf();
		menu_art = tmpSS.str();
		menu_screen.close();
	}

	cout <<opt << endl;
	setKey("NEW", "TEST", "naca", "./Options.ini");
	PAUSEN; CLS;

	Akimal game("akimal.txt");
	string newGame;
	do {
		cout << menu_art << endl;
		game.Game();
		cout << "Do you want to keep playing? (Yes/No) ";
		cin >> newGame;
		LowerCase(newGame);
		PAUSE; CLS;
	} while (PositiveAnswer(newGame));
	game.Save();
}
