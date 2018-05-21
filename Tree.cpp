#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tree.h"
#include "Strings.h"
#include "secEnter.h"

void addNode(treeNode*& node, char* data, bool leaf) {
	bool flagRoot = false;
	treeNode** tmp;
	if (node == nullptr) {
		tmp = &node;
		flagRoot = true;
	}
	else {	
		if (!leaf) tmp = &node->leftLeaf;
		else tmp = &node->rightLeaf;
		if (*tmp != nullptr) return;
	}

	*tmp = (treeNode*)malloc(sizeof(treeNode));
	
	(*tmp)->data = (char*)calloc(buffSizeStr1024,  sizeof(char));
	strcpy((*tmp)->data, data);

	if (flagRoot) {
		node->key = (char*)calloc(buffSizeStr1024, sizeof(char));
		*node->key = '*';
	}
	else {
		(*tmp)->key = (char*)calloc(buffSizeStr1024, sizeof(char));
		if (*node->key != '*') {
			strcpy((*tmp)->key, node->key);
			*((*tmp)->key + my_strlen((*tmp)->key)) = leaf + '0';
		}
		else {
			*((*tmp)->key) = leaf + '0';
		}
	}

	(*tmp)->leftLeaf = nullptr;
	(*tmp)->rightLeaf = nullptr;
}

void cleanTree(treeNode* node/*root at first request*/) {

	if (node->leftLeaf != nullptr) cleanTree(node->leftLeaf);
	if (node->rightLeaf != nullptr) cleanTree(node->rightLeaf);

	free(node->data);
	free(node->key);
	free(node);
}

void addAnswToTree(treeNode*& node, char* data, char* newData, bool leaf/*left or right. where data have to go*/) {
	addNode(node, node->data, !leaf);
	addNode(node, data, leaf);
	strcpy(node->data, newData);
}

treeNode* findLeaf(char* way, treeNode* node) {
	if (*(way + 1) == '\0') {
		return node;
	}
	if (*way == '0') return findLeaf(way + 1, node->leftLeaf);
	if (*way == '1') return findLeaf(way + 1, node->rightLeaf);
}


treeNode* findObject(treeNode* node/*root at 1st request*/) {
	bool select;
		if (node->leftLeaf && node->rightLeaf) {
			printf("%s ?\n1 - Да\n0 - Нет\n", node->data);
			select = securitedEnter(0, 1);
			if (select) return findObject(node->rightLeaf);
			else return findObject(node->leftLeaf);
		}
		else {
			printf("Это %s ?\n1 - Да\n0 - Нет\n", node->data);
			select = securitedEnter(0, 1);
			if (select) return nullptr;
			else return node;
		}
}
