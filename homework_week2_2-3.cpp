#include <iostream>

using namespace std;

int gcd(int, int);

int main(void)
{
	int n; // �Է¹��� ���� ����� �˷��ִ� ����
	int gcdNum; // �ִ������� ���� ���� ����

	cout << "�� ���� ���� �Է����� ������ : ";
	cin >> n;

	int* num = new int[n]; // n�� ��ŭ �迭�� �����Ҵ�
	for (int i = 0; i < n; i++) // �����̽��ٸ� �������� n���� ���� �Է¹���
		cin >> num[i];

	gcdNum = num[0]; // ó�� �ִ������� ���� �Է� ���� ó�� ������ ����
	for (int i = 1; i < n; i++) // �ݺ����� 1���� n-1���� ���鼭 �� �ִ������� �ִ������� ����
		gcdNum = gcd(gcdNum, num[i]);
	cout << "�ִ����� : " << gcdNum << endl;


	return 0;
}

int gcd(int num1, int num2)
{
	// ��Ŭ���� ȣ������ ����Ͽ� �ִ������� ���ϴ� �Լ�
	// ��Ŭ���� ȣ������ �� ���� ���� ���� ���� ������ ���ϴ� ���� ���
	// �˰����� ����(���⼭�� �ݺ����� �����)

	int temp; // �ӽ÷� ������ �����ϱ� ���� ����

	while (num2 > 0)
	{
		// �ݺ����� ����Ͽ� ��Ŭ���� ȣ������ ����

		temp = num1;
		num1 = num2;
		num2 = temp % num2;
	}

	return num1;
}