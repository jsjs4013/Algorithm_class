#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int*, int*);
void bubble(int[], int);

int main(void)
{
	int N[10]; // ������ �� 10���� �޴� �迭
	int K[1000]; // ������ �� 1000���� �޴� �迭

	// �Ź� rand()�� ���� �ٸ��� �ϱ����� srand()�� time()�� ����Ͽ� seed�� �ٸ��� ����
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		// ������ 1~10000������ �� �� 10���� �迭 N[]�� �����ϴ� �ݺ���

		int num = rand();

		N[i] = (int)num % 10000 + 1;
	}
	for (int i = 0; i < 1000; i++)
	{
		// ������ 1~10000������ �� �� 1000���� �迭 K[]�� �����ϴ� �ݺ���

		int num = rand();

		K[i] = (int)num % 10000 + 1;
	}

	bubble(N, 10);
	for (int i = 0; i < 10; i++) // ������������ ������ �Ǿ����� ������ִ� �ݺ���
		cout << N[i] << endl;

	
	return 0;
}

void swap(int* a, int* b)
{
	// ���� ���� a, b�� ��ȯ���ִ� �Լ�

	int temp = *a;

	*a = *b;
	*b = temp;
}

void bubble(int N[], int size)
{
	if (size == 1) // size�� ũ�Ⱑ 1�̵Ǹ� ���� ���� �����Ƿ� ����
		return;

	for (int i = 0; i < size - 1; i++)
	{
		// �����Ʈ�� �� ����Ŭ�� �����ϴ� �ݺ���

		if (N[i] < N[i + 1])
		{
			// �������� �����̹Ƿ� ����� ������ ���� ���Ͽ�
			// ���� ���� �� ������ ���� ���� ���� ���� ��ȯ�Ͽ��� ��

			swap(&N[i], &N[i + 1]);
		}
	}

	bubble(N, size - 1); // ���ȣ��
}