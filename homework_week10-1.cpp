#include <iostream>
#include <vector>

using namespace std;

void inititial(vector<string> s, int** maps, bool* visit);
void inputData(vector<string> s, int** maps, int same);
int findEnd(vector<string> s, int** maps);
void hemilton(vector<string> s, vector<int> stack, int same, bool* visit, int** maps);

int main(void)
{
	int same, start, end;
	vector<string>s;
	vector<int>stack;

	/*
	same = 2;
	s.push_back("AGT");
	s.push_back("AAA");
	s.push_back("ACT");
	s.push_back("AAC");

	s.push_back("CTT");
	s.push_back("GTA");
	s.push_back("TTT");
	s.push_back("TAA");
	*/

	/*
	same = 2;
	s.push_back("ATG");
	s.push_back("AGG");
	s.push_back("TGC");
	s.push_back("TCC");

	s.push_back("GTC");
	s.push_back("GGT");
	s.push_back("GCA");
	s.push_back("CAG");
	*/

	/*
	same = 2;
	s.push_back("ATG");
	s.push_back("TGG");
	s.push_back("TGC");
	s.push_back("GTG");

	s.push_back("GGC");
	s.push_back("GCA");
	s.push_back("GCG");
	s.push_back("CGT");
	*/

	/*
	same = 3;
	s.push_back("ATGC");
	s.push_back("TGCG");
	s.push_back("GCGG");
	s.push_back("CGGC");

	s.push_back("GGCT");
	s.push_back("GCTG");
	s.push_back("CTGT");
	s.push_back("TGTA");

	s.push_back("GTAT");
	s.push_back("TATG");
	s.push_back("ATGG");
	s.push_back("TGGT");
	s.push_back("GGTG");
	*/

	/*
	same = 2;
	s.push_back("ATG");
	s.push_back("GGT");
	s.push_back("GTG");
	s.push_back("TAT");

	s.push_back("TGC");
	s.push_back("TGG");
	*/

	/*
	same = 2;
	s.push_back("TAT");
	s.push_back("ATG");
	s.push_back("TGG");
	s.push_back("GGT");

	s.push_back("GTG");
	s.push_back("TGC");
	*/

	same = 2;
	// 내가 지정한 스펙트럼
	s.push_back("AGT");
	s.push_back("GTT");
	s.push_back("TTA");
	s.push_back("TAA");

	s.push_back("AAC");
	s.push_back("ACA");
	s.push_back("CAT");
	s.push_back("ATC");


	int** maps;
	maps = new int* [s.size()];
	bool* visit = new bool[s.size()];

	hemilton(s, stack, same, visit, maps);


	return 0;
}

void inititial(vector<string> s, int** maps, bool* visit, int check)
{
	// 처음에 값들을 생성하고 초기화하는 함수

	if (check == 0)
	{
		// 헤밀턴 패스는 여러번 반복할 수 있으므로
		// 처음만 동적으로 변수를 생성하기 위한 부분

		for (int i = 0; i < s.size(); i++)
		{
			// 그래프를 행렬을 통해 나타내기 위한
			// 입력받은 값의 개수의 제곱 만큼 배열을 생성해 주는 반복문
			// 즉 입력받은 값이 8이라면 8 * 8 행렬을 만들어 줌

			maps[i] = new int[s.size()];
		}
	}

	for (int i = 0; i < s.size(); i++)
	{
		// 그래프를 나타내는 행렬과 visit을 나타내는 변수를
		// 0과 false로 초기화 하는 반복문

		visit[i] = false;

		for (int j = 0; j < s.size(); j++)
		{
			maps[i][j] = 0;
		}
	}
}

void inputData(vector<string> s, int** maps, int same)
{
	// 행렬로 나타낸 그래프간의 연결을 만들어주기 위한 함수

	int count = 0; // 행렬의 열에 해당하는 변수
	int countRow = -1; // 행렬의 행에 해당하는 변수

	for (int i = 0; i < s.size() * s.size(); i++)
	{
		// 입력받은 값들의 개수의 제곱만큼을 반복문으로 반복
		// 반복문을 실행하면서 각 값들에 대해 same값 만큼
		// 연속적으로 일치하는 값들 끼리 연결함

		count++;
		if (i == 0 || count == s.size())
		{
			// 처음 반복과 각 값이 다 돌게 되면 새로운 값을 기준으로
			// 반복을 할 수 있게 만들어주는 부분

			count = 0;
			countRow++;
		}


		if (count != countRow)
		{
			// 같은 값에는 연결이 없으므로 그렇게 되도록 실행하는 조건문

			int check = 0; // 이 값이 same이랑 같으면 연속적으로 같은 값이 있다는 의미임

			for (int j = 0; j < same; j++)
			{
				// 기준이 되는 값과 비교하려는 값이 연속적으로 same개수 만큼 일치하는지
				// 확인하는 반복문

				if (s[countRow][j + 1] == s[count][j])
					check++;
			}

			if (check == same)
			{
				// same이랑 check랑 같으므로 그래프의 연결을 만들어 주게 됨

				maps[countRow][count] = 1;
			}
		}
	}
}

