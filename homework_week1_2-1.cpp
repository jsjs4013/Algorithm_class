#include <iostream>

using namespace std;

int* GreedyBetterChange(int, int[], int);

int main(void)
{
	int d; // ������ ������ �Է¹޴� ����
	int m = 40; // �� ���� M�� ��
	int* k; // ������ ������ �Է¹޴� ����

	cout << "������ ���� : ";
	cin >> d;

	int* c = new int[d]; // �������� ũ�⸦ �Է¹޾� ������ ������ �Է¹޴� ����
	cout << "������ �Է� : ";
	for (int i = 0; i < d; i++)
		cin >> c[i];

	k = GreedyBetterChange(m, c, d);


	for (int i = 0; i < d; i++)
	{
		// ��� ������ ������ ������ ����ϴ� �ݺ���

		cout << c[i] << " = " << k[i] << endl;
	}
	cout << "�� ���������ϴ�." << endl;

	delete[] k;


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