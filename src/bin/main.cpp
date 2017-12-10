#include <sstream>
#include "../Game/Akimal.h"

STD;

#define DEFAULT_ART_FILE		"../Akimal/bin/res/menu_text.txt"
#define DEFAULT_DATA_FILE	"../Akimal/bin/res/akimal.txt"
#define DEFAULT_LOG_FILE		"../Akimal/bin/res/log.txt"
#define DEFAULT_SPLASH_FILE	"../Akimal/bin/res/Title_splashscreen.txt"

// Displays splash screen
void ShowSplashScreen();

// Returns a string with an art
string GetArt();

// Assigns the file to read from
string FileSelection(string);

int main()
{
	// save problems to a log file
	ofstream log(DEFAULT_LOG_FILE);
	clog.rdbuf(log.rdbuf());	// redirect stderr stream to the log file

	Akimal game;	// instance to play the game
	string answer,	// holder for all answers
		menu_art;	// holder for art string

	ShowSplashScreen();
	PAUSEN; CLS;
	menu_art = GetArt();

	do
	{
		cout << menu_art << endl << endl;
		answer = FileSelection("Do you wish to use default file? (Yes/No) ");
		game.Load(answer);

		game.Game();

		cout << "Do you want to keep playing? (Yes/No) ";
		cin >> answer;

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		_PAUSE("put here localized text"); CLS;

	} while (PositiveAnswer(answer));
	game.Save();
	log.close();
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
		cin.ignore(numeric_limits<streampos>::max(), '\n');

		cout << "Insert your file path here: ";
		getline(cin, answer);
	}

	return answer;
}