#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int securitedEnter(int left_barricade, int right_barricade) {
	int flag;
	int answer;
	printf("Answer: ");
	do {
		flag = scanf("%d", &answer);
		rewind(stdin);
	} while (!flag || (answer < left_barricade || answer > right_barricade));
	puts("");
	return answer;
}