// 2014112022, 문주원

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
	cout << "l 입력 : ";
	cin >> l;
	cout << "n 입력 : ";
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
	// Reference file을 만드는 함수

	int temp;
	char tempList[3]; // 연속한 값을 확인하기 위한 변수
	int count = 0;
	string refFilePath = "reference_test.txt";


	srand((unsigned int)time(NULL));
	for (int i = 0; i < 300000; i++)
	{
		// 랜덤한 값을 정하고 그 값에 대해 ACGT중 하나를 택함

		int num = rand();

		temp = (int)num % 4; // 랜덤한 레퍼런스의 값을 생성

		// 레퍼런스 값을 문자로 변경하고 저장
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
			// 같은 문자에 대해 반복이 계속 나타나지 않게하기 위한 조건문

			count = 0;
			if (tempList[0] == tempList[1] && tempList[1] == tempList[2])
			{
				// count가 4가 되면 이전 값과 연속한 문자를 가지지 못하게 함

				num = rand();
				temp = (int)num % 3; // 랜덤한 레퍼런스의 값을 생성

				if (tempList[0] == 'A')
				{
					// 이전 연속한 값이 A인 경우 실행

					if (temp == 0)
						reference[i] = 'C';
					else if (temp == 1)
						reference[i] = 'G';
					else
						reference[i] = 'T';
				}
				else if (tempList[0] == 'C')
				{
					// 이전 연속한 값이 C인 경우 실행

					if (temp == 0)
						reference[i] = 'A';
					else if (temp == 1)
						reference[i] = 'G';
					else
						reference[i] = 'T';
				}
				else if (tempList[0] == 'G')
				{
					// 이전 연속한 값이 G인 경우 실행

					if (temp == 0)
						reference[i] = 'A';
					else if (temp == 1)
						reference[i] = 'C';
					else
						reference[i] = 'T';
				}
				else
				{
					// 이전 연속한 값이 T인 경우 실행

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
	// my DNA file을 만들기 위한 함수
	// Reference DNA와 전체 20%가 다르게 만들어짐

	int temp;
	int check = 1;
	int* tempList = new int[300000]; // 이미 한 번 이상 조회했는지 알려주는 변수
	string refFilePath = "reference.txt";
	string shortRdFilePath = "shortRead_test.txt";
	string originFilePath = "mySequence_snp_1.0_test.txt";

	char** tempMySeq; // 파일에 쓸 때 사용하는 변수
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
		// reference의 염기서열을 1.0%확률로 랜덤한 다른 염기로 바꾸는 절
		// 바뀐 염기서열은 my DNA의 염기서열로 들어감

		int num = rand();
		temp = (int)num % 1000; // 확률 계산을 위해 랜덤 값 생성

		if (temp < 10)
		{
			// 0.1%의 확률로 염기서열을 바꿈

			// 레퍼런스 값을 문자로 변경하고 저장
			if (reference[i] == 'A')
			{
				// A의 문자였다면 A를 T로 변경
				mySeq[i] = 'T';
			}
			else if (reference[i] == 'C')
			{
				// C의 문자였다면 C를 G로 변경
				mySeq[i] = 'G';
			}
			else if (reference[i] == 'G')
			{
				// G의 문자였다면 G를 C로 변경
				mySeq[i] = 'C';
			}
			else
			{
				// T의 문자였다면 T를 A로 변경
				mySeq[i] = 'A';
			}
		}
		else
			mySeq[i] = reference[i];
	}

	cout << "Snip complete" << endl;
	for (int i = 0; i < m; i++)
	{
		// m개의 short read를 만드는 절

		int num = rand();
		temp = (int)num % (300000 - l + 1); // 확률 계산을 위해 랜덤 값 생성
		if (tempList[temp] == 1)
		{
			// 이미 조회한 곳이라면 2칸 띈 위치부터 샘플링 하도록 하는 절
			if (temp < 300000 - l - 1)
				temp += 2;
		}

		for (int j = 0; j < l; j++)
		{
			// l길이의 short read를 만드는 절

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
		// my DNA와 trivial결과의 유사도를 계산하는 절

		if (mySeq[i] == ref[i])
		{
			count++;
		}
	}

	cout << "My DNA와 Reference의 일치율 : " << float(count) / 300000 * 100 << "%" << endl;
}