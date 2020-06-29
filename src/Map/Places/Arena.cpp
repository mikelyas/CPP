#include "Arena.h"

Arena::Arena(const string &filePath, shared_ptr<Hero> &hero)
        : Place(filePath, hero) {
    ifstream file(filePath);
    string line;
    while (getline(file, line)) {
        StringPlus linePlus(line, false);
        if (linePlus.firstWordIs("Enemies:"))
            break;
    }
    while (getline(file, line)) {
        m_characters.push_back(
                make_shared<Warrior>(Warrior(ENEMIES_FILES + "/" + StringPlus(line, false).getSubString(SUBCATEGORY))));
    }
}

void Arena::welcome() const {
    cout << "You are now in " << m_name << "." << endl
         << "You have to beat all the enemies here to go through." << endl
         << "Here are all the enemies in " << m_name << endl;
    this->showCharacters();
}

void Arena::showCharacters() const {
    for (auto &character : m_characters) {
        cout << "Name: " << character->getName() << "; "
             << "Health: " << character->getHealth() << "; "
             << "Strength: " << dynamic_pointer_cast<Warrior>(character)->getStrength() << endl;
    }
}

bool Arena::showOptions() {
    string choice;
    // while there are at lease one enemy left
    while (!m_characters.empty()) {
        cout << "Here are the options you have:" << endl
             << FIGHT << SEPARATOR << CHOOSE_ARMOUR << SEPARATOR << CHOOSE_WEAPON << SEPARATOR << GET_HEALING
             << SEPARATOR << SHOW_STATS << SEPARATOR << EXIT << endl
             << "Please, type in one of the options." << endl;
        if (!getline(cin, choice)) {
            return false;
        }
        StringPlus choicePlus(choice);
        // checks if player entered one of the options
        if (choicePlus != FIGHT && choicePlus != EXIT && choicePlus != CHOOSE_WEAPON &&
            choicePlus != CHOOSE_ARMOUR &&
            choicePlus != GET_HEALING && choicePlus != SHOW_STATS) {
            cout << "This is not the option. Please, try again." << endl;
            continue;
        }
        if (choicePlus == EXIT) {
            if (exit()) {
                return false;
            } else {
                continue;
            }
        } else if (choicePlus == CHOOSE_ARMOUR || choicePlus == CHOOSE_WEAPON || choicePlus == GET_HEALING) {
            this->storageInteraction(choicePlus.getLine());
        } else if (choice == FIGHT) {
            if (!fight()) {
                return false;
            }
        } else if (choice == SHOW_STATS) {
            m_hero->showStats();
        }
    }
    cout << "Here is a reward for make this world clearer:" << endl << REWARD << endl;
    m_hero->getReward(REWARD);
    return true;
}

bool Arena::exit() const {
    cout << "Your progress here won't be saved. Are you sure you want to exit? Yes/No" << endl;
    string choice;
    // checks input
    if (!getline(cin, choice)) {
        return false;
    }
    StringPlus choicePlus(choice);
    // checks input
    if (!choicePlus.YesNoAnswer()) {
        return false;
    }
    return !(choicePlus == YES);
}

bool Arena::fight() {
    cout << "Choose your opponent:" << endl;
    this->showCharacters();
    shared_ptr<Warrior> enemy = this->choose<Warrior>(m_characters);
    if (!enemy) {
        return false;
    }
    this->fightWithEnemy(enemy);
    if (m_hero->isDead()) {
        return false;
    }
    this->deleteCharacter(enemy, m_characters);
    cout << "Your health no is " << m_hero->getHealth() << endl;
    return true;
}

void Arena::fightWithEnemy(shared_ptr<Warrior> &enemy) {
    shared_ptr<Warrior> opponent = enemy;
    // while both fighters are alive
    while (!opponent->isDead() && !m_hero->isDead()) {
        // gets random number of another enemies, that will attack hero
        srand(time(NULL));
        size_t numOfOtherAttackers = rand() % m_characters.size();
        vector<shared_ptr<Warrior>> otherAttackers;
        int totalEnemyStrength = 0;
        // gets numOfOtherAttackers random enemies
        for (size_t i = 0; i < numOfOtherAttackers; i++) {
            bool pushed = false;
            while (!pushed) {
                size_t number = rand() % m_characters.size();
                if (m_characters[number] == enemy) {
                    continue;
                }
                bool found = false;
                for (auto &attacker : otherAttackers) {
                    if (attacker == m_characters[number]) {
                        found = true;
                    }
                }
                if (!found) {
                    otherAttackers.push_back(m_characters[number]);
                    totalEnemyStrength += m_characters[number]->getStrength();
                    pushed = true;
                }
            }
        }
        opponent->getDamage(m_hero->getStrength());
        m_hero->getDamage(totalEnemyStrength + opponent->getStrength());
    }
}

void Arena::deleteCharacter(shared_ptr<Warrior> characterToDelete, vector<shared_ptr<Warrior> > &characters) {
    for (auto iter = characters.begin(); iter != characters.end(); iter++) {
        if (*iter == characterToDelete) {
            characters.erase(iter);
            return;
        }
    }
    auto iter = lower_bound(characters.begin(), characters.end(), characterToDelete);
    characters.erase(iter);
}

string Arena::getType() {
    return ARENA;
}