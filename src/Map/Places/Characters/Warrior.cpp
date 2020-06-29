#include "Warrior.h"

Warrior::Warrior(const string &filePath)
        : Character(filePath) {
    ifstream file(filePath);
    string line;
    while (getline(file, line)) {
        StringPlus linePlus(line, false);
        if (linePlus.firstWordIs(STRENGTH + ": ")) {
            m_strength = stoi(linePlus.getSubString(STRENGTH + ": "));
        }
        if (linePlus.firstWordIs(ARMOUR + ": ")) {
            m_armourAmount = stoi(linePlus.getSubString(ARMOUR + ": "));
            break;
        }
    }
}

unsigned int Warrior::getArmour() const {
    return m_armourAmount;
}

unsigned int Warrior::getStrength() const {
    return m_strength;
}

bool Warrior::isDead() const {
    return getHealth() <= 0;
}

void Warrior::getDamage(const unsigned int &damage) {
    m_health -= (int) damage;
}

string Warrior::getType() const {
    return "Warrior";
}