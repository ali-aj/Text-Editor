#include"TrieTree.h"
#include<conio.h>
#include<fstream>
#include<iostream>
#include<Windows.h>

TrieTree::TrieTree() {
	root = new NodeTrieTree();
	root->endWord = false;
	for (int i = 0; i < 26; i++)
		root->children[i] = nullptr;
	tempNode = nullptr;
	suggestedWords = 0;
}

void TrieTree::destroyTrieTree(NodeTrieTree* rootNode) {
	for (int i = 0; i < 26; i++) {
		if (rootNode) {
			destroyTrieTree(rootNode->children[i]);
		}
	}
	delete rootNode;
	rootNode = nullptr;
}

TrieTree::~TrieTree() {
	destroyTrieTree(root);
}

NodeTrieTree* TrieTree::insertInTrieTree(NodeTrieTree* rootNode, char ch, bool endOfWord) {
	int index = ch - 97;
	if (index < 0 || index >= 25)
		return rootNode;
	if (!rootNode->children[index]) {
		NodeTrieTree* newNode;
		newNode = new NodeTrieTree();
		newNode->character = ch;
		newNode->endWord = endOfWord;

		rootNode->children[index] = newNode;
		for (int i = 0; i < 26; i++)
			rootNode->children[index]->children[i] = nullptr;
		return rootNode->children[index];
	}

	if (endOfWord == true)
		rootNode->children[index]->endWord = endOfWord;
	return rootNode->children[index];
}

void TrieTree::readFromFile() {
	std::ifstream in;
	std::string str;
	in.open("outfile.txt");
	while (!in.eof()) {
		tempNode = root;
		in >> str;
		for (int i = 0; i < str.length(); i++) {
			if (i == str.length() - 1)
				tempNode = insertInTrieTree(tempNode, str[i], true);
			else
				tempNode = insertInTrieTree(tempNode, str[i], false);
		}
		tempNode = nullptr;
	}
	in.close();
}

void TrieTree::find(NodeTrieTree* rootNode, std::string* suggestions, std::string input) {
	if (suggestedWords == 50)
		return;
	bool check = false;
	for (int i = 0; (i < 26) && suggestedWords <= 49; i++) {
		if (rootNode->children[i]) {
			rootNode = rootNode->children[i];
			suggestions[suggestedWords] += rootNode->character;
			if (rootNode->endWord == true) {
				suggestedWords++;
				if (suggestedWords == 50)
					break;
				for (int j = 0; j < 26; j++) {
					if (rootNode->children[j]) {
						check = true;
						break;
					}
				}
				if (!check)
					suggestions[suggestedWords] = input;
				else 
					suggestions[suggestedWords] = suggestions[suggestedWords - 1];
			}
			find(rootNode, suggestions, input);
		}
	}
}


void TrieTree::findSuggestions(NodeTrieTree* rootNode, std::string input, std::string* suggestions) {
	if (input.length() == 0) 
		return;
	suggestedWords = 0;
	tempNode = root;
	for (int i = 0; i < input.length(); i++) {
		int index = input[i] - 97;
		if (tempNode->children[index]) 
			tempNode = tempNode->children[index];
		else
			return;
	}
	suggestions[suggestedWords] = input;
	find(tempNode, suggestions, input);
}

void TrieTree::typingText(std::string* suggestions, char key, std::string data) {
	int currSuggestion = -1;
	if (key >= 'a' && key <= 'z') {
		currSuggestion = -1;
		inputData = data;

		int indexSpace = -1;
		for (int i = 0; i < inputData.length(); i++)
			if (inputData[i] == ' ')
				indexSpace = i + 1;

		std::string currentWord = "";
		if (indexSpace != -1)
			for (indexSpace; indexSpace < inputData.length(); indexSpace++)
				currentWord += inputData[indexSpace];
		else
			currentWord = inputData;

		findSuggestions(root, currentWord, suggestions);
	}
	else if (key == ' ' && inputData.length() > 0 && inputData[inputData.length() - 1] != ' ')
		inputData = data;
}

