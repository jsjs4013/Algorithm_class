#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int*, int*);
void bubble(int[], int);

int main(void)
{
	int N[10]; // 랜덤한 값 10개를 받는 배열
	int K[1000]; // 랜덤한 값 1000개를 받는 배열

	// 매번 rand()의 값을 다르게 하기위해 srand()와 time()을 사용하여 seed를 다르게 해줌
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		// 랜덤한 1~10000까지의 값 중 10개를 배열 N[]에 저장하는 반복문

		int num = rand();

		N[i] = (int)num % 10000 + 1;
	}
	for (int i = 0; i < 1000; i++)
	{
		// 랜덤한 1~10000까지의 값 중 1000개를 배열 K[]에 저장하는 반복문

		int num = rand();

		K[i] = (int)num % 10000 + 1;
	}

	bubble(N, 10);
	for (int i = 0; i < 10; i++) // 내림차순으로 정렬이 되었는지 출력해주는 반복문
		cout << N[i] << endl;

	
	return 0;
}

void swap(int* a, int* b)
{
	// 들어온 값인 a, b를 변환해주는 함수

	int temp = *a;

	*a = *b;
	*b = temp;
}

void bubble(int N[], int size)
{
	if (size == 1) // size의 크기가 1이되면 비교할 것이 없으므로 끝냄
		return;

	for (int i = 0; i < size - 1; i++)
	{
		// 버블소트의 한 사이클을 진행하는 반복문

		if (N[i] < N[i + 1])
		{
			// 내림차순 정렬이므로 현재와 다음의 값을 비교하여
			// 현재 값이 더 작으면 현재 값과 다음 값을 변환하여야 함

			swap(&N[i], &N[i + 1]);
		}
	}

	bubble(N, size - 1); // 재귀호출
}