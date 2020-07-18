#include <iostream>

using namespace std;

typedef struct Map
{
	int right; // Map struct의 right
	int down; // Map struct의 left
}Map;

void greedyAlgo(Map[][5]);

int main(void)
{
	// Map struct의 map변수를 만들어 맵을 표현함
	// struct 배열을 [5][5] 의 배열로 만듦
	Map map[5][5] = { { {3, 1}, {2, 0}, {4, 2}, {0, 4}, {-1, 3} },
					{ {3, 4}, {2, 6}, {4, 5}, {1, 2}, {-1, 1} },
					{ {0, 4}, {7, 4}, {3, 5}, {4, 2}, {-1, 1} },
					{ {3, 5}, {3, 6}, {0, 8}, {2, 5}, {-1, 3} },
					{ {1, -1}, {3, -1}, {2, -1}, {2, -1}, {-1, -1} } };

	greedyAlgo(map);


	return 0;
}

void greedyAlgo(Map map[][5])
{
	// Greedy algorithm을 만들어주는 함수

	// for반복문에서 j의 위치를 바꾸기 위한 변수
	// 바꾸는 이유는 맵은 오른쪽과 아래로밖에 향하지 못하므로
	// 아래로 내려가면 왼쪽으로의 이동이 불가능하기 때문
	int way = 0;

	for (int i = 0; i < 5; i++)
	{
		// 맵 탐색의 아래로의 반복문

		for (int j = way; j < 5; j++)
		{
			// 맵 탐색의 오른쪽으로의 반복문

			cout << "Map[" << j << "][" << i << "]" << endl; // 현재 위치를 경로로서 출력

			if (map[i][j].right < map[i][j].down)
			{
				// greedy 알고리즘을 만들어주는것이므로 right와 down중
				// right가 작으면 큰 down으로의 움직임이 있어야하며
				// 이 조건문에서 그것을 실행함
				// 이 외의 경우는 오른쪽 이동이기 때문에 별도의 조건문이 필요없음

				way = j; // 아래로 내려갔을 때 수평탐색의 최소의 탐색 위치

				break; // 아래로의 이동을 위하여 두 번째 for 반복문을 빠져나감
			}
		}
	}
}