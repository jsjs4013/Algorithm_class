#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(void)
{
	ifstream ifile;
	char read[200]; // �� �پ� �о ������ ����
	int check; // ȸ������ üũ�ϴ� ����
	int lineSize; // �ؽ�Ʈ������ �о ���� �ܾ��� ����� ����
	int i;

	ifile.open("exam_palindrome.txt"); // ���� ����

	if (ifile.is_open())
	{
		while (ifile.getline(read, sizeof(read)))
		{
			// ������ ���� �ؽ�Ʈ ������ �� �پ� ����

			check = 1; // ���� check�� 1�� �Ͽ� ȸ���� ��츦 ����
			lineSize = strlen(read); // ���� �ܾ��� ����� ����
			for (i = 0; i < lineSize / 2; i++)
			{
				// 0���� �ܾ��� ������ / 2 ��ŭ �ݺ��� ��

				if (read[i] != read[lineSize - 1 - i])
				{
					// �ݺ������� ���ư��鼭 i��° �ܾ�� ������ - i �ܾ ��
					// ���� ���� �ʴٸ� ȸ���� �ƴϹǷ� �� ���ǹ��� �����

					check = 0;

					break; // �ݺ����� ���̻� �� �ʿ簡 �����Ƿ� ������ ��������
				}
			}
			if (check) // ȸ���� ���
				cout << read << '\t' << "ȸ�� �Դϴ�." << endl;
			else // ȸ���� �ƴ� ���
				cout << read << '\t' << "ȸ���� �ƴմϴ�." << endl;
		}
	}

	return 0;
}