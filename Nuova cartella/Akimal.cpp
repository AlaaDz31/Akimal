#include "Akimal.h"

Akimal::Akimal(string _path)
{
	// values are assigned by default
	Load(_path);	// path is updated here
}

Akimal::~Akimal()
{
	Clear();
}

void Akimal::Dispose(node_p n)
{
	if (n != nullptr)
	{
		Dispose(n->left);
		Dispose(n->right);
		delete n;
	}
}

inline void Akimal::Clear()
{
	if (!Empty())
		Dispose(root);

	root = nullptr;
	size = 0;
}

inline bool Akimal::Empty() const
{
	return root == nullptr;
}

size_t Akimal::Size(node_p n) const
{
	if (n == nullptr)
		return 0;

	return 1 + Size(n->left) + Size(n->right);
}

inline size_t Akimal::Size() const
{
	return Size(root);
}

uint Akimal::getAnswerNum(node_p n) const
{
	if (n == nullptr)
		return 0;

	if (n->isLeaf())
		return 1;

	return getAnswerNum(n->left) + getAnswerNum(n->right);
}

void Akimal::Game(node_p current)
{
	string input;
	if (size == 0) return;
	if (current->isParent()) {
		cout << current->key << "? (Yes/No):";
		do {
			cin >> input;
			if (input == "y")
				return Game(current->left);
			else if (input == "n")
				return Game(current->right);
			else
				cout << "Not Valid\n";
		} while (input != "y"&&input != "n");
	}
	else {
		cout << "I guess " << current->key << ". (Yes/No):";
		do {
			cin >> input;
			if (input == "y")
				cout << "I won.\n";
			else if (input == "n")
				AddEntry(current);
			else
				cout << "Not Valid\n";
		} while (input != "y"&&input != "n");
	}
}

void Akimal::AddEntry(node_p current)
{
	string tmp = current->key, animal, question;
	cout << "What animal did you meant?: ";
	cin >> animal;
	cout << "What is the difference between the two?: ";
	cin >> question;
	current->key = question;
	current->left = new str_node(animal);
	current->right = new str_node(tmp);
}

inline uint Akimal::getAnswerNum() const
{
	return getAnswerNum(root);
}

inline uint Akimal::getQuestionNum() const
{
	return Size() - getAnswerNum();
}

inline void Akimal::Game()
{
	Game(root);
}

inline void Akimal::Save()
{
	Save(path);
}

inline void Akimal::Save(string _path)
{
	ofstream file(_path);

	// ensure it can be overwritten
	if (file.good())
		Save(file, root);

	else
		clog << "Save(string) @ Current configuration cannot be saved in " << _path << "." << endl;

	file.close();
}

void Akimal::Save(ofstream& file, node_p node)
{		// perform a pre-oreder function

	if (node->isParent())		// a question
	{
		file << QUESTION_ID << node->key << '\n';
		Save(file, node->left);
		Save(file, node->right);
	}

	else						// an answer
		file << node << '\n';
}

inline void Akimal::Reload()
{
	Load(path);
}

void Akimal::Load(string _path)
{
	// clear previous state and configuration
	Clear();
	path = _path;

	ifstream file(path);

	// ensure it can be read (not empty or damaged)
	if (file.peek() == ifstream::traits_type::eof())
		clog << "Load(string) @ File " << _path << " is empty! No data can be found." << endl;

	else if (file.good())
	{
		// get number of lines during input process
		int lines = Load(file, root);

		// check if eof wasn't reached
		if ((int)file.tellg() != ifstream::traits_type::eof())
		{
			clog << "Load(string) @ It was impossible to read the entire file at " << _path << "." << endl;
			Clear();
		}

		// ensure no node has only one child
		else if (lines % 2 == 0)
		{
			clog << "Load(string) @ An error occurred while reading file " << path << ": one or more lines are missing!" << endl;
			Clear();
		}

		// after all checks, we know configuration is safe
		else
			size = lines;
	}

	else
		clog << "Load(string) @ File " << _path << " cannot be loaded." << endl;

	file.close();
}

uint Akimal::Load(ifstream& file, node_p n)
{
	// if eof was reached, no new line
	if (file.eof())
		return 0;

	string line;

	if (getline(file, line))	// input successful
	{
		// check if line begins with '?'
		if (line.at(0) == QUESTION_ID)
		{
			n = new str_node(line.substr(1));
			return 1 + Load(file, n->left) + Load(file, n->right);
		}

		else
			n = new str_node(line);
	}
	// if either there was a reading error in a line,
	//	or it was a corrent answer line
	return 1;
}