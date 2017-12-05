#include "Akimal.h"


int main() {
	Akimal game("C:\\Users\\in4a11\\source\\repos\\test\\Debug\\tempDataFile.dat");
	string newGame;
	do {
		game.Game();
		cout << "Do you want to keep playing? (Yes/No) ";
		cin >> newGame;
		PAUSE;
		CLS;
	} while (newGame=="y");
	game.save();

	END_MAIN;
}
