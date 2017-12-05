#include "../Game/Akimal.cpp"

int main() {
	Akimal game("tempDataFile.dat");
	string newGame;
	do {
		game.Game();
		cout << "Do you want to keep playing? (Yes/No) ";
		cin >> newGame;
		transform(newGame.begin(), newGame.end(), newGame.begin(), tolower);
		PAUSE;
		CLS;
	} while (newGame=="y");
	game.save();
}