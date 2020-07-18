#include <iostream>

using namespace std;

int** inititial(string s);
void generateSuffix(string s, int** suf);
void sort(string s, int** suf, int len);
void reconstruct(string s, int** suf, int len);
void printChar(string s, int** suf, int len, int choose);
void printArNumber(string s, int** suf, int len);

int main(void)
{
	string s;
	int** suf;

	s = "CTAGCATGGAC";
	

	s.append(1, '$');
	suf = inititial(s);
	generateSuffix(s, suf);
	sort(s, suf, s.size());
	reconstruct(s, suf, s.size());


	return 0;
}

int **inititial(string s)
{
	// BWT를 위한 초기화를 하는 함수

	int** suf;

	// 동적으로 int형의 2차원 배열을 생성함
	suf = new int* [s.size()];
	for (int i = 0; i < s.size(); i++)
	{
		suf[i] = new int[s.size()];
	}

	return suf;
}

void generateSuffix(string s, int** suf)
{
	// bwt를 만들기 위한 suffixes를 만드는 함수

	int len = s.size() - 1;
	int count = 0;

	for (int i = len; i >= 0; i--)
	{
		// suffixes를 만드는 반복문

		count = 0;
		for (int j = i; j < s.size(); j++)
		{
			// generate all suffixes

			suf[len - i][count] = j;
			count++;
		}
		
		for (int j = 0; j < i; j++)
		{
			// fill the rest

			suf[len - i][count] = j;
			count++;
		}
	}

	printChar(s, suf, len + 1, 0);
}

void sort(string s, int** suf, int len)
{
	// bwt를 만들기 위해 sort하는 함수

	int temp;
	int check = 1;
	int count = 1;

	for (int i = 0; i < len; i++)
	{
		// sort를 위해 bubblesort를 함

		for (int j = 0; j < len - (i + 1); j++)
		{
			if (s[suf[j][0]] > s[suf[j + 1][0]])
			{
				// 오름차순의 sort를 위한 bubblesort 를 함

				for (int k = 0; k < len; k++)
				{
					// swap 하는 부분

					temp = suf[j + 1][k];
					suf[j + 1][k] = suf[j][k];
					suf[j][k] = temp;
				}
			}
			else if (s[suf[j][0]] == s[suf[j + 1][0]])
			{
				check = 1;
				count = 1;
				while (check)
				{
					// 같은 문자가 있으면 그 다음 문자를 비교하기 위한 반복문

					if (s[suf[j][count]] > s[suf[j + 1][count]])
					{
						// 오름차순의 sort를 위해 bubblesort를 함

						for (int k = 0; k < len; k++)
						{
							// swap 하는 부분

							temp = suf[j + 1][k];
							suf[j + 1][k] = suf[j][k];
							suf[j][k] = temp;
						}

						check = 0;
					}
					else if(s[suf[j][count]] < s[suf[j + 1][count]])
					{
						// 한개라도 더 작은게 있으면 바로 비교를 빠져나감

						check = 0;
					}

					// 비교할 대상을 한 칸 다음의 문자로 변경
					count++;
					if (count == len) // 비교할 대상이 마지막을 넘어서면 반복문 빠져나감
						check = 0;
				}
			}
		}
	}

	printChar(s, suf, len, 1);
	printArNumber(s, suf, len);
}

void reconstruct(string s, int** suf, int len)
{
	// 문자열을 복원하기 위한 함수

	int* temp = new int[len - 1];
	int tempNum;
	int find = len - 1; // 복원의 첫 시작은 무조건 $ 이므로 $를 나타내는 길이의 -1 한 값을 저장
	int checkEnd = 1;
	int count = 1;

	cout << "문자열 복원작업 시작" << endl;
	while(checkEnd)
	{
		// 모든 문자를 찾을 때 까지 반복함

		for (int i = 0; i < len; i++)
		{
			// 먼저 찾으려는 값이 pre bwt의 몇번째에 있는지 확인하는 반복문

			if (suf[i][0] == find)
			{
				// 찾으려는 값이 pre bwt에서 확인되면
				// 그 값을 임시변수에 저장함

				tempNum = i;

				break;
			}
		}

		if (suf[tempNum][len - 1] != len - 1)
		{
			// 만약 찾은 pre bwt에 대한 bwt의 값이 $가 아니라면 실행함
			// 이 값을 임시변수 배열에 저장하고 이 값이 pre bwt에서 찾아질 수 있도록 저장함

			find = suf[tempNum][len - 1];
			temp[len - count - 1] = find;

			for (int i = len - count - 1; i < len - 1; i++)
				cout << s[temp[i]] << ' ';
			cout << endl;
		}
		else // 만약 찾은 pre bwt의 값이 $라면 끝이므로 반복문을 종료하게 됨
			checkEnd = 0;

		count++;
	}
	cout << "복원완료" << endl;
}

void printChar(string s, int** suf, int len, int choose)
{
	// 2차원 배열을 print하는 함수

	if (choose == 0)
		cout << "fill the rest" << endl;
	else
		cout << "sort" << endl;

	for (int i = 0; i < len; i++)
	{
		// 배열의 각 값에 대해서 string s의 값을 출력함

		for (int j = 0; j < len; j++)
		{
			cout << s[suf[i][j]] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void printArNumber(string s, int** suf, int len)
{
	// bwt, pre bwt, ar number를 print하는 함수

	// 배열의 각 값에 대해서 string s의 값을 출력함
	cout << "bwt = ";
	for (int i = 0; i < len; i++)
	{
		cout << s[suf[i][len - 1]] << ' ';
	}
	cout << endl;

	cout << "pre_bwt = ";
	for (int i = 0; i < len; i++)
	{
		cout << s[suf[i][0]] << ' ';
	}
	cout << endl;

	// 배열의 각 값 자체가 ar number이 됨
	cout << "ar_number = ";
	for (int i = 0; i < len; i++)
	{
		cout << suf[i][0] << ' ';
	}
	cout << endl;
}