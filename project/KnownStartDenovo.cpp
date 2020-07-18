#pragma warning (disable: 4996)
#define CHECK_TIME_START if (QueryPerformanceFrequency((_LARGE_INTEGER*)&freq)) {QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a,b) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a=(float)((double)(end - start)/freq*1000); b=TRUE; } else b=FALSE;
#define RE_DEFINE __int64 freq, start, end;

#define REFER_FILENAME "reference_test2.txt"
#define MY_DNA_RESULT_FILENAME "My_DNA_Result.txt"

#define MY_DNA_FILENAME "mySequence_snp_10.0.txt"
#define MY_SHORT_FILENAME "shortRead_30000.txt"
#define CANDIDATE "Candidate_final.txt"
#define ERASED_BUF "Erased_ShortRead_final.txt"

#define THRESHOLD 8

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void brute_denovo();
void accuracy();

//������ �ѹ� ��� �����, �̾���ϱ�
int main() {
	RE_DEFINE;	//�ð� ������ ���� ���� ������
	float time = 0;	//���� �ð��� 0.0
	bool err;		//����ð� ������ err ����

	CHECK_TIME_START;	//���� ���۽��� ����(������)
	brute_denovo();
	CHECK_TIME_END(time, err);	//������� ���� �� ����-����(����ð�) ����(������)
	if (err) {
		cout << "\nDE NOVO Method ����ð� : " << time / 1000 << " s" << endl;
	}

	accuracy();

	return 0;
}

//���� :: ������ �������� ó�� �κ�(��Ʈ������ ���̸�ŭ)�� �˰��־�� �Ѵ�.
void brute_denovo() {
	ifstream ShortRead(MY_SHORT_FILENAME);	//��Ʈ������� �ִ� ����
	string buf_str;	//��Ʈ���� ������ ��ü ������ ���� ����
	//-----------------------���ۿ� ��Ʈ���� ���---------------------------//
	ShortRead.seekg(0, ios::end);
	int size1 = ShortRead.tellg();
	buf_str.resize(size1);
	ShortRead.seekg(0, ios::beg);
	ShortRead.read(&buf_str[0], size1);
	ShortRead.close();
	//----------------------------------------------------------------------//
	//------------------------------�ʱ�ȭ----------------------------------//
	//Final Test��
	string A = "GTGGGTAATCGAGTCATAGCCACCATACTTTACTCGAGCGAACCAGTAGT";
	//shortRead_test ���Ϸ� ������
	//string A = "AATACTAGCACCTCGATATGGTAACTCTACATAGTCGCTAGGAGAAGAGG";
	//shortRead_test2 ���Ϸ� ������
	//string A = "TTACGCACGGCGCTTCACCCTCGATGGTTATGATCGCCTCGAGTGTATGTGGACGCCGACTCCGCCACCGCTTCTAGTTAACCACGCCACGGCGCTGGCC";
	//shortRead_test3 ���Ϸ� ������
	//string A = "TACGCGATACACCTCTTGCCATTCGACGATCAGGCCGCAAATTGATAGCCACACGTCAATCGAGCTCCAAGGACGAGGTCTGCACTCGTCTTTGAACTCA";
	string n;
	int L = A.size();
	int j = 1;
	//----------------------------------------------------------------------//
	//-----------------------Start Shortread Ȯ��---------------------------//
	while (j > 0) {
		j = buf_str.find("\n", j + 1);	//������ �տ������� ���๮���� ��ġ�� ã�´�
		if (j < 0) break;				//���̻� ���๮�ڰ� ������ -1��ȯ(Ż��)
		if (buf_str[j - 1] == 'N') continue;	//N���� �ٲ�(ã��) ���ڿ� ��ġ�� �ѱ��
		n = buf_str.substr(j - L, L);	//���� ��Ʈ���� n�� (ã�� ���๮�� - ��Ʈ���� ����(L))��ġ���� L���� ���ڿ�
		int appendStartPoint = 0;		//�󸶳� Ŀ���� �̵��ߴ��� ������ ����
		for (int i = A.size() - L; i < A.size(); i++) {	//�����̵�(�� ������ġ)
			bool isMatch = TRUE;	//append ������ ���ڿ��϶� �����Ǵ� bool ����
			appendStartPoint++;		//append �ϰԵ� �������� ����ϴ� ����, �����̵�(�� ������ġ) �Ҷ����� ���� 
			for (int k = 0; k < L / THRESHOLD; k++) {	//L ������ �Ϻκ�(0.25�� L������ �ؼ� ���ǹ��ϰ� ���� ���� ��Ÿ���� Ƚ���� ����)
				if (A[k + i] != n[k]) {			//�����̵�(���ڿ�)
					isMatch = FALSE;			//����ġ�κ� �߽߰� �� ��ġ������ append �Ұ���
					break;						//�����̵� Ŀ�� �̵��� ���� 1��1�� �ݺ��� Ż��
				}
			}
			if (isMatch && appendStartPoint > 1 && appendStartPoint < n.size()) {	//L ������ �Ϻκ��� ������ ���
				A.append(n, n.size() - appendStartPoint + 1, appendStartPoint - 1);	//�����س��� append ���������� shortread �������� ���̱�
				buf_str.replace(j - n.size(), L, L, 'N');	//����� ���ڿ��� N���� �ٲپ ������ Ž������ �ʴ´�.
			}
		}
		j++;	//���� ���๮�ڸ� ã�� ���� ���� ���๮�� ��ġ �������� ã�� �� �ֵ��� j���� ����
	}
	//----------------------------------------------------------------------//
	//------------------Ȯ��� Shortread�κ��� ���� ����--------------------//
	int repeat = 300;	//�⺻������ �ִ� 500ȸ �������� �ݺ�
	while (repeat) {
		bool wasMatch = FALSE;	//������ �ϳ��̻� append �Ǿ��ٸ� TRUE�� ��ȯ��
	//���� ������ ���� ����, �ٸ� �ݺ���
		j = 1;
		while (j > 0) {
			j = buf_str.find("\n", j + 1);
			if (j < 0) break;
			if (buf_str[j - 1] == 'N') continue;
			n = buf_str.substr(j - L, L);
			int appendStartPoint = 0;
			for (int i = A.size() - L; i < A.size(); i++) {
				bool isMatch = TRUE;
				appendStartPoint++;
				for (int k = 0; k < L / THRESHOLD; k++) {
					if (A[k + i] != n[k]) {
						isMatch = FALSE;
						break;
					}
				}
				if (isMatch && appendStartPoint > 1 && appendStartPoint < n.size()) {
					A.append(n, n.size() - appendStartPoint + 1, appendStartPoint - 1);
					buf_str.replace(j - n.size(), L, L, 'N');
					wasMatch = TRUE;	//�� ���ǹ��� ���Դٴ� ���� append�� �߻��ߴٴ� ���̴�.
				}
			}
			j++;
		}
		if (!wasMatch) break;	//���� ���۸� ��ü ��ĵ�ϸ鼭 append�� ���� ���ٸ� Ż��
		cout << repeat << "ȸ �ݺ���...\n";
		repeat--;
	}
	//----------------------------------------------------------------------//
	cout << "De novo Method Result :: \n" << A;
	//-------------------���(�������/���ۻ����)����--------------------//
	ofstream resultCandidate1(CANDIDATE);
	if (resultCandidate1.is_open()) {
		resultCandidate1.write(A.c_str(), A.size());
	}
	resultCandidate1.close();

	ofstream resultBuf(ERASED_BUF, ios::out);
	if (resultBuf.is_open()) {
		resultBuf.write(buf_str.c_str(), buf_str.size());
	}
	resultBuf.close();
	//----------------------------------------------------------------------//
	return;
}

