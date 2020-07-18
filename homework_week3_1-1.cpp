#include <iostream>

using namespace std;

void merge(int[], int, int, int, int[]);
void mergeSort(int[], int, int, int[]);

int main(void)
{
	int A[10] = { 30, 20, 40, 35, 5, 50, 45, 10, 25, 15 };
	int sort[10]; // �迭 ������ ���縦 ���� �迭

	mergeSort(A, 0, 9, sort);

	cout << "\n���� ��� �迭 : ";
	for (int i = 0; i < 10; i++)
	{
		// ���ĵ� �迭�� ����ϴ� �ݺ���

		cout << A[i] << " ";
	}
	cout << endl;

	return 0;
}

void merge(int A[], int l, int m, int r, int sort[])
{
	int i, j, k;

	i = l; // �������� ���ҵ� �迭�� �պ��ϱ� ���� �ʿ��� ����
	j = m + 1; // �и��� �迭 �� ������ �迭�� ù ��°�� ���� ����
	k = l; // ���θ�������� �迭�� �ʿ��� ����

	while (i <= m && j <= r)
	{
		// ���ҵ� �迭�� �պ��� ���� �ݺ���

		if (A[i] <= A[j])
		{
			sort[k] = A[i];

			k++;
			i++;
		}
		else
		{
			sort[k] = A[j];

			k++;
			j++;
		}
	}

	if (i > m)
	{
		// �����ִ� ������ �����ϴ� ���ǹ�
		// �� ��쿡�� ������ �迭�� ���� �����ִ� ���

		for (int h = j; h <= r; h++)
		{
			sort[k] = A[h];

			k++;
		}
	}
	else
	{
		// �����ִ� ������ �����ϴ� ���ǹ�
		// �� ��쿡�� ������ �迭�� ���� �����ִ� ���

		for (int h = i; h <= m; h++)
		{
			sort[k] = A[h];

			k++;
		}
	}

	for (int h = l; h <= r; h++)
	{
		// �迭 sort[]�� ���� A[]�迭�� �����ϴ� �ݺ���

		A[h] = sort[h];
	}

	for (int h = l; h <= r; h++)
	{
		// �Ź� �ݺ����� ���۸� ����ϱ� ���� �ݺ���

		cout << sort[h] << " ";
	}
	cout << endl;
}

void mergeSort(int A[], int l, int r, int sort[])
{
	int m; // �迭�� ���������� �߰� ���� �����ϴ� ����

	if (l < r)
	{
		// �迭�� ���̰� 1�̻��̸� ����Ǵ� ���ǹ�

		m = (l + r) / 2; // �߰� ���� ����

		mergeSort(A, l, m, sort); // ���� �κ� �迭�� ����
		mergeSort(A, m + 1, r, sort); // ������ �κ� �迭�� ����
		merge(A, l, m, r, sort); // ������ ������� �� ���� ���� ��ġ�� �Լ�
	}
}