#include <iostream>

using namespace std;

int gcd(int[]);

int main(void)
{
	int num[2]; // �Է¹��� �� ���� ���� ���� ����
	int gcdNum; // �ִ������� ���� ���� ����

	cout << "���� �� �� �Է� : ";
	for (int i = 0; i < 2; i++) // �����̽��ٸ� �������� �� ���� �Է¹���
		cin >> num[i];

	gcdNum = gcd(num);
	cout << "�ִ����� : " << gcdNum << endl;


	return 0;
}

int gcd(int num[])
{
	// ��Ŭ���� ȣ������ ����Ͽ� �ִ������� ���ϴ� �Լ�
	// ��Ŭ���� ȣ������ �� ���� ���� ���� ���� ������ ���ϴ� ���� ���
	// �˰����� ����(���⼭�� ����Լ��� �����)

	int temp; // �ӽ÷� ������ �����ϱ� ���� ����


	// �� �Ʒ��� ����Լ��� ����Ͽ� ��Ŭ���� ȣ������ ����
	if (num[1] == 0)
		return num[0];
	else
	{
		temp = num[0];
		num[0] = num[1];
		num[1] = temp % num[1];

		return gcd(num);
	}
}