int findEnd(vector<string> s, int** maps)
{
	// 그래프의 연결되는 값 중 마지막에 해당하는 값을 찾아주는 함수

	int count;
	int end;

	for (int i = 0; i < s.size(); i++)
	{
		// 0부터 입력된 값의 개수만큼 반복함
		// 반복문을 실행하면서 아무것도 연결하지 않는 vertex를 찾음
		// 그러면 그 vertex가 연결의 끝이 될 값이 됨

		count = 0;
		for (int j = 0; j < s.size(); j++)
		{
			if (maps[i][j] == 1)
				count++;
		}

		if (count == 0)
		{
			// 연결을 아무것도 하지 않은 vertex인 i값이 end가 됨

			end = i;

			break;
		}
	}

	return end;
}

void dfs(vector<string> s, vector<int> stack, int start, int end, int same, bool* visit, int** maps)
{
	// start부터 end까지의 모든 경로를 구하는 dfs 함수

	visit[start] = true; // 방문하는 그래프의 vertex를 ture로 만들어줌
	stack.push_back(start); // 그 방문한 vertex를 stack에 push함

	if (start == end)
	{
		// 목표 노드에 도착하면 실행하는 조건문

		int size = stack.size(); // stack의 크기를 저장할 변수
		if (size == s.size())
		{
			// stack의 크기와 입력받은 값들의 개수가 같으면 실행하는 조건문
			// 다르면 모든 vertex를 순회한 것이 아니므로 다른 경로를 찾게 됨

			for (int i = 0; i < size; i++)
			{
				// stack의 값을 출력할 반복문

				if (i == 0)
				{
					// 첫 시작의 값은 모든 값이 다 출력되어야 하므로
					// 조건문으로 나누어 줌

					for (int j = 0; j < same + 1; j++)
					{
						cout << s[stack[i]][j];
					}
				}
				else
				{
					// 두 번째 부터는 끝 값만 출력해줌

					cout << s[stack[i]][same];
				}
			}
			cout << "\n" << endl;
		}

		stack.pop_back(); // DFS에서 빠져나올 때 pop을 함

		return;
	}

	for (int i = 0; i < s.size(); i++)
	{
		if (maps[start][i] == 1 && !visit[i])
		{
			// 그래프가 이어져있고 방문을 하지 않았다면 실행하는 부분

			dfs(s, stack, i, end, same, visit, maps);
			visit[i] = false; // DFS에서 빠져나오면 이 vertex는 방문하지 않은 것으로 함
			// 그래야 새로운 경로를 찾을 수 있음
		}
	}

	stack.pop_back(); // DFS에서 빠져나올 때 pop을 함
}

void hemilton(vector<string> s, vector<int> stack, int same, bool* visit, int** maps)
{
	int end;

	inititial(s, maps, visit, 0);
	inputData(s, maps, same);
	end = findEnd(s, maps);
	
	for (int start = 0; start < s.size(); start++)
	{
		// 헤밀턴 패스는 start의 값을 모든 경우에 대하여 대입해야 하므로
		// 반복문을 실행하여 end값 제외하고 모든 값을 start로 하고 실행

		if (start != end)
		{
			// 시작 값과 끝 값이 다르면 실행

			if (start == 0)
			{
				// 첫 시작인 경우 위에서 초기화를 해주므로 dfs()만 실행

				dfs(s, stack, start, end, same, visit, maps);
			}
			else
			{
				// 두 번째 시작부터 새로운 초기화와 그래프 초기화를 실행

				inititial(s, maps, visit, start);
				inputData(s, maps, same);

				dfs(s, stack, start, end, same, visit, maps);
			}
		}
	}
}