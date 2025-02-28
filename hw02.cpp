#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// File: warriors.cpp
//     Purpose: This program reads warrior data from a file, simulates battles between warriors,
//              and prints their statuses after battles.
//     Author: [Your Name]
//     Date: [Submission Date]
// -1 did not write name and file purpose in the header


// -1 did not handle case where one warrior tries to battle a dead warrior (when Jim battles Lancelot)


struct Warrior {
    string name;
    int points;
    // -1 wrote constructor for struct

};

void createWarrior(ifstream& ifs, vector<Warrior>& warriors);
size_t findWarrior(const vector<Warrior>& warriors, const string& name);
void conductBattle(ifstream& ifs, vector<Warrior>& warriors);
void printStatus(const vector<Warrior>& warriors);

int main() {
    vector<Warrior> warriors;
    ifstream ifs("warriors.txt");

    if (!ifs) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string word;
    while (ifs >> word) {
        if (word == "Warrior") {
            createWarrior(ifs, warriors);
        }
        else if (word == "Battle") {
            conductBattle(ifs, warriors);
        }
        else if (word == "Status") {
            printStatus(warriors);
        }
    }
    ifs.close(); //-1 did not close stream

}

void createWarrior(ifstream& ifs, vector<Warrior>& warriors) {
    string WarriorName;
    int WarriorPoints;
    ifs >> WarriorName >> WarriorPoints;

    size_t WarriorIndex = findWarrior(warriors, WarriorName);
    if (WarriorIndex == warriors.size()) {
        Warrior new_warrior= {WarriorName, WarriorPoints};
        // -1 wrote constructor for struct

        warriors.push_back(new_warrior);
    }
    else {
        cerr << "Error: Warrior " << WarriorName << " already exists!" << endl;
    }
}

size_t findWarrior(const vector<Warrior>& warriors, const string& name) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i].name == name) {
            return i;
        }
    }
    return warriors.size();
}

void conductBattle(ifstream& ifs, vector<Warrior>& warriors) {
    string war1, war2;
    ifs >> war1 >> war2;

    size_t index1 = findWarrior(warriors, war1);
    size_t index2 = findWarrior(warriors, war2);

    if (index1 == warriors.size() || index2 == warriors.size()) {
        cout << "error: " << war1 << " and/or " << war2 << " don't exist" << endl;
        return;
    }

    cout << war1 << " battles " << war2 << endl;
    Warrior& warrior1 = warriors[index1];
    Warrior& warrior2 = warriors[index2];

    if (warrior1.points > warrior2.points) {
        cout << warrior1.name << " defeats " << warrior2.name << endl;
        warrior1.points -= warrior2.points;
        warrior2.points = 0;
    }
    else if (warrior2.points > warrior1.points) {
        cout << warrior2.name << " defeats " << warrior1.name << endl;
        warrior2.points -= warrior1.points;
        warrior1.points = 0;
    }
    else {
        if (warrior1.points != 0) {
            cout << "Mutual Annihilation: " << warrior1.name << " and "
                 << warrior2.name << " die at each other's hands" << endl;
            warrior1.points = 0;
            warrior2.points = 0;
        } else {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    }
}

void printStatus(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (size_t i = 0; i < warriors.size(); i++) {
        cout << "Warrior: " << warriors[i].name << ", strength: " << warriors[i].points << endl;
    }
}
