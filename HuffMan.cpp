#include"HuffMan.h"
#include<fstream>
#include<Windows.h>
#include<string>
#include<iostream>

HuffMan::HuffMan() {
	size = 0;
	list = NULL;
	rootTree = NULL;
	charsList = NULL;
	compressedText = "";
	deCompressedText = "";
}

std::string HuffMan::noRepeatChars(std::string input) {
	std::string uniqueCharacts;
	// Storing the characters of input string in another variable (No repitition)
	for (int i = 0; i < input.length(); i++) {
		bool check = false;
		for (int j = 0; j < uniqueCharacts.length(); j++) {
			if (input[i] == uniqueCharacts[j]) {
				check = true;
				break;
			}
		}
		if (!check)
			uniqueCharacts += input[i];
	}
	return uniqueCharacts;
}

void HuffMan::createPointerArray(std::string input, std::string uniqueCharacts) {
	// creating an pointer array of character nodes
	size = uniqueCharacts.length();
	list = new NodeHuffMan * [size];
	charsList = new NodeList[size];
	NodeHuffMan* newNode;
	for (int i = 0; i < size; i++) {
		newNode = new NodeHuffMan();
		newNode->character = uniqueCharacts[i];
		int count = 0;
		for (int j = 0; j < input.length(); j++) {
			if (uniqueCharacts[i] == input[j])
				count++;
		}
		newNode->frequency = count;
		list[i] = newNode;
		charsList[i].character = newNode->character;
		newNode = nullptr;
	}
	sortPointerArray(0);
}

void HuffMan::sortPointerArray(int start) {
	// Sorting the pointers array in ascending order
	for (int i = start; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (list[i]->frequency > list[j]->frequency) {
				std::swap(list[i], list[j]);
			}
		}
	}
}

void HuffMan::compressString(std::string input) {
	compressedText = "";
	delete rootTree;
	rootTree = nullptr;
	std::string uniqueCharacts = noRepeatChars(input);
	createPointerArray(input, uniqueCharacts);

	// Creating huffman tree
	for (int i = 0; i < size - 1; i++) {
		NodeHuffMan* newNode = new NodeHuffMan();
		newNode->frequency = list[i]->frequency + list[i + 1]->frequency;
		newNode->left = list[i];
		newNode->right = list[i + 1];
		list[i] = list[i + 1] = nullptr;
		list[i + 1] = newNode;
		sortPointerArray(i + 1);
	}
	// Root node of final huffman tree
	rootTree = list[size - 1];
	int index = 0;
	int arr[1000];
	binaryCodes(rootTree, charsList, index, arr);
	for (int i = 0; i < input.length(); i++) {
		int index = -1;
		for (int j = 0; j < size; j++) {
			if (input[i] == charsList[j].character) {
				index = j;
				break;
			}
		}
		compressedText += charsList[index].binaryCode;
	}
	saveToFile(uniqueCharacts);
}

void HuffMan::binaryCodes(NodeHuffMan* root, NodeList*& characterNodes, int index, int arr[]) {
	if (root->left) {
		arr[index] = 0;
		binaryCodes(root->left, characterNodes, index + 1, arr);
	}

	if (root->right) {
		arr[index] = 1;
		binaryCodes(root->right, characterNodes, index + 1, arr);
	}

	if (!(root->left && root->right)) {
		int ind = -1;
		for (int i = 0; i < size; i++) {
			if (root->character == characterNodes[i].character) {
				ind = i;
				break;
			}
		}
		for (int i = 0; i < index; i++) {
			if (arr[i] == 1)
				characterNodes[ind].binaryCode += '1';
			else
				characterNodes[ind].binaryCode += '0';
		}
	}
}

void HuffMan::saveToFile(std::string uniqueCharacts) {
	std::ofstream out;
	out.open("compressedText.txt", std::ofstream::trunc);
	out << compressedText << "\n";
	out.close();
	out.open("uniqueCharsLength.txt", std::ofstream::trunc);
	out << uniqueCharacts.length() << "\n";
	out.close();
	out.open("compressedTree.txt", std::ofstream::trunc);
	for (int i = 0; i < size; i++)
		out << charsList[i].character << " " << charsList[i].binaryCode << "\n";
	out.close();
}

std::string HuffMan::readFromFile() {
	std::ifstream in;
	in.open("compressedText.txt");
	if (in.peek() == std::ifstream::traits_type::eof()) 
		return "";
	in >> compressedText;
	in.close();
	in.open("uniqueCharsLength.txt");
	in >> size;
	in.close();
	in.open("compressedTree.txt");
	charsList = new NodeList[size];
	for (int i = 0; i < size; i++) {
		in >> charsList[i].character;
		if (charsList[i].character == '0' || charsList[i].character == '1') {
			charsList[i].binaryCode = charsList[i].character;
			std::string binarycode;
			in >> binarycode;
			charsList[i].binaryCode += binarycode;
			charsList[i].character = ' ';
			continue;
		}
		in >> charsList[i].binaryCode;
	}
	in.close();
	deCompress();
	return deCompressedText;
}

void HuffMan::deCompress() {
	deCompressedText = "";
	std::string tempStr;
	for (int i = 0; i < compressedText.length(); i++) {
		tempStr += compressedText[i];
		for (int j = 0; j < size; j++) {
			if (tempStr == charsList[j].binaryCode) {
				deCompressedText += charsList[j].character;
				tempStr = "";
				break;
			}
		}
	}
}

void HuffMan::destroyHuffManTree(NodeHuffMan* root) {
	if (root) {
		destroyHuffManTree(root->left);
		destroyHuffManTree(root->right);
		delete root;
		root = nullptr;
	}
}

HuffMan::~HuffMan() {
	destroyHuffManTree(rootTree);
}