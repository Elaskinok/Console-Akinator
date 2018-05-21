#ifndef _FILE_H_
#define _FILE_H_

#define FILES_LIST "lst.txt"

void skipTrash(FILE*& fp);
bool openFile(FILE*& fp, const char* file_name); 
void initFromFile(FILE* fp, treeNode*& root);
void rewriteDatabase(FILE* fp, treeNode*& node, bool root/*"true" at 1st request*/);
void updateList(char* newFile);

#endif // !_FILE_H_
