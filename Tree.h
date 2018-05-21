#ifndef _TREE_H_
#define _TREE_H_

#define buffSizeStr1024 1024

#define left 0
#define right 1

struct treeNode {
	char* data;
	char* key;

	treeNode* leftLeaf;
	treeNode* rightLeaf;
};

void addNode(treeNode*& node, char* data, bool leaf);
void cleanTree(treeNode* node/*root at first request*/);
void addAnswToTree(treeNode*& node, char* data, char* newData, bool leaf/*left or right. where data have to go*/);
treeNode* findLeaf(char* way, treeNode* node);
treeNode* findObject(treeNode* root/*root at 1st request*/);

#endif // !_TREE_H_
