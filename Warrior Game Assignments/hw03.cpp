/*
    File: hw03.cpp
    Purpose: Implements Warrior battle simulation with OOP principles.
    Author: Gideok Min, gm3009@nyu.edu
    Date: Feb 14, 2025
*/

// Note
// data hiding: member variable, must be private.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Warrior {
  class Weapon;
  //(6) Status. prototype for friend function. Note: friend is not a member function
  friend ostream& operator<<(ostream& os, const Warrior& war_n);
  friend ostream& operator<<(ostream& os, const Weapon& wea_n);

//Warrior public
public:
    // (5) Initialization(Constructor): When a Warrior is created, instead of simply specifying his name and strength,
    // the Warrior command specifies the Warrior's name as well as his Weapon's name and its strength.
    Warrior(const string& war_n, const string& wea_n, const int& s ): warrior_name(war_n), weapon(wea_n, s) {}

    // (7) Any time the code needs to know or change the warrior's strength, the warrior who owns the weapon then
    //'asks' the weapon what the strength is or tells the weapon that the strength needs to be changed
    // getters and setters
  const string get_name() const {
    return warrior_name;
  }
    //becuase things about the weapon is nested class, use the func to call)
  const int get_strength() const {
    return weapon.get_strength();
  }
  void set_strength(int strength) {
    weapon.set_strength(strength);
  }


//(3) What do the things / types do? These "behaviors" should be represented as methods.
    void conductBattle(Warrior& vs_other) {
        cout << warrior_name << " battles " << vs_other.warrior_name << endl;

        if (get_strength() == 0 && vs_other.get_strength() == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (get_strength() == 0) {
            cout << "He's dead, " << vs_other.get_name() << endl;
        }
        else if (vs_other.get_strength() == 0) {
            cout << "He's dead, " << get_name() << endl;
        }
        else {  // both alive
            if (get_strength() == vs_other.get_strength()) {
                set_strength(0);
                vs_other.set_strength(0);
                cout << "Mutual Annihilation: " << get_name() << " and "
                     << vs_other.get_name() << " die at each other's hands" << endl;
            }
            else if (get_strength() > vs_other.get_strength()) {
                set_strength(get_strength() - vs_other.get_strength());
                vs_other.set_strength(0);
                cout << get_name() << " defeats " << vs_other.get_name() << endl;
            }
            else {  // get_strength() < vs_other.get_strength()
                vs_other.set_strength(vs_other.get_strength() - get_strength());
                set_strength(0);
                cout << vs_other.get_name() << " defeats " << get_name() << endl;
            }
        }
    }






//(4) nested class: The weapon is created together with the Warrior and must not be accessed by anyone else.
//(8) nesting the definition of the Weapon class inside the Warrior class.
// To make sure that no code other than Warrior's makes use of Weapon, we need to make the class private.

private: //Warrior private
  class Weapon{
      friend ostream& operator<<(ostream& os, const Weapon& wea_n);

  public: //Weapon public
      // (5) Initialization(Constructor): When a Warrior is created, instead of simply specifying his name and strength,
      // the Warrior command specifies the Warrior's name as well as his Weapon's name and its strength.
      Weapon(const string& wea_n, int s): weapon_name(wea_n), strength(s){}

      // (7) Any time the code needs to know or change the warrior's strength, the warrior who owns the weapon then
      //'asks' the weapon what the strength is or tells the weapon that the strength needs to be changed
      // getters and setters
      const int get_strength() const {
          return strength;
      }
      void set_strength(int s) {
          strength = s;
      }

  private: //Weapon private
      //(4) Weapons have both a name and a strength.
      //(7) the weapon is what actually holds the warrior's strength
    string weapon_name;
    int strength;
  };

  string warrior_name;
  Weapon weapon;
};

void openFile(ifstream& ifsWarrior); //(8) The name of the input file will be "warriors.txt". Please don't ask the user for the file's name.
void createWarrior(ifstream& ifs, vector<Warrior>& warriors);
size_t findWarrior(const vector<Warrior>& warriors, const string& name);
void printStatus(const vector<Warrior>& warriors);

int main() {
    ifstream ifsWarrior;
    openFile(ifsWarrior);

    // Using "Warrior class", made "warriors vector"
    vector<Warrior> warriors;


    string word;
    while (ifsWarrior >> word) {
        if (word == "Warrior") {
            createWarrior(ifsWarrior, warriors);
        }
        else if (word == "Battle") {
            string war1, war2;
            ifsWarrior >> war1 >> war2;

            size_t index1 = findWarrior(warriors, war1);
            size_t index2 = findWarrior(warriors, war2);

            if (index1 == warriors.size() || index2 == warriors.size()) {
                cout << "error: " << war1 << " and/or " << war2 << " don't exist" << endl;
            }
            warriors[index1].conductBattle(warriors[index2]);

        }
        else if (word == "Status") {
            printStatus(warriors);
        }
    }
    ifsWarrior.close(); //-1 did not close stream

}

//(8) The name of the input file will be "warriors.txt". Please don't ask the user for the file's name.
void openFile(ifstream& ifsWarrior) {
  ifsWarrior.open("warriors.txt");
    if (!ifsWarrior) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
}


void createWarrior(ifstream& ifsWarrior, vector<Warrior>& warriors) {
    string WarriorName;
    string WeaponName;
    int WarriorPoints;
    ifsWarrior >> WarriorName >> WeaponName >> WarriorPoints;

    size_t WarriorIndex = findWarrior(warriors, WarriorName);
    if (WarriorIndex == warriors.size()) {
        Warrior new_warrior(WarriorName, WeaponName, WarriorPoints);        // -1 wrote constructor for struct

        warriors.push_back(new_warrior);
    }
    else {
        cerr << "Error: Warrior " << WarriorName << " already exists!" << endl;
    }
}


size_t findWarrior(const vector<Warrior>& warriors, const string& name) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i].get_name() == name) {
            return i;
        }
    }
    return warriors.size();
}


//(6): The Status report is also modified to show the name of the Warrior's Weapon.
// Tried to use friend ostream. when one of the components of vector is called by for loop,
// which is Warrior class, friend ostream called, because friend ostream is inside of the class.
void printStatus(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (size_t i = 0; i < warriors.size(); i++) {
        cout << warriors[i];
    }
}
//note: friend is not a member function. Does not need a scope op (::)
ostream& operator<<(ostream& os, const Warrior& war_n) {
    os << "Warrior: " << war_n.warrior_name << ", " << war_n.weapon;
    return os;
}
//Because Weapon is nested class, :: is required at this time
ostream& operator<<(ostream& os, const Warrior::Weapon& wea_n) {
    os << "weapon: " << wea_n.weapon_name << ", " << wea_n.strength << endl;
    return os;
}
