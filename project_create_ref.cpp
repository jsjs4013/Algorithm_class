// 2014112022, ���ֿ�

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

void inititial(string);
string load(void);
void generateSuffix(string, int*);
void sort(string, int*, int);
void reconstruct(string* s, int** suf, int len);
void setBWT(char**, int*, int[][2], int*);
void setTable(char[][1000]);
string reconstruct(char**, int*, int[][2], int, int*);
string insertShortRead(string, string, int*, int);
void printBWT(string, int*);
void calDiff(string);

int main(void)
{
	// -----------------------------------
	// Only use test
	//string s = "CTAGCATCGAC";

	//inititial(s);
	// -----------------------------------

	// use variable
	string refString;
	char* refSequence;
	int* seqArray;
	char enter;


	// -----------------------------------
	// redy to algorithm
	refString = load();
	seqArray = new int[refString.size()];
	// -----------------------------------


	// -----------------------------------
	// create BWT, pre BWT, sequence array
	//cout << "Enter�� ���� BWT, Pre BWT, Array�� ����ʽÿ�" << endl;
	//cin >> enter;

	//generateSuffix(refString, seqArray);
	//printBWT(refString, seqArray);
	// -----------------------------------


	// -----------------------------------
	// exact Matching using BWT
	//cout << "Enter�� ���� BWT matching�� �����Ͻʽÿ�" << endl;
	//cin >> enter;

	int table[5][2];
	int* locationBWT = new int[1000];
	char** bwt = new char* [2];
	for (int i = 0; i < 2; i++)
		bwt[i] = new char[1000];

	//setBWT(bwt, seqArray, table, locationBWT);
	//refString = reconstruct(bwt, seqArray, table, 100, locationBWT);
	//calDiff(refString);
	// -----------------------------------


	string arrayPath = "BWT/test.txt";
	string a = "asdasdasd";
	ofstream writeFileArray(arrayPath.data());
	if (writeFileArray.is_open()) {
		writeFileArray << a;
		writeFileArray.close();
	}



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
	// bwt�� ����� ���� suffixes�� ����� �Լ�

	char stTemp;
	string suffixPath = "BWT/suffix.txt";
	string arrayPath = "BWT/array.txt";
	string openSufArrayFile = "BWT/sufarray.txt";
	int len = refString.size();
	int count = 0;
	int tempSeq;
	int temp;
	int* tempArr = new int[refString.size()];


	for (int i = 0; i < len; i++)
	{
		string tempSequence;

		if (i)
		{
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
			ifstream openSufArrayFile(openSufArrayFile.data());
			if (openSufArrayFile.is_open()) {
				string line;
				int con = 0;
				while (getline(openSufArrayFile, line))
				{
					tempArr[con] = atoi(line.c_str());
					con++;
				}
				openSufArrayFile.close();
			}
			// read File
			ifstream openFile(suffixPath.data());
			if (openFile.is_open()) {
				string line;
				while (getline(openFile, line))
					tempSequence.append(1, line[len - i - 1]);
				openFile.close();
			}

			for (int j = 0; j < i; j++)
			{
				if (seqArray[j] != tempArr[j])
				{
					for (int k = 0; k < i; k++)
					{
						if (seqArray[j] == tempArr[k])
						{
							stTemp = tempSequence[k];
							tempSequence[k] = tempSequence[j];
							tempSequence[j] = stTemp;

							temp = tempArr[k];
							tempArr[k] = tempArr[j];
							tempArr[j] = temp;

							break;
						}
					}
				}
			}

			sort(tempSequence, seqArray, i);

			seqArray[i] = i;
			tempSeq = i;
		}
		else
		{
			seqArray[i] = i;
			tempSeq = i;
		}


		// write File
		ofstream writeFile(suffixPath.data(), ios::app);
		if (writeFile.is_open()) {
			for (int j = i; j < len; j++)
			{
				writeFile << refString[j];
			}

			if (i > 0)
			{
				writeFile << refString[i - 1]; // BWT ����
			}
			else
			{
				writeFile << refString[len - 1]; // BWT ����
			}
			writeFile << endl;
			writeFile.close();
		}
		// write File
		ofstream writeFileArray(arrayPath.data());
		if (writeFileArray.is_open()) {
			for (int j = 0; j <= i; j++)
			{
				writeFileArray << seqArray[j];
				writeFileArray << endl;
			}

			writeFileArray.close();
		}
		// write File
		ofstream writeSufFileArray(openSufArrayFile.data(), ios::app);
		if (writeSufFileArray.is_open()) {
			writeSufFileArray << tempSeq;
			writeSufFileArray << endl;

			writeSufFileArray.close();
		}
	}
}

void sort(string tempSequence, int* seqArray, int n)
{
	// bwt�� ����� ���� sort�ϴ� �Լ�
	// ������� ���

	int countArr[4];
	int temp;
	int tempSeq;
	int* tempArr = new int[n];

	for (int i = 0; i < 4; i++)
		countArr[i] = 0; // �ʱ�ȭ
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
		countArr[i] = countArr[i] + countArr[i - 1]; // ������
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
}

string reconstruct(char** bwt, int* seqArray, int table[][2], int shortLen, int* locationBWT)
{
	// ���ڿ��� �����ϱ� ���� �Լ�

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

void setBWT(char** bwt, int* seqArray, int table[][2], int* locationBWT)
{
	string arrayPath = "BWT/array.txt";
	string BWTPath = "BWT/bwt.txt";
	string PreBWTPath = "BWT/pre_bwt.txt";


	cout << "File �б� ����" << endl;
	// read array File
	ifstream openFileArray(arrayPath.data());
	if (openFileArray.is_open()) {
		string line;
		int con = 1000;
		while (getline(openFileArray, line))
		{
			seqArray[con] = atoi(line.c_str());
			con--;
		}
		openFileArray.close();
	}
	cout << "Array �б� �Ϸ�" << endl;

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
				// table �ʱ� ����
				// pre train�� ù ���� ������ $ ��
				table[temp][0] = 0;
				temp++;
			}
			con++;
		}
		table[temp - 1][1] = con - 1;
		openFilePreBWT.close();
	}
	cout << "BWT �б� �Ϸ�" << endl;

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

			// �� ��ġ�� ����ִ� ��
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
	cout << "Pre BWT �б� �Ϸ�" << endl;
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


void printBWT(string tempSequence, int* seqArray)
{
	// BWT�� save�ϴ� �Լ�
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
			bwt.append(1, line[len - con]);
			preBwt.append(1, line[0]);
			con++;
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

	cout << "My DNA�� ������ ���� ��ġ�� : " << float(count) / reference.size() * 100 << "%" << endl;
}