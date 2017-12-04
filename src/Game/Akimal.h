#ifndef __AKIMAL__
#define __AKIMAL__

#include <fstream>
#include "GameData.h"
#include "..\..\lib\bst.cpp"

class Akimal
	: private BST<GameData>
{
	using DataNode = TreeNode<GameData>;
	using string_cref = const string&;

	ushort size;
	string path;	// default file path

	void assignWeight (DataNode*);		// assigns positive weights to all nodes, for later saving to file
	void save (ofstream&, DataNode*);

public:
	using BST::Empty;
	using BST::Clear;

	Akimal () : BST<GameData> () {}
	/*explicit*/ Akimal (string_cref);	// loads from file; there's no auto casting
	~Akimal () = default;

	// copy is not permitted
	Akimal (const Akimal&) = delete;
	Akimal& operator=(const Akimal&) = delete;

	// move is default move
	Akimal (Akimal&&) = default;
	Akimal& operator=(Akimal&&) = default;

	//void Game ();

	void save ();					// save to default file
	void save (string_cref);		// save to a different file
	void load (string_cref);		// load tree from file

	ushort AnswerNum ();
	ushort QuestionNum ();
};

#endif // !__AKIMAL__
