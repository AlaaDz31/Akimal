#include "Akimal.h"

// Constructor with file loader
Akimal::Akimal(string _path)
{
	// values are assigned by default
	Load(_path);	// path is updated here
	Initialize();
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
void Akimal::Game(node_p& current)
{
	string input;

	if (current->isParent())
	{
		std::cout << current->key << "? (y/n):";

		do
		{
			std::cin >> input;

			if (PositiveAnswer(input))
				return Game(current->left);

			else if (NegativeAnswer(input))
				return Game(current->right);

			else
				std::cout << "Not Valid\n";

		} while (!PositiveAnswer(input) && !NegativeAnswer(input));
	}

	else
	{
		std::cout << "I guess " << current->key << ". Am I correct? (Yes/No):";

		do
		{
			std::cin >> input;

			if (PositiveAnswer(input))
				std::cout << "I won.\n";

			else if (NegativeAnswer(input))
				AddEntry(current);

			else
				std::cout << "Not Valid. Answer either 'yes' or 'no': \n";

		} while (!PositiveAnswer(input) && !NegativeAnswer(input));
	}
}

// Adds a new animal to the tree
void Akimal::AddEntry(node_p& current)
{
	string answer,
		tmp = current->key;

	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	std::cout << "What animal did you mean?: ";
	getline(std::cin, answer);
	current->left = new str_node(answer);

	std::cout << "What is the difference between the two?: ";
	getline(std::cin, answer);

	answer.back() == '?' ?
		answer.pop_back()
		: void();

	current->key = answer;
	current->right = new str_node(tmp);
}

// Saves the tree
void Akimal::Save(string _path)
{
	ofstream file(_path);
	path = _path;
	// if tree is empty, there is nothing to save
	if (Empty())
		std::clog << "Akimal::Save(string) @ Cannot save data to " << _path << ": tree is empty." << std::endl;

	// ensure file can be overwritten
	else if (file.good())
		Save(file, root);

	else
		std::clog << "Akimal::Save(string) @ There was an error while trying to save current configuration in " << _path << "." << std::endl;

	file.close();
}

// Saves a subtree
void Akimal::Save(ofstream& file, node_p node)
{
	if (node->isParent())		// a question
	{
		file << '\n' << QUESTION_ID << node->key;
		Save(file, node->left);
		Save(file, node->right);
	}

	else						// an answer
		file << '\n' << node->key;
}

void Akimal::Load(string _path)
{
	// clear previous state and configuration
	Clear();
	path = _path;

	ifstream file(path);

	// have to ensure file can be read 
	//	(not empty or damaged)

	// check if it is empty
	//if (file.peek() == ifstream::traits_type::eof())
	//	std::clog << "Akimal::Load(string) @ File " << _path << " is empty! No data can be found." << std::endl;

	// prevent any reading error
	if (file.good())
	{
		int whiteLines = 0;
		string spaces = ALL_COMMON_SPACES;

		// remove all spaces before first "written" line
		while (!file.eof() && file.peek() != QUESTION_ID)
			if (spaces.find(file.get()) != string::npos)
			{
				std::clog << "Akimal::Load(string) @ Format error in file " << _path << "." << std::endl;
				return;
			}
		file.unget();

		// check if eof has been reached
		if (file.eof())//((int) file.tellg() != ifstream::traits_type::eof())
		{
			std::clog << "Akimal::Load(string) @ It was impossible to read the entire file at " << _path << "." << std::endl;
			Clear();
		}

		else
		{
			// get number of lines during input process
			int lines = Load(file, root);

			if (!file.eof())//((int) file.tellg() != ifstream::traits_type::eof())
			{
				std::clog << "Akimal::Load(string) @ It was impossible to read the entire file at " << _path << "." << std::endl;
				Clear();
			}

			// ensure no node has only one child
			else if (lines % 2 == 0)
			{
				std::clog << "Akimal::Load(string) @ An error occurred while reading file " << path << ": one or more lines are missing!" << std::endl;
				Clear();
			}

			// after all checks, we know configuration is safe
			else
				size = lines;
		}
	}

	else
		std::clog << "Akimal::Load(string) @ File " << _path << " cannot be loaded." << std::endl;

	file.close();
}

uint Akimal::Load(ifstream& file, node_p& n)
{
	// if eof was reached, no new line
	if (file.eof())
		return 0;

	string line;

	if (getline(file, line))	// input successful
	{
		// check if line begins with '?' --> it is a characteristic / question
		if (line.at(0) == QUESTION_ID)
		{
			n = new str_node(line.substr(1));
			return 1 + Load(file, n->left) + Load(file, n->right);
		}

		else
			n = new str_node(line);
	}

	// if either there was a reading error in the line,
	//	or it was a corrent answer line
	return 1;
}