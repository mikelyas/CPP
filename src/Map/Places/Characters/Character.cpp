#include "Character.h"

Character::Character(const string &filePath) {
    m_filePath = filePath;
    ifstream file(filePath);
    string line;
    getline(file, line);
    m_name = StringPlus(line, false).getSubString(NAME + ": ");
    getline(file, line);
    m_health = stoi(StringPlus(line, false).getSubString(HEALTH + ": "));
    file.close();
}

string Character::getName() const {
    return m_name;
}

int Character::getHealth() const {
    return m_health;
}