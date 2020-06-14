// 2014112022, 문주원

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

void inititial(string);
string load(void);
void generateSuffix(string, int*);
void sort(char*, int*, int);
void reconstruct(string* s, int** suf, int len);
void setBWT(char**, int*, int[][2], int*);
void setTable(char[][1000]);
string reconstruct(char**, int*, int[][2], int, int*);
string insertShortRead(string, string, int*, int);
void printBWT(string, int*);
void calDiff(string);


// 복원시킬 데이터 개수를 바꾸고 싶을 때 이곳을 바꿈
int changeDataNum = 100000;


int main(void)
{
	time_t start, end;
	double result;
	start = time(NULL); // 시간 측정 시작

	// -----------------------------------
	// Only use test

	//string s = "ACAACG";

	//s.append(1, '$');
	//inititial(s);
	// -----------------------------------


	// -----------------------------------
	// redy to algorithm

	// use variable
	string refString;
	int* seqArray;
	int col = 1000; // 열

	refString = load();
	seqArray = new int[refString.size()];
	// -----------------------------------


	// -----------------------------------
	// create BWT, pre BWT, sequence array

	generateSuffix(refString, seqArray);
	printBWT(refString, seqArray);
	// -----------------------------------


	// -----------------------------------
	// exact Matching using BWT

	cout << endl;
	cout << "Matching srtart" << endl;

	int table[5][2];
	int* locationBWT = new int[changeDataNum];
	char** bwt = new char* [2];
	for (int i = 0; i < 2; i++)
		bwt[i] = new char[changeDataNum];

	setBWT(bwt, seqArray, table, locationBWT);
	refString = reconstruct(bwt, seqArray, table, col, locationBWT);
	calDiff(refString);
	// -----------------------------------

	end = time(NULL);
	result = (double)(end - start);
	cout << endl;
	cout << "Total time = " << result << "(s)";
	cout << endl;


	return 0;
}

void inititial(string s)
{
	// Only use test

	string refFilePath = "BWT/sequence.txt";
	int len = s.size();

	// write File
	ofstream writeFile(refFilePath.data());
	if (writeFile.is_open()) {
		for (int i = 0; i < len; i++)
			writeFile << s[i];

		writeFile.close();
	}
}

string load(void)
{
	string line;
	string refFilePath = "reference_test.txt";

	// read File
	ifstream openFile(refFilePath.data());
	if (openFile.is_open()) {
		while (getline(openFile, line));
		line.append(1, '$');

		openFile.close();
	}

	return line;
}

void generateSuffix(string refString, int* seqArray)
{
	// bwt를 만들기 위한 suffixes를 만드는 함수

	string suffixPath = "BWT/suffix.txt";
	string arrayPath = "BWT/array.txt";
	string suffix;

	int len = refString.size();

	char* tempSequence = new char[len];


	cout << "Make Suffix" << endl;
	for (int i = 0; i < len; i++)
	{
		// write File
		ofstream writeFile(suffixPath.data(), ios::app);
		if (writeFile.is_open()) {
			if (i > 0)
			{
				writeFile << refString[i];
				writeFile << refString[i - 1]; // BWT 저장
			}
			else
			{
				for (int j = i; j < len; j++)
					writeFile << refString[j];

				writeFile << refString[len - 1]; // BWT 저장
			}
			writeFile << endl;
			writeFile.close();
		}
	}
	cout << "Make Suffix Done" << endl;

	// read File
	ifstream openFile(suffixPath.data());
	if (openFile.is_open()) {
		while (getline(openFile, suffix))
		{
			break;
		}
		openFile.close();
	}


	for (int i = 0; i < len; i++)
	{
		if (i)
		{
			for (int j = 0; j < i; j++)
				tempSequence[j] = suffix[(len - 1 - i) + seqArray[j]];

			sort(tempSequence, seqArray, i);

			seqArray[i] = i;
		}
		else
			seqArray[i] = i;
	}

	// write File
	ofstream writeFileArray(arrayPath.data());
	if (writeFileArray.is_open()) {
		for (int j = 0; j < len; j++)
		{
			writeFileArray << seqArray[j];
			writeFileArray << endl;
		}

		writeFileArray.close();
	}

	delete[] tempSequence;
}

void sort(char* tempSequence, int* seqArray, int n)
{
	// bwt를 만들기 위해 sort하는 함수
	// 계수정렬 사용

	int countArr[4];
	int tempSeq;
	int* tempArr = new int[n];


	for (int i = 0; i < 4; i++)
		countArr[i] = 0; // 초기화
	for (int i = 0; i < n; i++)
	{
		if (tempSequence[i] == 'A')
			countArr[0]++;
		else if (tempSequence[i] == 'C')
			countArr[1]++;
		else if (tempSequence[i] == 'G')
			countArr[2]++;
		else
			countArr[3]++;
	}
	for (int i = 1; i < 4; i++)
		countArr[i] = countArr[i] + countArr[i - 1]; // 누적합
	for (int i = 0; i < n; i++)
	{
		if (tempSequence[i] == 'A')
			tempSeq = 0;
		else if (tempSequence[i] == 'C')
			tempSeq = 1;
		else if (tempSequence[i] == 'G')
			tempSeq = 2;
		else
			tempSeq = 3;

		tempArr[n - countArr[tempSeq]] = seqArray[i];
		countArr[tempSeq]--;
	}

	for (int i = 0; i < n; i++)
		seqArray[i] = tempArr[i];

	delete[] tempArr;
}

