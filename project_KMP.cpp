#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <Windows.h>

using namespace std;

int misMatchAllowed = 2; // 허용된 미스매치 횟수
int refDNANumber[15000] = { 0, }; // 복원된 MyDNA의 복원된 문자열의 자리. 복원됐으면 각 자리마다 있는 0을 1로 변경.
// 넘버가 1인 문자열의 자리가 존재할 때는 비교하지 않고 바로 건너뛴다.

void kmpAlgorithm(string ref, string sr, string& md, int& start, int& end, int misMatch, int& correct); // KMP 알고리즘을 수행할 함수 선언
// 매개변수는 Reference, ShortRead, 복원할 My DNA, ShortRead와 비교를 시작할 Reference의 시작(start)과 끝(end) 부분, 미스매치, correct 변수이며,
// 이 중 start, end, correct, 복원할 My DNA 변수는 KMP 함수에서 즉시 수정 가능하다.

int main() {
	clock_t timeStart, timeEnd;
	double timeSub; // 시간을 재기 위한 변수 3가지를 선언

	ifstream refFile("reference_test.txt");
	if (refFile.fail()) {
		cout << "Reference DNA를 읽어들이는 데 실패했습니다.\n";
		return 1;
	}
	ifstream mydnaFile("mySequence_snp_1.0_test.txt");
	if (mydnaFile.fail()) {
		cout << "My DNA를 읽어들이는 데 실패했습니다.\n";
		return 1;
	}
	ifstream shortreadFile("shortRead_test.txt");
	if (shortreadFile.fail()) {
		cout << "ShortRead를 읽어들이는 데 실패했습니다.\n";
		return 1;
	} // Reference, SNP이 존재하는 비교용 My DNA, ShortRead이 존재하는 파일 읽기

	string refDNA; // 원본 데이터, 원래는 길이가 1억이지만 알고리즘 테스트를 위해 15,000으로 함
	string MyDNA; // 비교할 데이터, 원본 데이터에서 약 0.01% ~ 1%의 스닙만 발생
	string shortRead[10000]; // 원래는 2,000만개, 알고리즘 테스트를 위해 500개로만 함
	string MyDNA2(15000, 'O');; // ShortRead로 복원한 데이터
	int count = 0; // ShortRead 파일을 읽어들일 때 필요한 변수
	int index; // 쇼트리드 2,000만개를 비교하기 위해 필요한 변수
	int misMatch; // 비교했을 때 생기는 미스매치 횟수
	int start = 0, end = start + 50; // 비교할 때 Reference의 첫 문자의 위치와 마지막 문자의 위치, ShortRead 하나의 길이가 50일 때
	int correct; // shortRead로 복원했을 때 correct를 1로 변경 후 다음 shortRead로 넘어감.
	int j = 0; // KMP 알고리즘에 사용될 변수
	int count1 = 0; // 이미 복원된 문자열이 있는 지 파악하기 위한 변수, 0이 아니라면 비교하지 않고 ShortRead의 길이만큼 건너뛴다.

	if (refFile.is_open()) {
		refFile >> refDNA;
	}

	if (mydnaFile.is_open()) {
		mydnaFile >> MyDNA;
	} // Reference, 비교용 My DNA의 내용을 각각 미리 선언해 둔 string에 작성한다.

	cout << "SNP 1%의 My DNA ::" << endl;
	cout << MyDNA << endl;
	cout << endl;

	while (shortreadFile.peek() != EOF) {
		getline(shortreadFile, shortRead[count]);
		count++;
	} // ShortRead 파일을 한 줄씩 읽어들여 string 배열에 작성한다.

	timeStart = clock(); // 비교하기 직전에 시간을 잰다.
	for (index = 0; index < 10000; index++) { // 원래는 2,000만번 비교
		start = 0;
		end = start + 50;
		j = 0; // ShortRead를 이용하여 복원 완료 시, 다음 ShortRead를 이용하기 전에 이용할 변수들 0으로 초기화
		do {
			count1 = 0;
			misMatch = 0;
			correct = 0;
			for (int a = start; a < end; a++) {
				if (refDNANumber[a] == 1) {
					count1++;
				} // 복원된 문자가 하나라도 존재하면 count1을 증가시킨다.
			}
			if (count1 == 0) { // count1이 0이면 비교 시작
				for (int i = start; i < end; i++) {
					if (refDNA.substr(i, 1) != shortRead[index].substr(j, 1)) { // Reference와 Shortread 비교, Reference는 start번째부터 시작하고 ShortRead는 0번째부터 시작
						misMatch++; // 문자열이 다르면 미스매치 증가
					}
					j++; // ShortRead의 index 증가
				}
				if (misMatch <= misMatchAllowed) { // 미스매치가 3 이하이면
					MyDNA2.replace(start, 50, shortRead[index]);
					for (int a = start; a < end; a++) {
						refDNANumber[a] = 1;
					} // 복원하고 복원된 문자열의 위치에 해당하는 넘버는 1로 변경
					correct = 1; // correct 변수를 1로 바꾼다. 
				}
				else if (misMatch > misMatchAllowed) { // 미스매치가 3보다 크면 KMP 함수 실행
					kmpAlgorithm(refDNA, shortRead[index], MyDNA2, start, end, 0, correct);
				}
			}
			else if (count1 > 0) { // count1이 0보다 크면, 비교를 멈추고 ShortRead의 길이만큼 비교할 Reference의 부분 문자열 위치를 옮긴다.
				start += 50;
				end = start + 50;
			}
		} while (correct != 1); // correct 변수가 1이면 i번째 ShortRead와 Reference와의 비교를 끝내고 i + 1번째 ShortRead로 넘어간다.
	}

	cout << "복원한 My DNA ::" << endl;
	cout << MyDNA2 << endl;
	cout << endl;

	int compare = 0;

	for (int i = 0; i < 15000; i++) { // 복원한 My DNA와 비교용 My DNA를 비교
		if (MyDNA.substr(i, 1) == MyDNA2.substr(i, 1)) {
			compare++;
		}
	}

	double comparePercent = (double)compare / (double)15000; // 일치율 계산

	cout << "MyDNA와 복원한 MyDNA 일치율 ::" << endl;
	cout << comparePercent * 100 << "%" << endl;
	cout << endl;

	timeEnd = clock(); // 알고리즘 종료 시 재고 있던 시간을 멈춘다.
	timeSub = (double)timeEnd - (double)timeStart; // 걸린 시간 계산
	cout << "KMP 알고리즘 걸린 시간 :: " << endl;
	cout << timeSub / 1000 << "초" << endl;
	cout << endl;

	system("pause");
}

