#include "Akimal.h"

void Akimal::assignWeight (DataNode* n)
{
	if (n != nullptr)
	{
		assignWeight (n->left);
		n->key.data = size++;
		assignWeight (n->right);
	}
}

void Akimal::saver (ofstream& o, DataNode* n)
{
	if (n != nullptr && o.good ())
	{
		o << n->key.toString ();
		saver (o, n->left);
		saver (o, n->right);
	}

	else Clear ();		// there was an error
}

void Akimal::loader (ifstream& i, DataNode*& n)
{
	string line;
	int divPos, tmp;

	while (i.good () && getline (i, line))
	{
		divPos = line.find ('|');
		// check format
	}

	if (!i.eof ())		// there was an error
		Clear ();
}

Akimal::Akimal (string _path)
{
	path = _path;
	load ();
	size = Size ();
}

inline void Akimal::save ()
{
	size = 0;
	assignWeight (root);

	ofstream o (path);
	saver (o, root);
	o.close ();
}

inline void Akimal::load ()
{
	Clear ();

	ifstream i (path);
	loader (i, root);
	i.close ();
}

inline void Akimal::setFile (string _path)
{
	Clear ();
	local = Akimal (_path);
}

inline uint Akimal::AnswerNum ()
{
	return getLeafNum ();
}

inline uint Akimal::QuestionNum ()
{
	return size - AnswerNum ();
}