string reconstruct(char** bwt, int* seqArray, int table[][2], int shortLen, int* locationBWT)
{
	// 문자열을 복원하기 위한 함수

	string refFilePath = "reference_test.txt";
	string shortReadPath = "shortRead_test.txt";
	string reference;
	int check;

	// read reference File
	ifstream openFile(refFilePath.data());
	if (openFile.is_open()) {
		while (getline(openFile, reference));
		openFile.close();
	}


	// read shortRead File
	ifstream openSRFile(shortReadPath.data());
	string line;
	if (openSRFile.is_open()) {
		while (getline(openSRFile, line))
		{
			int fcon = 1;
			int econ = 1;
			int succe = -1;
			int front, end;
			int frontNext = -1;
			int endNext = -1;
			int missmatch[2] = { 0, 0 };


			if (line[shortLen - 1] == '$')
				check = 0;
			else if (line[shortLen - 1] == 'A')
				check = 1;
			else if (line[shortLen - 1] == 'C')
				check = 2;
			else if (line[shortLen - 1] == 'G')
				check = 3;
			else
				check = 4;

			front = table[check][0];
			end = table[check][1];
			while (1)
			{
				if (end - front < 0)
					if (frontNext == -1 && endNext == -1)
						break;


				if (front <= end || frontNext != -1)
				{
					// front 실행 구문
					if (shortLen - fcon >= 0)
					{
						if (frontNext == -1)
						{
							frontNext = locationBWT[front];
						}
						else
						{
							if (bwt[0][frontNext] == '$')
							{
								fcon = 0;
								front++;
								frontNext = -1;
								missmatch[0] = 0;
							}
							else
							{
								if (bwt[0][frontNext] == line[shortLen - fcon])
								{
									if (shortLen - fcon == 0)
									{
										// 레퍼런스에서 찾기 성공

										succe = frontNext;

										break;
									}

									frontNext = locationBWT[frontNext];
								}
								else
								{
									missmatch[0]++;

									if (missmatch[0] > 3)
									{
										// miss match 개수 3개까지 허용함

										fcon = 0;
										front++;
										frontNext = -1;
										missmatch[0] = 0;
									}
									else
									{
										if (shortLen - fcon == 0)
										{
											// 레퍼런스에서 찾기 성공

											succe = frontNext;

											break;
										}

										frontNext = locationBWT[frontNext];
									}
								}
							}
						}
					}
					else
					{
						fcon = 0;
						front++;
						frontNext = -1;
						missmatch[0] = 0;
					}

					fcon++;
				}

				if (end >= front || endNext != -1)
				{
					// end 실행 구문
					if (shortLen - econ >= 0)
					{
						if (endNext == -1)
						{
							endNext = locationBWT[end];
						}
						else
						{
							if (bwt[0][endNext] == '$')
							{
								econ = 0;
								end--;
								endNext = -1;
								missmatch[1] = 0;
							}
							else
							{
								if (bwt[0][endNext] == line[shortLen - econ])
								{
									if (shortLen - econ == 0)
									{
										// 레퍼런스에서 찾기 성공

										succe = endNext;

										break;
									}

									endNext = locationBWT[endNext];
								}
								else
								{
									missmatch[1]++;

									if (missmatch[1] > 3)
									{
										// miss match 개수 3개까지 허용함

										econ = 0;
										end--;
										endNext = -1;
										missmatch[1] = 0;
									}
									else
									{
										if (shortLen - econ == 0)
										{
											// 레퍼런스에서 찾기 성공

											succe = endNext;

											break;
										}

										endNext = locationBWT[endNext];
									}
								}
							}
						}
					}
					else
					{
						econ = 0;
						end--;
						endNext = -1;
						missmatch[1] = 0;
					}

					econ++;
				}
			}
			// 여기다가 레퍼런스에 삽입하는 함수 만듦
			reference = insertShortRead(reference, line, seqArray, succe);
		}
		openSRFile.close();
	}

	return reference;
}

