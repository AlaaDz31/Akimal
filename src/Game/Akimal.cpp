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
		std::cout << _current->key << "? (y/n):";

		do
		{
			std::cin >> input;
			toLowerCase(input);

			if (PositiveAnswer(input))
				return Game(_current->left);

			else if (NegativeAnswer(input))
				return Game(_current->right);

			else
				std::cout << "Not valid. Answer either 'yes' or 'no': ";

		} while (!PositiveAnswer(input) && !NegativeAnswer(input));
	}

	else
	{
		std::cout << "Do you mean " << _current->key << "? (y/n):";

		do
		{
			std::cin >> input;
			toLowerCase(input);

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (PositiveAnswer(input))
				std::cout << "I won :-)" << std::endl;

			else if (NegativeAnswer(input))
			{
				std::cout << "I lost :-(" << std::endl;
				AddEntry(_current);
			}

			else
				std::cout << "Not valid. Answer either 'yes' or 'no': ";

		} while (!PositiveAnswer(input) && !NegativeAnswer(input));
	}
}

// Adds a new animal to the tree
void Akimal::AddEntry(node_p _current)
{
	string answer,
		tmp = _current->key;

	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	std::cout << "What animal did you mean?: ";
	getline(std::cin, answer);
	_current->left = new str_node(answer);

	std::cout << "What's the difference between '" << answer << "' and '" << tmp << "'?: ";
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
		_file << QUESTION_ID << n->key << '\n';
		Save(_file, n->left);
		Save(_file, n->right);
	}

	else						// an answer
		_file << n->key << '\n';
}

// Loads the tree from a file
void Akimal::Load(string _path)
{
	// clear previous state and configuration
	Clear();
	path = _path;

	int whiteLnsAtBeg;
	ifstream file(_path);

	// re-use _path to hold input string
	// skip all empty string from the beginning of the file
	_path = IgnoreSpacesInFile(file, 0, whiteLnsAtBeg);

	// file exists and can be read
	if (file.good() && !_path.empty())
	{
		/*
		 * nlines is a 64-bits integer that holds info about number of file lines read:
		 *	• the first byte (from left) is the number of white-read lines, which can be either blank or badly-formatted
		 *	• the last three bytes stand for the real number of nodes loaded
		*/
		uint64_t nlines = (whiteLnsAtBeg - 1 >> 8) + 1;	// assigned no. of whitelines read + 1

		// format error: first line is not a question
		if (_path[0] != QUESTION_ID && _path.find_first_not_of(ALL_COMMON_SPACES) != string::npos)
			std::clog << "Akimal::Load(string) @ Error -- In file " << path << " line no. " << (whiteLnsAtBeg - 1 >> 8) + 1 << " has an incorrect format." << std::endl;
		
		else
		{
			root = new str_node(_path.substr(1));

			// begin recursive assignment -- nlines is passed by ref
			root->left = Load(file, nlines);
			root->right = Load(file, nlines);

			// check both failbit and badbit of the stream
			if (file.bad())
			{
				std::clog << "Akimal::Load(string) @ Error -- There was an unexpected error while reading file " << path << "." << std::endl;
				Clear();
			}

			// ensure eof was reached (or remaining chars are spaces)
			else if (!file.eof() && !IgnoreSpacesInFile(file, file.tellg()).empty())
			{
				std::clog << "Akimal::Load(string) @ Error -- It was impossible to read entire file at " << path << "." << std::endl;
				Clear();
			}

			// number of question must be number of unswers -1, otherwise at least one node is missing
			else if ((nlines & ANSWER_SIZE_MASK) == ((nlines & QUESTION_SIZE_MASK) >> 28) + 1)
			{
				std::clog << "Akimal::Load(string) @ Error -- In file " << path << " one or more entries are missing." << std::endl;
				Clear();
			}

			// if first byte is low, loading was correct
			else
				size = (nlines & ANSWER_SIZE_MASK) + ((nlines & QUESTION_SIZE_MASK) >> 28) + 1;
		}
	}

	else
		std::clog << "Akimal::Load(string) @ Error -- Cannot read file " << path << "." << std::endl;
}

// Loads a subtree from a file
Akimal::node_p Akimal::Load(ifstream& _file, uint64_t& _line_n)
{
	string line;

	// input a line
	if (getline(_file, line))
	{
		// if it begins with '?', it is a question line
		if (line[0] == QUESTION_ID)
		{
			node_p tmp = new str_node(line.substr(1));	// exclude '?' from the line

			_line_n += QUESTION_SIZE_UNIT;

			// assign childrens
			tmp->left = Load(_file, _line_n);
			tmp->right = Load(_file, _line_n);

			return tmp;
		}

		// empty line: send a warning
		else if (EmptyLine(line))
		{
			_line_n += BLANK_LINES_UNIT;
			std::clog << "Akimal::Load(ifstream&, uint&) @ Warning -- In file " << path << " line no. " << (_line_n & BLANK_LINES_MASK + _line_n & QUESTION_SIZE_MASK + _line_n & ANSWER_SIZE_MASK) << " is empty." << std::endl;

			// skip this line and continue recursion
			return Load(_file, _line_n);
		}

		// it is an answer line
		else
		{
			_line_n += ANSWER_SIZE_UNIT;
			return new str_node(line);
		}
	}

	// reading error
	return nullptr;
}