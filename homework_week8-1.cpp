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

	cout << "text 입력 : ";
	for (int i = 0; i < 100; i++)
	{
		// text 입력받는 반복문

		cin.get(text[i]); // 엔터를 입력받기 위해 cin.get() 사용
		if (text[i] == '\n')
		{
			for (int j = i; j < 100; j++)
				text[j] = NULL;

			break;
		}
	}

	cout << "pattern 입력 : ";
	for (int i = 0; i < 100; i++)
	{
		// pattern 입력받는 반복문

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
	cout << "BruteForce가 실행되는데 걸린시간 : " << result / CLOCKS_PER_SEC << "\n" << endl;

	start = clock();
	RabinKarp(text, pattern);
	end = clock();
	result = (double)(end - start);
	cout << "Rabin Karp가 실행되는데 걸린시간 : " << result / CLOCKS_PER_SEC << "\n" << endl;

	start = clock();
	KMP(text, pattern);
	end = clock();
	result = (double)(end - start);
	cout << "KMP가 실행되는데 걸린시간 : " << result / CLOCKS_PER_SEC << "\n" << endl;


	return 0;
}

void BruteForce(char * t, char * p)
{
	int patternNum = 0; // 몇 개의 패턴이 일치하는지 알아보는 변수
	int n = strlen(t); // 텍스트의 길이
	int m = strlen(p); // 패턴의 길이
	int j;

	for (int i = 0; i <= n - m; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (p[j] != t[i + j])
				// 텍스트와 패턴의 문자가 하나라도 일치하지 않으면
				// 반복문을 빠져나감

				break;
		}

		if (j == m)
		{
			// 텍스트와 패턴의 문자열이 같다면
			// 텍스트 내에서 패턴을 찾은 개수 1을 증가시켜줌

			patternNum++;
		}
	}

	cout << "Burte Force : 패턴의 총 개수는 " << patternNum << "이다." << endl;
}

