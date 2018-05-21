#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int my_strlen(char* string) {
	int size = 0;
	do {
		if (*(string + size) != '\0' && *(string + size) != '\n') size++;
	} while (*(string + size) != '\0' && *(string + size) != '\n');
	return size;
}

void enterFileName(char*& fileName) {
	printf("Придумайте название для новой базы:\n");
	fscanf(stdin, "%[^\n]", fileName); rewind(stdin);
	*(fileName + my_strlen(fileName)) = '.';
	*(fileName + my_strlen(fileName)) = 't';
	*(fileName + my_strlen(fileName)) = 'x';
	*(fileName + my_strlen(fileName)) = 't';
}