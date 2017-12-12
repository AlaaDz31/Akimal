#include <sstream>
#include "../Game/Akimal.h"
#include "Graphics.h"

STD;

#define DEFAULT_ART_FILE		"../BinTree/bin/res/menu_text.txt"
#define DEFAULT_DATA_FILE		"../BinTree/bin/res/akimal.txt"
#define DEFAULT_LOG_FILE		"../BinTree/bin/res/log.txt"
#define DEFAULT_SPLASH_FILE		"../BinTree/bin/res/Title_splashscreen.txt"

// Displays splash screen
void ShowSplashScreen();

// Returns a string with an art
string GetArt();

// Assigns the file to read from
string FileSelection(string);

int main()
{
	string scelte[] = { "Gioca", "Opzioni", "Esci" };
	// save problems to a log file
	ofstream log(DEFAULT_LOG_FILE);
	clog.rdbuf(log.rdbuf());	// redirect stderr stream to the log file

	Akimal game(DEFAULT_DATA_FILE);	// instance to play the game
	string answer,	// holder for all answers
		menu_art;	// holder for art string

	ShowSplashScreen();
	PAUSEN; CLS;
	menu_art = GetArt();
	do
	{
		cout << menu_art << endl << endl;
		DrawTop();
		int res = Menu(scelte, 3);
		//game.Load(answer);

		switch (res) {
		case 1:
			CLS;
			game.Game();
			break;
		case 2:
			//TODO:
			break;
		case 3: 
			game.Save();
			log.close();
			break;
		default:
			clog << "Main:switch(default) @ Unexpected error\n";
		}



		cout << "Do you want to keep playing? (Yes/No) ";
		cin >> answer;

		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		_PAUSE("put here localized text"); CLS;

	} while (true);
	
}

void ShowSplashScreen()
{
	ifstream splashscreen(DEFAULT_SPLASH_FILE);
	cout << splashscreen.rdbuf() << endl;
	splashscreen.close();
}

string GetArt()
{
	string art;
	ifstream menu_screen(DEFAULT_ART_FILE);
	stringstream tmpSS;

	tmpSS << menu_screen.rdbuf();
	art = tmpSS.str();
	menu_screen.close();

	return art;
}

string FileSelection(string request)
{
	string answer;

	cout << request;
	cin >> answer;

	if (PositiveAnswer(answer))
		answer = DEFAULT_DATA_FILE;

	else
	{
		// need to clear input stream
		cin.ignore((numeric_limits<streampos>::max)(), '\n');

		cout << "Insert your file path here: ";
		getline(cin, answer);
	}

	return answer;
}

string GetArt_i(ifstream& from,uint indx)
{
	string answer;
	from.seekg(0);
	for(;indx>0;indx++)
	if (from.good()) {
		from >> answer;
	}
	return answer;
}

