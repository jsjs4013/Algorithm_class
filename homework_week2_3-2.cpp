#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int*, int*);
void quick(int[], int);

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

	quick(N, 10);
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

void quick(int N[], int size)
{
	int start, end, l, r;
	int pivot;
	int* stack = new int[size * 2 + 2]; // stack을 사용하는데 최대 크기가 2n + 2 임
	int push = -1; // 배열을 stack의 LIFO처럼 사용하기 위한 변수

	// LIFO 구조의 배열을 임의로 만들어줌
	stack[++push] = size - 1;
	stack[++push] = 0;

	while (push >= 0)
	{
		// stack이 -1이 되면 즉 push값이 -1이 되면 빠져나옴
		// 그전까지 분할하면서 퀵소트를 수행

		start = stack[push--];
		end = stack[push--];

		if (end - start + 1 > 1)
		{
			// 각 분할된 곳의 값이 2이상이면 실행

			pivot = N[end]; // pivot을 맨 뒤의 숫자로 만들어줌

			l = start; // 비교할 배열의 왼쪽 부분
			r = end - 1; // 비교할 배열의 오른쪽 부분
			while (1)
			{
				// 비교대상이(l과 r) 교차될 때 까지 비교하기위한 반복문

				while (N[l] > pivot) // pivot보다 큰 왼쪽 수를 위한 반복문
					l++;
				while (r > start && N[r] < pivot) // pivot보다 작은 오른쪽 수를 위한 반복문
					r--;

				if (l >= r) // l과 r이 교차되면 반복문을 빠져나감
					break;

				swap(&N[l], &N[r]); // 서로의 값을 바꿔줌

				l++;
				r--;
			}

			// pivot의 자리와 l의 자리를 교환
			N[end] = N[l];
			N[l] = pivot;

			// 재귀대신 반복문을 사용하면 이렇게 해야함
			stack[++push] = end;
			stack[++push] = l + 1; // 여기까지 나누는 부분의 오른쪽 배열 부분
			stack[++push] = l - 1;
			stack[++push] = start; // 여기까지 나누는 부분의 왼쪽 배열 부분
		}
	}

	delete[] stack;
}