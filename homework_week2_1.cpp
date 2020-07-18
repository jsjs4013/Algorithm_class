#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(void)
{
	ifstream ifile;
	char read[200]; // 한 줄씩 읽어서 저장할 공간
	int check; // 회문인지 체크하는 변수
	int lineSize; // 텍스트파일을 읽어서 얻은 단어의 사이즈를 저장
	int i;

	ifile.open("exam_palindrome.txt"); // 파일 열기

	if (ifile.is_open())
	{
		while (ifile.getline(read, sizeof(read)))
		{
			// 파일을 열고 텍스트 파일을 한 줄씩 읽음

			check = 1; // 최초 check는 1로 하여 회문일 경우를 가정
			lineSize = strlen(read); // 읽은 단어의 사이즈를 구함
			for (i = 0; i < lineSize / 2; i++)
			{
				// 0부터 단어의 사이즈 / 2 만큼 반복을 함

				if (read[i] != read[lineSize - 1 - i])
				{
					// 반복문으로 돌아가면서 i번째 단어와 마지막 - i 단어를 비교
					// 만약 같지 않다면 회문이 아니므로 이 조건문이 실행됨

					check = 0;

					break; // 반복문을 더이상 돌 필욜가 없으므로 강제로 빠져나감
				}
			}
			if (check) // 회문일 경우
				cout << read << '\t' << "회문 입니다." << endl;
			else // 회문이 아닐 경우
				cout << read << '\t' << "회문이 아닙니다." << endl;
		}
	}

	return 0;
}