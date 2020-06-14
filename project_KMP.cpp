#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <Windows.h>

using namespace std;

int misMatchAllowed = 25; // ���� �̽���ġ Ƚ��
int refDNANumber[1000] = { 0, }; // ������ MyDNA�� ������ ���ڿ��� �ڸ�. ���������� �� �ڸ����� �ִ� 0�� 1�� ����.
// �ѹ��� 1�� ���ڿ��� �ڸ��� ������ ���� ������ �ʰ� �ٷ� �ǳʶڴ�.

void kmpAlgorithm(string ref, string sr, string& md, int& start, int& end, int misMatch, int& correct); // KMP �˰����� ������ �Լ� ����
// �Ű������� Reference, ShortRead, ������ My DNA, ShortRead�� �񱳸� ������ Reference�� ����(start)�� ��(end) �κ�, �̽���ġ, correct �����̸�,
// �� �� start, end, correct, ������ My DNA ������ KMP �Լ����� ��� ���� �����ϴ�.

int main() {
	clock_t timeStart, timeEnd;
	double timeSub; // �ð��� ��� ���� ���� 3������ ����

	ifstream refFile("reference_test.txt");
	if (refFile.fail()) {
		cout << "Reference DNA�� �о���̴� �� �����߽��ϴ�.\n";
		return 1;
	}
	ifstream mydnaFile("mySequence_snp_1.0_test.txt");
	if (mydnaFile.fail()) {
		cout << "My DNA�� �о���̴� �� �����߽��ϴ�.\n";
		return 1;
	}
	ifstream shortreadFile("shortRead_test.txt");
	if (shortreadFile.fail()) {
		cout << "ShortRead�� �о���̴� �� �����߽��ϴ�.\n";
		return 1;
	} // Reference, SNP�� �����ϴ� �񱳿� My DNA, ShortRead�� �����ϴ� ���� �б�

	string refDNA; // ���� ������, ������ ���̰� 1�������� �˰��� �׽�Ʈ�� ���� 15,000���� ��
	string MyDNA; // ���� ������, ���� �����Ϳ��� �� 0.01% ~ 1%�� ���ո� �߻�
	string shortRead[1000]; // ������ 2,000����, �˰��� �׽�Ʈ�� ���� 500���θ� ��
	string MyDNA2(1000, 'O');; // ShortRead�� ������ ������
	int count = 0; // ShortRead ������ �о���� �� �ʿ��� ����
	int index; // ��Ʈ���� 2,000������ ���ϱ� ���� �ʿ��� ����
	int misMatch; // ������ �� ����� �̽���ġ Ƚ��
	int start = 0, end = start + 50; // ���� �� Reference�� ù ������ ��ġ�� ������ ������ ��ġ, ShortRead �ϳ��� ���̰� 50�� ��
	int correct; // shortRead�� �������� �� correct�� 1�� ���� �� ���� shortRead�� �Ѿ.
	int j = 0; // KMP �˰��� ���� ����
	int count1 = 0; // �̹� ������ ���ڿ��� �ִ� �� �ľ��ϱ� ���� ����, 0�� �ƴ϶�� ������ �ʰ� ShortRead�� ���̸�ŭ �ǳʶڴ�.

	if (refFile.is_open()) {
		refFile >> refDNA;
	}

	if (mydnaFile.is_open()) {
		mydnaFile >> MyDNA;
	} // Reference, �񱳿� My DNA�� ������ ���� �̸� ������ �� string�� �ۼ��Ѵ�.

	cout << "SNP 1%�� My DNA ::" << endl;
	cout << MyDNA << endl;
	cout << endl;

	while (shortreadFile.peek() != EOF) {
		getline(shortreadFile, shortRead[count]);
		count++;
	} // ShortRead ������ �� �پ� �о�鿩 string �迭�� �ۼ��Ѵ�.

	timeStart = clock(); // ���ϱ� ������ �ð��� ���.
	for (index = 0; index < 1000; index++) { // ������ 2,000���� ��
		start = 0;
		end = start + 50;
		j = 0; // ShortRead�� �̿��Ͽ� ���� �Ϸ� ��, ���� ShortRead�� �̿��ϱ� ���� �̿��� ������ 0���� �ʱ�ȭ
		do {
			count1 = 0;
			misMatch = 0;
			correct = 0;
			for (int a = start; a < end; a++) {
				if (refDNANumber[a] == 1) {
					count1++;
				} // ������ ���ڰ� �ϳ��� �����ϸ� count1�� ������Ų��.
			}
			if (count1 == 0) { // count1�� 0�̸� �� ����
				for (int i = start; i < end; i++) {
					if (refDNA.substr(i, 1) != shortRead[index].substr(j, 1)) { // Reference�� Shortread ��, Reference�� start��°���� �����ϰ� ShortRead�� 0��°���� ����
						misMatch++; // ���ڿ��� �ٸ��� �̽���ġ ����
					}
					j++; // ShortRead�� index ����
				}
				if (misMatch <= misMatchAllowed) { // �̽���ġ�� 3 �����̸�
					MyDNA2.replace(start, 50, shortRead[index]);
					for (int a = start; a < end; a++) {
						refDNANumber[a] = 1;
					} // �����ϰ� ������ ���ڿ��� ��ġ�� �ش��ϴ� �ѹ��� 1�� ����
					correct = 1; // correct ������ 1�� �ٲ۴�. 
				}
				else if (misMatch > misMatchAllowed) { // �̽���ġ�� 3���� ũ�� KMP �Լ� ����
					kmpAlgorithm(refDNA, shortRead[index], MyDNA2, start, end, 0, correct);
				}
			}
			else if (count1 > 0) { // count1�� 0���� ũ��, �񱳸� ���߰� ShortRead�� ���̸�ŭ ���� Reference�� �κ� ���ڿ� ��ġ�� �ű��.
				for (int i = start; i < end; i++) {
					if (refDNANumber[i] == 0) {
						if (refDNA.substr(i, 1) != shortRead[index].substr(j, 1)) { // Reference�� Shortread ��, Reference�� start��°���� �����ϰ� ShortRead�� 0��°���� ����
							misMatch++; // ���ڿ��� �ٸ��� �̽���ġ ����
						}
					}
					j++; // ShortRead�� index ����
				}
				if (misMatch <= misMatchAllowed) { // �̽���ġ�� 3 �����̸�
					MyDNA2.replace(start, 50, shortRead[index]);
					for (int a = start; a < end; a++) {
						if (refDNANumber[a] == 0) {
							refDNANumber[a] = 1;
						}
					} // �����ϰ� ������ ���ڿ��� ��ġ�� �ش��ϴ� �ѹ��� 1�� ����
					correct = 1; // correct ������ 1�� �ٲ۴�. 
				}
				else if (misMatch > misMatchAllowed) { // �̽���ġ�� 3���� ũ�� KMP �Լ� ����
					kmpAlgorithm(refDNA, shortRead[index], MyDNA2, start, end, 0, correct);
				}
			}
		} while (correct != 1); // correct ������ 1�̸� i��° ShortRead�� Reference���� �񱳸� ������ i + 1��° ShortRead�� �Ѿ��.
	}

	cout << "������ My DNA ::" << endl;
	cout << MyDNA2 << endl;
	cout << endl;

	int recover = 0;
	int compare = 0;

	for (int i = 0; i < 1000; i++) {
		if (MyDNA2.substr(i, 1) != "O") {
			recover++;
		}
	}

	double recoverPercent = (double)recover / (double)1000;

	cout << "MyDNA ������ ::" << endl;
	cout << recoverPercent * 100 << "%" << endl;
	cout << endl;

	for (int i = 0; i < 1000; i++) { // ������ My DNA�� �񱳿� My DNA�� ��
		if (MyDNA.substr(i, 1) == MyDNA2.substr(i, 1)) {
			compare++;
		}
	}

	double comparePercent = (double)compare / (double)1000; // ��ġ�� ���

	cout << "MyDNA�� ������ MyDNA ��ġ�� ::" << endl;
	cout << comparePercent * 100 << "%" << endl;
	cout << endl;

	timeEnd = clock(); // �˰��� ���� �� ��� �ִ� �ð��� �����.
	timeSub = (double)timeEnd - (double)timeStart; // �ɸ� �ð� ���
	cout << "KMP �˰��� �ɸ� �ð� :: " << endl;
	cout << timeSub / 1000 << "��" << endl;
	cout << endl;

	system("pause");
}

