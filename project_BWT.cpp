// 2014112022, 문주원

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include<vector>

using namespace std;


bool cmp(int i, int j);
void constructSA();

string load(void);
void generateSuffix(string, int*, char*, char*);
void sort(int k, vector<int>&, vector<int>&);
void findSuffixArr(string&, int*);
int* setBWT(char**, int*, int[][2], int*);
void setTable(char[][1000]);
string reconstruct(string, char**, int*, int[][2], int, int*);
string insertShortRead(string, string, int*, int);
void printBWT(string, int*, char*, char*);
void calDiff(string);



string bwtReal;
string preBwtReal;

string refFilePath = "test_ref_1000.txt";
string shortReadPath = "shortread_1000.txt";
string mySeqPath = "Mydna_1000.txt";


int main(void)
{
	time_t start, end;
	double result;
	start = time(NULL); // 시간 측정 시작

	// -----------------------------------
	// redy to algorithm

	// use variable
	string refString;
	int* seqArray;
	int col = 0; // 열

	char* front_suf;
	char* end_suf;

	//refString = "CTAGCATGGAC$";
	refString = load();
	seqArray = new int[refString.size()];
	front_suf = new char[refString.size()];
	end_suf = new char[refString.size()];
	// -----------------------------------


	// -----------------------------------
	// create BWT, pre BWT, sequence array

	generateSuffix(refString, seqArray, front_suf, end_suf);
	printBWT(refString, seqArray, front_suf, end_suf);
	// -----------------------------------


	// -----------------------------------
	// exact Matching using BWT

	cout << endl;
	cout << "Matching srtart" << endl;

	int table[5][2];
	int* locationBWT = new int[refString.size()];
	char** bwt = new char* [2];
	for (int i = 0; i < 2; i++)
		bwt[i] = new char[refString.size()];

	seqArray = setBWT(bwt, seqArray, table, locationBWT);
	refString = reconstruct(refString, bwt, seqArray, table, col, locationBWT);
	calDiff(refString);
	// -----------------------------------

	end = time(NULL);
	result = (double)(end - start);
	cout << endl;
	cout << "Total time = " << result << "(s)";
	cout << endl;


	return 0;
}




void sort(int k, vector<int>& suffixRank, vector<int>& tempRank)
{
	// 계수 정렬 함수

	int n = suffixRank.size();

	// 계수 정렬시 사용하는 범위
	// 첫 tempRank 번호는 문자의 아스키 코드를 이용
	// 그 이후에는 0번부터 최대 n-1 알맞게 range를 잡음
	int range = max(n, (int)numeric_limits<char>::max());

	vector<int> cnt(range + 1, 0);
	for (int i = 0; i < n; i++)
	{
		if (i + k < n)
			cnt[tempRank[i + k]]++;
		else
			cnt[0]++;
	}

	for (int i = 1; i <= range; i++)
	{
		cnt[i] += cnt[i - 1];
	}

	vector<int> newSuffixRank(n);
	for (int i = n - 1; i >= 0; i--)
	{
		if (suffixRank[i] + k < n)
			newSuffixRank[--cnt[tempRank[suffixRank[i] + k]]] = suffixRank[i];
		else
			newSuffixRank[--cnt[0]] = suffixRank[i];
	}
	swap(suffixRank, newSuffixRank);
}


void findSuffixArr(string& refString, int* seqArray)
{
	// 문자열 의 suffix array를 구하는 함수

	int len = refString.size();

	vector<int> suffixRank(len);
	for (int i = 0; i < len; i++)
	{
		suffixRank[i] = i;
	}

	vector<int> tempRank(len + 1);
	for (int i = 0; i < len; i++)
	{
		tempRank[i] = refString[i];
	}

	for (int k = 1; k < len; k *= 2)
	{
		sort(k, suffixRank, tempRank);
		sort(0, suffixRank, tempRank);

		// tempRank 번호를 갱신
		vector<int> newTempRank(len + 1);
		newTempRank[suffixRank[0]] = 0;
		for (int i = 1; i < len; i++)
		{
			if (tempRank[suffixRank[i]] == tempRank[suffixRank[i - 1]] && tempRank[suffixRank[i] + k] == tempRank[suffixRank[i - 1] + k])
				newTempRank[suffixRank[i]] = newTempRank[suffixRank[i - 1]];
			else
				newTempRank[suffixRank[i]] = newTempRank[suffixRank[i - 1]] + 1;
		}

		swap(tempRank, newTempRank);

		if (tempRank[suffixRank[len - 1]] == len - 1)
			break;
	}


	for (int i = len - 1; i >= 0; i--)
		seqArray[i] = suffixRank[len - 1 - i];
}


