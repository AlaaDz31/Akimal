#pragma once

#include <fstream>
#include "../Node/nodes.h"

#define DEFAULT_QUESTION	"Vertebrate"
#define DEFAULT_CORRECT_ANS	"Condor"
#define DEFAULT_WRONG_ANS	"Opabinia"

#define QUESTION_ID '?' // easy-to-change question identifier in file. Allows for quick remaking of file rules

/*
WP = Wroking progress

 * TODO AND DISCUSSION
 *	add possibility to play with a new or empty file
 *	WP - consider to log into kind of 'log.txt'
 *  WP - Options file
 *	avoid using PositiveAnswer and NegativeAnswer in the same check
 *	consider using a file_utils.h
 *	add possibility to ahve withe lines in the middle of akimal.txt file, not oly at beg and end
*/

class Akimal
{
	//Aliases and Private Methods Section
private:

	/// Aliases of std namespace's
	using ifstream = std::ifstream;
	using ofstream = std::ofstream;
	using string = std::string;

	/// Aliases for the game
	using str_node = TreeNode<string>;
	using node_p = TreeNode<string>*;

	/// Recursive methods
	void Dispose(node_p);				// Free memory space of sub-tree
	uint getAnswerNum(node_p) const;	// Retrieves number of answers in sub-tree
	void Game(node_p&);					// Recursive function for main game
	void AddEntry(node_p&);				// Add new Question-Answers group at node
	void Initialize();					// Initialize to default non-empty tree

	void Save(ofstream&, node_p);		// Saves sub-tree to specified std::ofstream
	uint Load(ifstream&, node_p&);		// Loads sub-tree from specified istream. Returns number of lines read, corresponding to current size

	//Public Methods Section
public:

	/// Constructors and memory management
	Akimal() = default;					// C++11 compliant
	Akimal(const Akimal&) = delete;		// Disabled Copy Constructor (only single istance of specified game) - C++11 compliant 
	Akimal(Akimal&&) = default;			// Defaulted Move Constructor - C++11 compliant
	Akimal(string);						// Constructor passing file path
	~Akimal();							// Destructor

	/// Content Data Management
	bool Empty() const;					// Whether the game tree is empty
	void Clear();						// Clears the tree to default state
	size_t Size() const;				// Get Total Number of Nodes
	uint getAnswerNum() const;			// Get Number of Answers (Leaves)
	uint getQuestionNum() const;		// Get Number of Questions (Non-Leaves)

	/// Game Methods
	void Game();						// Main Game Method

	/// File input/output
	void Load(string);					// Load from a specific path
	void Reload();						// Reload info from default path, if it's set
	void Save();						// Save to default path
	void Save(string);					// Save to a specific path

	/// Operators
	Akimal& operator= (const Akimal&) = delete;	// Disabled Copy Assignment Operator - C++11 compliant
	Akimal& operator= (Akimal&&) = default;		// Defaulted Move Assignment Operator - C++11 compliant

	//Private Data Members Section
private:

	string path = null;		// Path of default file
	node_p root = nullptr;	// Root of the tree
	size_t size = 0;		// Size of the tree
};

// Tree dispose function
inline void Akimal::Clear()
{
	if (!Empty())
		Dispose(root);

	root = nullptr; //Reset tree to default state
	size = 0;
}

// Returns true if tree is empty
inline bool Akimal::Empty() const
{
	return root == nullptr;
}

// Returns number of nodes
inline size_t Akimal::Size() const
{
	return size;
}

// Returns number of leafs
inline uint Akimal::getAnswerNum() const
{
	return getAnswerNum(root);
}

// Returns number of non-leaf nodes
inline uint Akimal::getQuestionNum() const
{
	return Size() - getAnswerNum();
}

// Initializes 
inline void Akimal::Initialize()
{
	root = new str_node(DEFAULT_QUESTION);
	root->left = new str_node(DEFAULT_CORRECT_ANS);
	root->right = new str_node(DEFAULT_WRONG_ANS);
	size = 3;
}

inline void Akimal::Game()
{
	if (!Empty())
		Game(root);
}

inline void Akimal::Save()
{
	Save(path);
}

inline void Akimal::Reload()
{
	Load(path);
}