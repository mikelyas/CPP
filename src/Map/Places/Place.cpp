#include "Place.h"

Place::Place(const string &filePath, shared_ptr<Hero> &hero) {
    ifstream file(filePath);
    string line;
    getline(file, line);
    m_name = StringPlus(line, false).getSubString(NAME + ": ");
    m_hero = hero;
    m_filePath = filePath;
}

string Place::getName() {
    return m_name;
}

string Place::getFilePath() {
    return m_filePath;
}

void Place::storageInteraction(const string &action) {
    if (action == CHOOSE_ARMOUR) {
        m_hero->putOnArmour();
    } else if (action == CHOOSE_WEAPON) {
        m_hero->chooseWeapon();
    } else if (action == GET_HEALING) {
        m_hero->getHealing();
    }
}
