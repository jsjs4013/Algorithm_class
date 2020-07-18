#include <iostream>

using namespace std;

void heapify(int[], int, int);

int main(void)
{
	int A[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };

	for (int i = 10 / 2; i >= 0; i--)
	{
		// heap 생성을 하는 반복문

		heapify(A, 10, i);
	}

	cout << "Heap 생성 결과 : ";
	for (int i = 0; i < 10; i++)
	{
		// 생성된 배열을 출력하는 반복문
		
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