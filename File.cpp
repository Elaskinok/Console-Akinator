#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"
#include "Strings.h"
#include "File.h"

void skipTrash(FILE*& fp) {
	char symb = fgetc(fp);
	do {
		if (symb == ' ' || symb == '\n' || symb == '\0')
			symb = fgetc(fp);
	} while (symb == ' ' && symb == '\n' && symb == '\0');
	if (!feof(fp)) fseek(fp, -1, SEEK_CUR);
}

bool openFile(FILE*& fp, const char* file_name) {
	if (fp == nullptr) {
		printf("Can't open file \"%s\"!\n", file_name);
		system("CLS");
		return false;
	}
	return true;
}

void initFromFile(FILE* fp, treeNode*& root) {
	char* tmp = (char*)malloc(buffSizeStr1024 * sizeof(char));
	char* way = (char*)malloc(buffSizeStr1024 * sizeof(char));

	do {
		fscanf(fp, "%[^*0-9]", tmp);
		fscanf(fp, "%s", way);

		if (*way == '*') addNode(root, tmp, 0);
		else {
			treeNode* tempNode = findLeaf(way, root);
			addNode(tempNode, tmp, *(way + my_strlen(way) - 1) - '0');
		}
		skipTrash(fp);
	} while (!feof(fp));

	free(way);
	free(tmp);
}

void rewriteDatabase(FILE* fp, treeNode*& node, bool root/*"true" at 1st request*/) {
	if (root) fprintf(fp, "%s*\n", node->data);

	if (node->leftLeaf != nullptr) {
		fprintf(fp, "%s%s\n", node->leftLeaf->data, node->leftLeaf->key);
		rewriteDatabase(fp, node->leftLeaf, false);
	}
	if (node->rightLeaf != nullptr) {
		fprintf(fp, "%s%s\n", node->rightLeaf->data, node->rightLeaf->key);
		rewriteDatabase(fp, node->rightLeaf, false);
	}
}

void updateList(char* newFile) {
	FILE* fp;
	fopen_s(&fp, FILES_LIST, "a+");
	fprintf(fp, "%s\n", newFile);
	fclose(fp);
}