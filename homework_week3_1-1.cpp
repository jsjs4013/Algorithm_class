#include <iostream>

using namespace std;

void merge(int[], int, int, int, int[]);
void mergeSort(int[], int, int, int[]);

int main(void)
{
	int A[10] = { 30, 20, 40, 35, 5, 50, 45, 10, 25, 15 };
	int sort[10]; // 배열 값들의 복사를 위한 배열

	mergeSort(A, 0, 9, sort);

	cout << "\n최종 결과 배열 : ";
	for (int i = 0; i < 10; i++)
	{
		// 정렬된 배열을 출력하는 반복문

		cout << A[i] << " ";
	}
	cout << endl;

	return 0;
}

void merge(int A[], int l, int m, int r, int sort[])
{
	int i, j, k;

	i = l; // 논리적으로 분할된 배열을 합병하기 위해 필요한 변수
	j = m + 1; // 분리된 배열 중 오른쪽 배열의 첫 번째를 위한 변수
	k = l; // 새로만들어지는 배열에 필요한 변수

	while (i <= m && j <= r)
	{
		// 분할된 배열의 합병을 위한 반복문

		if (A[i] <= A[j])
		{
			sort[k] = A[i];

			k++;
			i++;
		}
		else
		{
			sort[k] = A[j];

			k++;
			j++;
		}
	}

	if (i > m)
	{
		// 남아있는 값들을 복사하는 조건문
		// 이 경우에는 오른쪽 배열의 값이 남아있는 경우

		for (int h = j; h <= r; h++)
		{
			sort[k] = A[h];

			k++;
		}
	}
	else
	{
		// 남아있는 값들을 복사하는 조건문
		// 이 경우에는 오른쪽 배열의 값이 남아있는 경우

		for (int h = i; h <= m; h++)
		{
			sort[k] = A[h];

			k++;
		}
	}

	for (int h = l; h <= r; h++)
	{
		// 배열 sort[]의 값을 A[]배열로 복사하는 반복문

		A[h] = sort[h];
	}

	for (int h = l; h <= r; h++)
	{
		// 매번 반복마다 버퍼를 출력하기 위한 반복문

		cout << sort[h] << " ";
	}
	cout << endl;
}

void mergeSort(int A[], int l, int r, int sort[])
{
	int m; // 배열을 나누기위해 중간 값을 저장하는 변수

	if (l < r)
	{
		// 배열의 길이가 1이상이면 실행되는 조건문

		m = (l + r) / 2; // 중간 값을 구함

		mergeSort(A, l, m, sort); // 왼쪽 부분 배열의 퀀쿼
		mergeSort(A, m + 1, r, sort); // 오른쪽 부분 배열의 퀀쿼
		merge(A, l, m, r, sort); // 위에서 만들어진 두 개의 값을 합치는 함수
	}
}