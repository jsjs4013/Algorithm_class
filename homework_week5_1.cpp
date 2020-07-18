#include <iostream>

using namespace std;

typedef struct Map
{
	int right; // Map struct�� right
	int down; // Map struct�� left
}Map;

void dp(Map[][5], int[][5]);

int main(void)
{
	// Map struct�� map������ ����� ���� ǥ����
	// struct �迭�� [5][5] �� �迭�� ����
	Map map[5][5] = { { {3, 1}, {2, 0}, {4, 2}, {0, 4}, {-1, 3} },
					{ {3, 4}, {2, 6}, {4, 5}, {1, 2}, {-1, 1} },
					{ {0, 4}, {7, 4}, {3, 5}, {4, 2}, {-1, 1} },
					{ {3, 5}, {3, 6}, {0, 8}, {2, 5}, {-1, 3} },
					{ {1, -1}, {3, -1}, {2, -1}, {2, -1}, {-1, -1} } };
	int mapResult[5][5] = { 0 }; // ��� ���� �����ϴ� �迭

	dp(map, mapResult);

	for (int i = 0; i < 5; i++)
	{
		// ���� ���� �迭�� ��� ����ϴ� �ݺ���

		for (int j = 0; j < 5; j++)
		{
			cout << mapResult[i][j] << "\t";
		}
		cout << endl;
	}

	return 0;
}

void dp(Map map[][5], int mapResult[][5])
{
	int temp1 = 0;
	int temp2 = 0;

	for (int i = 1; i < 5; i++)
	{
		// ���� 1���� ���� ��� ����

		mapResult[0][i] = mapResult[0][i - 1] + map[0][i - 1].right;
	}
	for (int i = 1; i < 5; i++)
	{
		// 1���� ���� ��� ����
		// ���� �� �ݺ����� ���� ���� ���ϴ� ��

		mapResult[i][0] = mapResult[i - 1][0] + map[i - 1][0].down;
	}

	for (int i = 1; i < 5; i++)
	{
		// right�� down�� ���� ���� ����� ���� ���Ͽ�
		// �� ū ���� ���ο� �迭�� �����ϴ� �ݺ���

		for (int j = 1; j < 5; j++)
		{
			temp1 = mapResult[i - 1][j] + map[i - 1][j].down;
			temp2 = mapResult[i][j - 1] + map[i][j - 1].right;

			// ���׿����ڸ� ����Ͽ� �� ū ���� ����
			mapResult[i][j] = temp1 > temp2 ? temp1 : temp2;
		}
	}
}