string load(void)
{
	string line;

	// read File
	ifstream openFile(refFilePath.data());
	if (openFile.is_open()) {
		while (getline(openFile, line));
		line.append(1, '$');

		openFile.close();
	}

	return line;
}

void generateSuffix(string refString, int* seqArray, char* front, char* end)
{
	// bwt를 만들기 위한 suffixes를 만드는 함수

	string suffixPath = "BWT/suffix.txt";
	string arrayPath = "BWT/array.txt";
	string suffix;

	int len = refString.size();


	// BWT와 Pre BWT 복원 시 필요한 문자를 셋
	for (int i = 0; i < len; i++)
	{
		front[i] = refString[i];

		if (i)
			end[i] = refString[i - 1];
		else
			end[i] = refString[len - 1];
	}


	cout << "Start Manber-Myers Algorithm" << endl;
	findSuffixArr(refString, seqArray);

	cout << "Manber-Myers Algorithm done" << endl;
}

string reconstruct(string reference, char** bwt, int* seqArray, int table[][2], int shortLen, int* locationBWT)
{
	// 문자열을 복원하기 위한 함수

	int check;


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

			shortLen = line.size();


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

int* setBWT(char** bwt, int* seqArray, int table[][2], int* locationBWT)
{
	int* seq = new int[bwtReal.size()];

	int i;
	int len = bwtReal.size();

	int temp = 0;

	int temp_0;
	int temp_A;
	int temp_C;
	int temp_G;
	int temp_T;


	for (int j = len - 1; j >= 0; j--)
		seq[j] = seqArray[len - 1 - j];
	cout << "Array 정렬 완료" << endl;


	for (i = 0; i < len; i++)
	{
		bwt[0][i] = preBwtReal[i];

		if (i)
		{
			if (bwt[0][i - 1] != bwt[0][i])
			{
				// 각 문자의 시작과 마지막 위치 세팅

				table[temp][0] = i;
				if (temp < 5)
				{
					table[temp - 1][1] = i - 1;
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
	}
	table[temp - 1][1] = i - 1;
	cout << "Pre BWT 위치 테이블1 완료" << endl;


	temp_0 = table[0][0];
	temp_A = table[1][0];
	temp_C = table[2][0];
	temp_G = table[3][0];
	temp_T = table[4][0];

	for (int j = 0; j < len; j++)
	{
		bwt[1][j] = bwtReal[j];

		// 각 위치를 잡아주는 절
		if (bwt[1][j] == '$')
		{
			locationBWT[j] = temp_0;
			temp_0++;
		}
		else if (bwt[1][j] == 'A')
		{
			locationBWT[j] = temp_A;
			temp_A++;
		}
		else if (bwt[1][j] == 'C')
		{
			locationBWT[j] = temp_C;
			temp_C++;
		}
		else if (bwt[1][j] == 'G')
		{
			locationBWT[j] = temp_G;
			temp_G++;
		}
		else
		{
			locationBWT[j] = temp_T;
			temp_T++;
		}
	}
	cout << "BWT 테이블 셋 완료" << endl;

	delete[] seqArray;

	return seq;
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


void printBWT(string tempSequence, int* seqArray, char* front, char* end)
{
	// BWT를 save하는 함수
	int len = tempSequence.size();


	for (int i = len - 1; i >= 0; i--)
	{
		bwtReal.append(1, end[seqArray[i]]);
		preBwtReal.append(1, front[seqArray[i]]);
	}

	delete[] front;
	delete[] end;
}

void calDiff(string reference)
{
	string myDNAPath = "repair_dna_1000.txt";
	string mySeq;

	int count = 0;

	// 마지막 $ 문자 제거
	reference = reference.substr(0, reference.size() - 1);

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



	// write MyDNA File
	ofstream writeSufPreBWT(myDNAPath.data());
	if (writeSufPreBWT.is_open())
	{
		writeSufPreBWT << reference;
		writeSufPreBWT.close();
	}
}