#include <sstream>
#include "..\Game\Akimal.h"
#include "..\bin\Graphics\Graphics.h"
#include "..\bin\Options\Options.h"
#include "..\bin\Options\ini.h"

#pragma comment(lib, "Winmm.lib")

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
	music_wav,
	music_enabled,
	def_question,
	def_correct_ans,
	def_wrong_ans,
	exit
};

// instance to play the game
Akimal game;

// Menu of strings
string game_menu[] = { "Play", "Options", "Exit" };

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

	string	answer;						// holder for all answers
	MainMenu res;

	game.Load (local_options.path);

	ShowSplashScreen();
	cin.ignore(); CLS;
	menu_art = GetArt();

	do	// Game loop
	{
		// log configuration
		ofstream log(local_options.log_file, ios::app);
		if (local_options.log_enabled)
		{
			log << endl;
			clog.rdbuf(log.rdbuf());	// redirect clog stream to the log file
		}
		else
			clog.rdbuf(cerr.rdbuf());

		// music configuration
		if (local_options.music_enabled)
			PlaySound(local_options.music_wav.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		else
			PlaySound(NULL, NULL, NULL);

		// game obj configuration
		game.setDefaultInitializationKeys(local_options.def_question, local_options.def_correct_ans, local_options.def_wrong_ans);

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
	return
	{
		getKey("Options", "path", ini),
		getKey("Options", "splash", ini),
		getKey("Options", "menu", ini),
		getKey("DefaultTree", "question", ini),
		getKey("DefaultTree", "correct", ini),
		getKey("DefaultTree", "wrong", ini),
		getKey("Options", "log_file", ini),
		(getKey("Options", "log_enabled", ini) == "1"),
		getKey("Options", "music_wav", ini),
		(getKey("Options", "music_enabled", ini) == "1")
	};
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
	setKey("Options", "music_wav", options.music_wav, ini);
	setKey("Options", "music_enabled", options.music_enabled ? "1" : "0", ini);
}

void ShowOptionsMenu(GameOptions& options)
{
	string options_menu[] =
	{
		"Change saving file",
		"Change splash art file",
		"Change menu art file",
		"Change log file",
		"Enable/disable logging",
		"Change music file",
		"Enable/Disable music",
		"Change default question",
		"Change default correct answer",
		"Change default wrong answer",
		"Exit"
	};
	string yes_no[] = { "Enable", "Disable" };
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
			cout << "New saving file (" << options.path << "):";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				if (FileChanger (options.path, answer))
				{
					cout << "\nEdit success." << endl;
					game.Load (options.path);
				}
				else
					cout << "\nValue unchanged." << endl;

				cin.ignore();
			}
			break;

		case OptionsMenu::splash_file:
			//Change Splash Art
			cout << "New splash art file (" << options.splash_art << "):";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				if (FileChanger(options.splash_art, answer))
					cout << "\nEdit success." << endl;

				else
					cout << "\nValue unchanged." << endl;

				cin.ignore();
			}
			break;

		case OptionsMenu::art_file:
			//Change Menu Art
			cout << "New menu art file (" << options.menu_art << "):";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				if (FileChanger(options.menu_art, answer))
					cout << "\nEdit success." << endl;

				else
					cout << "\nValue unchanged." << endl;

				cin.ignore();
			}
			break;

		case OptionsMenu::log_file:
			//Change log file
			cout << "New log file (" << options.log_file << "):";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				if (FileChanger(options.log_file, answer))
					cout << "\nEdit success." << endl;

				else
					cout << "\nValue unchanged." << endl;

				cin.ignore();
			}
			break;

		case OptionsMenu::log_enabled:
			//Change log enabler
			DrawTop();
			options.log_enabled = Menu(yes_no, 2) % 2;
			break;

		case OptionsMenu::music_wav:
			//Change music file
			cout << "New music file (" << options.music_wav << "):";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				options.music_wav = answer;
				cout << "\nEdit success." << endl;
				cin.ignore();
			}
			break;

		case OptionsMenu::music_enabled:
			//Change music enabler
			DrawTop();
			options.music_enabled = Menu(yes_no, 2) % 2;
			break;

		case OptionsMenu::def_question:
			//Change default question
			cout << "New default question:";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				options.def_question = answer;
				cout << "\nEdit success." << endl;
				cin.ignore();
			}
			break;

		case OptionsMenu::def_correct_ans:
			//Change default correct answer
			cout << "New default correct answer:";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				options.def_correct_ans = answer;
				cout << "\nEdit success." << endl;
				cin.ignore();
			}
			break;

		case OptionsMenu::def_wrong_ans:
			//Change default wrong answer
			cout << "New default wrong answer:";
			getline(cin, answer);
			if (!QuitAnswer(answer, false))
			{
				options.def_wrong_ans = answer;
				cout << "\nEdit success." << endl;
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

	if (local_options.splash_art.empty() || !FileExists(local_options.splash_art))
		local_options.splash_art = DEFAULT_SPLASH_FILE;

	if (local_options.menu_art.empty() || !FileExists(local_options.menu_art))
		local_options.menu_art = DEFAULT_ART_FILE;

	if (local_options.log_file.empty() || !FileExists(local_options.log_file))
		local_options.log_file = DEFAULT_LOG_FILE;

	if (local_options.def_question.empty())
		local_options.def_question = DEFAULT_QUESTION;

	if (local_options.def_correct_ans.empty())
		local_options.def_correct_ans = DEFAULT_CORRECT_ANS;

	if (local_options.def_wrong_ans.empty())
		local_options.def_wrong_ans = DEFAULT_WRONG_ANS;
}

bool FileChanger(string& _to_change, string _new_path)
{
	if (!FileExists(_new_path))
	{
		string ans;

		cout << "File " << " does not exist. Do you wish to create it? (y/n) ";
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