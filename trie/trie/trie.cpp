#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct trieNode {
	//int data;
	trieNode *children[26];
	bool isLeaf;
};
//returns new trie node
trieNode* getNode() {
	trieNode *pNode = NULL;
	pNode = (trieNode*)malloc(sizeof(trieNode));
	if (pNode) {
		int i;
		pNode->isLeaf = false;
		for (i = 0; i < 26; i++) {
			pNode->children[i] = NULL;
		}
	}
	return pNode;
}
//if not inserted, inserts key into trie, if the key is the prefix of 
//the node, marks the node as leaf

void insert(trieNode *root, char* key) {
	int level;
	int length = strlen(key);
	int index;
	trieNode *p = root;
	for (level = 0; level < length; level++) {
		index = (int)key[level] - (int)'a';      //converts key current character into index
		if (!p->children[index]) {
			p->children[index] = getNode();
		}
		p = p->children[index];
	}
	p->isLeaf = true;
	//p->data = value;
}
//returns true if key is present in trie

bool search(trieNode *root, char *key) {
	int level;
	int length = strlen(key);
	int index;
	trieNode *p = root;
	for (level = 0; level < length; level++) {
		index = (int)key[level] - (int)'a';
		if (!p->children[index]) {
			return false;
		}
		p = p->children[index];
	}
	return (p != NULL && p->isLeaf);
}

char* append(char *pre, char part) {
	char *string =(char*)malloc(sizeof(char)*(strlen(pre) + 2));
	int i = 0;
	while (pre[i] != '\0') {
		string[i] = pre[i++];
	}
	string[i++] = part;
	string[i] = '\0';
	return string;
}

void printKey(trieNode *root, char *pre) {
	if (root == NULL) {
		return;
	}
	if (root->isLeaf) {
		printf("%s\n", pre);
	}
	for (int i = 0; i < 26; i++) {
		if (root->children[i] != NULL) {
			printKey(root->children[i], append(pre, i + 97));
		}
	}
}

void autocomplete(trieNode *root, char *pre) {
	int len = strlen(pre);
	for (int i = 0; i < len; i++) {
		root = root->children[pre[i] % 97];
	}
	printKey(root, pre);
}

int main() {
	char keys[][8] = { "the","and","there","answer","any","by","bye","their" };
	char output[][32] = { "Not present in trie","Present in trie" };
	trieNode *root = getNode();
	for (int i = 0; i < 8; i++) {
		insert(root, keys[i]);
	}
	printf("%s --- %s\n", "the", output[search(root, "the")]);
	printf("%s --- %s\n", "these", output[search(root, "these")]);
	printf("%s --- %s\n", "their", output[search(root, "their")]);
	printf("%s --- %s\n", "thaw", output[search(root, "thaw")]);

	char input[100];
	printf("Prefix to be searched: ");
	scanf("%s", input);
	autocomplete(root, input);

	getchar();
	getchar();
	return 0;
}