#include "Weapon.h"


Weapon::Weapon(const string &filePath)
        : Item(filePath) {
    ifstream file(filePath);
    string line;
    while (getline(file, line)) {
        if (StringPlus(line, false).firstWordIs(ATTACK + ": ")) {
            m_attack = stoi(StringPlus(line, false).getSubString(ATTACK + ": "));
            break;
        }
    }
    file.close();
}

void Weapon::showItem() const {
    Item::showItem();
    cout << "; Attack: " << m_attack << endl;
}

string Weapon::getType() const {
    return WEAPON;
}

int Weapon::getSpecificParameter() const {
    return (int) m_attack;
}