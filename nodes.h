#ifndef __NODES__
#define __NODES__

#include "basics.h"

GENERIC_TEMP struct UniNode
{
	UniNode* next;
	T elem;

	UniNode ();
	UniNode (T);
	UniNode (T, UniNode*);
};

GENERIC_TEMP struct Node
{
	Node* next, *previous;
	T elem;

	Node ();
	Node (T);
	Node (T, Node*, Node*);
};

#pragma region UniNode

template<class T>
UniNode<T>::UniNode ()
	: next (nullptr)
{		// default UniNode
}

template<class T>
UniNode<T>::UniNode (T _value)
	: next (nullptr), elem (_value)
{		// isolated UniNode
}

template<class T>
UniNode<T>::UniNode (T _value, UniNode* _next)
	: next (_next), elem (_value)
{		// matched UniNode
}

#pragma endregion

#pragma region Node

template<class T>
Node<T>::Node ()
	: next (nullptr), previous (nullptr)
{		// default node
}

template<class T>
Node<T>::Node (T _value)
	: next (nullptr), previous (nullptr), elem (_value)
{		// isolated node
}

template<class T>
Node<T>::Node (T _value, Node* _prev, Node* _next)
	: next (_next), previous (_prev), elem (_value)
{		// matched node
}

#pragma endregion

#endif // !__NODES__
