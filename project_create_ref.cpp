// 2014112022, ���ֿ�

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

void makeRefFile(char*);
void makeSReadFile(char*, char*, int, int);
void compareDiff(char*, char*);

int main(void)
{
	clock_t start, end;
	char* reference = new char[300000];
	char* mySeq = new char[300000];
	int l;
	int m;

	/*
	cout << "l �Է� : ";
	cin >> l;
	cout << "n �Է� : ";
	cin >> n;
	*/

	l = 50;
	m = 10000;

	makeRefFile(reference);
	makeSReadFile(mySeq, reference, l, m);
	compareDiff(reference, mySeq);


	return 0;
}

void makeRefFile(char* reference)
{
	// Reference file�� ����� �Լ�

	int temp;
	char tempList[3]; // ������ ���� Ȯ���ϱ� ���� ����
	int count = 0;
	string refFilePath = "reference_test.txt";


	srand((unsigned int)time(NULL));
	for (int i = 0; i < 300000; i++)
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
		for(int i = 0;i< 300000;i++)
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
	int* tempList = new int[300000]; // �̹� �� �� �̻� ��ȸ�ߴ��� �˷��ִ� ����
	string refFilePath = "reference.txt";
	string shortRdFilePath = "shortRead_test.txt";
	string originFilePath = "mySequence_snp_1.0_test.txt";

	char** tempMySeq; // ���Ͽ� �� �� ����ϴ� ����
	tempMySeq = new char* [m];
	
	for (int i = 0; i < m; i++)
		tempMySeq[i] = new char[l];
	
	for (int i = 0; i < 300000; i++)
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
	/*
	ifstream openFile2(originFilePath.data());
	if (openFile2.is_open()) {
		string line;
		while (getline(openFile2, line))
			openFile2.close();
		strcpy(mySeq, line.c_str());
	}*/

	
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 300000; i++)
	{
		// reference�� ���⼭���� 1.0%Ȯ���� ������ �ٸ� ����� �ٲٴ� ��
		// �ٲ� ���⼭���� my DNA�� ���⼭���� ��

		int num = rand();
		temp = (int)num % 1000; // Ȯ�� ����� ���� ���� �� ����

		if (temp < 10)
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
		temp = (int)num % (300000 - l + 1); // Ȯ�� ����� ���� ���� �� ����
		if (tempList[temp] == 1)
		{
			// �̹� ��ȸ�� ���̶�� 2ĭ �� ��ġ���� ���ø� �ϵ��� �ϴ� ��
			if (temp < 300000 - l - 1)
				temp += 2;
		}

		for (int j = 0; j < l; j++)
		{
			// l������ short read�� ����� ��

			tempMySeq[i][j] = mySeq[temp + j];
			tempList[temp + j] = 1;
		}
	}

	
	// write origin File
	ofstream writeFile(originFilePath.data());
	if (writeFile.is_open()) {
		for (int i = 0; i < 300000; i++)
			writeFile << mySeq[i];

		writeFile.close();
	}

	// write short read File
	ofstream writeFile2(shortRdFilePath.data());
	if (writeFile2.is_open()) {
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < l; j++)
				writeFile2 << tempMySeq[i][j];
			writeFile2 << endl;
		}

		writeFile2.close();
	}

	delete[] tempList;
	for (int i = 0; i < m; i++)
		delete[] tempMySeq[i];
	delete[] tempMySeq;
}



void compareDiff(char* ref, char* mySeq)
{
	string refFilePath = "reference_test.txt";
	string originFilePath = "shortRead_test.txt";
	int count = 0;


	// read File
	ifstream openFile(refFilePath.data());
	if (openFile.is_open()) {
		string line;
		while (getline(openFile, line))
			openFile.close();
		strcpy(ref, line.c_str());
	}

	ifstream openFile2(originFilePath.data());
	if (openFile2.is_open()) {
		string line;
		while (getline(openFile2, line))
			openFile2.close();
		strcpy(mySeq, line.c_str());
	}

	for (int i = 0; i < 300000; i++)
	{
		// my DNA�� trivial����� ���絵�� ����ϴ� ��

		if (mySeq[i] == ref[i])
		{
			count++;
		}
	}

	cout << "My DNA�� Reference�� ��ġ�� : " << float(count) / 300000 * 100 << "%" << endl;
}