// 2014112022, ���ֿ�

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
void reconstruct(string*, int**, int);
int* setBWT(char**, int*, int[][2], int*);
void setTable(char[][1000]);
string reconstruct(char**, int*, int[][2], int, int*);
string insertShortRead(string, string, int*, int);
void printBWT(string, int*, char*, char*);
void calDiff(string);



// ������ų ������ ������ �ٲٰ� ���� �� �̰��� �ٲ�
int changeDataNum = 1000000;
string bwtReal;
string preBwtReal;

string refFilePath = "reference_1000000.txt";
string shortReadPath = "shortRead_300000.txt";
string mySeqPath = "mySequence_snp_10.0.txt";


int main(void)
{
	time_t start, end;
	double result;
	start = time(NULL); // �ð� ���� ����

	// -----------------------------------
	// redy to algorithm

	// use variable
	string refString;
	int* seqArray;
	int col = 50; // ��

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
	int* locationBWT = new int[changeDataNum];
	char** bwt = new char* [2];
	for (int i = 0; i < 2; i++)
		bwt[i] = new char[changeDataNum];

	seqArray = setBWT(bwt, seqArray, table, locationBWT);
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




void sort(int k, vector<int>& perm, vector<int>& group)
{
	// ù k ���ڸ� �������� �Ű��� group ��ȣ�� �̿��Ͽ� ���̻� �迭�� ��� �����Ѵ�.

	int n = perm.size();

	// ��� ���Ľ� ����ϴ� bucket�� ����
	// ù group ��ȣ�� ������ �ƽ�Ű �ڵ带 �̿��ϹǷ� char�� �ִ��� ���� �� �־�� �ϰ�,
	// �� ���Ŀ��� 0������ �ִ� n-1���� �Ű��� �� �����Ƿ� �̿� �°� range�� ��´�.
	int range = max(n, (int)numeric_limits<char>::max());

	vector<int> cnt(range + 1, 0);
	for (int i = 0; i < n; i++)
	{
		if (i + k < n)
			cnt[group[i + k]]++;
		else
			cnt[0]++;
	}

	for (int i = 1; i <= range; i++)
	{
		cnt[i] += cnt[i - 1];
	}

	vector<int> newPerm(n);
	for (int i = n - 1; i >= 0; i--)
	{
		if (perm[i] + k < n)
			newPerm[--cnt[group[perm[i] + k]]] = perm[i];
		else
			newPerm[--cnt[0]] = perm[i];
	}
	swap(perm, newPerm);
}


void findSuffixArr(string& refString, int* seqArray)
{
	// ���ڿ� s�� ���̻� �迭�� ��ȯ��

	int len = refString.size();

	// ���̻� �迭, �� ���̻��� ���� ��ġ�� �����ϴ� ������ �� �� �ִ�.
	vector<int> perm(len);
	for (int i = 0; i < len; i++)
	{
		perm[i] = i;
	}

	// �� ���̻���� ù k ���ڸ� �������� �Ű��� group ��ȣ
	// ù k ���ڰ� ������ �տ� ���� ���� ��������� ���� ��ȣ�� �ο��Ѵ�.
	vector<int> group(len + 1);
	for (int i = 0; i < len; i++)
	{
		group[i] = refString[i];
	}

	for (int k = 1; k < len; k *= 2)
	{
		sort(k, perm, group); // ù [k ~ 2*k) ���ڸ� �������� ����
		sort(0, perm, group); // ù [0 ~ k) ���ڸ� �������� ����

		// group ��ȣ�� �����Ѵ�.
		vector<int> newGroup(len + 1); // �� group ��ȣ (�ӽ� �迭)
		newGroup[perm[0]] = 0;
		for (int i = 1; i < len; i++)
		{
			if (group[perm[i]] == group[perm[i - 1]] && group[perm[i] + k] == group[perm[i - 1] + k])
				newGroup[perm[i]] = newGroup[perm[i - 1]];
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
		}

		swap(group, newGroup);

		if (group[perm[len - 1]] == len - 1) break; // ����ȭ
	}


	for (int i = len - 1; i >= 0; i--)
		seqArray[i] = perm[len - 1 - i];
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
	// bwt�� ����� ���� suffixes�� ����� �Լ�

	string suffixPath = "BWT/suffix.txt";
	string arrayPath = "BWT/array.txt";
	string suffix;

	int len = refString.size();


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

string reconstruct(char** bwt, int* seqArray, int table[][2], int shortLen, int* locationBWT)
{
	// ���ڿ��� �����ϱ� ���� �Լ�

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
					// front ���� ����
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
										// ���۷������� ã�� ����

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
										// miss match ���� 3������ �����

										fcon = 0;
										front++;
										frontNext = -1;
										missmatch[0] = 0;
									}
									else
									{
										if (shortLen - fcon == 0)
										{
											// ���۷������� ã�� ����

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
					// end ���� ����
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
										// ���۷������� ã�� ����

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
										// miss match ���� 3������ �����

										econ = 0;
										end--;
										endNext = -1;
										missmatch[1] = 0;
									}
									else
									{
										if (shortLen - econ == 0)
										{
											// ���۷������� ã�� ����

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
			// ����ٰ� ���۷����� �����ϴ� �Լ� ����
			reference = insertShortRead(reference, line, seqArray, succe);
		}
		openSRFile.close();
	}

	return reference;
}

int* setBWT(char** bwt, int* seqArray, int table[][2], int* locationBWT)
{
	string arrayPath = "BWT/array.txt";
	string BWTPath = "BWT/bwt.txt";
	string PreBWTPath = "BWT/pre_bwt.txt";

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
	cout << "Array ���� �Ϸ�" << endl;


	for (i = 0; i < len; i++)
	{
		bwt[0][i] = preBwtReal[i];

		if (i)
		{
			if (bwt[0][i - 1] != bwt[0][i])
			{
				// �� ������ ���۰� ������ ��ġ ����

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
			// table �ʱ� ����
			// pre train�� ù ���� ������ $ ��
			table[temp][0] = 0;
			temp++;
		}
	}
	table[temp - 1][1] = i - 1;
	cout << "Pre BWT ��ġ ���̺�1 �Ϸ�" << endl;


	temp_0 = table[0][0];
	temp_A = table[1][0];
	temp_C = table[2][0];
	temp_G = table[3][0];
	temp_T = table[4][0];

	for (int j = 0; j < len; j++)
	{
		bwt[1][j] = bwtReal[j];

		// �� ��ġ�� ����ִ� ��
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
	cout << "BWT ���̺� �� �Ϸ�" << endl;

	delete[] seqArray;

	return seq;
}


string insertShortRead(string reference, string shortRd, int* seqArray, int succe)
{
	// ���۷����� short read �����ϴ� �Լ�

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
	// BWT�� save�ϴ� �Լ�
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
	string myDNAPath = "BWT/Reconstruction.txt";
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

	cout << "My DNA�� ������ ���� ��ġ�� : " << float(count) / reference.size() * 100 << "%" << endl;



	// write MyDNA File
	ofstream writeSufPreBWT(myDNAPath.data());
	if (writeSufPreBWT.is_open())
	{
		writeSufPreBWT << reference;
		writeSufPreBWT.close();
	}
}