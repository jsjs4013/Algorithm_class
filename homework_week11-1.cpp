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
	// BWT�� ���� �ʱ�ȭ�� �ϴ� �Լ�

	int** suf;

	// �������� int���� 2���� �迭�� ������
	suf = new int* [s.size()];
	for (int i = 0; i < s.size(); i++)
	{
		suf[i] = new int[s.size()];
	}

	return suf;
}

void generateSuffix(string s, int** suf)
{
	// bwt�� ����� ���� suffixes�� ����� �Լ�

	int len = s.size() - 1;
	int count = 0;

	for (int i = len; i >= 0; i--)
	{
		// suffixes�� ����� �ݺ���

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
	// bwt�� ����� ���� sort�ϴ� �Լ�

	int temp;
	int check = 1;
	int count = 1;

	for (int i = 0; i < len; i++)
	{
		// sort�� ���� bubblesort�� ��

		for (int j = 0; j < len - (i + 1); j++)
		{
			if (s[suf[j][0]] > s[suf[j + 1][0]])
			{
				// ���������� sort�� ���� bubblesort �� ��

				for (int k = 0; k < len; k++)
				{
					// swap �ϴ� �κ�

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
					// ���� ���ڰ� ������ �� ���� ���ڸ� ���ϱ� ���� �ݺ���

					if (s[suf[j][count]] > s[suf[j + 1][count]])
					{
						// ���������� sort�� ���� bubblesort�� ��

						for (int k = 0; k < len; k++)
						{
							// swap �ϴ� �κ�

							temp = suf[j + 1][k];
							suf[j + 1][k] = suf[j][k];
							suf[j][k] = temp;
						}

						check = 0;
					}
					else if(s[suf[j][count]] < s[suf[j + 1][count]])
					{
						// �Ѱ��� �� ������ ������ �ٷ� �񱳸� ��������

						check = 0;
					}

					// ���� ����� �� ĭ ������ ���ڷ� ����
					count++;
					if (count == len) // ���� ����� �������� �Ѿ�� �ݺ��� ��������
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
	// ���ڿ��� �����ϱ� ���� �Լ�

	int* temp = new int[len - 1];
	int tempNum;
	int find = len - 1; // ������ ù ������ ������ $ �̹Ƿ� $�� ��Ÿ���� ������ -1 �� ���� ����
	int checkEnd = 1;
	int count = 1;

	cout << "���ڿ� �����۾� ����" << endl;
	while(checkEnd)
	{
		// ��� ���ڸ� ã�� �� ���� �ݺ���

		for (int i = 0; i < len; i++)
		{
			// ���� ã������ ���� pre bwt�� ���°�� �ִ��� Ȯ���ϴ� �ݺ���

			if (suf[i][0] == find)
			{
				// ã������ ���� pre bwt���� Ȯ�εǸ�
				// �� ���� �ӽú����� ������

				tempNum = i;

				break;
			}
		}

		if (suf[tempNum][len - 1] != len - 1)
		{
			// ���� ã�� pre bwt�� ���� bwt�� ���� $�� �ƴ϶�� ������
			// �� ���� �ӽú��� �迭�� �����ϰ� �� ���� pre bwt���� ã���� �� �ֵ��� ������

			find = suf[tempNum][len - 1];
			temp[len - count - 1] = find;

			for (int i = len - count - 1; i < len - 1; i++)
				cout << s[temp[i]] << ' ';
			cout << endl;
		}
		else // ���� ã�� pre bwt�� ���� $��� ���̹Ƿ� �ݺ����� �����ϰ� ��
			checkEnd = 0;

		count++;
	}
	cout << "�����Ϸ�" << endl;
}

void printChar(string s, int** suf, int len, int choose)
{
	// 2���� �迭�� print�ϴ� �Լ�

	if (choose == 0)
		cout << "fill the rest" << endl;
	else
		cout << "sort" << endl;

	for (int i = 0; i < len; i++)
	{
		// �迭�� �� ���� ���ؼ� string s�� ���� �����

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
	// bwt, pre bwt, ar number�� print�ϴ� �Լ�

	// �迭�� �� ���� ���ؼ� string s�� ���� �����
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

	// �迭�� �� �� ��ü�� ar number�� ��
	cout << "ar_number = ";
	for (int i = 0; i < len; i++)
	{
		cout << suf[i][0] << ' ';
	}
	cout << endl;
}