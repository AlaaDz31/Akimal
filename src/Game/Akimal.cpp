#include "Akimal.h"

// Constructor with file loader
Akimal::Akimal(string _path)
{
	// values are assigned by default
	Load(_path);	// path is updated here
}

// Destructor
Akimal::~Akimal()
{
	Clear();
}

// Disposes a subtree
void Akimal::Dispose(node_p n)
{
	if (n != nullptr)
	{
		Dispose(n->left);
		Dispose(n->right);
		delete n;
	}
}

// Returns number of leafs in a subtree
uint Akimal::getAnswerNum(node_p n) const
{
	if (n == nullptr)
		return 0;

	if (n->isLeaf())
		return 1;

	return getAnswerNum(n->left) + getAnswerNum(n->right);
}

// Guesser
void Akimal::Game(node_p _current)
{
	string input;

	if (_current->isParent())
	{
		std::cout << _current->key << "? (s/n):";

		do
		{
			std::cin >> input;
			toLowerCase(input);

			if (PositiveAnswer(input))
				return Game(_current->left);

			else if (NegativeAnswer(input))
				return Game(_current->right);

			else
				std::cout << "Risposta non valida. Rispondi o 's" << (char) 141 << "' o 'no': \n";

		} while (!PositiveAnswer(input) && !NegativeAnswer(input));
	}

	else
	{
		std::cout << "Intendi " << _current->key << "? (s/n):";

		do
		{
			std::cin >> input;
			toLowerCase(input);

			if (PositiveAnswer(input))
				std::cout << "I won.\n";

			else if (NegativeAnswer(input))
				AddEntry(_current);

			else
				std::cout << "Risposta non valida. Rispondi o 's" << (char) 141 << "' o 'no': \n";

		} while (!PositiveAnswer(input) && !NegativeAnswer(input));
	}
}

// Adds a new animal to the tree
void Akimal::AddEntry(node_p _current)
{
	string answer,
		tmp = _current->key;

	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	std::cout << "Che animale intendevi?: ";
	getline(std::cin, answer);
	_current->left = new str_node(answer);

	std::cout << "Cosa differenzia l'animale " << answer << " dall'animale " << tmp << "?: ";
	getline(std::cin, answer);

	answer.back() == '?' ?
		answer.pop_back()
		: void();

	_current->key = answer;
	_current->right = new str_node(tmp);
}

// Saves the tree to a file
void Akimal::Save(string _path)
{
	// if tree is empty, there is nothing to save
	if (Empty())
		std::clog << "Akimal::Save(string) @ Cannot save data to " << _path << ": tree is empty." << std::endl;

	else
	{
		ofstream file(_path);

		// ensure file can be overwritten
		if (file.good())
			Save(file, root);

		else
			std::clog << "Akimal::Save(string) @ There was an error while trying to save current configuration in " << _path << "." << std::endl;

		file.close();
	}
}

// Saves a subtree to a file
void Akimal::Save(ofstream& _file, node_p n)
{
	if (n->isParent())		// a question
	{
		_file << '\n' << QUESTION_ID << n->key;
		Save(_file, n->left);
		Save(_file, n->right);
	}

	else						// an answer
		_file << '\n' << n->key;
}

// Loads a tree from a file
//void Akimal::Load(string _path)
//{
//	// clear previous state and configuration
//	Clear();
//	path = _path;
//
//	ifstream file(path);
//
//	// NOTE: have to ensure file can be read (neither empty nor damaged)
//
//	// prevent any stream-reading error
//	if (file.good())
//	{
//		int whiteLines = 0;		// counts whitelines
//		string garbage;			// contains non-relevant lines
//
//		// remove all spaces before first '?'-char-beginning line
//		while (getline(file, garbage) && ++whiteLines)
//		{
//			// check if the first question line has been reached
//			if (garbage[0] == QUESTION_ID)
//			{
//				//
//				break;
//			}
//
//			// check if there are unwanted characters before first question line
//			if (garbage.find_first_not_of(ALL_COMMON_SPACES) != std::string::npos)
//			{
//				std::clog << "Akimal::Load(string) @ Format error in file " << _path << " at line " << whiteLines << ". Cannot read it." << std::endl;
//				goto End;
//			}
//		}
//
//		// check if eof has been reached
//		if ((int) file.tellg() == ifstream::traits_type::eof())
//		{
//			// check if previous loop has been skipped
//			if (whiteLines == 0)
//				std::clog << "Akimal::Load(string) @ File " << _path << " is empty." << std::endl;
//
//			else
//				std::clog << "Akimal::Load(string) @ File " << _path << " has only not allowed lines." << std::endl;
//		}
//
//		else
//		{
//			// get number of lines during input process
//			int lines = Load(file, root);
//			std::cout << lines << std::endl;
//
//			/// Read whitelines again, by first setting whitelines to 0
//
//			getline(file, garbage);
//			std::cout << "::" << garbage << "::" << std::endl;
//
//			if ((int) file.tellg() != ifstream::traits_type::eof())
//			{
//				std::clog << "Akimal::Load(string) @ It was impossible to read the entire file at " << _path << "." << std::endl;
//				Clear();
//			}
//
//			// ensure no node has only one child
//			else if (lines % 2 == 0)
//			{
//				std::clog << "Akimal::Load(string) @ An error occurred while reading file " << path << ": one or more lines are missing!" << std::endl;
//				Clear();
//			}
//
//			// after all checks, we know configuration is safe
//			else
//				size = lines;
//		}
//	}
//
//	else
//		std::clog << "Akimal::Load(string) @ File " << _path << " cannot be loaded." << std::endl;
//
//End:
//	file.close();
//}

void Akimal::Load(string _path)
{
	// clear previous state and configuration
	Clear();
	path = _path;

	ifstream file(_path);

	// file exists and can be read
	if (file.good())
	{
		uint32_t nlines = Load(file, root);
	}
}

//// Loads a subtree from a file
//uint Akimal::Load(ifstream& _file, node_p& n)
//{
//	// if eof was reached, no new line
//	if ((int) _file.tellg() == ifstream::traits_type::eof())
//		return 0;
//
//	string line;
//
//	if (getline(_file, line))	// input successful -- line is not empty
//	{
//		std::cout << line << std::endl;
//		// check if line begins with '?' --> it is a characteristic / question
//		if (line.at(0) == QUESTION_ID)
//		{
//			n = new str_node(line.substr(1));
//			return 1 + Load(_file, n->left) + Load(_file, n->right);
//		}
//
//		n = new str_node(line);
//		return 1;
//	}
//
//	// empty lines are not counted
//	if (EmptyLine(line))
//		return Load(_file, n->left) + Load(_file, n->right);
//
//	// there was a reading error in the line
//	return 0;
//}

uint32_t Akimal::Load(ifstream& _file, node_p& n)
{
	string line;
	if (getline(_file, line))
	{
		if (line[0] == QUESTION_ID)
		{

		}
		else if (EmptyLine(line))
		{

		}
		else if (root == nullptr && line.find_first_not_of(ALL_COMMON_SPACES) != string::npos)
		{

		}
		else
		{

		}
	}
}