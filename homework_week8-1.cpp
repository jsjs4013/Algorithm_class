#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>

using namespace std;

void BruteForce(char *, char *);
void RabinKarp(char *, char *);
void computeSP(char *, int *, int);
void KMP(char *, char *);

int main(void)
{
	clock_t start, end;
	double result;

	char text[100];
	char pattern[100];

	cout << "text �Է� : ";
	for (int i = 0; i < 100; i++)
	{
		// text �Է¹޴� �ݺ���

		cin.get(text[i]); // ���͸� �Է¹ޱ� ���� cin.get() ���
		if (text[i] == '\n')
		{
			for (int j = i; j < 100; j++)
				text[j] = NULL;

			break;
		}
	}

	cout << "pattern �Է� : ";
	for (int i = 0; i < 100; i++)
	{
		// pattern �Է¹޴� �ݺ���

		cin.get(pattern[i]);
		if (pattern[i] == '\n')
		{
			for (int j = i; j < 100; j++)
				pattern[j] = NULL;

			break;
		}
	}

	start = clock();
	BruteForce(text, pattern);
	end = clock();
	result = (double)(end - start);
	cout << "BruteForce�� ����Ǵµ� �ɸ��ð� : " << result / CLOCKS_PER_SEC << "\n" << endl;

	start = clock();
	RabinKarp(text, pattern);
	end = clock();
	result = (double)(end - start);
	cout << "Rabin Karp�� ����Ǵµ� �ɸ��ð� : " << result / CLOCKS_PER_SEC << "\n" << endl;

	start = clock();
	KMP(text, pattern);
	end = clock();
	result = (double)(end - start);
	cout << "KMP�� ����Ǵµ� �ɸ��ð� : " << result / CLOCKS_PER_SEC << "\n" << endl;


	return 0;
}

void BruteForce(char * t, char * p)
{
	int patternNum = 0; // �� ���� ������ ��ġ�ϴ��� �˾ƺ��� ����
	int n = strlen(t); // �ؽ�Ʈ�� ����
	int m = strlen(p); // ������ ����
	int j;

	for (int i = 0; i <= n - m; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (p[j] != t[i + j])
				// �ؽ�Ʈ�� ������ ���ڰ� �ϳ��� ��ġ���� ������
				// �ݺ����� ��������

				break;
		}

		if (j == m)
		{
			// �ؽ�Ʈ�� ������ ���ڿ��� ���ٸ�
			// �ؽ�Ʈ ������ ������ ã�� ���� 1�� ����������

			patternNum++;
		}
	}

	cout << "Burte Force : ������ �� ������ " << patternNum << "�̴�." << endl;
}

