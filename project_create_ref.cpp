// 2014112022, ���ֿ�

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

void makeRefFile(char*);
void makeSReadFile(char*, char*, int, int);

int main(void)
{
	clock_t start, end;
	char* reference = new char[100000000];
	char* mySeq = new char[100000000];
	int l;
	int m;

	/*
	cout << "l �Է� : ";
	cin >> l;
	cout << "n �Է� : ";
	cin >> n;
	*/

	l = 50;
	m = 20000000;

	makeRefFile(reference);
	makeSReadFile(mySeq, reference, l, m);


	return 0;
}

void makeRefFile(char* reference)
{
	// Reference file�� ����� �Լ�

	int temp;
	char tempList[3]; // ������ ���� Ȯ���ϱ� ���� ����
	int count = 0;
	string refFilePath = "reference.txt";


	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100000000; i++)
	{
		// ������ ���� ���ϰ� �� ���� ���� ACGT�� �ϳ��� ����

		int num = rand();

		temp = (int)num % 4; // ������ ���۷����� ���� ����

		// ���۷��� ���� ���ڷ� �����ϰ� ����
		if (temp == 0)
		{
			reference[i] = 'A';
			tempList[count] = 'A';
		}
		else if (temp == 1)
		{
			reference[i] = 'C';
			tempList[count] = 'C';
		}
		else if (temp == 2)
		{
			reference[i] = 'G';
			tempList[count] = 'G';
		}
		else
		{
			reference[i] = 'T';
			tempList[count] = 'T';
		}
		count++;

		if (count > 2)
		{
			// ���� ���ڿ� ���� �ݺ��� ��� ��Ÿ���� �ʰ��ϱ� ���� ���ǹ�

			count = 0;
			if (tempList[0] == tempList[1] && tempList[1] == tempList[2])
			{
				// count�� 4�� �Ǹ� ���� ���� ������ ���ڸ� ������ ���ϰ� ��

				num = rand();
				temp = (int)num % 3; // ������ ���۷����� ���� ����

				if (tempList[0] == 'A')
				{
					// ���� ������ ���� A�� ��� ����

					if (temp == 0)
						reference[i] = 'C';
					else if (temp == 1)
						reference[i] = 'G';
					else
						reference[i] = 'T';
				}
				else if (tempList[0] == 'C')
				{
					// ���� ������ ���� C�� ��� ����

					if (temp == 0)
						reference[i] = 'A';
					else if (temp == 1)
						reference[i] = 'G';
					else
						reference[i] = 'T';
				}
				else if (tempList[0] == 'G')
				{
					// ���� ������ ���� G�� ��� ����

					if (temp == 0)
						reference[i] = 'A';
					else if (temp == 1)
						reference[i] = 'C';
					else
						reference[i] = 'T';
				}
				else
				{
					// ���� ������ ���� T�� ��� ����

					if (temp == 0)
						reference[i] = 'A';
					else if (temp == 1)
						reference[i] = 'C';
					else
						reference[i] = 'G';
				}
			}
		}
	}

	// write File
	ofstream writeFile(refFilePath.data());
	if (writeFile.is_open()) {
		for(int i = 0;i< 100000000;i++)
			writeFile << reference[i];

		writeFile.close();
	}
}

void makeSReadFile(char* mySeq, char* reference, int l, int m)
{
	// my DNA file�� ����� ���� �Լ�
	// Reference DNA�� ��ü 20%�� �ٸ��� �������

	int temp;
	int check = 1;
	int* tempList = new int[100000000]; // �̹� �� �� �̻� ��ȸ�ߴ��� �˷��ִ� ����
	string refFilePath = "reference.txt";
	string originFilePath = "shortRead.txt";

	char** tempMySeq; // ���Ͽ� �� �� ����ϴ� ����
	tempMySeq = new char* [m];
	
	for (int i = 0; i < m; i++)
		tempMySeq[i] = new char[l];
	
	for (int i = 0; i < 100000000; i++)
		tempList[i] = 0;
	
	/*
	// read File
	ifstream openFile(refFilePath.data());
	if (openFile.is_open()) {
		string line;
		while (getline(openFile, line))
		openFile.close();
		strcpy(reference, line.c_str());
	}*/

	
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100000000; i++)
	{
		// reference�� ���⼭���� 0.1%Ȯ���� ������ �ٸ� ����� �ٲٴ� ��
		// �ٲ� ���⼭���� my DNA�� ���⼭���� ��

		int num = rand();
		temp = (int)num % 1000; // Ȯ�� ����� ���� ���� �� ����

		if (temp < 1)
		{
			// 0.1%�� Ȯ���� ���⼭���� �ٲ�

			// ���۷��� ���� ���ڷ� �����ϰ� ����
			if (reference[i] == 'A')
			{
				// A�� ���ڿ��ٸ� A�� T�� ����
				mySeq[i] = 'T';
			}
			else if (reference[i] == 'C')
			{
				// C�� ���ڿ��ٸ� C�� G�� ����
				mySeq[i] = 'G';
			}
			else if (reference[i] == 'G')
			{
				// G�� ���ڿ��ٸ� G�� C�� ����
				mySeq[i] = 'C';
			}
			else
			{
				// T�� ���ڿ��ٸ� T�� A�� ����
				mySeq[i] = 'A';
			}
		}
		else
			mySeq[i] = reference[i];
	}

	cout << "Snip complete" << endl;
	for (int i = 0; i < m; i++)
	{
		// m���� short read�� ����� ��

		int num = rand();
		temp = (int)num % (100000000 - l + 1); // Ȯ�� ����� ���� ���� �� ����
		if (tempList[temp] == 1)
		{
			// �̹� ��ȸ�� ���̶�� 2ĭ �� ��ġ���� ���ø� �ϵ��� �ϴ� ��
			if (temp < 100000000 - l - 1)
				temp += 2;
		}

		for (int j = 0; j < l; j++)
		{
			// l������ short read�� ����� ��

			tempMySeq[i][j] = mySeq[temp + j];
			tempList[temp + j] = 1;
		}
	}

	// write File
	ofstream writeFile(originFilePath.data());
	if (writeFile.is_open()) {
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < l; j++)
				writeFile << tempMySeq[i][j];
			writeFile << endl;
		}

		writeFile.close();
	}

	delete[] tempList;
	for (int i = 0; i < m; i++)
		delete[] tempMySeq[i];
	delete[] tempMySeq;
}