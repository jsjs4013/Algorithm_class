#include <iostream>

using namespace std;

void mergeSort(int[], int[], int);

int main(void)
{
	int A[10] = { 30, 20, 40, 35, 5, 50, 45, 10, 25, 15 };
	int sort[10]; // 배열 값들의 복사를 위한 배열

	mergeSort(A, sort, 10);

	cout << "\n최종 결과 배열 : ";
	for (int i = 0; i < 10; i++)
	{
		// 정렬된 배열을 출력하는 반복문

		cout << A[i] << " ";
	}
	cout << endl;


	return 0;
}

void mergeSort(int A[], int sort[], int size)
{
	int left, right, sortLocate, last;
	int* tempArr; // A[]배열을 sort[]배열에 옮겨주기 위한 임시 포인터 변수

	for (int curSize = 1; curSize < size; curSize *= 2)
	{
		// 본 머지소트도 재귀에서와 같이 제일 밑으로 내려가면 처음에 두 개씩
		// 비교하고 다음으로 4개를 비교하고 하는 방법으로 반복문을 구성함
		// 따라서 비교대상이 2배씩 많아짐

		left = 0;
		right = 0;
		sortLocate = 0;
		last = curSize;

		while(sortLocate < size)
		{
			// 더미 배열의(sort) 원소의 위치가 size보다 작으면 계속 실행
			// 더미 배열을(sort) 끝까지 저장하면 반복문을 탈출함

			for (int i = 0; i < (curSize * 2) && sortLocate < size; i++)
			{
				if (left < last && right < last)
				{
					// 재귀함수에서와 마찬가지로 왼쪽과 오른쪽으로 나눠서 비교

					if (curSize + right < size && A[left] > A[curSize + right])
					{
						sort[sortLocate] = A[curSize + right];
						right++;
					}
					else
					{
						sort[sortLocate] = A[left];
						left++;
					}
				}
				else if (left < last)
				{
					// 먼저 오른쪽이 모두 비교되면 나머지 왼쪽 원소들을
					// 더미 배열에 저장

					sort[sortLocate] = A[left];
					left++;
				}
				else
				{
					// 먼저 왼쪽이 모두 비교되면 나머지 오른쪽 원소들을
					// 더미 배열에 저장

					sort[sortLocate] = A[curSize + right];
					right++;
				}
				sortLocate++; // 더미 배열의 현재 위치를 1씩 증가시킴
			}

			// for() 반복문이 다 돌았으면 다음 반복문이 돌 위치를 정하는 부분
			left += curSize;
			right += curSize;
			last += (curSize * 2);
		}

		// 결과와 입력된 배열을 치환하고 다음 크기의 배열로
		// 머지소트를 수행하기 위한 준비과정
		tempArr = A;
		A = sort;
		sort = tempArr;

		cout << "더미 배열 : ";
		for (int i = 0; i < 10; i++)
		{
			// 매번 반복마다 버퍼를 출력하기 위한 반복문

			cout << sort[i] << " ";
		}
		cout << endl;
	}
}