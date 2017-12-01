#ifndef __LIST_BODY__
#define __LIST_BODY__

#include "list.h"

template<class T>
inline List<T>::List ()
	: first (nullptr), last (nullptr)
{		// empty list
}

template<class T>
inline List<T>::List (int _size, T _key)
{		// create a list of _size elements with value _key

	MultipleAllocation (_size, _key);
}

template<class T>
List<T>::List (initializer_list<T> _init)
{		// initialization with initailizer_list

	T* current = (int*) _init.begin ();		// cast from const int* to int*

	while (current != _init.end ())
	{
		PushBack (*current);
		current++;
	}
}

template<class T>
List<T>::List (const List<T>& _list)
{
	first = last = nullptr;
	Copy (_list);
}

template<class T>
List<T>::List (List<T>&& _list)
{
	first = nullptr;
	Copy (_list);
	_list.Clear ();
}

template<class T>
List<T>::~List ()
{
	Clear ();	// delete allocated memory
}

template<class T>
inline Node<T>* List<T>::Begin ()
{
	return first;
}

template<class T>
inline Node<T>* List<T>::Last ()
{
	return last;
}

template<class T>
Node<T>* List<T>::NodeAt (int _index)
{		// returns pointer to node in position _index

	if (Empty ()) throw emptylist_exception;

	else if (_index < 0 || _index >= size) throw outofrange_exception;

	// node is in the first half
	else if (_index < size / 2)
	{
		int i = 0;
		Node<T>* current = first;

		while (i < _index)
		{
			if (current == nullptr) throw unexcepted_exception;

			current = current->next;
			i++;
		}
		return current;
	}

	// node is in the second half
	else
	{
		int i = size - 1;
		Node<T>* current = last;

		while (i > _index)
		{
			if (current == nullptr) throw unexcepted_exception;

			current = current->previous;
			i--;
		}
		return current;
	}
}

template<class T>
void List<T>::MultipleAllocation (int _size, T _key)
{		// list of more objects with same value

	for (int i = 0; i < _size; i++)
		PushBack (_key);
}

template<class T>
void List<T>::CreateParent (T _key)
{		// used to create first node

	first = new Node<T> (_key);
	last = first;
	size = 1;
}

template<class T>
void List<T>::PushBack (T _key)
{
	if (!Empty ())
	{
		last->next = new Node<T> (_key, last, nullptr);
		last = last->next;
		size++;
	}

	else CreateParent (_key);
}

template<class T>
void List<T>::PushFront (T _key)
{
	if (!Empty ())
	{
		first->previous = new Node<T> (_key, nullptr, first);
		first = first->previous;
		size++;
	}

	else CreateParent (_key);
}

template<class T>
void List<T>::Insert (int _where, T _key)
{		// inserts an alement at _where index, scaling the others

	if (_where < 0 || _where >= size) throw outofrange_exception;

	else if (Empty ()) CreateParent (_key);

	else if (_where == 0) PushFront (_key);

	else
	{
		Node<T>* tmp = NodeAt (_where);

		tmp->previous->next = new Node<T> (_key, tmp->previous, tmp);
		tmp->previous = tmp->previous->next;

		size++;
	}
}

template<class T>
void List<T>::Copy (const List& _l)
{
	Clear ();

	Node<T>* current = _l.first;

	while (current != nullptr)
	{
		PushBack (current->elem);
		current = current->next;
	}
}

template<class T>
void List<T>::Reverse ()
{
	Node<T>* current = first;

	while (current != nullptr)
	{
		swap (current->previous, current->next);
		current = current->previous;
	}
	swap (first, last);
}

template<class T>
T List<T>::PopBack ()
{
	if (Empty ()) throw emptylist_exception;

	T tmp = Back ();

	if (Single ())
		Clear ();

	else
	{
		last = last->previous;
		delete last->next;
		last->next = nullptr;
		size--;
	}

	return tmp;
}

