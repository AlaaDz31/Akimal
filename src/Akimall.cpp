#include "Akimall.h"



Akimall::Akimall()
	: root(nullptr), size(0), path(null)
{
}

Akimall::Akimall(string _path)
	: root(nullptr), size(0) // path changed in Load()
{
	Load(_path);
}

Akimall::~Akimall()
{
	Clear();
}

void Akimall::Dispose(node_p n)
{
	if (n != nullptr)
	{
		Dispose(n->left);
		Dispose(n->right);
		delete n;
	}
}

inline void Akimall::Clear()
{
	if (!Empty())
		Dispose(root);

	root = nullptr;
}

inline bool Akimall::Empty()
{
	return root == nullptr;
}

size_t Akimall::Size(node_p n)
{
	if (n == nullptr)
		return 0;

	return 1 + Size(n->left) + Size(n->right);
}

inline size_t Akimall::Size()
{
	return Size(root);
}

uint Akimall::getAnswerNum(node_p n)
{
	if (n == nullptr)
		return 0;

	if (n->isLeaf())
		return 1;

	return getAnswerNum(n->left) + getAnswerNum(n->right);
}

void Akimall::Save(ofstream & file, node_p node)
{
	if (node->isParent()) {
		file << QUESTION_ID << node << '\n';
		Save(file, node->left);
		Save(file, node->right);
	}
	else {
		file << node << '\n';
	}
}

inline uint Akimall::getAnswerNum()
{
	return getAnswerNum(root);
}

inline uint Akimall::getQuestionNum() {
	return Size() - getAnswerNum();
}