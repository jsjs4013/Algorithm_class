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
	// ���� ������ ����Ʈ��
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
	// ó���� ������ �����ϰ� �ʱ�ȭ�ϴ� �Լ�

	if (check == 0)
	{
		// ����� �н��� ������ �ݺ��� �� �����Ƿ�
		// ó���� �������� ������ �����ϱ� ���� �κ�

		for (int i = 0; i < s.size(); i++)
		{
			// �׷����� ����� ���� ��Ÿ���� ����
			// �Է¹��� ���� ������ ���� ��ŭ �迭�� ������ �ִ� �ݺ���
			// �� �Է¹��� ���� 8�̶�� 8 * 8 ����� ����� ��

			maps[i] = new int[s.size()];
		}
	}

	for (int i = 0; i < s.size(); i++)
	{
		// �׷����� ��Ÿ���� ��İ� visit�� ��Ÿ���� ������
		// 0�� false�� �ʱ�ȭ �ϴ� �ݺ���

		visit[i] = false;

		for (int j = 0; j < s.size(); j++)
		{
			maps[i][j] = 0;
		}
	}
}

void inputData(vector<string> s, int** maps, int same)
{
	// ��ķ� ��Ÿ�� �׷������� ������ ������ֱ� ���� �Լ�

	int count = 0; // ����� ���� �ش��ϴ� ����
	int countRow = -1; // ����� �࿡ �ش��ϴ� ����

	for (int i = 0; i < s.size() * s.size(); i++)
	{
		// �Է¹��� ������ ������ ������ŭ�� �ݺ������� �ݺ�
		// �ݺ����� �����ϸ鼭 �� ���鿡 ���� same�� ��ŭ
		// ���������� ��ġ�ϴ� ���� ���� ������

		count++;
		if (i == 0 || count == s.size())
		{
			// ó�� �ݺ��� �� ���� �� ���� �Ǹ� ���ο� ���� ��������
			// �ݺ��� �� �� �ְ� ������ִ� �κ�

			count = 0;
			countRow++;
		}


		if (count != countRow)
		{
			// ���� ������ ������ �����Ƿ� �׷��� �ǵ��� �����ϴ� ���ǹ�

			int check = 0; // �� ���� same�̶� ������ ���������� ���� ���� �ִٴ� �ǹ���

			for (int j = 0; j < same; j++)
			{
				// ������ �Ǵ� ���� ���Ϸ��� ���� ���������� same���� ��ŭ ��ġ�ϴ���
				// Ȯ���ϴ� �ݺ���

				if (s[countRow][j + 1] == s[count][j])
					check++;
			}

			if (check == same)
			{
				// same�̶� check�� �����Ƿ� �׷����� ������ ����� �ְ� ��

				maps[countRow][count] = 1;
			}
		}
	}
}

int findEnd(vector<string> s, int** maps)
{
	// �׷����� ����Ǵ� �� �� �������� �ش��ϴ� ���� ã���ִ� �Լ�

	int count;
	int end;

	for (int i = 0; i < s.size(); i++)
	{
		// 0���� �Էµ� ���� ������ŭ �ݺ���
		// �ݺ����� �����ϸ鼭 �ƹ��͵� �������� �ʴ� vertex�� ã��
		// �׷��� �� vertex�� ������ ���� �� ���� ��

		count = 0;
		for (int j = 0; j < s.size(); j++)
		{
			if (maps[i][j] == 1)
				count++;
		}

		if (count == 0)
		{
			// ������ �ƹ��͵� ���� ���� vertex�� i���� end�� ��

			end = i;

			break;
		}
	}

	return end;
}

void dfs(vector<string> s, vector<int> stack, int start, int end, int same, bool* visit, int** maps)
{
	// start���� end������ ��� ��θ� ���ϴ� dfs �Լ�

	visit[start] = true; // �湮�ϴ� �׷����� vertex�� ture�� �������
	stack.push_back(start); // �� �湮�� vertex�� stack�� push��

	if (start == end)
	{
		// ��ǥ ��忡 �����ϸ� �����ϴ� ���ǹ�

		int size = stack.size(); // stack�� ũ�⸦ ������ ����
		if (size == s.size())
		{
			// stack�� ũ��� �Է¹��� ������ ������ ������ �����ϴ� ���ǹ�
			// �ٸ��� ��� vertex�� ��ȸ�� ���� �ƴϹǷ� �ٸ� ��θ� ã�� ��

			for (int i = 0; i < size; i++)
			{
				// stack�� ���� ����� �ݺ���

				if (i == 0)
				{
					// ù ������ ���� ��� ���� �� ��µǾ�� �ϹǷ�
					// ���ǹ����� ������ ��

					for (int j = 0; j < same + 1; j++)
					{
						cout << s[stack[i]][j];
					}
				}
				else
				{
					// �� ��° ���ʹ� �� ���� �������

					cout << s[stack[i]][same];
				}
			}
			cout << "\n" << endl;
		}

		stack.pop_back(); // DFS���� �������� �� pop�� ��

		return;
	}

	for (int i = 0; i < s.size(); i++)
	{
		if (maps[start][i] == 1 && !visit[i])
		{
			// �׷����� �̾����ְ� �湮�� ���� �ʾҴٸ� �����ϴ� �κ�

			dfs(s, stack, i, end, same, visit, maps);
			visit[i] = false; // DFS���� ���������� �� vertex�� �湮���� ���� ������ ��
			// �׷��� ���ο� ��θ� ã�� �� ����
		}
	}

	stack.pop_back(); // DFS���� �������� �� pop�� ��
}

void hemilton(vector<string> s, vector<int> stack, int same, bool* visit, int** maps)
{
	int end;

	inititial(s, maps, visit, 0);
	inputData(s, maps, same);
	end = findEnd(s, maps);
	
	for (int start = 0; start < s.size(); start++)
	{
		// ����� �н��� start�� ���� ��� ��쿡 ���Ͽ� �����ؾ� �ϹǷ�
		// �ݺ����� �����Ͽ� end�� �����ϰ� ��� ���� start�� �ϰ� ����

		if (start != end)
		{
			// ���� ���� �� ���� �ٸ��� ����

			if (start == 0)
			{
				// ù ������ ��� ������ �ʱ�ȭ�� ���ֹǷ� dfs()�� ����

				dfs(s, stack, start, end, same, visit, maps);
			}
			else
			{
				// �� ��° ���ۺ��� ���ο� �ʱ�ȭ�� �׷��� �ʱ�ȭ�� ����

				inititial(s, maps, visit, start);
				inputData(s, maps, same);

				dfs(s, stack, start, end, same, visit, maps);
			}
		}
	}
}