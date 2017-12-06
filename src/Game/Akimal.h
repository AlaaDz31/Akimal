#pragma once
#include <fstream>
#include "..\..\lib\nodes.h"

#define QUESTION_ID '?'

/*
 * maybe Size() methods aren not needed
*/

class Akimal
{
	/// aliases
	using str_node = TreeNode<string>;
	using node_p = TreeNode<string>*;

	/// recursive methods:
	void Dispose(node_p);
	size_t Size(node_p) const;
	uint getAnswerNum(node_p) const;

	//void Game(node_p);
	void Save(ofstream&, node_p);
	uint Load(ifstream&, node_p);	// returns number of lines read, corresponding to current size

public:
	Akimal () = default;
	Akimal (const Akimal&) = delete;
	Akimal (Akimal&&) = default;
	Akimal(string);
	~Akimal();

	bool Empty() const;
	void Clear();
	size_t Size() const;
	uint getAnswerNum() const;
	uint getQuestionNum() const;

	//void Game();
	void Save();			// save to default path
	void Save(string);		// save to a specific path
	void Load(string);		// load from a specific path
	void Reload();			// reload info from default path, if it's set

	Akimal& operator= (const Akimal&) = delete;
	Akimal& operator= (Akimal&&) = default;

private:

	node_p root = nullptr;	// root of the tree
	size_t size = 0;		// size of the tree
	string path = null;		// path of default file
};

