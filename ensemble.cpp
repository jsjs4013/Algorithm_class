#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

// 여기서 레퍼런스 파일의 길이를 입력
int len = 1000;
string myDNAPath = "Mydna_1000.txt";
string votPath = "repair_dna_1000_ensemble.txt";

void priority(string s, int index, const int num, int& aNum, int& tNum, int& cNum, int& gNum, int& aVote, int& tVote, int& cVote, int& gVote);
void tied1(int num1, int num2, int& finalNum);
void tied2(int num1, int num2, int num3, int& finalNum);
void tied3(int num1, int num2, int num3, int num4, int& finalNum);

int main() {
    string mySeq;
    int count = 0;

    ifstream bwtFile("repair_dna_1000_BWT.txt");
    if (bwtFile.fail()) {
        cout << "BWT 파일을 읽어들이는 데 실패했습니다.\n";
        return 1;
    }
    ifstream trivialFile("repair_dna_1000_trivial.txt");
    if (trivialFile.fail()) {
        cout << "Trivial 파일을 읽어들이는 데 실패했습니다.\n";
        return 1;
    }
    ifstream kmpFile("repair_dna_1000_KMP.txt");
    if (kmpFile.fail()) {
        cout << "KMP 파일을 읽어들이는 데 실패했습니다.\n";
        return 1;
    }
    ifstream denovoFile("repair_dna_1000_denovo.txt");
    if (denovoFile.fail()) {
        cout << "KMP 파일을 읽어들이는 데 실패했습니다.\n";
        return 1;
    } // 파일을 받는다.

    string bwtDNA, triDNA, kmpDNA, denovoDNA;
    if (bwtFile.is_open()) {
        bwtFile >> bwtDNA;
    }
    if (trivialFile.is_open()) {
        trivialFile >> triDNA;
    }
    if (kmpFile.is_open()) {
        kmpFile >> kmpDNA;
    }
    if (denovoFile.is_open()) {
        denovoFile >> denovoDNA;
    } // 선언한 각각의 문자열에 저장

    int tmp = denovoDNA.length();
    if (denovoDNA.length() <= len) { // Denovo로 복원한 My DNA가 다른 것들보다 적다면 길이가 같아질 때까지 임의의 문자로 채워넣음. if (denovoDNA.length() <= [문자열의 길이])로 수정
        for (int i = 0; i < len - tmp; i++) { // for (int i = 0; i < [문자열의 길이] - denovoDNA.length(); i++) { 로 수정
            denovoDNA += "O";
        }
    }
    else { // Denovo로 복원한 My DNA가 다른 것들보다 많다면 길이가 같아질 때까지 문자를 지움.
        denovoDNA.erase(len, denovoDNA.length() - len); // denovoDNA.erase(15000, denovoDNA.length() - [문자열의 길이])로 수정
    }

    const int bwtNum = 9, triNum = 6, kmpNum = 4, denNum = 2; // 각각의 알고리즘의 우선순위
    int aNum = 0, tNum = 0, cNum = 0, gNum = 0; // A, T, C, G에 각각 더해지는 우선순위
    int aVote = 0, tVote = 0, cVote = 0, gVote = 0; // A, T, C, G가 각각 받은 투표수
    string finalDNA(len, 'O'); // 최종 My DNA, string finalDNA([문자열의 길이], 'O')로 수정
    int finalNum = 0, finalVote = 0; // 최종 My DNA의 문자를 결정하는 변수

    for (int i = 0; i < len; i++) { // for (int i = 0; i < [문자열의 길이]; i++) { 로 수정
        aNum = 0, tNum = 0, cNum = 0, gNum = 0, finalNum = 0;
        aVote = 0, tVote = 0, cVote = 0, gVote = 0; // 우선순위 및 투표수를 초기화시킴
        priority(bwtDNA, i, bwtNum, aNum, tNum, cNum, gNum, aVote, tVote, cVote, gVote);
        priority(triDNA, i, triNum, aNum, tNum, cNum, gNum, aVote, tVote, cVote, gVote);
        priority(kmpDNA, i, kmpNum, aNum, tNum, cNum, gNum, aVote, tVote, cVote, gVote);
        priority(denovoDNA, i, denNum, aNum, tNum, cNum, gNum, aVote, tVote, cVote, gVote); // 각각의 알고리즘이 갖는 문자를 따져서, A, T, C, G에 투표수 추가 및 우선순위를 더함.
        if (aVote == 2 && tVote == 2) {
            tied1(aNum, tNum, finalNum);
        }
        else if (aVote == 2 && cVote == 2) {
            tied1(aNum, cNum, finalNum);
        }
        else if (aVote == 2 && gVote == 2) {
            tied1(aNum, gNum, finalNum);
        }
        else if (tVote == 2 && cVote == 2) {
            tied1(tNum, cNum, finalNum);
        }
        else if (tVote == 2 && gVote == 2) {
            tied1(tNum, gNum, finalNum);
        }
        else if (cVote == 2 && gVote == 2) {
            tied1(cNum, gNum, finalNum);
        } // 비어 있는 문자가 없을 때, 2 : 2로 동률이 나온 경우, 우선순위를 따져서 결정
        else if (aVote == tVote && aVote == cVote && aVote == gVote && tVote == cVote && tVote == gVote && cVote == gVote) {
            tied3(aNum, tNum, cNum, gNum, finalNum);
        } // 비어 있는 문자가 없을 때, 1 : 1 : 1 : 1로 동률이 나온 경우, 우선순위를 따져서 결정
        else if (aVote == tVote && aVote == cVote && tVote == cVote && gVote == 0) {
            tied2(aNum, tNum, cNum, finalNum);
        }
        else if (aVote == tVote && aVote == gVote && tVote == gVote && cVote == 0) {
            tied2(aNum, tNum, gNum, finalNum);
        }
        else if (aVote == cVote && aVote == gVote && cVote == gVote && tVote == 0) {
            tied2(aNum, cNum, gNum, finalNum);
        }
        else if (tVote == cVote && tVote == gVote && cVote == gVote && aVote == 0) {
            tied2(tNum, cNum, gNum, finalNum);
        } // 비어 있는 문자가 1개일 때, 1 : 1 : 1로 동률이 나온 경우, 우선순위를 따져서 결정
        else if (aVote == 1 && tVote == 1 && cVote == 0 && gVote == 0) {
            tied1(aNum, tNum, finalNum);
        }
        else if (aVote == 1 && cVote == 1 && tVote == 0 && gVote == 0) {
            tied1(aNum, cNum, finalNum);
        }
        else if (aVote == 1 && gVote == 1 && cVote == 0 && tVote == 0) {
            tied1(aNum, gNum, finalNum);
        }
        else if (tVote == 1 && cVote == 1 && aVote == 0 && gVote == 0) {
            tied1(tNum, cNum, finalNum);
        }
        else if (tVote == 1 && gVote == 1 && cVote == 0 && aVote == 0) {
            tied1(tNum, gNum, finalNum);
        }
        else if (cVote == 1 && gVote == 1 && aVote == 0 && tVote == 0) {
            tied1(cNum, gNum, finalNum);
        } // 비어 있는 문자가 2개일 때, 1 : 1로 동률이 나온 경우, 우선순위를 따져서 결정
        else {
            finalVote = aVote;
            if (finalVote > tVote) {
                if (finalVote > cVote) {
                    if (finalVote < gVote) {
                        finalVote = gVote;
                    }
                }
                else {
                    finalVote = cVote;
                    if (finalVote < gVote) {
                        finalVote = gVote;
                    }
                }
            }
            else {
                finalVote = tVote;
                if (finalVote > cVote) {
                    if (finalVote < gVote) {
                        finalVote = gVote;
                    }
                }
                else {
                    finalVote = cVote;
                    if (finalVote < gVote) {
                        finalVote = gVote;
                    }
                }
            }
        } // 그 외의 경우에는 투표수로 결정

        if (finalNum > 0) {
            if (finalNum == aNum) {
                finalDNA.replace(i, 1, "A");
            }
            else if (finalNum == tNum) {
                finalDNA.replace(i, 1, "T");
            }
            else if (finalNum == cNum) {
                finalDNA.replace(i, 1, "C");
            }
            else if (finalNum == gNum) {
                finalDNA.replace(i, 1, "G");
            }
        }
        else if (finalNum == 0) {
            if (finalVote == aVote) {
                finalDNA.replace(i, 1, "A");
            }
            else if (finalVote == tVote) {
                finalDNA.replace(i, 1, "T");
            }
            else if (finalVote == cVote) {
                finalDNA.replace(i, 1, "C");
            }
            else if (finalVote == gVote) {
                finalDNA.replace(i, 1, "G");
            }
        } // 최종적으로 결정된 문자를 최종 문자열에 추가
    }

    // write voting File
    ofstream writeVot(votPath.data());
    if (writeVot.is_open())
    {
        writeVot << finalDNA;
        writeVot.close();
    }

    // read mydna File
    ifstream openFile(myDNAPath.data());
    if (openFile.is_open()) {
        while (getline(openFile, mySeq));
        openFile.close();
    }


    for (int i = 0; i < finalDNA.size(); i++)
    {
        if (finalDNA[i] == mySeq[i])
            count++;
    }

    cout << "My DNA와 ensemble 값의 일치율 : " << float(count) / finalDNA.size() * 100 << "%" << endl;

    system("pause");
}

