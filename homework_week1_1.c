#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	float avr[1000]; // ��������� �����ϱ� ���� ����
	int x[1000]; // �Է¹��� ���� int������ �����ϱ� ���� ����
	char input[1000]; // �Է��� �ޱ����� ����
	char* tmp[1000]; // �Է¹��� ������ ��� �����ϱ����� ����

	int count = 1; // �Է¹��� ���� ������ ī��Ʈ�ϱ� ���� ����
	int i = 1;
	float temp = 0.0; // �������� �����ϱ����� ����


	printf("�迭�� �Է����ּ��� : ");
	gets(input);
	printf("\n");
	// strtok�� ����Ͽ� ����ڰ� �Է��� ���� ����� �˾Ƴ��� �κ�
	tmp[0] = strtok(input, " ");
	while (tmp[i] = strtok(NULL, " "))
	{
		// strtok�� ����Ͽ� ���� �Ǿ��� ���ڵ��� �Է��� �޾ƿ�
		// �� ��� ���ڰ� �ԷµǾ����� �ݺ����� ���� �˾Ƴ��� �κ�

		i++;
		count++;
	}
	for (i = 0; i < count; i++)
	{
		// �ӽ������ �������� int���� �ƴϹǷ� atoi�� ����Ͽ�
		// ��� �ӽ������ ������ int������ ������־� x[i]������ �����ϴ� �κ�

		x[i] = atoi(tmp[i]);
	}

	printf("Avr ���\n");
	for (i = 0; i < count; i++)
	{
		// �����հ� ��������� ���ϴ� �κ�

		temp += x[i];
		avr[i] = temp / (i + 1);

		printf("Avr[%d]: %f\n", i, avr[i]);
	}


	return 0;
}