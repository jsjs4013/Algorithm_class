#include <iostream>

using namespace std;

void mergeSort(int[], int[], int);

int main(void)
{
	int A[10] = { 30, 20, 40, 35, 5, 50, 45, 10, 25, 15 };
	int sort[10]; // �迭 ������ ���縦 ���� �迭

	mergeSort(A, sort, 10);

	cout << "\n���� ��� �迭 : ";
	for (int i = 0; i < 10; i++)
	{
		// ���ĵ� �迭�� ����ϴ� �ݺ���

		cout << A[i] << " ";
	}
	cout << endl;


	return 0;
}

void mergeSort(int A[], int sort[], int size)
{
	int left, right, sortLocate, last;
	int* tempArr; // A[]�迭�� sort[]�迭�� �Ű��ֱ� ���� �ӽ� ������ ����

	for (int curSize = 1; curSize < size; curSize *= 2)
	{
		// �� ������Ʈ�� ��Ϳ����� ���� ���� ������ �������� ó���� �� ����
		// ���ϰ� �������� 4���� ���ϰ� �ϴ� ������� �ݺ����� ������
		// ���� �񱳴���� 2�辿 ������

		left = 0;
		right = 0;
		sortLocate = 0;
		last = curSize;

		while(sortLocate < size)
		{
			// ���� �迭��(sort) ������ ��ġ�� size���� ������ ��� ����
			// ���� �迭��(sort) ������ �����ϸ� �ݺ����� Ż����

			for (int i = 0; i < (curSize * 2) && sortLocate < size; i++)
			{
				if (left < last && right < last)
				{
					// ����Լ������� ���������� ���ʰ� ���������� ������ ��

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
					// ���� �������� ��� �񱳵Ǹ� ������ ���� ���ҵ���
					// ���� �迭�� ����

					sort[sortLocate] = A[left];
					left++;
				}
				else
				{
					// ���� ������ ��� �񱳵Ǹ� ������ ������ ���ҵ���
					// ���� �迭�� ����

					sort[sortLocate] = A[curSize + right];
					right++;
				}
				sortLocate++; // ���� �迭�� ���� ��ġ�� 1�� ������Ŵ
			}

			// for() �ݺ����� �� �������� ���� �ݺ����� �� ��ġ�� ���ϴ� �κ�
			left += curSize;
			right += curSize;
			last += (curSize * 2);
		}

		// ����� �Էµ� �迭�� ġȯ�ϰ� ���� ũ���� �迭��
		// ������Ʈ�� �����ϱ� ���� �غ����
		tempArr = A;
		A = sort;
		sort = tempArr;

		cout << "���� �迭 : ";
		for (int i = 0; i < 10; i++)
		{
			// �Ź� �ݺ����� ���۸� ����ϱ� ���� �ݺ���

			cout << sort[i] << " ";
		}
		cout << endl;
	}
}