void priority(string s, int index, const int num, int& aNum, int& tNum, int& cNum, int& gNum, int& aVote, int& tVote, int& cVote, int& gVote) { // 우선순위와 투표수 결정
    if (s.substr(index, 1) == "A") {
        aVote++;
        aNum += num;
    }
    else if (s.substr(index, 1) == "T") {
        tVote++;
        tNum += num;
    }
    else if (s.substr(index, 1) == "C") {
        cVote++;
        cNum += num;
    }
    else if (s.substr(index, 1) == "G") {
        gVote++;
        gNum += num;
    }
}

// 동률일 때 비교
void tied1(int num1, int num2, int& finalNum) { // 빈 문자가 없고 동률일 때(2 : 2), 혹은 빈 문자가 2개 있고 동률일 때(1 : 1)
    if (num1 > num2) {
        finalNum = num1;
    }
    else {
        finalNum = num2;
    }
}

void tied2(int num1, int num2, int num3, int& finalNum) { // 빈 문자가 1개 있고 동률일 때(1 : 1 : 1)
    finalNum = num1;
    if (finalNum > num2) {
        if (finalNum < num3) {
            finalNum = num3;
        }
    }
    else {
        finalNum = num2;
        if (finalNum < num3) {
            finalNum = num3;
        }
    }
}

void tied3(int num1, int num2, int num3, int num4, int& finalNum) { // 빈 문자가 없고 동률일 때(1 : 1 : 1 : 1)
    finalNum = num1;
    if (finalNum > num2) {
        if (finalNum > num3) {
            if (finalNum < num4) {
                finalNum = num4;
            }
        }
        else {
            finalNum = num3;
            if (finalNum < num4) {
                finalNum = num4;
            }
        }
    }
    else {
        finalNum = num2;
        if (finalNum > num3) {
            if (finalNum < num4) {
                finalNum = num4;
            }
        }
        else {
            finalNum = num3;
            if (finalNum < num4) {
                finalNum = num4;
            }
        }
    }
}