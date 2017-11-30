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
void BST<T>::Copy (Node<T>* from, Node<T>* to)
{
	to = new Node<T> (from->elem, from->previous, from->next);

	if (from->previous != nullptr)
		Copy (from->previous, to->previous);

	if (from->next != nullptr)
		Copy (from->next, to->next);
}

template<class T>
inline void BST<T>::Copy (const BST& tree)
{
	Clear ();
	Copy (tree.root, root);
}

template<class T>
inline void BST<T>::CreateRoot (T key)
{
	root = new Node<T> (key);
}

template<class T>
void BST<T>::Insert (T key, Node<T>* n)
{
	if (comparator (key, n->elem))
	{
		if (n->previous == nullptr)
			n->previous = new Node<T> (key);

		else
			Insert (key, n->previous);
	}

	else
	{
		if (n->next == nullptr)
			n->next = new Node<T> (key);

		else
			Insert (key, n->next);
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
void BST<T>::Dispose (Node<T>* n)
{
	if (!Leaf(n))
	{
		Dispose (n->previous); 
		Dispose (n->next);
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
string BST<T>::toString (Node<T>* n)
{
	if (n == nullptr)
		return string ();

	return (toString (n->previous) + to_string(n->elem) + toString (n->next));
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
inline bool BST<T>::Leaf (Node<T>* n)
{		// no check if empty

	return n->next == nullptr && n->previous == nullptr;
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
uint BST<T>::Size (Node<T>* n)
{
	if (n == nullptr)
		return 0;

	return 1 + Size (n->previous) + Size (n->next);
}

template<class T>
inline uint BST<T>::Size ()
{
	return Size (root);
}

template<class T>
int BST<T>::getDepth (Node<T>* n)
{
	if (n == nullptr)
		return -1;

	return max (getDepth (n->previous) + 1, getDepth (n->next) + 1);
}

template<class T>
inline int BST<T>::getDepth ()
{
	return getDepth (root);
}

template<class T>
int BST<T>::getLeafNum (Node<T>* n)
{
	if (n == nullptr)
		return 0;

	if (Leaf (n))
		return 1;

	return getLeafNum (n->previous) + getLeafNum (n->next);
}

template<class T>
inline int BST<T>::getLeafNum ()
{
	return getLeafNum (root);
}

template<class T>
Node<T>* BST<T>::Find (T key, Node<T>* n)
{
	if (n == nullptr || n->elem == key)
		return n;

	if (comparator (key, n->elem))
		return Find (key, n->previous);

	return Find (key, n->next);
}

template<class T>
inline T& BST<T>::operator[](T key)
{
	Node<T>* tmp = Find (key, root);

	if (tmp == nullptr)
		throw valuenotfound_exception;

	return tmp->elem;
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
