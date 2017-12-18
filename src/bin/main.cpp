#include <sstream>
#include "..\Game\Akimal.h"
#include "..\bin\Graphics\Graphics.h"
#include "..\bin\Options\Options.h"
#include "..\bin\Options\ini.h"

STD;

// Default file paths:
#define DEFAULT_ART_FILE		"../Akimal/bin/res/menu_text.txt"
#define DEFAULT_DATA_FILE		"../Akimal/bin/res/akimal.txt"
#define DEFAULT_LOG_FILE		"../Akimal/bin/res/log.txt"
#define DEFAULT_SPLASH_FILE		"../Akimal/bin/res/splash.txt"
#define DEFAULT_OPTIONS_FILE	"../Akimal/bin/res/Options.ini"

// Enumeration with options provided by the game menu
enum class MainMenu
{
	play = 1,
	options,
	exit
};

// Enumeration with options provided by the options menu
enum class OptionsMenu
{
	save_file = 1,
	splash_file,
	art_file,
	log_file,
	log_enabled,
	def_question,
	def_correct_ans,
	def_wrong_ans,
	exit
};

// Menu of strings
string game_menu[] = { "Gioca", "Opzioni", "Esci" };

// Object that contains current state of .ini options
GameOptions local_options;

// holder for art string
string menu_art;

// Displays splash screen
void ShowSplashScreen();

// Displays Options menu
void ShowOptionsMenu(GameOptions&);

// Returns a string with an art
string GetArt();

// Assigns the file to read from
string FileSelection(string);

// Loads options from option file
GameOptions loadOptions(string);

// Corrects invalid options loaded
void correctLoadingFailures();

// Saves options to options file
void saveOptions(const GameOptions, string);

// Performs all checks before a file path change
bool FileChanger(string&, string);

int main()
{
	local_options = loadOptions(DEFAULT_OPTIONS_FILE);
	correctLoadingFailures();

	// log configuration
	ofstream log(local_options.log_file, ios::app);
	if (local_options.log_enabled)
	{
		log << endl;
		clog.rdbuf(log.rdbuf());	// redirect stderr stream to the log file
	}

	Akimal game(local_options.path);	// instance to play the game
	string	answer;						// holder for all answers
	MainMenu res;

	ShowSplashScreen();
	cin.ignore(); CLS;
	menu_art = GetArt();

	do	// Game loop
	{
		cout << menu_art << endl;
		DrawTop();
		res = (MainMenu) Menu(game_menu, sizeof(game_menu) / sizeof(string));

		switch (res)
		{
		case MainMenu::play:
			game.Game();
			break;

		case MainMenu::options:
			ShowOptionsMenu(local_options);
			cin.putback('\n');		// to overpass cin.ignore after switch statement
			break;

		case MainMenu::exit:
			saveOptions(local_options, DEFAULT_OPTIONS_FILE);
			game.Save(local_options.path);
			log.close();
			break;

		default:
			clog << "Main:switch(default) @ Unexpected error.\n";
			break;
		}

		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		CLS;

	} while (res != MainMenu::exit);
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
	return tmp;
}

void saveOptions(GameOptions options, string ini)
{
	setKey("Options", "path", options.path, ini);
	setKey("Options", "splash", options.splash_art, ini);
	setKey("Options", "menu", options.menu_art, ini);
	setKey("DefaultTree", "question", options.def_question, ini);
	setKey("DefaultTree", "correct", options.def_correct_ans, ini);
	setKey("DefaultTree", "wrong", options.def_wrong_ans, ini);
	setKey("Options", "log_file", options.log_file, ini);
	setKey("Options", "log_enabled", options.log_enabled ? "1" : "0", ini);
}

