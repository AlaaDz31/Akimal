#pragma once

/*
 *  This library and all other connected non-STL .h and .cpp files
 * are written following the standard ISO C++11 and later versions.
 */

#include <fstream>
#include "../Node/nodes.h"

#define QUESTION_ID '?' // easy-to-change question identifier in file. Allows for quick remaking of file rules

/*
WP = Wroking progress

 * TODO AND DISCUSSION
 *	add possibility to play with a new or empty file
 *	WP - consider to log into kind of 'log.txt'
 *	WP - consider to add localization
 *	verify which is faster: [ getline() ] or [ cin>>, cin.clear(), cin.ignore(streamsize) ]
 *	maybe private only? Or only metadata-oriented?
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
	void Game(node_p);					// Recursive function for main game
	void AddEntry(node_p);				// Add new Question-Answers group at node

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

	void Save();						// Save to default path
	void Save(string);					// Save to a specific path
	void Load(string);					// Load from a specific path
	void Reload();						// Reload info from default path, if it's set

	/// Operators
	Akimal& operator= (const Akimal&) = delete;	// Disabled Copy Assignment Operator - C++11 compliant
	Akimal& operator= (Akimal&&) = default;		// Defaulted Move Assignment Operator - C++11 compliant

	//Private Data Members Section
private:

	node_p root = nullptr;	// Root of the tree
	size_t size = 0;		// Size of the tree
	string path = null;		// Path of default file
};

inline void Akimal::Clear()
{
	if (!Empty())
		Dispose(root);

	root = nullptr; //Reset tree to default state
	size = 0;
}

inline bool Akimal::Empty() const
{
	return root == nullptr;
}

inline size_t Akimal::Size() const
{
	return size;
}

inline uint Akimal::getAnswerNum() const
{
	return getAnswerNum(root);
}

inline uint Akimal::getQuestionNum() const
{
	return Size() - getAnswerNum();
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