template<class T>
T List<T>::PopFront ()
{
	if (Empty ()) throw emptylist_exception;

	T tmp = Front ();

	if (Single ())
		Clear ();

	else
	{
		first = first->next;
		delete first->previous;
		first->previous = nullptr;
		size--;
	}

	return tmp;
}

template<class T>
inline T List<T>::Front ()
{
	if (Empty ()) throw emptylist_exception;

	return first->elem;
}

template<class T>
inline T List<T>::Back ()
{
	if (Empty ()) throw emptylist_exception;

	return last->elem;
}

template<class T>
void List<T>::Erase (int _index)
{		// erases the node at _index position

	Node<T>* tmp = NodeAt (_index);		// thorws exceptions itself

	if (size == 1)
	{
		Clear ();	// delete the only one node
		return;
	}

	if (tmp == first)
		PopFront ();

	else if (tmp == last)
		PopBack ();

	else
	{
		tmp->previous->next = tmp->next;
		tmp->next->previous = tmp->previous;
		size--;
		delete tmp;
	}
}

template<class T>
void List<T>::Erase (Node<T>*& _toerase)
{		// assigns the next pointer

	if (_toerase == nullptr) throw unexcepted_exception;

	if (size == 1)
	{
		Clear ();
		_toerase = nullptr;
	}

	else if (_toerase == first)
	{
		PopFront ();
		_toerase = first;		// assign new first
	}

	else if (_toerase == last)
	{
		PopBack ();
		_toerase = nullptr;		// assign following value, so none
	}

	else
	{
		_toerase->previous->next = _toerase->next;
		_toerase->next->previous = _toerase->previous;

		Node<T>* tmp = _toerase->next;
		delete _toerase;
		size--;

		_toerase = tmp;
	}
}

template<class T>
void List<T>::Remove (T _key)
{		// erases all nodes with specified value

	Node<T>* tmp = first;

	while (tmp != nullptr)
	{
		if (tmp->elem == _key) Erase (tmp);

		else tmp = tmp->next;
	}
}

template<class T>
void List<T>::Clear ()
{		// erases all nodes in the list

	if (!Empty ())
	{
		while (!Single ())
		{
			first = first->next;
			delete first->previous;
		}

		delete last;
		first = last = nullptr;
		size = 0;
	}
}

template<class T>
inline int List<T>::Size ()
{
	return size;
}

template<class T>
inline bool List<T>::Empty ()
{
	return first == nullptr;
}

template<class T>
inline bool List<T>::Single ()
{
	return first == last && !Empty ();
}

template<class T>
int List<T>::Find (T _key)
{
	Node<T>* current = first;
	int i = 0;

	while (current != nullptr)
	{
		if (current->elem == _key)
			return i;

		current = current->next;
		i++;
	}

	return -1;
}

template<class T>
int List<T>::Find (initializer_list<T> _list)
{
	Node<T>* current = first;
	T* it = (int*) _list.begin ();
	int i = 0;

	while (current != nullptr)
	{
		if (current->elem == *it)
		{
			if (it == _list.end () - 1)
				return i - (it - _list.begin ());
			it++;
		}

		else if (it != _list.begin ())
			it = (int*) _list.begin ();

		current = current->next;
		i++;
	}

	return -1;
}

template<class T>
int List<T>::Find (T* _arr, int _count)
{
	Node<T>* current = first;
	int i = 0, it = 0;

	while (current != nullptr)
	{
		if (current->elem == _arr[it])
		{
			if (it == _count - 1)
				return i - it;
			it++;
		}

		else if (it != 0)
			it = 0;

		current = current->next;
		i++;
	}

	return -1;
}

template<class T>
int List<T>::rFind (T _key)
{
	Node<T>* current = last;
	int i = size - 1;

	while (current != nullptr)
	{
		if (current->elem == _key)
			return i;

		current = current->previous;
		i--;
	}

	return -1;
}

