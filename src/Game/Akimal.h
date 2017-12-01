#pragma once
#include "..\Game\GameData.h"
#include "..\Tree\bst.cpp"
#include "..\List\list.cpp"
#include <fstream>

class Akimal
	: private BST<GameData> {

private:
	using DataNode = TreeNode<GameData>;
	using DataList = List<GameData>;

	DataList DLRList; //for saving
	ushort wC;				//weight construction variable
	ushort size;			

	Akimal(const DataList&);
	void assignWeight(DataNode*);
	void makeDLRList(DataNode*);
	
public:
	Akimal(string);//loads from file
	//inherited destructor

	void Game();
	
	string toString();
	void saveTo(string);
	void loadFrom(string);

	using BST::Empty;
	using BST::Clear;
	uint AnswerNum();
	uint QuestionNum();

};

