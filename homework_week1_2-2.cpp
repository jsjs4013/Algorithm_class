#include <iostream>

using namespace std;

int BruteForceChange(int, int[], int, int[], int, int[], int);

int main(void)
{
	int d; // 동전의 개수를 입력받는 변수
	int m = 40; // 총 값인 M값
	int smallestNumOfCoins; // 제일 작은 동전의 개수를 저장하는 변수

	cout << "코인의 개수 : ";
	cin >> d;

	int* c = new int[d]; // 개수가 d개만큼 동적할당 되는 동전의 종류를 담는 변수
	cout << "코인을 입력 : ";
	for (int i = 0; i < d; i++)
		cin >> c[i];

	int* bestChange = new int[d]; // 동전의 개수만큼 동적할당되는 최고의 동전별 개수를 담는 변수
	for (int i = 0; i < d; i++)
		bestChange[i] = 0;

	int* tempNum = new int[d]; // BruteForceChange() 함수에서 사용되는 현재 위치를 나타내는 변수
	for (int i = 0; i < d; i++)
		tempNum[i] = 0;


	smallestNumOfCoins = BruteForceChange(m, c, d, bestChange, INT_MAX, tempNum, -1);
	
	cout << "최고의 결과 :" << endl;
	for (int i = 0; i < d; i++)
		cout << c[i] << " : " << bestChange[i] << endl;
	cout << "smallestNumberOfCoins : " << smallestNumOfCoins << endl;


	return 0;
}

int BruteForceChange(int m, int c[], int d, int bestChange[], int smallestNumberOfCoins, int tempNum[], int here)
{
	int numberOfCoins; // Coin의 수를 나타내는 변수
	int valueOfCoins; // 사용한 동전을 이용하여 현재 값을 알아내는 변수
	int* k = new int[d]; // 각 동전별로 최종 몇개가 쓰일지를 저장하는 변수

	here += 1; // 재귀함수로 함수가 도는데 현재 몇 번째 위치인지를 알려주는 변수
	for (int i = 0; i < d; i++)
	{
		// 각 동전의 종류가 최고 몇개까지 쓰일 수 있는지를
		// 확인하는 반복문이며 각 값을 k[i]배열에 저장

		k[i] = m / c[i];
	}
	
	
	for (int i = 0; i <= k[here]; i++)
	{
		// 동전의 개수에 상관없이 모든 값을 참조할 수 있도록 재귀를 사용하는 반복문
		// 재귀함수 방법을 사용하여 수도코드에서 만들어진것과 같은 반복문 효과를 만들어내게 됨

		if (here == d - 1)
		{
			// 마지막 동전위치가 되었을 때 반복문을 모두 돌아 최소값을 찾아내는 부분

			valueOfCoins = 0; // 계산을 위해 첫 초기화값을 0으로 만듦
			for (int j = 0; j < here; j++)
				valueOfCoins += tempNum[j] * c[j]; // 각 값을 동전의 종류에 곱하여 계산
			valueOfCoins += i * c[here]; // 마지막 값은 현재 함수에 위치하므로 따로 i로 계산

			if (valueOfCoins == m)
			{
				// 만약 계산된 값이 M의 값과 같다면 최소의 동전을 사용했는지를 계산

				numberOfCoins = 0;
				for (int j = 0; j < here; j++)
					numberOfCoins += tempNum[j]; // 동전을 몇개 썼는지를 확인하는 부분
				numberOfCoins += i;

				if (numberOfCoins < smallestNumberOfCoins)
				{
					// 만약 최소의 동전을 사용했다면 smallestNumberOfCoins변수가 업데이트 됨

					for (int j = 0; j < here; j++)
						bestChange[j] = tempNum[j]; // 최소의 동전을 사용하는 동전의 종류별 개수를 업데이트 함
					bestChange[here] = i;

					smallestNumberOfCoins = numberOfCoins;
				}
			}
		}
		else
		{
			// 제일 마지막 동전이 아니라면 새로운 BruteForceChange()함수를 불러 재귀형식이 되게함
			// 해서 반복문 안의 반복문의 형식이 되게끔 만들게 됨

			tempNum[here] = i; // 현재 위치에 해당하는 반복문의 i값을 tempNum변수에 저장하고 다음 함수실행 시 넣어줌
			smallestNumberOfCoins = BruteForceChange(m, c, d, bestChange, smallestNumberOfCoins,tempNum , here);
		}
	}
	tempNum[here] = 0; // 모든 값을 돌기 위하여 현재 위치에 해당하는 반복 i값을 0으로 만들어줌
	

	return smallestNumberOfCoins;
}