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

	switch (num)
	{
	case 1:
		for (int i = 0; i < 3; i++)
		{
			printf("�̸� : %s\n", meso[i].name);
			printf("���� : %d\n", meso[i].cost);
			printf("���� : %d\n", meso[i].count);
			printf("\n");
		}
		break;
	case 2:
		printf("�ݵ� ũ�������ͺ��� ����ϽǼ��ֽ��ϴ�.(�̱�����)\n");
		break;
	default:
		printf("�߸��� �Է��Դϴ�.\n");
		return 0;
	}



	return 0;
}