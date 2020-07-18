#include <iostream>

using namespace std;

int* GreedyBetterChange(int, int[], int);
int BruteForceChange(int, int[], int, int[], int, int[], int);

int main(void)
{
	int d; // Coin�� ������ �Է¹޴� ����
	int m; // �� ���� �޶����Ƿ� M�� �Է¹޴� ����
	int* k; // ������ ������ �Է¹޴� ����
	int greedyCoins; // greedy������� ������� coin�� �ּ� ������ Ȯ���ϴ� ����
	int bruteCoins; // brute������� coin�� �ּ� ������ Ȯ���ϴ� ����

	cout << "������ ���� : ";
	cin >> d;

	int* c = new int[d]; // �������� ũ�⸦ �Է¹޾� ������ ������ �Է¹޴� ����
	cout << "������ �Է� : ";
	for (int i = 0; i < d; i++)
		cin >> c[i];

	int* bestChange = new int[d]; // ������ ������ŭ �����Ҵ�Ǵ� �ְ��� ������ ������ ��� ����
	for (int i = 0; i < d; i++)
		bestChange[i] = 0;

	int* tempNum = new int[d]; // BruteForceChange() �Լ����� ���Ǵ� ���� ��ġ�� ��Ÿ���� ����
	for (int i = 0; i < d; i++)
		tempNum[i] = 0;

	for (m = 1; m <= 100; m++)
	{
		// M���� 1���� 100���� ���ʴ�� ���ư��鼭 �ݺ��Ǵ� �ݺ���
		// �� �ݺ������� GreedyBetterChange()�� BruteForceChange()�� ���� �񱳵Ǿ�����
		// ���� �ٸ� ��� "���� ���� �ٸ�" �̶�� ����ϰԵǸ�, ������� ������ ���� ��µ�

		for (int i = 0; i < d; i++)
			bestChange[i] = 0; // ������ ������ŭ �����Ҵ�Ǵ� �ְ��� ������ ������ ��� ����(Brute���� ���)

		greedyCoins = 0; // greedy�� �ʱⰪ�� 0���� �ʱ�ȭ ��
		k = GreedyBetterChange(m, c, d);
		for (int i = 0; i < d; i++)
			greedyCoins += k[i]; // GreedyBetterChange()�� ��� ���� �ݺ����� ����Ͽ� �� ���� ������ ���Ǿ����� Ȯ��

		bruteCoins = BruteForceChange(m, c, d, bestChange, INT_MAX, tempNum, -1);

		if (greedyCoins != bruteCoins) // �� ���� ����� ���� ���� ������ ������ �������ִ��� �ƴ��� Ȯ��
			cout << "M : " << m << "\tGreedyBetterChange = " << greedyCoins << "\tBruteForceChange = " << bruteCoins << " ���� ���� �ٸ�" << endl;

		else
			cout << "M : " << m << "\tGreedyBetterChange = " << greedyCoins << "\tBruteForceChange = " << bruteCoins << endl;
	}


	return 0;
}

int* GreedyBetterChange(int m, int c[], int d)
{
	int* k = new int[d]; // �� �������� ���� ��� �������� �����ϴ� ����

	for (int i = 0; i < d; i++)
	{
		// ���� �������� �� ������ k[i]�� ���ϴ� �ݺ���
		// M�� ���� 0�� �ǰ� ����� �ش�.

		k[i] = m / c[i]; // �����⸦ ���� �� �������� ������ ������ ����
		m = m - (c[i] * k[i]);
	}

	return k;
}

int BruteForceChange(int m, int c[], int d, int bestChange[], int smallestNumberOfCoins, int tempNum[], int here)
{
	int numberOfCoins; // Coin�� ���� ��Ÿ���� ����
	int valueOfCoins; // ����� ������ �̿��Ͽ� ���� ���� �˾Ƴ��� ����
	int* k = new int[d]; // �� �������� ���� ��� �������� �����ϴ� ����

	here += 1; // ����Լ��� �Լ��� ���µ� ���� �� ��° ��ġ������ �˷��ִ� ����
	for (int i = 0; i < d; i++)
	{
		// �� ������ ������ �ְ� ����� ���� �� �ִ�����
		// Ȯ���ϴ� �ݺ����̸� �� ���� k[i]�迭�� ����

		k[i] = m / c[i];
	}


	for (int i = 0; i <= k[here]; i++)
	{
		// ������ ������ ������� ��� ���� ������ �� �ֵ��� ��͸� ����ϴ� �ݺ���
		// ����Լ� ����� ����Ͽ� �����ڵ忡�� ��������Ͱ� ���� �ݺ��� ȿ���� ������ ��

		if (here == d - 1)
		{
			// ������ ������ġ�� �Ǿ��� �� �ݺ����� ��� ���� �ּҰ��� ã�Ƴ��� �κ�

			valueOfCoins = 0; // ����� ���� ù �ʱ�ȭ���� 0���� ����
			for (int j = 0; j < here; j++)
				valueOfCoins += tempNum[j] * c[j]; // �� ���� ������ ������ ���Ͽ� ���
			valueOfCoins += i * c[here]; // ������ ���� ���� �Լ��� ��ġ�ϹǷ� ���� i�� ���

			if (valueOfCoins == m)
			{
				// ���� ���� ���� M�� ���� ���ٸ� �ּ��� ������ ����ߴ����� ���

				numberOfCoins = 0;
				for (int j = 0; j < here; j++)
					numberOfCoins += tempNum[j]; // ������ � ������� Ȯ���ϴ� �κ�
				numberOfCoins += i;

				if (numberOfCoins < smallestNumberOfCoins)
				{
					// ���� �ּ��� ������ ����ߴٸ� smallestNumberOfCoins������ ������Ʈ ��

					for (int j = 0; j < here; j++)
						bestChange[j] = tempNum[j]; // �ּ��� ������ ����ϴ� ������ ������ ������ ������Ʈ ��
					bestChange[here] = i;

					smallestNumberOfCoins = numberOfCoins;
				}
			}
		}
		else
		{
			// ���� ������ ������ �ƴ϶�� ���ο� BruteForceChange()�Լ��� �ҷ� ��������� �ǰ���
			// �ؼ� �ݺ��� ���� �ݺ����� ������ �ǰԲ� ����� ��

			tempNum[here] = i; // ���� ��ġ�� �ش��ϴ� �ݺ����� i���� tempNum������ �����ϰ� ���� �Լ����� �� �־���
			smallestNumberOfCoins = BruteForceChange(m, c, d, bestChange, smallestNumberOfCoins, tempNum, here);
		}
	}
	tempNum[here] = 0; // ��� ���� ���� ���Ͽ� ���� ��ġ�� �ش��ϴ� �ݺ� i���� 0���� �������


	return smallestNumberOfCoins;
}