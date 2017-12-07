#include "Akimal.h"

int main() {
	Akimal game("tempDataFile.txt");
	string newGame;
	do {
		game.Game();
		cout << "Do you want to keep playing? (Yes/No) ";
		cin >> newGame;
		PAUSE;
		CLS;
	} while (newGame=="y");
	game.Save();
}
