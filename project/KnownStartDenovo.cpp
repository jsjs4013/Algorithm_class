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

//파일을 한번 열어서 덮어쓰기, 이어쓰기하기
int main() {
	RE_DEFINE;	//시간 측정에 쓰일 변수 재정의
	float time = 0;	//시작 시간은 0.0
	bool err;		//실행시간 측정시 err 검증

	CHECK_TIME_START;	//실행 시작시점 저장(재정의)
	brute_denovo();
	CHECK_TIME_END(time, err);	//종료시점 저장 및 종료-시작(실행시간) 측정(재정의)
	if (err) {
		cout << "\nDE NOVO Method 실행시간 : " << time / 1000 << " s" << endl;
	}

	accuracy();

	return 0;
}

//조건 :: 복원할 유전자의 처음 부분(쇼트리드의 길이만큼)을 알고있어야 한다.
void brute_denovo() {
	ifstream ShortRead(MY_SHORT_FILENAME);	//쇼트리드들이 있는 파일
	string buf_str;	//쇼트리드 파일의 전체 내용이 담기는 버퍼
	//-----------------------버퍼에 쇼트리드 담기---------------------------//
	ShortRead.seekg(0, ios::end);
	int size1 = ShortRead.tellg();
	buf_str.resize(size1);
	ShortRead.seekg(0, ios::beg);
	ShortRead.read(&buf_str[0], size1);
	ShortRead.close();
	//----------------------------------------------------------------------//
	//------------------------------초기화----------------------------------//
	//Final Test용
	string A = "GTGGGTAATCGAGTCATAGCCACCATACTTTACTCGAGCGAACCAGTAGT";
	//shortRead_test 파일로 복원시
	//string A = "AATACTAGCACCTCGATATGGTAACTCTACATAGTCGCTAGGAGAAGAGG";
	//shortRead_test2 파일로 복원시
	//string A = "TTACGCACGGCGCTTCACCCTCGATGGTTATGATCGCCTCGAGTGTATGTGGACGCCGACTCCGCCACCGCTTCTAGTTAACCACGCCACGGCGCTGGCC";
	//shortRead_test3 파일로 복원시
	//string A = "TACGCGATACACCTCTTGCCATTCGACGATCAGGCCGCAAATTGATAGCCACACGTCAATCGAGCTCCAAGGACGAGGTCTGCACTCGTCTTTGAACTCA";
	string n;
	int L = A.size();
	int j = 1;
	//----------------------------------------------------------------------//
	//-----------------------Start Shortread 확장---------------------------//
	while (j > 0) {
		j = buf_str.find("\n", j + 1);	//버퍼의 앞에서부터 개행문자의 위치를 찾는다
		if (j < 0) break;				//더이상 개행문자가 없으면 -1반환(탈출)
		if (buf_str[j - 1] == 'N') continue;	//N으로 바뀐(찾은) 문자열 위치는 넘긴다
		n = buf_str.substr(j - L, L);	//비교할 쇼트리드 n은 (찾은 개행문자 - 쇼트리드 길이(L))위치부터 L개의 문자열
		int appendStartPoint = 0;		//얼마나 커서를 이동했는지 저장할 변수
		for (int i = A.size() - L; i < A.size(); i++) {	//슬라이딩(비교 시작위치)
			bool isMatch = TRUE;	//append 가능한 문자열일때 유지되는 bool 변수
			appendStartPoint++;		//append 하게될 시작점을 기록하는 변수, 슬라이딩(비교 시작위치) 할때마다 증가 
			for (int k = 0; k < L / THRESHOLD; k++) {	//L 길이의 일부분(0.25의 L제곱을 해서 유의미하게 작은 값이 나타나는 횟수로 가정)
				if (A[k + i] != n[k]) {			//슬라이딩(문자열)
					isMatch = FALSE;			//불일치부분 발견시 현 위치에서는 append 불가능
					break;						//슬라이딩 커서 이동을 위해 1대1비교 반복문 탈출
				}
			}
			if (isMatch && appendStartPoint > 1 && appendStartPoint < n.size()) {	//L 길이의 일부분이 동일한 경우
				A.append(n, n.size() - appendStartPoint + 1, appendStartPoint - 1);	//저장해놓던 append 시작점부터 shortread 시작점에 붙이기
				buf_str.replace(j - n.size(), L, L, 'N');	//사용한 문자열은 N으로 바꾸어서 다음에 탐색하지 않는다.
			}
		}
		j++;	//다음 개행문자를 찾기 위해 이전 개행문자 위치 다음부터 찾을 수 있도록 j변수 조정
	}
	//----------------------------------------------------------------------//
	//------------------확장된 Shortread로부터 복원 시작--------------------//
	int repeat = 300;	//기본적으로 최대 500회 복원과정 반복
	while (repeat) {
		bool wasMatch = FALSE;	//이전에 하나이상 append 되었다면 TRUE로 변환됨
	//이하 내용은 위와 동일, 다만 반복함
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
					wasMatch = TRUE;	//이 조건문에 들어왔다는 것은 append가 발생했다는 것이다.
				}
			}
			j++;
		}
		if (!wasMatch) break;	//만약 버퍼를 전체 스캔하면서 append된 적이 없다면 탈출
		cout << repeat << "회 반복중...\n";
		repeat--;
	}
	//----------------------------------------------------------------------//
	cout << "De novo Method Result :: \n" << A;
	//-------------------결과(복원결과/버퍼사용결과)저장--------------------//
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

	//실제 DNA 전체 받아오기
	MyDNA.seekg(0, ios::end);
	int originalSize = MyDNA.tellg();
	DNA.resize(originalSize);
	MyDNA.seekg(0, ios::beg);
	MyDNA.read(&DNA[0], originalSize);

	//시퀸싱된 DNA 전체 받아오기
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
			//실제 데이터와 같지 않은 핵염기 갯수 파악
			if (Result[i] != DNA[i]) {
				missMatch++;
			}
			i++;
			j--;
		}
		accuracy = ((double)missMatch * 100.0) / (double)originalSize;
		cout << "정확도(ovrematched) :: " << 100 - accuracy << "%\n";
		return;
	}

	while (j) {
		//실제 데이터와 같지 않은 핵염기 갯수 파악
		if (Result[i] != DNA[i]) {
			missMatch++;
		}
		i++;
		j--;
	}
	cout << "실제 데이터와 일치하지 않는 핵염기는 총 " << missMatch << "개 입니다.\n";
	cout << "실제 데이터크기 대비 복원율은 " << ((double)candidateSize / (double)originalSize) * 100 << "% 입니다.\n";

	accuracy = ((double)missMatch * 100.0) / (double)originalSize;

	cout << "정확도 :: " << 100 - accuracy << "%\n";
}