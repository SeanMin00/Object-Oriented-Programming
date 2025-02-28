//
// Created by Gideok Min on 2025. 1. 30..
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void caesar(string& letter, int shift);


// -1. Don't forget leaving the comment! (each function requires the comment)
int main() {
    ifstream ifs;
    ifs.open("encrypted.txt");
    if (!ifs) {
        cerr << "Failed to open encrypted.txt.\n";
        //ifs.close();
        return 1;  // -1 . Make sure exit from program if fails to open file
    }

    int shift;
    ifs >> shift;
    ifs.ignore();

    vector<string> lines;
    for (string line; getline(ifs, line);) {
        lines.push_back(line);
    }

    ifs.close(); // -1. Don't forget closing file after using it!

    for (size_t i = lines.size(); i > 0; --i) {
        caesar(lines[i-1], shift);
        cout << lines[i-1] << endl;
    }

}

void caesar(string& letter, int shift) {
    shift %= 26; // -1. did not handle case of shift going beyond 'Z'

    for (size_t i = 0; i < letter.length(); i++) {
        if (letter[i] >= 'A' && letter[i] <= 'Z') {
            letter[i] -= shift;
            if (letter[i] < 'A') {
                letter[i] += 26;
            }
        }
    }
}

// -3 not using a separate function to convert characters. 함수 안에 함수 쓰자!!
