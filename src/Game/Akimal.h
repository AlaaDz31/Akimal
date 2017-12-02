#pragma once
#include "GameData.h"
#include "..\..\lib\bst.cpp"
#include <fstream>
#include <sstream>

class Akimal
	: private BST<GameData>
{
	using DataNode = TreeNode<GameData>;
	ushort size;
	string path;

	void assignWeight (DataNode*);

	void saver (ofstream&, DataNode*);
	void loader (ifstream&, DataNode*&);

public:
	using BST::Empty;
	using BST::Clear;

	Akimal (string);			// loads from file
	// inherited destructor

	void Game ();

	void save ();
	void load ();
	void setFile (string);

	uint AnswerNum ();
	uint QuestionNum ();
};

