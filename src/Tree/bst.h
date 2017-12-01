#ifndef __TREE__
#define __TREE__
#include <vector>
#include <functional>
#include "..\Node\nodes.h"

GENERIC_TEMP using compare_f = function<bool (T, T)>;

template<class T>
class BST
{
protected:

	TreeNode<T>* root;
	compare_f<T> comparator;
	
	void CreateRoot (T);

	static void Copy (TreeNode<T>*, TreeNode<T>*&);
	void Copy (const BST&);

	void Insert (T, TreeNode<T>*);
	void Dispose (TreeNode<T>*);
	string toString (TreeNode<T>*);
	uint Size (TreeNode<T>*);
	int getDepth (TreeNode<T>*);
	int getLeafNum (TreeNode<T>*);

	TreeNode<T>* Find (T, TreeNode<T>*);

public:

	BST (compare_f<T> = less<T> ());
	BST (initializer_list<T>, compare_f<T> = less<T>());
	BST (const BST&);
	BST (BST&&);
	~BST ();

	void Insert (T);
	//void Remove (T);

	bool Empty ();
	bool Leaf ();

	void Clear ();

	void setComparator (const compare_f<T>&);
	compare_f<T> getComparator ();

	uint Size ();
	int getDepth ();
	int getLeafNum ();

	string toString ();
	T& operator[] (T);

	BST operator= (const BST&);
	BST operator= (BST&&);
};

#endif // !__TREE__
