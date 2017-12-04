#ifndef __TREE__
#define __TREE__
#include <vector>
#include <functional>
#include "nodes.h"

template<class T>
using compare_f = function<bool (T, T)>;

template<class T>
class BST
{
protected:
	using type_cref = const T&;
	using init_cref = const initializer_list<T>&;
	using compare_f = compare_f<T>;
	using func_cref = const BST::compare_f&;

	TreeNode<T>* root;
	compare_f<T> comparator;
	
	void CreateRoot (type_cref);

	void Copy (const BST&);

	// recursive methods:
	void Insert (type_cref, TreeNode<T>*);
	void Dispose (TreeNode<T>*);
	string toString (TreeNode<T>*);
	uint Size (TreeNode<T>*);
	int getDepth (TreeNode<T>*);
	uint getLeafNum (TreeNode<T>*);
	static void Copy (TreeNode<T>*, TreeNode<T>*&);

	TreeNode<T>* Find (type_cref, TreeNode<T>*);

public:

	BST (func_cref = less<T> ());
	BST (init_cref, func_cref = less<T>());
	BST (const BST&);
	BST (BST&&);
	~BST ();

	void Insert (type_cref);
	//void Remove (type_cref);

	bool Empty ();
	bool Leaf ();

	void Clear ();

	void setComparator (func_cref);
	compare_f getComparator ();

	uint Size ();
	int getDepth ();
	uint getLeafNum ();

	string toString ();
	T& operator[] (type_cref);

	BST& operator= (const BST&);
	BST& operator= (BST&&);
};

#endif // !__TREE__