template<class T>
int List<T>::rFind (initializer_list<T> _list)
{
	Node<T>* current = last;
	T* it = (int*) _list.end () - 1;
	int i = size - 1;

	while (current != nullptr)
	{
		if (current->elem == *it)
		{
			if (it == _list.begin ())
				return i;
			it--;
		}

		else if (it != _list.end () - 1)
			it = (int*) _list.end () - 1;

		current = current->previous;
		i--;
	}

	return -1;
}

template<class T>
int List<T>::rFind (T* _arr, int _count)
{
	Node<T>* current = last;
	int i = size - 1, it = _count - 1;

	while (current != nullptr)
	{
		if (current->elem == _arr[it])
		{
			if (it == 0)
				return i;
			it--;
		}

		else if (it != _count - 1)
			it = _count - 1;

		current = current->previous;
		i--;
	}

	return -1;
}

template<class T>
int List<T>::FindFirstOf (initializer_list<T> _list)
{
	T* it = (int*) _list.begin ();
	int i = -1, tmp;

	while (it != _list.end ())
	{
		tmp = Find (*it);
		if (tmp != -1 && (tmp < i || i == -1))
			i = tmp;

		it++;
	}

	return i;
}

template<class T>
int List<T>::FindFirstOf (T* _arr, int _count)
{
	int i = -1, tmp, it = 0;

	while (it < _count)
	{
		tmp = Find (_arr[it]);
		if (tmp != -1 && (tmp < i || i == -1))
			i = tmp;

		it++;
	}

	return i;
}

template<class T>
int List<T>::FindLastOf (initializer_list<T> _list)
{
	T* it = (int*) _list.begin ();
	int i = -1, tmp;

	while (it != _list.end ())
	{
		tmp = rFind (*it);
		if (tmp != -1 && tmp > i)
			i = tmp;

		it++;
	}

	return i;
}

template<class T>
int List<T>::FindLastOf (T* _arr, int _count)
{
	int i = -1, tmp, it = 0;

	while (it < _count)
	{
		tmp = rFind (_arr[it]);
		if (tmp != -1 && tmp > i)
			i = tmp;

		it++;
	}

	return i;
}

template<class T>
inline T& List<T>::operator[](int _index)
{
	return NodeAt (_index)->elem;
}

template<class T>
List<T> List<T>::operator+(const List& _right)
{		// chain local and _right in local

	List<T> tmp = local;
	Node<T>* current = _right.first;

	while (current != nullptr)
	{
		tmp.PushBack (current->elem);
		current = current->next;
	}

	return tmp;
}

template<class T>
List<T> List<T>::operator-(const List& _right)
{
	List<T> tmp = local;
	Node<T>* current = _right.first;

	while (current != nullptr && !Empty ())
	{
		tmp.Remove (current->elem);
		current = current->next;
	}

	return tmp;
}

template<class T>
void List<T>::operator+=(const List& _right)
{		// chain local and _right in local

	Node<T>* current = _right.first;

	while (current != nullptr)
	{
		PushBack (current->elem);
		current = current->next;
	}
}

template<class T>
void List<T>::operator-=(const List& _right)
{
	Node<T>* current = _right.first;

	while (current != nullptr)
	{
		Remove (current->elem);
		current = current->next;
	}
}

template<class T>
bool List<T>::operator==(const List& _right)
{		// true if lists have the same elements in the same order

	if (size != _right.size) return false;

	Node<T>* i1 = first;
	Node<T>* i2 = _right.first;

	while (i1 != nullptr)
	{
		if (i1->elem != i2->elem) return false;
		i1 = i1->next;
		i2 = i2->next;
	}

	return true;
}

template<class T>
inline bool List<T>::operator!=(const List& _right)
{
	return !operator== (_right);
}

template<class T>
List<T> List<T>::operator=(const List& _right)
{
	Copy (_right);
	return local;
}

template<class T>
List<T> List<T>::operator=(List&& _right)
{
	Copy (move(right));
	return local;
}
#endif // !__LIST_BODY__
