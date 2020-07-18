#include <iostream>
#include <ctime>

using namespace std;

int Minimum(int[], int);
int Maximum(int[], int);

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

	min = Minimum(A, 1000);
	max = Maximum(A, 1000);

	cout << "�ּ� �� : " << min << endl;
	cout << "�ְ� �� : " << max << endl;


	return 0;
}

int Minimum(int A[], int n)
{
	int temp; // ���� ���� ���� �����ϴ� ����

	temp = A[0]; // �ӽ÷� �迭�� ���� ù ���� ����

	for (int i = 1; i < n; i++)
	{
		// �迭�� ó������ ������ �˻��ؼ� �ּ��� ���� ã�� �ݺ���

		if (temp > A[i])
		{
			// ���� temp�� ���� A[i]�� ������ ũ��
			// ���� ���� ���� �ӽ÷� A[i]�� �����ϰ�
			// temp�� A[i]�� ����

			temp = A[i];
		}
	}

	return temp;
}

int Maximum(int A[], int n)
{
	int temp; // ���� ū ���� �����ϴ� ����

	temp = A[0]; // �ӽ÷� �迭�� ���� ù ���� ����

	for (int i = 1; i < n; i++)
	{
		// �迭�� ó������ ������ �˻��ؼ� �ּ��� ���� ã�� �ݺ���

		if (temp < A[i])
		{
			// ���� temp�� ���� A[i]�� ������ ������
			// ���� ū ���� �ӽ÷� A[i]�� �����ϰ�
			// temp�� A[i]�� ����

			temp = A[i];
		}
	}

	return temp;
}