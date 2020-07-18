#include <iostream>

using namespace std;

void dp(int[], int[], int, int);

int main(void)
{
	int d; // ������ ������ �Է¹޴� ����
	int m; // �� ���� M��

	cout << "���� �ϴ� ���� : ";
	cin >> m;

	// ������ m + 1����ŭ �����Ҵ� �Ǵ� ���� ���� ������ ������ �����ϴ� �迭
	// m + 1�� ������ ���� ù ���� ���� �� ��ü�� ����ϴ� ��� �ּ��� ����
	// 1�� ��Ÿ���� ���� 12���� ���� �����
	int* smallestNumOfCoins = new int[m + 1];
	for (int i = 0; i < m + 1; i++)
		smallestNumOfCoins[i] = 0;

	cout << "������ ���� : ";
	cin >> d;

	int* c = new int[d]; // ������ d����ŭ �����Ҵ� �Ǵ� ������ ������ ��� ����
	cout << "������ �Է� : ";
	for (int i = 0; i < d; i++)
		cin >> c[i];

	dp(smallestNumOfCoins, c, m, d);

	for (int i = 1; i < 12; i++)
	{
		// ��� ������ ���ؼ� �ּ��� ���� ��Ÿ���� �ݺ���

		cout << i << " ��° ��� �ּ��� ���� ���� : " << smallestNumOfCoins[i] << endl;
	}

	return 0;
}

void dp(int smallestNumOfCoins[], int c[], int m, int d)
{
	for (int i = 1; i <= m; i++)
	{
		// �� ��ǥ �� ���� �ּ��� ������ ã�� ���̳��� ���α׷��� �Լ��� �ݺ���

		// ���Ϸ��� ���� ���� ���ʿ� INT�� �ִ� ���� �����
		smallestNumOfCoins[i] = INT_MAX;

		for (int j = 0; j < d; j++)
		{
			// �������� ���ؾ��ϹǷ� ����ϴ� �ݺ���

			if (i >= c[j])
			{
				// ��ǥ ���� ������ ũ�⺸�� ���ų� Ŭ ��� ����Ǵ� ���ǹ�

				if (smallestNumOfCoins[i - c[j]] + 1 < smallestNumOfCoins[i])
				{
					// ��ǥ ���� ���ؼ� ��밡���� ������ �ݺ������� ���鼭 ����
					// ��ǥ ������ ������ ���� �� ���� ������ �������� +1 �� �Ͽ�
					// ������ ������ ����������
					// �� �� �������α׷��� ����� ����ϹǷ� ������ ���� �̸� �����ϰ� ����


					// ��ǥ ���� �ش��ϴ� �迭�� ���� ��ǥ ������ ������ ���� �� �迭�� ������
					// ������ +1 �� �Ͽ� ��ǥ ���� ���� ������ ������ 1 ������Ŵ
					smallestNumOfCoins[i] = smallestNumOfCoins[i - c[j]] + 1; // ������ �ּ� ����
				}
			}
		}
	}
}