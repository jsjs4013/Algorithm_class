#include <iostream>
#include <ctime>

using namespace std;

void FindMinMax(int[], int, int*, int*);

int main(void)
{
	int A[1000];
	int min, max;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		// ������ 1~100000������ �� �� 1000���� �迭 A[]�� �����ϴ� �ݺ���

		int num = rand();

		A[i] = (int)num % 100000 + 1;
	}

	FindMinMax(A, 1000, &min, &max);
	cout << "�ּ� �� : " << min << endl;
	cout << "�ּ� �� : " << max << endl;


	return 0;
}

void FindMinMax(int A[], int n, int* min, int* max)
{
	int small, large; // �񱳵Ǵ� ���ӵ� �� �ΰ� �� ���� ���� ū ���� �����ϴ� ����
	*min = A[0];
	*max = A[0];

	for (int i = 1; i < n - 1; i += 2)
	{
		// min�� max�� A[0]���� ���ϹǷ� i=1���� n-1������ ������ ��

		if (A[i] < A[i + 1])
		{
			// i��° �迭�� ���� i + 1��° �迭�� ���� ���Ͽ�
			// i��°�� ������ ����Ǵ� ���ǹ�

			small = A[i];
			large = A[i + 1];
		}
		else
		{
			// i��°�� ũ�� ����Ǵ� ���ǹ�

			small = A[i + 1];
			large = A[i];
		}

		if (small < *min)
		{
			// �� ���ǹ����� ã���� small�� ���� min���� ũ��
			// min���� small�� ���� ����

			*min = small;
		}
		if (large > *max)
		{
			// �� ���ǹ����� ã���� large�� ���� min���� ũ��
			// max���� large�� ���� ����

			*max = large;
		}
	}
}