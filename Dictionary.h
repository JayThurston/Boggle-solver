#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define alphabet 26


struct Node {
	struct Node* children[alphabet]={NULL};
	bool flag[alphabet]={false};
	int value;
};

class Dictionary
{
public:
	Dictionary();
	Dictionary(string FILE);
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	int wordCount();

private:
	Node* root;
	int numWords;
};


#endif /* DICTIONARY_H_ */