void setBWT(char** bwt, int* seqArray, int table[][2], int* locationBWT)
{
	string arrayPath = "BWT/array.txt";
	string BWTPath = "BWT/bwt.txt";
	string PreBWTPath = "BWT/pre_bwt.txt";


	cout << "File 읽기 시작" << endl;
	// read array File
	ifstream openFileArray(arrayPath.data());
	if (openFileArray.is_open()) {
		string line;
		int con = changeDataNum;
		while (getline(openFileArray, line))
		{
			seqArray[con] = atoi(line.c_str());
			con--;
		}
		openFileArray.close();
	}
	cout << "Array 읽기 완료" << endl;

	// read pre BWT File
	ifstream openFilePreBWT(PreBWTPath.data());
	if (openFilePreBWT.is_open()) {
		string line;
		int con = 0;
		int temp = 0;
		while (getline(openFilePreBWT, line))
		{
			bwt[0][con] = line[0];

			if (con)
			{
				if (bwt[0][con - 1] != bwt[0][con])
				{
					table[temp][0] = con;
					if (temp < 5)
					{
						table[temp - 1][1] = con - 1;
						temp++;
					}
				}
			}
			else
			{
				// table 초기 셋팅
				// pre train의 첫 줄은 무조건 $ 임
				table[temp][0] = 0;
				temp++;
			}
			con++;
		}
		table[temp - 1][1] = con - 1;
		openFilePreBWT.close();
	}
	cout << "BWT 읽기 완료" << endl;

	// read BWT File
	ifstream openFileBWT(BWTPath.data());
	if (openFileBWT.is_open()) {
		string line;
		int con = 0;
		int temp_0 = table[0][0];
		int temp_A = table[1][0];
		int temp_C = table[2][0];
		int temp_G = table[3][0];
		int temp_T = table[4][0];
		while (getline(openFileBWT, line))
		{
			bwt[1][con] = line[0];

			// 각 위치를 잡아주는 절
			if (bwt[1][con] == '$')
			{
				locationBWT[con] = temp_0;
				temp_0++;
			}
			else if (bwt[1][con] == 'A')
			{
				locationBWT[con] = temp_A;
				temp_A++;
			}
			else if (bwt[1][con] == 'C')
			{
				locationBWT[con] = temp_C;
				temp_C++;
			}
			else if (bwt[1][con] == 'G')
			{
				locationBWT[con] = temp_G;
				temp_G++;
			}
			else
			{
				locationBWT[con] = temp_T;
				temp_T++;
			}

			con++;
		}
		openFileBWT.close();
	}
	cout << "Pre BWT 읽기 완료" << endl;
}


string insertShortRead(string reference, string shortRd, int* seqArray, int succe)
{
	// 레퍼런스에 short read 삽입하는 함수

	if (succe == -1)
		return reference;

	int len = reference.size();
	int locate = seqArray[succe];


	for (int i = 0; i < shortRd.size(); i++)
	{
		if (locate + i >= len)
			break;

		reference[locate + i] = shortRd[i];
	}

	return reference;
}


void printBWT(string tempSequence, int* seqArray)
{
	// BWT를 save하는 함수
	int len = tempSequence.size();

	string bwt;
	string preBwt;
	string suffixPath = "BWT/suffix.txt";
	string arrayPath = "BWT/array.txt";
	string BWTPath = "BWT/bwt.txt";
	string PreBWTPath = "BWT/pre_bwt.txt";

	// read File
	ifstream openArrayFile(arrayPath.data());
	if (openArrayFile.is_open()) {
		string line;
		int con = 0;
		while (getline(openArrayFile, line))
		{
			seqArray[con] = atoi(line.c_str());
			con++;
		}
		openArrayFile.close();
	}

	// read File
	ifstream openFile(suffixPath.data());
	if (openFile.is_open()) {
		string line;
		int con = 0;
		while (getline(openFile, line))
		{
			if (con == 0)
			{
				bwt.append(1, line[len - con]);
				preBwt.append(1, line[0]);
				con++;
			}
			else
			{
				bwt.append(1, line[1]);
				preBwt.append(1, line[0]);
			}
		}
		openFile.close();
	}

	// write BWT File
	ofstream writeBWT(BWTPath.data());
	if (writeBWT.is_open()) {
		for (int i = len - 1; i >= 0; i--)
		{
			writeBWT << bwt[seqArray[i]];
			writeBWT << endl;
		}
		writeBWT.close();
	}
	// write PreBWT File
	ofstream writeSufPreBWT(PreBWTPath.data(), ios::app);
	if (writeSufPreBWT.is_open()) {
		for (int i = len - 1; i >= 0; i--)
		{
			writeSufPreBWT << preBwt[seqArray[i]];
			writeSufPreBWT << endl;
		}
		writeSufPreBWT.close();
	}
}

void calDiff(string reference)
{
	string mySeqPath = "mySequence_snp_1.0_test.txt";
	string mySeq;

	int count = 0;

	// read File
	ifstream openFile(mySeqPath.data());
	if (openFile.is_open()) {
		while (getline(openFile, mySeq));
		openFile.close();
	}


	for (int i = 0; i < reference.size(); i++)
	{
		if (reference[i] == mySeq[i])
			count++;
	}

	cout << "My DNA와 복원한 값의 일치율 : " << float(count) / reference.size() * 100 << "%" << endl;
}