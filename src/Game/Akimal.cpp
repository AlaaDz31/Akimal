#include "Akimal.h"

inline Akimal::Akimal (string_cref _path)
{
	root = nullptr;
	comparator = less<const GameData> ();
	path = _path;
	load (path);
	size = Size ();
}

void Akimal::assignWeight (DataNode* n)
{
	if (n != nullptr)
	{
		assignWeight (n->left);
		n->key.weight = size++;
		assignWeight (n->right);
	}
}

void Akimal::save (ofstream& o, DataNode* n)
{
	if (o.good ())
	{
		if (n != nullptr)
		{
			o << n->key.toString ();
			save (o, n->left);
			save (o, n->right);
		}
	}

	else
	{		// generic error

		clog << "An error occurred while trying to save data." << endl;
		Clear ();
	}
}

inline void Akimal::save ()
{
	save (path);
}

inline void Akimal::save (string_cref _path)
{
	size = 0;
	assignWeight (root);

	ofstream o (_path);
	save (o, root);
	o.close ();
}

void Akimal::load (string_cref _path)
{
	Clear ();

	path = _path;
	ifstream i (_path);	// file input stream
	string line;		// stores input lines
	int lineCnt = -1;	// line counter, needed to report format errors
	GameData data;		// temporary stores data from lines

	// if at the beginning is eof, it is empty
	if (i.eof ())
		clog << "File \"" << path << "\" is empty." << endl;

	// insert each line, if the format is good
	while (i.good () && getline (i, line) && ++lineCnt && GameData () != (data = GameData::checkFormat (line)))
		Insert (data);

	// end of file has not been reached
	if (!i.eof ())
	{
		// there is a line with an incorrect format
		if (data == GameData ())
			clog << "Error at line " << lineCnt << " in file \"" << path << "\": format is not correct." << endl;

		clog << "An error occurred while trying to load data." << endl;
	}

	i.close ();
}

inline ushort Akimal::AnswerNum ()
{
	return getLeafNum ();
}

inline ushort Akimal::QuestionNum ()
{
	return size - AnswerNum ();
}
