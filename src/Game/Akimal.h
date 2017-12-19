#pragma once

#include "../Node/nodes.h"

#define DEFAULT_QUESTION	"Vertebrate"
#define DEFAULT_CORRECT_ANS	"Condor"
#define DEFAULT_WRONG_ANS	"Opabinia"

#define QUESTION_ID			'?'							// easy-to-change question identifier in file. Allows for quick remaking of file rules

// values based on a 64-bit integer type
#define ANSWER_SIZE_MASK	0x0F'FF'FF'FF				// first 28 bits
#define QUESTION_SIZE_MASK	0xFF'FF'FF'F0'00'00'00		// from 29th to 56th bit
#define BLANK_LINES_MASK	0xFF'00'00'00'00'00'00'00	// MSByte
#define ANSWER_SIZE_UNIT	0x01
#define QUESTION_SIZE_UNIT	0x10'00'00'00
#define BLANK_LINES_UNIT	0x01'00'00'00'00'00'00'00

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
	void Initialize();					// Initialize to default non-empty tree

	void Save(ofstream&, node_p);		// Saves sub-tree to specified std::ofstream
	node_p Load(ifstream&, uint64_t&);	// Loads sub-tree from specified istream. Takes a 64-bit integer to hold some reading information

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

	void setDefaultInitializationKeys(string, string, string);	// Set default question, correct and wrong answer

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

	string def_question = DEFAULT_QUESTION;
	string def_correct_ans = DEFAULT_CORRECT_ANS;
	string def_wrong_ans = DEFAULT_WRONG_ANS;
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

// Set default first question and first correct and wrong answers to that question
inline void Akimal::setDefaultInitializationKeys(string _question, string _correct_ans, string _wrong_ans)
{
	def_question = _question;
	def_correct_ans = _correct_ans;
	def_wrong_ans = _wrong_ans;
}

// Initializes the tree
inline void Akimal::Initialize()
{
	root = new str_node(def_question);
	root->left = new str_node(def_correct_ans);
	root->right = new str_node(def_wrong_ans);
	size = 3;
}

// Begins the game
inline void Akimal::Game()
{
	if (Empty())
		Initialize();

	Game(root);
	std::cout << "Game ended." << std::endl;
}

// Saves the tree
inline void Akimal::Save()
{
	Save(path);
}

// Reaload the tree from the same file
inline void Akimal::Reload()
{
	Load(path);
}