void ShowOptionsMenu(GameOptions& options)
{
	string options_menu[] =
	{
		"Modifica file di salvataggio",
		"Modifica file di splash art",
		"Modifica file di menu art",
		"Modifica file di log",
		"Abilita/Disabilita logging",
		"Cambia domanda predefinita",
		"Cambia risposta corretta predefinita",
		"Cambia risposta sbagliata predefinita",
		"Esci"
	};
	string yes_no[] = { "Abilita", "Disabilita" };
	string answer;
	OptionsMenu res;

	do
	{
		CLS;

		cout << menu_art << endl;
		DrawTop();
		res = (OptionsMenu) Menu(options_menu, sizeof(options_menu) / sizeof(string));

		CLS;
		cout << menu_art << endl;
		switch (res)
		{
		case OptionsMenu::save_file:
			//Change Saving File
			cout << "Nuovo file di salvataggio (" << options.path << "):";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				if (FileChanger(options.path, answer))
					cout << "\nModifica effettuata correttamente." << endl;

				else
					cout << "\nModifica non effettuata." << endl;

				cin.ignore();
			}
			break;

		case OptionsMenu::splash_file:
			//Change Splash Art
			cout << "Nuovo file di splash art (" << options.splash_art << "):";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				if (FileChanger(options.splash_art, answer))
					cout << "\nModifica effettuata correttamente." << endl;

				else
					cout << "\nModifica non effettuata." << endl;

				cin.ignore();
			}
			break;

		case OptionsMenu::art_file:
			//Change Menu Art
			cout << "Nuovo file di menu art (" << options.menu_art << "):";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				if (FileChanger(options.menu_art, answer))
					cout << "\nModifica effettuata correttamente." << endl;

				else
					cout << "\nModifica non effettuata." << endl;

				cin.ignore();
			}
			break;

		case OptionsMenu::log_file:
			//Change log file
			cout << "Nuovo file di log (" << options.log_file << "):";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				if (FileChanger(options.path, answer))
					cout << "\nModifica effettuata correttamente." << endl;

				else
					cout << "\nModifica non effettuata." << endl;

				cin.ignore();
			}
			break;

		case OptionsMenu::log_enabled:
			//Change log enabler
			DrawTop();
			options.log_enabled = Menu(yes_no, 2) % 2;
			break;

		case OptionsMenu::def_question:
			//Change default question
			cout << "Nuova domanda predefinita:";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				options.def_question = answer;
				cout << "\nModifica effettuata correttamente." << endl;
				cin.ignore();
			}
			break;

		case OptionsMenu::def_correct_ans:
			//Change default correct answer
			cout << "Nuova risposta corretta predefinita:";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				options.def_correct_ans = answer;
				cout << "\nModifica effettuata correttamente." << endl;
				cin.ignore();
			}
			break;

		case OptionsMenu::def_wrong_ans:
			//Change default wrong answer
			cout << "Nuova risposta sbagliata predefinita:";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				options.def_wrong_ans = answer;
				cout << "\nModifica effettuata correttamente." << endl;
				cin.ignore();
			}
			break;
		}

	} while (res != OptionsMenu::exit);
}

void correctLoadingFailures()
{
	if (local_options.path.empty() || !FileExists(local_options.path))
		local_options.path = DEFAULT_DATA_FILE;

	if (local_options.log_file.empty() || !FileExists(local_options.path))
		local_options.log_file = DEFAULT_LOG_FILE;

	if (local_options.splash_art.empty() || !FileExists(local_options.path))
		local_options.splash_art = DEFAULT_SPLASH_FILE;

	if (local_options.menu_art.empty() || !FileExists(local_options.path))
		local_options.menu_art = DEFAULT_ART_FILE;
}

bool FileChanger(string& _to_change, string _new_path)
{
	if (!FileExists(_new_path))
	{
		string ans;

		cout << "Il file " << " non esiste. Vuoi crearlo? (s/n) ";
		cin >> ans;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');

		if (NegativeAnswer(ans, false))
			return false;

		// Create file:
		ofstream o(_new_path);
		o.close();
	}

	_to_change = _new_path;
	return true;
}