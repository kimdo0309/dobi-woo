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

	strcpy(meso[0].name, "�̺�Ʈ �� ť��");
	meso[0].cost = 100;
	meso[0].count = 50;

	strcpy(meso[1].name, "���� ����ɷ� �ο� �ֹ���");
	meso[1].cost = 300;
	meso[1].count = 5;

	strcpy(meso[2].name, "����ų� ����ɷ� �ο� �ֹ���");
	meso[2].cost = 300;
	meso[2].count = 5;

	printf("���μ��� 1, �޼Ҽ��� 2�� �Է��ϼ���\n");
	scanf("%d", &num);

	while(1)
	{
		printf("������ �ִ� ���� : %d\n", yourcoin);
		printf("������ �ִ� �޼� : %d\n", yourmeso);
		switch (num)
		{
		case 1:
			for (int i = 0; i < 3; i++)
			{
				printf("%d.", i + 1);
				printf("�̸� : %s\n", meso[i].name);
				printf("���� : %d\n", meso[i].cost);
				printf("���� : %d\n", meso[i].count);
				printf("\n");
			}
			printf("�����Ͻ� �������� ��ȣ�� �Է��ϼ���\n");
			scanf("%d", &num3);
			if (num3 > 4)
			{
				printf("�߸��� �Է��Դϴ�.\n");
			}
			else
			{
				yourcoin = yourcoin - meso[num3 - 1].cost;
				if (yourcoin < 0)
				{
					printf("������ ������ �����մϴ�!!\n");
					yourcoin = yourcoin + meso[num3 - 1].cost;
					meso[num3 - 1].count++;
				}
				meso[num3 - 1].count--;
			}
			break;
		case 2:
			printf("�ݵ� ũ�������ͺ��� ����ϽǼ��ֽ��ϴ�.(�̱�����)\n");
			break;
		default:
			printf("�߸��� �Է��Դϴ�.\n");
			break;
		}

		printf("������ ��� �Ͻðڽ��ϱ�?\n");
		printf("yes = 1, no = �ٸ� ���� �Է�\n");
		scanf("%d", &num2);
		if (num2 == 1)
		{
			printf("������ ��� �մϴ�.\n");
			printf("\n");
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
}