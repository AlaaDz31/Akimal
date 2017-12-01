#ifndef __LIST__
#define __LIST__

#include "nodes.h"

GENERIC_TEMP class List
{
protected:

	Node<T>* first;
	Node<T>* last;
	int size;

	void MultipleAllocation (int, T);
	void CreateParent (T);

	void Erase (Node<T>*&);

	Node<T>* NodeAt (int);

	void Copy (const List&);

public:

	List ();
	List (int, T);
	List (initializer_list<T>);
	List (const List&);
	List (List&&);
	~List ();

	Node<T>* Begin ();
	Node<T>* Last ();

	void PushBack (T);
	void PushFront (T);
	void Insert (int, T);

	T PopBack ();
	T PopFront ();

	T Front ();
	T Back ();

	void Remove (T);
	void Clear ();
	void Erase (int);

	int Size ();

	bool Empty ();
	bool Single ();

	void Reverse ();

	// search for a complete equality from left
	int Find (T);
	int Find (initializer_list<T>);
	int Find (T*, int);

	// serach for a complete equality from right
	int rFind (T);
	int rFind (initializer_list<T>);
	int rFind (T*, int);

	// serch for first occurrence from left
	int FindFirstOf (initializer_list<T>);
	int FindFirstOf (T*, int);

	// search for first occurrence from right
	int FindLastOf (initializer_list<T>);
	int FindLastOf (T*, int);

	T& operator[](int);

	List operator+(const List&);
	List operator-(const List&);
	void operator+=(const List&);
	void operator-=(const List&);

	bool operator==(const List&);
	bool operator!=(const List&);

	List operator=(const List&);
	List operator=(List&&);
};

#endif // !__LIST__