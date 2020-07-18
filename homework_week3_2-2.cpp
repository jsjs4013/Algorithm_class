#include <iostream>

using namespace std;

void heapify(int[], int, int);
void heapSort(int[], int);

int main(void)
{
	int A[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };

	for (int i = 10 / 2; i >= 0; i--)
	{
		// heap ������ �ϴ� �ݺ���

		heapify(A, 10, i);
	}
	heapSort(A, 10);

	cout << "Heap ���� ��� : ";
	for (int i = 0; i < 10; i++)
	{
		// ���ĵ� �迭�� ����ϴ� �ݺ���

		cout << A[i] << " ";
	}

	return 0;
}

void heapify(int A[], int size, int root)
{
	int cur; // ���� tree���� ��ġ�ϴ� �ε��� ��ȣ
	int temp;


	cur = root * 2 + 1; // ���� root�� ���� �ڽ� node�� �ǹ�

	if (cur < size && A[cur] < A[cur + 1])
	{
		// root node�� �ڽ� �� �߿� ������ �ڽ��� �� ũ�� cur�� 1 �÷���

		cur++;
	}

	if (cur < size && A[root] < A[cur])
	{
		// root�� ������ ���� node�� ���� ũ�� ū ���� ���� ������ �ϹǷ�
		// root node�� ���� ���� node�� �ڽ� node�� ���� �ٲ�

		temp = A[root];
		A[root] = A[cur];
		A[cur] = temp;
	}

	if (cur <= size / 2)
	{
		// node�� ���� �ѹ��� �ٲ�°� �ƴ϶� �� �Ʒ���
		// ���� �� node���� �񱳵� �ؾ��ϹǷ� ����Լ��� ���

		heapify(A, size, cur);
	}
}

void heapSort(int A[], int size)
{
	int cur;
	int root;
	int temp;

	for (int i = size - 1; i >= 0; i--)
	{
		// root node�� ���� ������ node�� �ٲ���
		temp = A[0];
		A[0] = A[i];
		A[i] = temp;

		root = 0;
		cur = 1; // root�� 0�̹Ƿ� �ٷ� ���� ���� �ǹ�

		while (cur < i)
		{
			// ���⼭ i�� ���� ������ node

			cur = root * 2 + 1; // root node�� �ڽ��� ã��

			if (A[cur] < A[cur + 1] && cur < i - 1)
			{
				// root node�� �ڽ� �� �߿� ������ �ڽ��� �� ũ�� cur�� 1 �÷���

				cur++;
			}
			if (A[root] < A[cur] && cur < i)
			{
				// root�� ������ ���� node�� ���� ũ�� ū ���� ���� ������ �ϹǷ�
				// root node�� ���� ���� node�� �ڽ� node�� ���� �ٲ�

				temp = A[root];
				A[root] = A[cur];
				A[cur] = temp;
			}
			root = cur; // root�� cur�� �ٲ����μ� root�� root�� ���������� �񱳰����ϰ� ��
		}
	}
}