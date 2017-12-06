#ifndef __TREE__
#define __TREE__

#include <vector>
#include <functional>
#include "nodes.h"

template<class T>
class BST
{
protected:
	using bst_ref = BST&;							// bst reference
	using bst_cref = const BST&;					// bst const reference
	using type_ref = T&;							// template type T reference
	using type_cref = const T&;						// template type T const reference
	using init_cref = const initializer_list<T>&;	// initializer_list const reference
	using compare_f = function<bool (T, T)>;		// specific function
	using func_cref = const compare_f&;				// function const reference
	using node_p = TreeNode<T>*;					// treenode pointer

	node_p root;
	compare_f comparator;

	void CreateRoot (type_cref);

	void Copy (bst_cref);

	// recursive methods:
	void Insert (type_cref, node_p);
	void Dispose (node_p);
	string toString (node_p);
	uint Size (node_p);
	int getDepth (node_p);
	uint getLeafNum (node_p);
	static void Copy (node_p, node_p&);

	node_p Find (type_cref, node_p);

public:

	BST (func_cref = less<T> ());
	BST (init_cref, func_cref = less<T> ());
	BST (const BST&);
	BST (BST&&);
	~BST ();

	void Insert (type_cref);
	//void Remove (type_cref);

	bool Empty ();
	bool Leaf ();

	void Clear ();

	void setComparator (func_cref);
	func_cref getComparator ();

	uint Size ();
	int getDepth ();
	uint getLeafNum ();

	string toString ();
	type_ref operator[] (type_cref);

	bst_ref operator= (const BST&);
	bst_ref operator= (BST&&);
};

// redefinition of aliases for use outside classes:
template<class T>
using node_p = TreeNode<T>*;

template<class T>
using compare_f = function<bool (T, T)>;

template<class T>
using func_cref = const compare_f<T>&;

template<class T>
using bst_ref = BST<T>&;

template<class T>
using type_ref = T&;

#endif // !__TREE__
