#include <iostream>

using namespace std;

void dp(int[], int[], int, int);

int main(void)
{
	int d; // 동전의 개수를 입력받는 변수
	int m; // 총 값인 M값

	cout << "목료로 하는 동전 : ";
	cin >> m;

	// 개수가 m + 1개만큼 동적할당 되는 제일 작은 동전의 개수를 저장하는 배열
	// m + 1인 이유는 제일 첫 열에 동전 그 자체를 사용하는 경우 최소의 값인
	// 1을 나타내기 위해 12개의 열을 사용함
	int* smallestNumOfCoins = new int[m + 1];
	for (int i = 0; i < m + 1; i++)
		smallestNumOfCoins[i] = 0;

	cout << "코인의 개수 : ";
	cin >> d;

	int* c = new int[d]; // 개수가 d개만큼 동적할당 되는 동전의 종류를 담는 변수
	cout << "코인을 입력 : ";
	for (int i = 0; i < d; i++)
		cin >> c[i];

	dp(smallestNumOfCoins, c, m, d);

	for (int i = 1; i < 12; i++)
	{
		// 모든 동전에 대해서 최소의 값을 나타내는 반복문

		cout << i << " 번째 경우 최소의 동전 갯수 : " << smallestNumOfCoins[i] << endl;
	}

	return 0;
}

void dp(int smallestNumOfCoins[], int c[], int m, int d)
{
	for (int i = 1; i <= m; i++)
	{
		// 각 목표 값 마다 최소의 동전을 찾는 다이나믹 프로그래밍 함수의 반복문

		// 비교하려는 값의 열을 최초에 INT의 최대 값을 사용함
		smallestNumOfCoins[i] = INT_MAX;

		for (int j = 0; j < d; j++)
		{
			// 동전별로 비교해야하므로 사용하는 반복문

			if (i >= c[j])
			{
				// 목표 값이 동전의 크기보다 같거나 클 경우 실행되는 조건문

				if (smallestNumOfCoins[i - c[j]] + 1 < smallestNumOfCoins[i])
				{
					// 목표 값에 대해서 사용가능한 동전을 반복문으로 돌면서 비교함
					// 목표 값에서 동전의 값을 뺀 값의 동전의 개수에서 +1 을 하여
					// 동전의 개수를 증가시켜줌
					// 이 때 동적프로그래밍 방법을 사용하므로 이전의 값을 미리 저장하고 있음


					// 목표 값에 해당하는 배열의 열에 목표 값에서 동전의 값을 뺀 배열의 동전의
					// 개수에 +1 을 하여 목표 값에 대한 동전의 개수를 1 증가시킴
					smallestNumOfCoins[i] = smallestNumOfCoins[i - c[j]] + 1; // 동전의 최소 개수
				}
			}
		}
	}
}