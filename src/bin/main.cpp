#include <sstream>
#include "..\Game\Akimal.h"
#include "..\bin\Graphics\Graphics.h"
#include "..\bin\Options\Options.h"
#include "..\bin\Options\ini.h"

STD;

// Default file paths:
#define DEFAULT_ART_FILE		"../BinTree/bin/res/menu_text.txt"
#define DEFAULT_DATA_FILE		"../BinTree/bin/res/akimal.txt"
#define DEFAULT_LOG_FILE		"../BinTree/bin/res/log.txt"
#define DEFAULT_SPLASH_FILE		"../BinTree/bin/res/splash.txt"
#define DEFAULT_OPTIONS_FILE	"./Options.ini"

// Enumeration with options provided by the menu
enum class MenuOptions
{
	play = 1,
	options,
	exit
};

// Menu of strings
string game_menu[] = { "Gioca", "Opzioni", "Esci" };

// Object that contains current state of .ini options
GameOptions local_options;

// Displays splash screen
void ShowSplashScreen();

void OptionsMenu(GameOptions&);

// Returns a string with an art
string GetArt();

// Assigns the file to read from
string FileSelection(string);

// Loader and saver for options (.ini file)
GameOptions loadOptions(string);
void correct_loading_failures();
void saveOptions(const GameOptions, string);

int main()
{
	local_options = loadOptions("Options.ini");
	correct_loading_failures();
	
	ofstream log(local_options.log_file);
	// save problems to a log file
	if (local_options.log_enabled) {
		clog.rdbuf(log.rdbuf());	// redirect stderr stream to the log file
	}

	Akimal game(local_options.path);	// instance to play the game
	string	answer,						// holder for all answers
		menu_art;						// holder for art string
	MenuOptions res;

	ShowSplashScreen();
	PAUSEN; CLS;
	menu_art = GetArt();

	do	// Game loop
	{
		cout << menu_art << endll;
		DrawTop();
		res = (MenuOptions) Menu(game_menu, sizeof(game_menu) / sizeof(string));

		CLS;
		switch (res)
		{
		case MenuOptions::play:
			game.Game();
			break;

		case MenuOptions::options:
			OptionsMenu(local_options);
			break;

		case MenuOptions::exit:
			saveOptions(local_options, DEFAULT_OPTIONS_FILE);
			game.Save(local_options.path);
			log.close();
			break;

		default:
			clog << "Main:switch(default) @ Unexpected error\n";
			break;
		}


		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		ENPAUSE; CLS;

	} while (res != MenuOptions::exit);
}

void ShowSplashScreen()
{
	ifstream splashscreen(local_options.splash_art);
	cout << splashscreen.rdbuf() << endl;
	splashscreen.close();
}

string GetArt()
{
	string art;
	ifstream menu_screen(local_options.menu_art);
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

	// need to clear garbage stream
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');

	if (PositiveAnswer(answer))
		answer = DEFAULT_DATA_FILE;

	else
	{
		cout << "Insert your file path here: ";
		getline(cin, answer);
	}

	return answer;
}

GameOptions loadOptions(string ini)
{
	GameOptions tmp = 
	{
		getKey("Options", "path", ini),
		getKey("Options", "splash", ini),
		getKey("Options", "menu", ini),
		getKey("DefaultTree", "question", ini),
		getKey("DefaultTree", "correct", ini),
		getKey("DefaultTree", "wrong", ini),
		getKey("Options", "log_file", ini),
		(getKey("Options", "log_enabled", ini) == "1") ? true : false
	};
	clog << tmp.log_file;
	return tmp;
}

void saveOptions(GameOptions options, string ini)
{
	setKey("Options", "path", options.path, ini);
	setKey("Options", "splash", options.splash_art, ini);
	setKey("Options", "menu", options.menu_art, ini);
	setKey("DefaultTree", "question",options.def_question, ini),
	setKey("DefaultTree", "correct", options.def_correct_ans, ini),
	setKey("DefaultTree", "wrong", options.def_wrong_ans, ini),
	setKey("Options", "log_file", options.log_file, ini);
	setKey("Options", "log_enabled", options.log_enabled ? "1" : "0", ini);
}

void OptionsMenu(GameOptions& options) {
	string menu[] = { "Save Path Select", "Change SplashArt", "Change Menu Art", "Default Question", "Default Correct", "Default Wrong", "Log File Path", "Log File Enable" };
	DrawTop();
	int choice = Menu(menu, 8);
	switch (choice) {
	case 1:
		//Save Path selection;
		CLS;
		cout << "New Save Path ("<<options.path<<"):";
		getline(cin, options.path);
		break;
	case 2:
		//Change SplashArt
		CLS;
		cout << "New SplashArt Path(" << options.splash_art << "):";
		getline(cin, options.splash_art);
		break;
	case 3:
		//Change Menu Art
		CLS;
		cout << "New MenuArt Path(" << options.menu_art << "):";
		getline(cin, options.menu_art);
		break;
	case 4:
		//Change Default Question
		CLS;
		cout << "New Default Question:";
		getline(cin, options.def_question);
		break;
	case 5:
		//Change Default correct
		CLS;
		cout << "New Default Correct:";
		getline(cin, options.def_correct_ans);
		break;
	case 6:
		//Change Default Wrong
		CLS;
		cout << "New Default Wrong:";
		getline(cin, options.def_wrong_ans);
		break;
	case 7:
		//Change log path
		CLS;
		cout << "New Log Path(" << options.log_file << "):";
		getline(cin, options.log_file);
		break;
	case 8:
		//change if log enabled
		CLS;
		DrawTop();
		string yesno[] = { "Yes", "No" };
		options.log_enabled = Menu(yesno, 2) == 1 ? true : false;
		break;
	}
}

void correct_loading_failures() {
	if (local_options.path == "") {
		local_options.path = DEFAULT_DATA_FILE;
	}
	if (local_options.log_file == "") {
		local_options.log_file = DEFAULT_LOG_FILE;
	}
	if (local_options.splash_art == "") {
		local_options.splash_art = DEFAULT_SPLASH_FILE;
	}
	if (local_options.menu_art == "") {
		local_options.menu_art = DEFAULT_ART_FILE;
	}
}