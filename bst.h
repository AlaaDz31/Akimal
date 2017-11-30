#ifndef __TREE__
#define __TREE__

#include <vector>
#include <functional>
#include "nodes.h"

/*Copy does not work*/

GENERIC_TEMP using compare_f = function<bool (T, T)>;

template<class T>
class BST
{
protected:

	Node<T>* root;
	compare_f<T> comparator;
	
	void CreateRoot (T);

	static void Copy (Node<T>*, Node<T>*);
	void Copy (const BST&);

	void Insert (T, Node<T>*);
	void Dispose (Node<T>*);
	string toString (Node<T>*);
	uint Size (Node<T>*);
	int getDepth (Node<T>*);
	int getLeafNum (Node<T>*);

	static bool Leaf (Node<T>*);

	Node<T>* Find (T, Node<T>*);

public:

	BST (compare_f<T> = less<T> ());
	BST (initializer_list<T>, compare_f<T> = less<T> ());
	BST (const BST&);
	BST (BST&&);
	~BST ();

	void Insert (T);
	//void Remove (T);

	bool Empty ();
	bool Leaf ();

	void Clear ();

	void setComparator (compare_f<T> = less<T> ());
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