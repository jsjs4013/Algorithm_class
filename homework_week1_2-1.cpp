#include <iostream>

using namespace std;

int* GreedyBetterChange(int, int[], int);

int main(void)
{
	int d; // 코인의 개수를 입력받는 변수
	int m = 40; // 총 값인 M의 값
	int* k; // 코인의 종류를 입력받는 변수

	cout << "코인의 개수 : ";
	cin >> d;

	int* c = new int[d]; // 동적으로 크기를 입력받아 동전의 종류를 입력받는 변수
	cout << "코인을 입력 : ";
	for (int i = 0; i < d; i++)
		cin >> c[i];

	k = GreedyBetterChange(m, c, d);


	for (int i = 0; i < d; i++)
	{
		// 모든 동전의 종류별 개수를 출력하는 반복문

		cout << c[i] << " = " << k[i] << endl;
	}
	cout << "로 나누어집니다." << endl;

	delete[] k;


	return 0;
}

int* GreedyBetterChange(int m, int c[], int d)
{
	int* k = new int[d]; // 각 동전별로 최종 몇개가 쓰일지를 저장하는 변수

	for (int i = 0; i < d; i++)
	{
		// 동전 종류별로 각 개수인 k[i]를 구하는 반복문
		// M의 값이 0이 되게 만들어 준다.

		k[i] = m / c[i]; // 나누기를 통해 각 종류별로 가능한 개수를 구함
		m = m - (c[i] * k[i]);
	}

	return k;
}