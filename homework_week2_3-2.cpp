#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int*, int*);
void quick(int[], int);

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

	quick(N, 10);
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

void quick(int N[], int size)
{
	int start, end, l, r;
	int pivot;
	int* stack = new int[size * 2 + 2]; // stack�� ����ϴµ� �ִ� ũ�Ⱑ 2n + 2 ��
	int push = -1; // �迭�� stack�� LIFOó�� ����ϱ� ���� ����

	// LIFO ������ �迭�� ���Ƿ� �������
	stack[++push] = size - 1;
	stack[++push] = 0;

	while (push >= 0)
	{
		// stack�� -1�� �Ǹ� �� push���� -1�� �Ǹ� ��������
		// �������� �����ϸ鼭 ����Ʈ�� ����

		start = stack[push--];
		end = stack[push--];

		if (end - start + 1 > 1)
		{
			// �� ���ҵ� ���� ���� 2�̻��̸� ����

			pivot = N[end]; // pivot�� �� ���� ���ڷ� �������

			l = start; // ���� �迭�� ���� �κ�
			r = end - 1; // ���� �迭�� ������ �κ�
			while (1)
			{
				// �񱳴����(l�� r) ������ �� ���� ���ϱ����� �ݺ���

				while (N[l] > pivot) // pivot���� ū ���� ���� ���� �ݺ���
					l++;
				while (r > start && N[r] < pivot) // pivot���� ���� ������ ���� ���� �ݺ���
					r--;

				if (l >= r) // l�� r�� �����Ǹ� �ݺ����� ��������
					break;

				swap(&N[l], &N[r]); // ������ ���� �ٲ���

				l++;
				r--;
			}

			// pivot�� �ڸ��� l�� �ڸ��� ��ȯ
			N[end] = N[l];
			N[l] = pivot;

			// ��ʹ�� �ݺ����� ����ϸ� �̷��� �ؾ���
			stack[++push] = end;
			stack[++push] = l + 1; // ������� ������ �κ��� ������ �迭 �κ�
			stack[++push] = l - 1;
			stack[++push] = start; // ������� ������ �κ��� ���� �迭 �κ�
		}
	}

	delete[] stack;
}