void kmpAlgorithm(string ref, string sr, string& md, int& start, int& end, int mM, int& correct) {
	int count = 0;
	int count1 = 0;
	int j = 0;
	string tmp;
	int tmpCount = 0;

	if (start < 14950 && end < 15000) { // start 지점이 (Reference의 길이 - ShortRead의 길이)를 넘어가버리면 비교가 불가능하므로 제약 조건을 걸어둔다.
		for (int i = 0; i < 50; i++) {
			if (ref.substr(start + i, 1) == sr.substr(i, 1)) {
				tmp += ref.substr(start + i, 1);
			} // KMP 알고리즘 시작
			else {
				if (tmp == "") {
					count++;
					break;
				}
				else {
					break;
				}
			}
		}
		if (tmp != "") { // tmp 문자열의 접두사, 접미사를 이용하여 비교가 필요 없는 부분들은 건너뛴다.
			for (int i = 0; i < tmp.length(); i++) {
				if (tmp.substr(i, 0) == tmp.substr(tmp.length() - 1 - i, 1)) {
					count++;
				}
				else {
					break;
				}
			}

			start += (tmp.length() - count);
		}
		else if (tmp == "") { // tmp 문자열이 비면 그냥 한 칸 넘어감.
			start += count;
		}

		tmp.erase(0, tmp.length()); // tmp 문자열을 비운다.
		end = start + 50;

		// 여기서부터는 main()에 있는 복원 과정과 동일하다.
		if (start < 14950 && end < 15000) {
			for (int a = start; a < end; a++) {
				if (refDNANumber[a] == 1) {
					count1++;
				}
			}
			if (count1 == 0) {
				for (int i = start; i < end; i++) {
					if (ref.substr(i, 1) != sr.substr(j, 1)) {
						mM++;
					}
					j++;
				}
				if (mM <= misMatchAllowed) {
					md.replace(start, 50, sr);
					correct = 1;
				}
				else if (mM > misMatchAllowed) {
					kmpAlgorithm(ref, sr, md, start, end, 0, correct);
				}
			}
			else if (count1 > 0) {
				start += 50;
				end = start + 50;
				kmpAlgorithm(ref, sr, md, start, end, 0, correct);
			}
		}
		else if (start >= 14950 || end >= 15000) { // 복원도 못하고 start가 (Reference의 길이 - ShortRead의 길이)를 넘어가버리면 다음 ShortRead로 넘어간다.
			correct = 1;
		}
	}
	else if (start >= 14950 || end >= 15000) { // start가 (Reference의 길이 - ShortRead의 길이)를 넘어가버리면 다음 ShortRead로 넘어간다.
		correct = 1;
	}
}