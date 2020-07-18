#include <iostream>

using namespace std;

void heapify(int[], int, int);
void heapSort(int[], int);

int main(void)
{
	int A[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };

	for (int i = 10 / 2; i >= 0; i--)
	{
		// heap 생성을 하는 반복문

		heapify(A, 10, i);
	}
	heapSort(A, 10);

	cout << "Heap 정렬 결과 : ";
	for (int i = 0; i < 10; i++)
	{
		// 정렬된 배열을 출력하는 반복문

		cout << A[i] << " ";
	}

	return 0;
}

void heapify(int A[], int size, int root)
{
	int cur; // 현재 tree에서 위치하는 인덱스 번호
	int temp;


	cur = root * 2 + 1; // 현재 root의 왼쪽 자식 node를 의미

	if (cur < size && A[cur] < A[cur + 1])
	{
		// root node의 자식 값 중에 오른쪽 자식이 더 크면 cur의 1 올려줌

		cur++;
	}

	if (cur < size && A[root] < A[cur])
	{
		// root의 값보다 현재 node의 값이 크면 큰 값을 위로 보내야 하므로
		// root node의 값과 현재 node인 자식 node의 값을 바꿈

		temp = A[root];
		A[root] = A[cur];
		A[cur] = temp;
	}

	if (cur <= size / 2)
	{
		// node의 값이 한번만 바뀌는게 아니라 그 아래에
		// 연결 된 node와의 비교도 해야하므로 재귀함수를 사용

		heapify(A, size, cur);
	}
}

void heapSort(int A[], int size)
{
	int cur;
	int root;
	int temp;

	for (int i = size - 1; i >= 0; i--)
	{
		// root node와 가장 마지막 node를 바꿔줌
		temp = A[0];
		A[0] = A[i];
		A[i] = temp;

		root = 0;
		cur = 1; // root는 0이므로 바로 다음 값을 의미

		while (cur < i)
		{
			// 여기서 i는 가장 마지막 node

			cur = root * 2 + 1; // root node의 자식을 찾음

			if (A[cur] < A[cur + 1] && cur < i - 1)
			{
				// root node의 자식 값 중에 오른쪽 자식이 더 크면 cur의 1 올려줌

				cur++;
			}
			if (A[root] < A[cur] && cur < i)
			{
				// root의 값보다 현재 node의 값이 크면 큰 값을 위로 보내야 하므로
				// root node의 값과 현재 node인 자식 node의 값을 바꿈

				temp = A[root];
				A[root] = A[cur];
				A[cur] = temp;
			}
			root = cur; // root를 cur로 바꿈으로서 root의 root도 연쇄적으로 비교가능하게 함
		}
	}
}