#include <iostream>

using namespace std;

typedef struct Map
{
	int right; // Map struct의 right
	int down; // Map struct의 left
}Map;

void dp(Map[][5], int[][5]);

int main(void)
{
	// Map struct의 map변수를 만들어 맵을 표현함
	// struct 배열을 [5][5] 의 배열로 만듦
	Map map[5][5] = { { {3, 1}, {2, 0}, {4, 2}, {0, 4}, {-1, 3} },
					{ {3, 4}, {2, 6}, {4, 5}, {1, 2}, {-1, 1} },
					{ {0, 4}, {7, 4}, {3, 5}, {4, 2}, {-1, 1} },
					{ {3, 5}, {3, 6}, {0, 8}, {2, 5}, {-1, 3} },
					{ {1, -1}, {3, -1}, {2, -1}, {2, -1}, {-1, -1} } };
	int mapResult[5][5] = { 0 }; // 결과 값을 저장하는 배열

	dp(map, mapResult);

	for (int i = 0; i < 5; i++)
	{
		// 구한 값의 배열을 모두 출력하는 반복문

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
		// 먼저 1행의 값을 모두 더함

		mapResult[0][i] = mapResult[0][i - 1] + map[0][i - 1].right;
	}
	for (int i = 1; i < 5; i++)
	{
		// 1열의 값을 모두 더함
		// 위와 본 반복문은 기준 값을 구하는 것

		mapResult[i][0] = mapResult[i - 1][0] + map[i - 1][0].down;
	}

	for (int i = 1; i < 5; i++)
	{
		// right와 down를 각각 이전 노드의 값에 더하여
		// 더 큰 값을 새로운 배열에 저장하는 반복문

		for (int j = 1; j < 5; j++)
		{
			temp1 = mapResult[i - 1][j] + map[i - 1][j].down;
			temp2 = mapResult[i][j - 1] + map[i][j - 1].right;

			// 삼항연산자를 사용하여 더 큰 값을 저장
			mapResult[i][j] = temp1 > temp2 ? temp1 : temp2;
		}
	}
}