void accuracy() {
	ifstream MyDNA(MY_DNA_FILENAME);
	ifstream MyResult(CANDIDATE);
	string DNA;
	string Result;

	//���� DNA ��ü �޾ƿ���
	MyDNA.seekg(0, ios::end);
	int originalSize = MyDNA.tellg();
	DNA.resize(originalSize);
	MyDNA.seekg(0, ios::beg);
	MyDNA.read(&DNA[0], originalSize);

	//�����̵� DNA ��ü �޾ƿ���
	MyResult.seekg(0, ios::end);
	int candidateSize = MyResult.tellg();
	Result.resize(candidateSize);
	MyResult.seekg(0, ios::beg);
	MyResult.read(&Result[0], candidateSize);

	int i = 0;
	int j = candidateSize;
	int missMatch = 0;
	double accuracy = 0;
	if (candidateSize > originalSize) {
		j = originalSize;
		cout << "\nCAUTION :: 'OVER RECONSTRUCTED DNA' PROBLEM HAS BEEN OCCURED!\n";
		while (j) {
			//���� �����Ϳ� ���� ���� �ٿ��� ���� �ľ�
			if (Result[i] != DNA[i]) {
				missMatch++;
			}
			i++;
			j--;
		}
		accuracy = ((double)missMatch * 100.0) / (double)originalSize;
		cout << "��Ȯ��(ovrematched) :: " << 100 - accuracy << "%\n";
		return;
	}

	while (j) {
		//���� �����Ϳ� ���� ���� �ٿ��� ���� �ľ�
		if (Result[i] != DNA[i]) {
			missMatch++;
		}
		i++;
		j--;
	}
	cout << "���� �����Ϳ� ��ġ���� �ʴ� �ٿ���� �� " << missMatch << "�� �Դϴ�.\n";
	cout << "���� ������ũ�� ��� �������� " << ((double)candidateSize / (double)originalSize) * 100 << "% �Դϴ�.\n";

	accuracy = ((double)missMatch * 100.0) / (double)originalSize;

	cout << "��Ȯ�� :: " << 100 - accuracy << "%\n";
}