void RabinKarp(char* t, char* p)
{
	int patternNum = 0; // 몇 개의 패턴이 일치하는지 알아보는 변수
	int q = 79; // 해쉬 값의 충돌을 피하기 위해 큰 소수로 q를 설정함
	int d = 36; // 알파벳 사이즈 + 0~9
	int j;
	int dM = 1;
	int hT = 0;
	int hP = 0;
	int n = strlen(t);
	int m = strlen(p);


	for (int i = 1; i < m; i++)
	{
		// mod 연산은 dM의 크기가 계속 커질 수 있기 때문에 해줌

		dM = (dM * d) % q; // d^(m-1) 값 사전계산
	}

	for (int i = 0; i < m; i++)
	{
		// Horner 방법을 통한 hT와 hP 계산
		// 텍스트와 패턴의 첫번째 사이즈만큼의 해쉬값 설정하는 반복문

		if (t[i] != '0' && t[i] != '1' && t[i] != '2' && t[i] != '3' && t[i] != '4' && t[i] != '5' && t[i] != '6' && t[i] != '7' && t[i] != '8' && t[i] != '9')
		{
			// 텍스트의 값이 알파벳인 경우 실행하는 조건문

			hT = ((d * hT) + (t[i] - 'a')) % q;
		}
		else
		{
			// 텍스트의 값이 숫자인 경우 실행하는 조건문

			hT = ((d * hT) + int(t[i]) + 10) % q;
		}

		if (p[i] != '0' && p[i] != '1' && p[i] != '2' && p[i] != '3' && p[i] != '4' && p[i] != '5' && p[i] != '6' && p[i] != '7' && p[i] != '8' && p[i] != '9')
		{
			// 패턴의 값이 알파벳인 경우 실행하는 조건문

			hP = ((d * hP) + (p[i] - 'a')) % q;
		}
		else
		{
			// 패턴의 값이 숫자인 경우 실행하는 조건문

			hP = ((d * hP) + (int(p[i]) + 10)) % q;
		}
	}

	for (int i = 0; i < n - m + 1; i++)
	{
		// 텍스트 각 위치 별로 패턴 매칭하는 반복문

		if (hT == hP)
		{
			// 텍스트와 패턴의 해쉬 값이 같을 때 세부 패턴 매칭 진행함

			for (j = 0; j < m; j++)
			{
				if (p[j] != t[i + j])
				{
					// 패턴이 하나라도 다르다면 반복문을 빠져나감

					break;
				}
			}

			if (j == m)
			{
				// 패턴이 모두 동일하다면 텍스트 내에서 패턴을 찾은 개수 1 증가시켜줌

				patternNum++;
			}
		}

		if (i < n - m) // 다음 문자열 비교를 위해 텍스트 문자열의 오른쪽으로 한 번 옮긴 해쉬값을 구함.
		{
			if (t[i] != '0' && t[i] != '1' && t[i] != '2' && t[i] != '3' && t[i] != '4' && t[i] != '5' && t[i] != '6' && t[i] != '7' && t[i] != '8' && t[i] != '9')
			{
				// 텍스트의 값이 알파벳인 경우 실행하는 조건문
				// 텍스트의 i번째 자리를 빼줌

				hT = ((hT + q) - ((t[i] - 'a') * dM % q)) % q;
			}
			else
			{
				// 텍스트의 값이 숫자인 경우 실행하는 조건문
				// 텍스트의 i번째 자리를 빼줌

				hT = ((hT + q) - ((int(t[i]) + 10) * dM % q)) % q;
			}

			if (t[i + m] != '0' && t[i + m] != '1' && t[i + m] != '2' && t[i + m] != '3' && t[i + m] != '4' && t[i + m] != '5' && t[i + m] != '6' && t[i + m] != '7' && t[i + m] != '8' && t[i + m] != '9')
			{
				// 텍스트의 값이 알파벳인 경우 실행하는 조건문
				// 텍스트의 i + m 번째 자리의 해쉬값을 더해줌

				hT = (hT * d + (t[i + m] - 'a')) % q;
			}
			else
			{
				// 텍스트의 값이 숫자인 경우 실행하는 조건문
				// 텍스트의 i + m 번째 자리의 해쉬값을 더해줌

				hT = (hT * d + (int(t[i + m]) + 10)) % q;
			}
		}
	}

	cout << "Rabin Karp : 패턴의 총 개수는 " << patternNum << "이다." << endl;
}

void computeSP(char* p, int * SP, int m)
{
	SP[0] = -1;
	int k = -1;

	for (int i = 1; i < m; i++)
	{
		// pattern table을 만드는 반복문

		while (k >= 0 && (p[k + 1] != p[i]))
		{
			// 일치되던 중 불일치가 발생하면 k값을 SP값으로 반복해 수정

			k = SP[k];
		}
		if (p[k + 1] == p[i])
		{
			// 일치 발생 시 k값 증가

			k++;
		}
		SP[i] = k;
	}
}

void KMP(char * t, char * p)
{
	int patternNum = 0; // 몇 개의 패턴이 일치하는지 알아보는 변수
	int n = strlen(t); // 텍스트의 길이
	int m = strlen(p); // 패턴의 길이
	int j = -1;
	int *SP = NULL; // prefix table을 만들기 위한 포인터 변수 선언
	SP = (int*)malloc(sizeof(int) * m); // 패턴의 길이만큼 동적할당
	memset(SP, 0, (sizeof(int) * m)); // prefix table을 0으로 모두 초기화함

	// pattern table를 만듦
	computeSP(p, SP, m);

	for (int i = 0; i < n; i++)
	{
		// 근본적으로 computeSP 동작방식과 동일함
		// 패턴 내에서 prefix와 suffix를 찾는 것이 아니라 pattern table을 활용해
		// 패턴과 텍스트의 prefix와 suffix를 비교해가면서 문자열을 비교함

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
			// 패턴이 모두 동일하다면 텍스트 내에서 패턴을 찾은 개수 1 증가시켜줌

			patternNum++;
			j = SP[j];
		}
	}

	cout << "KMP : 패턴의 총 개수는 " << patternNum << "이다." << endl;
}
