#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Tree.h"
#include "Strings.h"
#include "File.h"
#include "secEnter.h"

// !!!��� ����������� ������������� ������� ����� � ���� ? � ��� � ���!!!

int main()
{
	system("chcp 1251 > nul");
	FILE* file_pointer;
	printf("������ ���� ?\n1 - ��\n0 - ���\n");
	if (securitedEnter(0, 1))	while (1) {
		bool flagAdd = false;
		system("CLS");
		treeNode* root = nullptr;
		char* fileName = (char*)calloc(buffSizeStr1024, sizeof(char));;
		printf("������ �� �� ������������ ������������ ���� ������ ��� ������� ������� ����� ?\n");
		printf("1 - ������������ ������������\n2 - ������� �����\n");
		if (securitedEnter(1, 2) == 1) {
			fopen_s(&file_pointer, FILES_LIST, "r");
			if (file_pointer) {
				printf("�������� ���� �� ������������ �������:\n");
				int i = 1;
				do {
					char* tmp = (char*)calloc(buffSizeStr1024, sizeof(char));
					fscanf(file_pointer, "%[^\n]", tmp);
					skipTrash(file_pointer);
					printf("%d - %s\n", i, tmp);
					++i;
					free(tmp);
				} while (!feof(file_pointer));
				int indexStr = securitedEnter(1, i);
				i = 1;
				rewind(file_pointer);
				do {
					fscanf(file_pointer, "%[^\n]", fileName);
					skipTrash(file_pointer);
					if (i == indexStr) break;
					i++;
				} while (!feof(file_pointer));
				fclose(file_pointer);
			}
			else {
				printf("��� ������ �� ����������!!!\n");
				enterFileName(fileName);
				flagAdd = true;
			}
		}
		else {
			enterFileName(fileName);
			flagAdd = true;
		}


		fopen_s(&file_pointer, fileName, "r+");
		if (file_pointer) {
			rewind(file_pointer);
			initFromFile(file_pointer, root);
			fclose(file_pointer);
		}
		else {
			char* tmp = (char*)malloc(sizeof(char)*buffSizeStr1024);
			printf("���� ������ �����! ���������� ������ ������.\n������: ");
			fscanf(stdin, "%[^\n]", tmp); rewind(stdin);
			addNode(root, tmp, 0);
			free(tmp);
		}

		printf("============================================================\n\n�����!!!");
		printf("\n\n============================================================\n");

		treeNode* tempNode = findObject(root);
		if (!tempNode) {
			printf("����� �����!\n");
		}
		else {
			char* tmp1 = (char*)malloc(buffSizeStr1024 * sizeof(char));
			printf("� ��� ��� ?\n");
			fscanf(stdin, "%[^\n]", tmp1); rewind(stdin);
			char* tmp2 = (char*)malloc(buffSizeStr1024 * sizeof(char));

			printf("� ��� �� ���������� �� %s ?\n", tempNode->data);
			fscanf(stdin, "%[^\n]", tmp2); rewind(stdin);
			addAnswToTree(tempNode, tmp1, tmp2, right);

			free(tmp1);
			free(tmp2);
		}
		
		fopen_s(&file_pointer, fileName, "w+");
		if (file_pointer) {	
			rewriteDatabase(file_pointer, root, true);
			if(flagAdd) updateList(fileName);
			fclose(file_pointer);
			cleanTree(root);
		}

		free(fileName);

		printf("������ ���������� ?\n1 - ��\n0 - ���\n");
		if (!securitedEnter(0, 1)) break;
	}
	
	return 0;
}