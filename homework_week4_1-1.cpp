#include <iostream>
#include <ctime>

using namespace std;

int Minimum(int[], int);
int Maximum(int[], int);

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

	min = Minimum(A, 1000);
	max = Maximum(A, 1000);

	cout << "최소 값 : " << min << endl;
	cout << "최고 값 : " << max << endl;


	return 0;
}

int Minimum(int A[], int n)
{
	int temp; // 제일 작은 값을 저장하는 변수

	temp = A[0]; // 임시로 배열의 제일 첫 값을 저장

	for (int i = 1; i < n; i++)
	{
		// 배열을 처음부터 끝까지 검사해서 최소인 값을 찾는 반복문

		if (temp > A[i])
		{
			// 만약 temp의 값이 A[i]의 값보다 크면
			// 제일 작은 값을 임시로 A[i]로 지정하고
			// temp에 A[i]를 저장

			temp = A[i];
		}
	}

	return temp;
}

int Maximum(int A[], int n)
{
	int temp; // 제일 큰 값을 저장하는 변수

	temp = A[0]; // 임시로 배열의 제일 첫 값을 저장

	for (int i = 1; i < n; i++)
	{
		// 배열을 처음부터 끝까지 검사해서 최소인 값을 찾는 반복문

		if (temp < A[i])
		{
			// 만약 temp의 값이 A[i]의 값보다 작으면
			// 제일 큰 값을 임시로 A[i]로 지정하고
			// temp에 A[i]를 저장

			temp = A[i];
		}
	}

	return temp;
}