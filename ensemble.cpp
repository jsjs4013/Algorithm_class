#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

// ���⼭ ���۷��� ������ ���̸� �Է�
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
        cout << "BWT ������ �о���̴� �� �����߽��ϴ�.\n";
        return 1;
    }
    ifstream trivialFile("repair_dna_1000_trivial.txt");
    if (trivialFile.fail()) {
        cout << "Trivial ������ �о���̴� �� �����߽��ϴ�.\n";
        return 1;
    }
    ifstream kmpFile("repair_dna_1000_KMP.txt");
    if (kmpFile.fail()) {
        cout << "KMP ������ �о���̴� �� �����߽��ϴ�.\n";
        return 1;
    }
    ifstream denovoFile("repair_dna_1000_denovo.txt");
    if (denovoFile.fail()) {
        cout << "KMP ������ �о���̴� �� �����߽��ϴ�.\n";
        return 1;
    } // ������ �޴´�.

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
    } // ������ ������ ���ڿ��� ����

    int tmp = denovoDNA.length();
    if (denovoDNA.length() <= len) { // Denovo�� ������ My DNA�� �ٸ� �͵麸�� ���ٸ� ���̰� ������ ������ ������ ���ڷ� ä������. if (denovoDNA.length() <= [���ڿ��� ����])�� ����
        for (int i = 0; i < len - tmp; i++) { // for (int i = 0; i < [���ڿ��� ����] - denovoDNA.length(); i++) { �� ����
            denovoDNA += "O";
        }
    }
    else { // Denovo�� ������ My DNA�� �ٸ� �͵麸�� ���ٸ� ���̰� ������ ������ ���ڸ� ����.
        denovoDNA.erase(len, denovoDNA.length() - len); // denovoDNA.erase(15000, denovoDNA.length() - [���ڿ��� ����])�� ����
    }

    const int bwtNum = 9, triNum = 6, kmpNum = 4, denNum = 2; // ������ �˰����� �켱����
    int aNum = 0, tNum = 0, cNum = 0, gNum = 0; // A, T, C, G�� ���� �������� �켱����
    int aVote = 0, tVote = 0, cVote = 0, gVote = 0; // A, T, C, G�� ���� ���� ��ǥ��
    string finalDNA(len, 'O'); // ���� My DNA, string finalDNA([���ڿ��� ����], 'O')�� ����
    int finalNum = 0, finalVote = 0; // ���� My DNA�� ���ڸ� �����ϴ� ����

    for (int i = 0; i < len; i++) { // for (int i = 0; i < [���ڿ��� ����]; i++) { �� ����
        aNum = 0, tNum = 0, cNum = 0, gNum = 0, finalNum = 0;
        aVote = 0, tVote = 0, cVote = 0, gVote = 0; // �켱���� �� ��ǥ���� �ʱ�ȭ��Ŵ
        priority(bwtDNA, i, bwtNum, aNum, tNum, cNum, gNum, aVote, tVote, cVote, gVote);
        priority(triDNA, i, triNum, aNum, tNum, cNum, gNum, aVote, tVote, cVote, gVote);
        priority(kmpDNA, i, kmpNum, aNum, tNum, cNum, gNum, aVote, tVote, cVote, gVote);
        priority(denovoDNA, i, denNum, aNum, tNum, cNum, gNum, aVote, tVote, cVote, gVote); // ������ �˰����� ���� ���ڸ� ������, A, T, C, G�� ��ǥ�� �߰� �� �켱������ ����.
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
        } // ��� �ִ� ���ڰ� ���� ��, 2 : 2�� ������ ���� ���, �켱������ ������ ����
        else if (aVote == tVote && aVote == cVote && aVote == gVote && tVote == cVote && tVote == gVote && cVote == gVote) {
            tied3(aNum, tNum, cNum, gNum, finalNum);
        } // ��� �ִ� ���ڰ� ���� ��, 1 : 1 : 1 : 1�� ������ ���� ���, �켱������ ������ ����
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
        } // ��� �ִ� ���ڰ� 1���� ��, 1 : 1 : 1�� ������ ���� ���, �켱������ ������ ����
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
        } // ��� �ִ� ���ڰ� 2���� ��, 1 : 1�� ������ ���� ���, �켱������ ������ ����
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
        } // �� ���� ��쿡�� ��ǥ���� ����

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
        } // ���������� ������ ���ڸ� ���� ���ڿ��� �߰�
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

    cout << "My DNA�� ensemble ���� ��ġ�� : " << float(count) / finalDNA.size() * 100 << "%" << endl;

    system("pause");
}

void priority(string s, int index, const int num, int& aNum, int& tNum, int& cNum, int& gNum, int& aVote, int& tVote, int& cVote, int& gVote) { // �켱������ ��ǥ�� ����
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

// ������ �� ��
void tied1(int num1, int num2, int& finalNum) { // �� ���ڰ� ���� ������ ��(2 : 2), Ȥ�� �� ���ڰ� 2�� �ְ� ������ ��(1 : 1)
    if (num1 > num2) {
        finalNum = num1;
    }
    else {
        finalNum = num2;
    }
}

void tied2(int num1, int num2, int num3, int& finalNum) { // �� ���ڰ� 1�� �ְ� ������ ��(1 : 1 : 1)
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

void tied3(int num1, int num2, int num3, int num4, int& finalNum) { // �� ���ڰ� ���� ������ ��(1 : 1 : 1 : 1)
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