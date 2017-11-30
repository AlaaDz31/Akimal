#ifndef _TREE_BODY__
#define _TREE_BODY__

#include "bst.h"

template<class T>
BST<T>::BST (compare_f<T> fcomparator)
	: comparator (fcomparator), root (nullptr)
{
}

template<class T>
BST<T>::BST (initializer_list<T> init, compare_f<T> fcomparator)
{
	comparator = fcomparator;

	for (T e in init)
		Insert (e);
}

template<class T>
BST<T>::BST (const BST& tree)
{
	Copy (tree);
}

template<class T>
BST<T>::BST (BST&& tree)
{
	Copy (tree);
	tree.Clear ();
}

template<class T>
BST<T>::~BST ()
{
}

template<class T>
void BST<T>::Copy (TreeNode<T>* from, TreeNode<T>* to)
{
	to = new TreeNode<T> (from->key, from->left, from->right);

	if (from->left != nullptr)
		Copy (from->left, to->left);

	if (from->right != nullptr)
		Copy (from->right, to->right);
}

template<class T>
inline void BST<T>::Copy (const BST& tree)
{
	Clear ();
	setComparator(tree.comparator);
	Copy (tree.root, root);
}

template<class T>
inline void BST<T>::CreateRoot (T key)
{
	root = new TreeNode<T> (key);
}

template<class T>
void BST<T>::Insert (T key, TreeNode<T>* n)
{
	if (comparator (key, n->key))
	{
		if (n->left == nullptr)
			n->left = new TreeNode<T> (key);

		else
			Insert (key, n->left);
	}

	else
	{
		if (n->right == nullptr)
			n->right = new TreeNode<T> (key);

		else
			Insert (key, n->right);
	}
}

template<class T>
inline void BST<T>::Insert (T key)
{
	if (Empty ())
		CreateRoot (key);

	else Insert (key, root);
}

template<class T>
void BST<T>::Dispose (TreeNode<T>* n)
{
	if (!Leaf(n))
	{
		Dispose (n->left); 
		Dispose (n->right);
	}

	delete n;
}

template<class T>
inline void BST<T>::Clear ()
{
	if (!Empty ())
		Dispose (root);

	root = nullptr;
	comparator = less<T> ();
}

template<class T>
string BST<T>::toString (TreeNode<T>* n)
{
	if (n == nullptr)
		return string ();

	return (toString (n->left) + to_string(n->key) + toString (n->right));
}

template<class T>
inline string BST<T>::toString ()
{
	return toString (root);
}

template<class T>
inline bool BST<T>::Empty ()
{
	return root == nullptr;
}

template<class T>
inline bool BST<T>::Leaf (TreeNode<T>* n)
{		// no check if empty

	return n->right == nullptr && n->left == nullptr;
}

template<class T>
inline bool BST<T>::Leaf ()
{
	return !Empty() && Leaf(root);
}

template<class T>
inline compare_f<T> BST<T>::getComparator ()
{
	return comparator;
}

template<class T>
inline void BST<T>::setComparator (compare_f<T> fcomparator)
{
	comparator = fcomparator;
}

template<class T>
uint BST<T>::Size (TreeNode<T>* n)
{
	if (n == nullptr)
		return 0;

	return 1 + Size (n->left) + Size (n->right);
}

template<class T>
inline uint BST<T>::Size ()
{
	return Size (root);
}

template<class T>
int BST<T>::getDepth (TreeNode<T>* n)
{
	if (n == nullptr)
		return -1;

	return max (getDepth (n->left) + 1, getDepth (n->right) + 1);
}

template<class T>
inline int BST<T>::getDepth ()
{
	return getDepth (root);
}

template<class T>
int BST<T>::getLeafNum (TreeNode<T>* n)
{
	if (n == nullptr)
		return 0;

	if (Leaf (n))
		return 1;

	return getLeafNum (n->left) + getLeafNum (n->right);
}

template<class T>
inline int BST<T>::getLeafNum ()
{
	return getLeafNum (root);
}

template<class T>
TreeNode<T>* BST<T>::Find (T key, TreeNode<T>* n)
{
	if (n == nullptr || n->key == key)
		return n;

	if (comparator (key, n->key))
		return Find (key, n->left);

	return Find (key, n->right);
}

template<class T>
inline T& BST<T>::operator[](T key)
{
	TreeNode<T>* tmp = Find (key, root);

	if (tmp == nullptr)
		throw valuenotfound_exception;

	return tmp->key;
}

template<class T>
inline BST<T> BST<T>::operator= (const BST& tree)
{
	Copy (tree);
	return tree;
}

template<class T>
inline BST<T> BST<T>::operator= (BST&& tree)
{
	Copy (move (tree));
	return local;
}

#endif // !_TREE_BODY__
