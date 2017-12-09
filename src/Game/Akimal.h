#pragma once
#include <fstream>
#include "../Node/nodes.h"

#define QUESTION_ID '?' //easy-to-change question identifier in file. Allows for quick remaking of file rules

/*
 * TODO AND DISCUSSION
 * maybe Size() methods aren not needed.
 * maybe private only? Or only metadata-oriented?
*/

class Akimal
{
	//Aliases and methods Section
private:
	/// aliases
	using str_node = TreeNode<string>;
	using node_p = TreeNode<string>*;

	/// recursive methods:
	void Dispose(node_p);				// Free memory space of sub-tree
	size_t Size(node_p) const;			// Retrieves size of sub-tree
	uint getAnswerNum(node_p) const;	// Retrieves number of answers in sub-tree
	void Game(node_p);					// Recursive function for main game
	void AddEntry(node_p);				// Add new Question-Answers group at node

	void Save(ofstream&, node_p);		// Saves sub-tree to specified ofstream
	uint Load(ifstream&, node_p&);		// Loads sub-tree from specified istream. Returns number of lines read, corresponding to current size

	//Public Methods Section
public:

	/// Constructors and memory management
	Akimal () = default;				// C++11 compliant
	Akimal (const Akimal&) = delete;	// Disable Copy Constructor (only single istance of specified game) C++11 compliant 
	Akimal (Akimal&&) = default;		// C++11 compliant
	Akimal (string);
	~Akimal();

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
	Akimal& operator= (const Akimal&) = delete;	// Disabled copy operator C++11 compliant
	Akimal& operator= (Akimal&&) = default;		// C++11 compliant

	//Private Members Section
private:

	node_p root = nullptr;	// Root of the tree
	size_t size = 0;		// Size of the tree
	string path = null;		// Path of default file
};
