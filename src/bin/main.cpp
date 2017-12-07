#include <sstream>
#include "../Game/Akimal.h"

int main() {
	string menu_art;

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
