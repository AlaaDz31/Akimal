#ifndef __NODES__
#define __NODES__

#include "basics.h"

GENERIC_TEMP struct UniNode
{
	UniNode* next;
	T elem;

	UniNode ();
	UniNode (T);
	UniNode (T, UniNode*);
};

GENERIC_TEMP struct Node
{
	Node* next, *previous;
	T elem;

	Node ();
	Node (T);
	Node (T, Node*, Node*);
};

GENERIC_TEMP struct TreeNode
{
	TreeNode* right, *left;
	T key;

	TreeNode();
	TreeNode(T);
	TreeNode(T, TreeNode*, TreeNode*);

	bool isLeaf();
	bool isParent();
};


#pragma region UniNode

template<class T>
UniNode<T>::UniNode ()
	: next (nullptr)
{		// default UniNode
}

template<class T>
UniNode<T>::UniNode (T _value)
	: next (nullptr), elem (_value)
{		// isolated UniNode
}

template<class T>
UniNode<T>::UniNode (T _value, UniNode* _next)
	: next (_next), elem (_value)
{		// matched UniNode
}

#pragma endregion

#pragma region Node

template<class T>
Node<T>::Node ()
	: next (nullptr), previous (nullptr)
{		// default node
}

template<class T>
Node<T>::Node (T _value)
	: next (nullptr), previous (nullptr), elem (_value)
{		// isolated node
}

template<class T>
Node<T>::Node (T _value, Node* _prev, Node* _next)
	: next (_next), previous (_prev), elem (_value)
{		// matched node
}

#pragma endregion

#pragma region TreeNode

template<class T>
TreeNode<T>::TreeNode()
	: right(nullptr), left(nullptr)
{		// default node
}

template<class T>
TreeNode<T>::TreeNode(T _key)
	: right(nullptr), left(nullptr), key(_key)
{		// isolated node
}

template<class T>
TreeNode<T>::TreeNode(T _key, TreeNode* _left, TreeNode* _right)
	: right(_right), left(_left), key(_key)
{		// matched node
}

template<class T>
inline bool TreeNode<T>::isLeaf() {
	return right == nullptr && left == nullptr;
}

template<class T>
inline bool TreeNode<T>::isParent() {
	return !isLeaf();
}

#pragma endregion

#endif // !__NODES__
