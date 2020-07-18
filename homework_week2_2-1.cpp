#include <iostream>

using namespace std;

int gcd(int[]);

int main(void)
{
	int num[2]; // 입력받을 두 개의 값을 위한 변수
	int gcdNum; // 최대공약수의 값을 위한 변수

	cout << "숫자 두 개 입력 : ";
	for (int i = 0; i < 2; i++) // 스페이스바를 기점으로 두 수를 입력받음
		cin >> num[i];

	gcdNum = gcd(num);
	cout << "최대공약수 : " << gcdNum << endl;


	return 0;
}

int gcd(int num[])
{
	// 유클리드 호제법을 사용하여 최대공약수를 구하는 함수
	// 유클리드 호제법은 두 수가 서로 상대방 수를 나누어 원하는 수를 얻는
	// 알고리즘을 말함(여기서는 반복문을 사용함)

	int temp; // 임시로 변수를 저장하기 위한 변수

	while (num[1] > 0)
	{
		// 반복문을 사용하여 유클리드 호제법을 실행

		temp = num[0];
		num[0] = num[1];
		num[1] = temp % num[1];
	}

	return num[0];
}