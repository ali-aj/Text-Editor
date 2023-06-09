#pragma once
#include<iostream>
#include"HuffMan.h"
#include<Windows.h>

#define ESCAPE 27

struct NodeTrieTree {
	char character;
	bool endWord;
	NodeTrieTree* children[26];
};

class TrieTree {
private:
	NodeTrieTree* root;
	NodeTrieTree* tempNode;
	int suggestedWords;
	HuffMan objHuffMan;
	std::string inputData;
public:
	TrieTree();
	void destroyTrieTree(NodeTrieTree* rootNode);
	~TrieTree();

	NodeTrieTree* insertInTrieTree(NodeTrieTree* rootNode, char ch, bool endOfWord);

	void readFromFile();
	void typingText(std::string* suggestions, char key, std::string data);

	void findSuggestions(NodeTrieTree* rootNode, std::string input, std::string* suggestions);
	void find(NodeTrieTree* rootNode, std::string* suggestions, std::string input);
};