#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct menu
{
	char name[50];
	int cost;
	int count;
};

int main()
{
	int num = 0;
	int yourmeso = 1000;
	int yourcoin = 1000;

	struct menu meso[10];
	struct menu coin[10];

	strcpy(meso[0].name, "이벤트 링 큐브");
	meso[0].cost = 100;
	meso[0].count = 50;

	strcpy(meso[1].name, "에픽 잠재능력 부여 주문서");
	meso[1].cost = 300;
	meso[1].count = 5;

	strcpy(meso[2].name, "에디셔널 잠재능력 부여 주문서");
	meso[2].cost = 300;
	meso[2].count = 5;

	printf("코인샵은 1, 메소샵은 2를 입력하세요\n");
	scanf("%d", &num);

	switch (num)
	{
	case 1:
		for (int i = 0; i < 3; i++)
		{
			printf("이름 : %s\n", meso[i].name);
			printf("가격 : %d\n", meso[i].cost);
			printf("개수 : %d\n", meso[i].count);
			printf("\n");
		}
		break;
	case 2:
		printf("콜드 크리에이터부터 사용하실수있습니다.(미구현ㅋ)\n");
		break;
	default:
		printf("잘못된 입력입니다.\n");
		return 0;
	}



	return 0;
}