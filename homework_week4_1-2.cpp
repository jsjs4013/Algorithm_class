#include <iostream>
#include <ctime>

using namespace std;

void FindMinMax(int[], int, int*, int*);

int main(void)
{
	int A[1000];
	int min, max;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		// 랜덤한 1~100000까지의 값 중 1000개를 배열 A[]에 저장하는 반복문

		int num = rand();

		A[i] = (int)num % 100000 + 1;
	}

	FindMinMax(A, 1000, &min, &max);
	cout << "최소 값 : " << min << endl;
	cout << "최소 값 : " << max << endl;


	return 0;
}

void FindMinMax(int A[], int n, int* min, int* max)
{
	int small, large; // 비교되는 연속된 값 두개 중 작은 값과 큰 값을 저장하는 변수
	*min = A[0];
	*max = A[0];

	for (int i = 1; i < n - 1; i += 2)
	{
		// min과 max가 A[0]부터 비교하므로 i=1부터 n-1까지의 값들을 비교

		if (A[i] < A[i + 1])
		{
			// i번째 배열의 값과 i + 1번째 배열의 값을 비교하여
			// i번째가 작으면 실행되는 조건문

			small = A[i];
			large = A[i + 1];
		}
		else
		{
			// i번째가 크면 실행되는 조건문

			small = A[i + 1];
			large = A[i];
		}

		if (small < *min)
		{
			// 위 조건문에서 찾아진 small값 보다 min값이 크면
			// min값에 small의 값을 저장

			*min = small;
		}
		if (large > *max)
		{
			// 위 조건문에서 찾아진 large값 보다 min값이 크면
			// max값에 large의 값을 저장

			*max = large;
		}
	}
}