void RabinKarp(char* t, char* p)
{
	int patternNum = 0; // �� ���� ������ ��ġ�ϴ��� �˾ƺ��� ����
	int q = 79; // �ؽ� ���� �浹�� ���ϱ� ���� ū �Ҽ��� q�� ������
	int d = 36; // ���ĺ� ������ + 0~9
	int j;
	int dM = 1;
	int hT = 0;
	int hP = 0;
	int n = strlen(t);
	int m = strlen(p);


	for (int i = 1; i < m; i++)
	{
		// mod ������ dM�� ũ�Ⱑ ��� Ŀ�� �� �ֱ� ������ ����

		dM = (dM * d) % q; // d^(m-1) �� �������
	}

	for (int i = 0; i < m; i++)
	{
		// Horner ����� ���� hT�� hP ���
		// �ؽ�Ʈ�� ������ ù��° �����ŭ�� �ؽ��� �����ϴ� �ݺ���

		if (t[i] != '0' && t[i] != '1' && t[i] != '2' && t[i] != '3' && t[i] != '4' && t[i] != '5' && t[i] != '6' && t[i] != '7' && t[i] != '8' && t[i] != '9')
		{
			// �ؽ�Ʈ�� ���� ���ĺ��� ��� �����ϴ� ���ǹ�

			hT = ((d * hT) + (t[i] - 'a')) % q;
		}
		else
		{
			// �ؽ�Ʈ�� ���� ������ ��� �����ϴ� ���ǹ�

			hT = ((d * hT) + int(t[i]) + 10) % q;
		}

		if (p[i] != '0' && p[i] != '1' && p[i] != '2' && p[i] != '3' && p[i] != '4' && p[i] != '5' && p[i] != '6' && p[i] != '7' && p[i] != '8' && p[i] != '9')
		{
			// ������ ���� ���ĺ��� ��� �����ϴ� ���ǹ�

			hP = ((d * hP) + (p[i] - 'a')) % q;
		}
		else
		{
			// ������ ���� ������ ��� �����ϴ� ���ǹ�

			hP = ((d * hP) + (int(p[i]) + 10)) % q;
		}
	}

	for (int i = 0; i < n - m + 1; i++)
	{
		// �ؽ�Ʈ �� ��ġ ���� ���� ��Ī�ϴ� �ݺ���

		if (hT == hP)
		{
			// �ؽ�Ʈ�� ������ �ؽ� ���� ���� �� ���� ���� ��Ī ������

			for (j = 0; j < m; j++)
			{
				if (p[j] != t[i + j])
				{
					// ������ �ϳ��� �ٸ��ٸ� �ݺ����� ��������

					break;
				}
			}

			if (j == m)
			{
				// ������ ��� �����ϴٸ� �ؽ�Ʈ ������ ������ ã�� ���� 1 ����������

				patternNum++;
			}
		}

		if (i < n - m) // ���� ���ڿ� �񱳸� ���� �ؽ�Ʈ ���ڿ��� ���������� �� �� �ű� �ؽ����� ����.
		{
			if (t[i] != '0' && t[i] != '1' && t[i] != '2' && t[i] != '3' && t[i] != '4' && t[i] != '5' && t[i] != '6' && t[i] != '7' && t[i] != '8' && t[i] != '9')
			{
				// �ؽ�Ʈ�� ���� ���ĺ��� ��� �����ϴ� ���ǹ�
				// �ؽ�Ʈ�� i��° �ڸ��� ����

				hT = ((hT + q) - ((t[i] - 'a') * dM % q)) % q;
			}
			else
			{
				// �ؽ�Ʈ�� ���� ������ ��� �����ϴ� ���ǹ�
				// �ؽ�Ʈ�� i��° �ڸ��� ����

				hT = ((hT + q) - ((int(t[i]) + 10) * dM % q)) % q;
			}

			if (t[i + m] != '0' && t[i + m] != '1' && t[i + m] != '2' && t[i + m] != '3' && t[i + m] != '4' && t[i + m] != '5' && t[i + m] != '6' && t[i + m] != '7' && t[i + m] != '8' && t[i + m] != '9')
			{
				// �ؽ�Ʈ�� ���� ���ĺ��� ��� �����ϴ� ���ǹ�
				// �ؽ�Ʈ�� i + m ��° �ڸ��� �ؽ����� ������

				hT = (hT * d + (t[i + m] - 'a')) % q;
			}
			else
			{
				// �ؽ�Ʈ�� ���� ������ ��� �����ϴ� ���ǹ�
				// �ؽ�Ʈ�� i + m ��° �ڸ��� �ؽ����� ������

				hT = (hT * d + (int(t[i + m]) + 10)) % q;
			}
		}
	}

	cout << "Rabin Karp : ������ �� ������ " << patternNum << "�̴�." << endl;
}

void computeSP(char* p, int * SP, int m)
{
	SP[0] = -1;
	int k = -1;

	for (int i = 1; i < m; i++)
	{
		// pattern table�� ����� �ݺ���

		while (k >= 0 && (p[k + 1] != p[i]))
		{
			// ��ġ�Ǵ� �� ����ġ�� �߻��ϸ� k���� SP������ �ݺ��� ����

			k = SP[k];
		}
		if (p[k + 1] == p[i])
		{
			// ��ġ �߻� �� k�� ����

			k++;
		}
		SP[i] = k;
	}
}

void KMP(char * t, char * p)
{
	int patternNum = 0; // �� ���� ������ ��ġ�ϴ��� �˾ƺ��� ����
	int n = strlen(t); // �ؽ�Ʈ�� ����
	int m = strlen(p); // ������ ����
	int j = -1;
	int *SP = NULL; // prefix table�� ����� ���� ������ ���� ����
	SP = (int*)malloc(sizeof(int) * m); // ������ ���̸�ŭ �����Ҵ�
	memset(SP, 0, (sizeof(int) * m)); // prefix table�� 0���� ��� �ʱ�ȭ��

	// pattern table�� ����
	computeSP(p, SP, m);

	for (int i = 0; i < n; i++)
	{
		// �ٺ������� computeSP ���۹�İ� ������
		// ���� ������ prefix�� suffix�� ã�� ���� �ƴ϶� pattern table�� Ȱ����
		// ���ϰ� �ؽ�Ʈ�� prefix�� suffix�� ���ذ��鼭 ���ڿ��� ����

		while (j >= 0 && (p[j + 1] != t[i]))
		{
			j = SP[j];
		}

		if (p[j + 1] == t[i])
		{
			j++;
		}
		if (j == m - 1)
		{
			// ������ ��� �����ϴٸ� �ؽ�Ʈ ������ ������ ã�� ���� 1 ����������

			patternNum++;
			j = SP[j];
		}
	}

	cout << "KMP : ������ �� ������ " << patternNum << "�̴�." << endl;
}
