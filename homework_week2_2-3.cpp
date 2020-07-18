#include <iostream>

using namespace std;

int gcd(int, int);

int main(void)
{
	int n; // 입력받을 값이 몇개인지 알려주는 변수
	int gcdNum; // 최대공약수의 값을 위한 변수

	cout << "몇 개의 값을 입력할지 쓰세요 : ";
	cin >> n;

	int* num = new int[n]; // n개 만큼 배열을 동적할당
	for (int i = 0; i < n; i++) // 스페이스바를 기점으로 n개의 수를 입력받음
		cin >> num[i];

	gcdNum = num[0]; // 처음 최대공약수의 값을 입력 값의 처음 값으로 저장
	for (int i = 1; i < n; i++) // 반복문을 1부터 n-1까지 돌면서 각 최대공약수의 최대공약수를 구함
		gcdNum = gcd(gcdNum, num[i]);
	cout << "최대공약수 : " << gcdNum << endl;


	return 0;
}

int gcd(int num1, int num2)
{
	// 유클리드 호제법을 사용하여 최대공약수를 구하는 함수
	// 유클리드 호제법은 두 수가 서로 상대방 수를 나누어 원하는 수를 얻는
	// 알고리즘을 말함(여기서는 반복문을 사용함)

	int temp; // 임시로 변수를 저장하기 위한 변수

	while (num2 > 0)
	{
		// 반복문을 사용하여 유클리드 호제법을 실행

		temp = num1;
		num1 = num2;
		num2 = temp % num2;
	}

	return num1;
}