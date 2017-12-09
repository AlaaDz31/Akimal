#include <sstream>
#include "../Game/Akimal.h"

#define DEFAULT_ART		"../Akimal/bin/res/menu_text.txt"
#define DEFAULT_FILE	"../Akimal/bin/res/akimal.txt"
#define DEFAULT_LOG		"../Akimal/bin/res/log.txt"
#define DEFAULT_SPLASH	"../Akimal/bin/res/Title_splashscreen.txt"

// Displays splash screen (game art displayed at launch)
void ShowSplashScreen();

// Returns a string with an art
string GetArt();

// Assigns the file to read from
string FileSelection(string);

int main()
{
	// save problems to a log file
	ofstream log(DEFAULT_LOG);
	clog.rdbuf(log.rdbuf());	// redirect stderr stream to the log file

	string 	answer,		// holder for all answers
		menu_art;	// holder for art string
	Akimal game;		// instance of game

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

		cin.clear();
		cin.ignore (numeric_limits<streamsize>::max (), '\n');
		ENPAUSE; CLS;

	} while (PositiveAnswer(answer));
	game.Save();
	log.close();
}

void ShowSplashScreen()
{
	ifstream splashscreen(DEFAULT_SPLASH);
	cout << splashscreen.rdbuf() << endl;
	splashscreen.close();
}

string GetArt()
{
	string art;
	ifstream menu_screen(DEFAULT_ART);
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

	// need to clear eventual input stream buffer
	cin.clear();
	cin.ignore(numeric_limits<streampos>::max(), '\n');

	if (PositiveAnswer(answer))
		answer = DEFAULT_FILE;

	else
	{
		cout << "Insert your file path here: ";
		getline(cin, answer);
	}

	return answer;
}