void kmpAlgorithm(string ref, string sr, string& md, int& start, int& end, int mM, int& correct) {
	int count = 0;
	int count1 = 0;
	int j = 0;
	string tmp;
	int tmpCount = 0;

	if (start < 950 && end < 1000) { // start ������ (Reference�� ���� - ShortRead�� ����)�� �Ѿ������ �񱳰� �Ұ����ϹǷ� ���� ������ �ɾ�д�.
		for (int i = 0; i < 50; i++) {
			if (ref.substr(start + i, 1) == sr.substr(i, 1)) {
				tmp += ref.substr(start + i, 1);
			} // KMP �˰��� ����
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
		if (tmp != "") { // tmp ���ڿ��� ���λ�, ���̻縦 �̿��Ͽ� �񱳰� �ʿ� ���� �κе��� �ǳʶڴ�.
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
		else if (tmp == "") { // tmp ���ڿ��� ��� �׳� �� ĭ �Ѿ.
			start += count;
		}

		tmp.erase(0, tmp.length()); // tmp ���ڿ��� ����.
		end = start + 50;

		// ���⼭���ʹ� main()�� �ִ� ���� ������ �����ϴ�.
		if (start < 950 && end < 1000) {
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
				for (int i = start; i < end; i++) {
					if (refDNANumber[i] == 0) {
						if (ref.substr(i, 1) != sr.substr(j, 1)) { // Reference�� Shortread ��, Reference�� start��°���� �����ϰ� ShortRead�� 0��°���� ����
							mM++; // ���ڿ��� �ٸ��� �̽���ġ ����
						}
					}
					j++; // ShortRead�� index ����
				}
				if (mM <= misMatchAllowed) { // �̽���ġ�� 3 �����̸�
					md.replace(start, 50, sr);
					for (int a = start; a < end; a++) {
						if (refDNANumber[a] == 0) {
							refDNANumber[a] = 1;
						}
					} // �����ϰ� ������ ���ڿ��� ��ġ�� �ش��ϴ� �ѹ��� 1�� ����
					correct = 1; // correct ������ 1�� �ٲ۴�. 
				}
				else if (mM > misMatchAllowed) { // �̽���ġ�� 3���� ũ�� KMP �Լ� ����
					kmpAlgorithm(ref, sr, md, start, end, 0, correct);
				}
			}
		}
		else if (start >= 950 || end >= 1000) { // ������ ���ϰ� start�� (Reference�� ���� - ShortRead�� ����)�� �Ѿ������ ���� ShortRead�� �Ѿ��.
			correct = 1;
		}
	}
	else if (start >= 950 || end >= 1000) { // start�� (Reference�� ���� - ShortRead�� ����)�� �Ѿ������ ���� ShortRead�� �Ѿ��.
		correct = 1;
	}
}