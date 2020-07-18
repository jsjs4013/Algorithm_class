#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

bool isPalindrome(char[], int, int);

int main(void)
{
	ifstream ifile;
	char read[200]; // �� �پ� �о ������ ����
	bool check; // ȸ������ üũ�ϴ� bool�� ����
	int lineSize; // �ؽ�Ʈ������ �о ���� �ܾ��� ����� ����
	int i = 0; // ����Լ��� ���鼭 ���� ���� ��ġ�� ����

	ifile.open("exam_palindrome.txt"); // ���� ����

	if (ifile.is_open())
	{
		while (ifile.getline(read, sizeof(read)))
		{
			// ������ ���� �ؽ�Ʈ ������ �� �پ� ����

			lineSize = strlen(read); // ���� �ܾ��� ����� ����
			check = isPalindrome(read, lineSize, i); // ȸ���� ���ϴ� ����Լ��� ����

			if (check) // ȸ���� ���
				cout << read << '\t' << "ȸ�� �Դϴ�." << endl;
			else // ȸ���� �ƴ� ���
				cout << read << '\t' << "ȸ���� �ƴմϴ�." << endl;
		}
	}

	return 0;
}

bool isPalindrome(char read[], int lineSize, int i)
{
	// ����Լ��̸� ȸ���ܾ �˷��ִ� �Լ�

	if (lineSize <= 1)
	{
		// Ż������ #1, �ܾ 1�� ���ϸ� ȸ���̹Ƿ� true ����
		return true;
	}
	else if (i >= lineSize / 2)
	{
		// Ż������ #2, i�� ũ�Ⱑ lineSize / 2 ���� ���ų� ũ�� true ����
		return true;
	}
	else if (read[i] != read[lineSize - i - 1])
	{
		// Ż������ #3, i��° �ܾ�� ������ - i ��° �ܾ �ٸ��� false ����
		return false;
	}

	i += 1; // ���� ��ġ�� +1 ����

	return isPalindrome(read, lineSize, i); // ����Լ��� ���Ե�
}