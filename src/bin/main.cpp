#include <sstream>
#include "../Game/Akimal.h"
#include "Graphics.h"
#include "Options Loading\ini.h"
#include "../Options.h"

STD;

#define DEFAULT_ART_FILE		"D:/Programming/C++/Akimal/Akimal/bin/res/menu_text.txt"
#define DEFAULT_DATA_FILE		"D:/Programming/C++/Akimal/Akimal/bin/res/akimal.txt"
#define DEFAULT_LOG_FILE		"D:/Programming/C++/Akimal/Akimal/bin/res/log.txt"
#define DEFAULT_SPLASH_FILE		"D:/Programming/C++/Akimal/Akimal/bin/res/Title_splashscreen.txt"

string game_menu[] = { "Gioca", "Opzioni", "Esci" };
Game_Options local_options;

// Displays splash screen
void ShowSplashScreen();

// Returns a string with an art
string GetArt();

// Assigns the file to read from
string FileSelection(string);

Game_Options getOptions(string);
void saveOptions(Game_Options, string);

int main()
{	
	local_options = getOptions("Options.ini");

	// save problems to a log file
	ofstream log(DEFAULT_LOG_FILE);
	clog.rdbuf(log.rdbuf());	// redirect stderr stream to the log file

	
	string	answer,		// holder for all answers
			menu_art;	// holder for art string
	ShowSplashScreen();
	PAUSEN; CLS;
	menu_art = GetArt();

	Akimal game(DEFAULT_DATA_FILE);	// instance to play the game
	while (true)	//Game loop
	{
		cout << menu_art << endl << endl;
		DrawTop();
		int res = Menu(game_menu, sizeof(game_menu)/sizeof(string));

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


		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		ENPAUSE; CLS;

	};
	
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
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');

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

Game_Options getOptions(string ini) {
	return{
		getKey("Options", "path", ini),
		getKey("Options", "splash", ini),
		getKey("Options", "menu", ini),
		getKey("Options", "log_file", ini),
		(getKey("Options", "log_enabled", ini) == "1") ? true : false
	};
}

void saveOptions(Game_Options options, string ini) {
	setKey("Options", "path", options.path, ini);
	setKey("Options", "splash", options.splash_art, ini);
	setKey("Options", "menu", options.menu_art, ini);
	setKey("Options", "log_file", options.log_file, ini);
	setKey("Options", "log_enabled", options.log_enabled ? "1" : "0", ini);
}