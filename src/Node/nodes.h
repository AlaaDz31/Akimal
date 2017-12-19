#pragma once

#include "../Utils/basics.h"

template<class T>
struct UniNode
{
	UniNode* next = nullptr;
	T elem = T();

	UniNode() = default;
	UniNode(const T&);
	UniNode(const T&, UniNode*);
};

template<class T>
struct Node
{
	Node* next = nullptr;
	Node* previous = nullptr;
	T elem = T();

	Node() = default;
	Node(const T&);
	Node(const T&, Node*, Node*);
};

template<class T>
struct TreeNode
{
	TreeNode* right = nullptr;
	TreeNode* left = nullptr;
	T key = T();

	TreeNode() = default;
	TreeNode(const T&);
	TreeNode(const T&, TreeNode*, TreeNode*);

	bool isLeaf();
	bool isParent();
};


#pragma region UniNode

template<class T>
UniNode<T>::UniNode(const T& _value)
	: elem(_value)
{		// isolated UniNode
}

template<class T>
UniNode<T>::UniNode(const T& _value, UniNode* _next)
	: next(_next), elem(_value)
{		// matched UniNode
}

#pragma endregion

#pragma region Node

template<class T>
Node<T>::Node(const T& _value)
	: elem(_value)
{		// isolated node
}

template<class T>
Node<T>::Node(const T& _value, Node* _prev, Node* _next)
	: next(_next), previous(_prev), elem(_value)
{		// matched node
}

#pragma endregion

#pragma region TreeNode

template<class T>
TreeNode<T>::TreeNode(const T& _key)
	: key(_key)
{		// isolated node
}

template<class T>
TreeNode<T>::TreeNode(const T& _key, TreeNode* _left, TreeNode* _right)
	: right(_right), left(_left), key(_key)
{		// matched node
}

template<class T>
inline bool TreeNode<T>::isLeaf()
{
	return right == nullptr && left == nullptr;
}

template<class T>
inline bool TreeNode<T>::isParent()
{
	return !isLeaf();
}

#pragma endregion