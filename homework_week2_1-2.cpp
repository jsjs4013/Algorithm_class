#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

bool isPalindrome(char[], int, int);

int main(void)
{
	ifstream ifile;
	char read[200]; // 한 줄씩 읽어서 저장할 공간
	bool check; // 회문인지 체크하는 bool형 변수
	int lineSize; // 텍스트파일을 읽어서 얻은 단어의 사이즈를 저장
	int i = 0; // 재귀함수를 돌면서 현재 읽을 위치를 저장

	ifile.open("exam_palindrome.txt"); // 파일 열기

	if (ifile.is_open())
	{
		while (ifile.getline(read, sizeof(read)))
		{
			// 파일을 열고 텍스트 파일을 한 줄씩 읽음

			lineSize = strlen(read); // 읽은 단어의 사이즈를 구함
			check = isPalindrome(read, lineSize, i); // 회문을 구하는 재귀함수를 실행

			if (check) // 회문일 경우
				cout << read << '\t' << "회문 입니다." << endl;
			else // 회문이 아닐 경우
				cout << read << '\t' << "회문이 아닙니다." << endl;
		}
	}

	return 0;
}

bool isPalindrome(char read[], int lineSize, int i)
{
	// 재귀함수이며 회문단어를 알려주는 함수

	if (lineSize <= 1)
	{
		// 탈출조건 #1, 단어가 1개 이하면 회문이므로 true 리턴
		return true;
	}
	else if (i >= lineSize / 2)
	{
		// 탈출조건 #2, i의 크기가 lineSize / 2 보다 같거나 크면 true 리턴
		return true;
	}
	else if (read[i] != read[lineSize - i - 1])
	{
		// 탈출조건 #3, i번째 단어와 마지막 - i 번째 단어가 다르면 false 리턴
		return false;
	}

	i += 1; // 현재 위치를 +1 해줌

	return isPalindrome(read, lineSize, i); // 재귀함수를 돌게됨
}