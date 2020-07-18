#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int*, int*);
void bubble(int[], int);
void quick(int[], int);

int main(void)
{
	int N[10]; // 랜덤한 값 10개를 받는 배열
	int K[1000]; // 랜덤한 값 1000개를 받는 배열

	clock_t start, end;
	double result_bubble, result_quick;

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

	// time함수를 쓰면 함수가 너무빨리끝나 측정을 못하여 clock()함수를 사용
	start = clock();
	bubble(K, 1000);
	end = clock();
	result_bubble = (double)(end - start);

	start = clock();
	quick(K, 1000);
	end = clock();
	result_quick = (double)(end - start);

	cout << "버블정렬이 실행되는데 걸린시간 : " << result_bubble / CLOCKS_PER_SEC << endl;
	cout << "퀵정렬이 실행되는데 걸린시간 : " << result_quick / CLOCKS_PER_SEC << endl;


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
				while (r > start&& N[r] < pivot) // pivot보다 작은 오른쪽 수를 위한 반복문
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