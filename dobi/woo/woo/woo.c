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
	int num2 = 0;
	int num3 = 0;

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

	while(1)
	{
		printf("가지고 있는 코인 : %d\n", yourcoin);
		printf("가지고 있는 메소 : %d\n", yourmeso);
		switch (num)
		{
		case 1:
			for (int i = 0; i < 3; i++)
			{
				printf("%d.", i + 1);
				printf("이름 : %s\n", meso[i].name);
				printf("가격 : %d\n", meso[i].cost);
				printf("개수 : %d\n", meso[i].count);
				printf("\n");
			}
			printf("구매하실 아이템의 번호를 입력하세요\n");
			scanf("%d", &num3);
			if (num3 > 4)
			{
				printf("잘못된 입력입니다.\n");
			}
			else
			{
				yourcoin = yourcoin - meso[num3 - 1].cost;
				if (yourcoin < 0)
				{
					printf("코인의 개수가 부족합니다!!\n");
					yourcoin = yourcoin + meso[num3 - 1].cost;
					meso[num3 - 1].count++;
				}
				meso[num3 - 1].count--;
			}
			break;
		case 2:
			printf("콜드 크리에이터부터 사용하실수있습니다.(미구현ㅋ)\n");
			break;
		default:
			printf("잘못된 입력입니다.\n");
			break;
		}

		printf("쇼핑을 계속 하시겠습니까?\n");
		printf("yes = 1, no = 다른 숫자 입력\n");
		scanf("%d", &num2);
		if (num2 == 1)
		{
			printf("쇼핑을 계속 합니다.\n");
			printf("\n");
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
}