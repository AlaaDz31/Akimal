#ifndef _TREE_BODY__
#define _TREE_BODY__

/*
Remove: 
for each Node:
	/// BEGIN RECURSION
	if (me->key > _to_delete && !me->isLeaf()) then /// GO LEFT
		• Node* tmp = thisfoo(me->left)
		• if (tmp != nullptr)
			• del me->left
			• me->left = tmp->left
	else if (me->key <= to_delete && !me->isLeaf()) then
		• Node* tmp = thisfoo(me->right)
		• if (tmp != nullptr)
			• del me->right
			• me->right = tmp->right
	else /// THIS IS TO DELETE
	/// NEED TO UNIFY LEFT AND RIGHT FOR PARENT
		• if (left == nullptr) then
		• else
			• RECURSION: me->left.setToLeafestRight(me->right) as right
		• ret &me
	ret nullptr	/// WILL BE DISCARDED
*/

#include "bst.h"

template<class T>
BST<T>::BST (func_cref fcomparator)
	: comparator (fcomparator), root (nullptr)
{
}

template<class T>
BST<T>::BST (init_cref init, func_cref fcomparator)
{
	setComparator (fcomparator);

	for (T e in init)
		Insert (e);
}

template<class T>
BST<T>::BST (const BST& tree)
{
	root = nullptr;
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
	Clear ();
}

template<class T>
void BST<T>::Copy (node_p from, node_p& to)
{
	to = new TreeNode<T> (from->key, from->left, from->right);

	if (from->left != nullptr)
		Copy (from->left, to->left);

	if (from->right != nullptr)
		Copy (from->right, to->right);
}

template<class T>
inline void BST<T>::Copy (bst_cref tree)
{
	Clear ();
	setComparator (tree.comparator);
	Copy (tree.root, root);
}

template<class T>
inline void BST<T>::CreateRoot (type_cref key)
{
	root = new TreeNode<T> (key);
}

template<class T>
void BST<T>::Insert (type_cref key, node_p n)
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
inline void BST<T>::Insert (type_cref key)
{
	if (Empty ())
		CreateRoot (key);

	else Insert (key, root);
}

template<class T>
void BST<T>::Dispose (node_p n)
{
	if (n != nullptr)
	{
		Dispose (n->left);
		Dispose (n->right);
		delete n;
	}
}

template<class T>
inline void BST<T>::Clear ()
{
	if (!Empty ())
		Dispose (root);

	root = nullptr;
}

template<class T>
string BST<T>::toString (node_p n)
{
	if (n == nullptr)
		return null;

	return (toString (n->left) + to_string (n->key) + '\t' + toString (n->right));
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
inline bool BST<T>::Leaf ()
{
	return !Empty () && root->isLeaf ();
}

template<class T>
inline func_cref<T> BST<T>::getComparator ()
{
	return comparator;
}

template<class T>
inline void BST<T>::setComparator (func_cref fcomparator)
{
	comparator = fcomparator;
}

template<class T>
uint BST<T>::Size (node_p n)
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
int BST<T>::getDepth (node_p n)
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
uint BST<T>::getLeafNum (node_p n)
{
	if (n == nullptr)
		return 0;

	if (n->isLeaf())
		return 1;

	return getLeafNum (n->left) + getLeafNum (n->right);
}

template<class T>
inline uint BST<T>::getLeafNum ()
{
	return getLeafNum (root);
}

template<class T>
node_p<T> BST<T>::Find (type_cref key, node_p n)
{
	if (n == nullptr || n->key == key)
		return n;

	if (comparator (key, n->key))
		return Find (key, n->left);

	return Find (key, n->right);
}

template<class T>
type_ref<T> BST<T>::operator[](type_cref key)
{
	node_p tmp = Find (key, root);

	if (tmp == nullptr)
		throw keynotfound_exception;

	return tmp->key;
}

template<class T>
inline bst_ref<T> BST<T>::operator= (const BST& tree)
{
	Copy (tree);
	return tree;
}

template<class T>
inline bst_ref<T> BST<T>::operator= (BST&& tree)
{
	Copy (move (tree));
	return local;
}

#endif // !_TREE_BODY__
