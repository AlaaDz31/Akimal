#pragma once
#include <fstream>
#include "nodes.h"

#define QUESTION_ID '?'

class Akimall
{
private:
	using str_node = TreeNode<string>;
	using node_p = str_node*;

	node_p root;
	size_t size;
	string path;

	void Dispose(node_p);
	size_t Size(node_p);
	uint getAnswerNum(node_p);

	void Game(node_p);
	void Save(ofstream&, node_p);
	uint Load(ifstream&, node_p);
public:
	Akimall();
	Akimall(string);
	~Akimall();

	bool Empty();
	void Clear();
	size_t Size();
	uint getAnswerNum();
	uint getQuestionNum();

	void Game();
	void Save();
	void Save(string);
	void Load(string);
	void Reload();
};

