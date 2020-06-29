#include "Village.h"

Village::Village(const string &filePath, shared_ptr<Hero> &hero)
        : Place(filePath, hero) {
    ifstream file(filePath);
    string line;
    while (getline(file, line)) {
        StringPlus linePlus(line, false);
        if (linePlus.firstWordIs("Good Characters:")) {
            break;
        }
    }
    string category; // can be seller, blacksmith or witch
    while (getline(file, line)) {
        StringPlus linePlus(line, false);
        if (!linePlus.firstWordIs(SUBCATEGORY + SUBCATEGORY)) {
            category = StringPlus(linePlus.getSubString(SUBCATEGORY)).wordBefore(':');
        } else {
            m_characters.push_back(make_shared<GoodCharacter>(GoodCharacter(
                    CHARACTERS_FILES + "/" + category + "/" + linePlus.getSubString(SUBCATEGORY + SUBCATEGORY))));
        }
    }
}

void Village::welcome() const {
    cout << "Welcome to the " << this->m_name << " village." << endl;
    cout << "Here are all the villagers, that can help you in this journey:" << endl;
    this->showCharacters();
}

void Village::showCharacters() const {
    for (auto &character : m_characters) {
        cout << character->getName() << endl;
    }
}

bool Village::showOptions() {
    string answer = ANYTHING;
    while (answer != LEAVE) {
        cout << "That's the options you have here:" << endl;
        cout << TRADE << SEPARATOR << CHOOSE_ARMOUR << SEPARATOR << CHOOSE_WEAPON << SEPARATOR
             << GET_HEALING << SEPARATOR << CHANGE_BACKPACK << SEPARATOR << SHOW_STATS << SEPARATOR << LEAVE
             << SEPARATOR << EXIT << endl;
        cout << "Please, choose one of them." << endl;
        if (!getline(cin, answer)) {
            return false;
        }
        StringPlus answerPlus(answer);
        // checks if player typed in one of the options
        if (answerPlus != LEAVE && answerPlus != TRADE && answerPlus != CHOOSE_ARMOUR && answerPlus != CHOOSE_WEAPON &&
            answerPlus != GET_HEALING && answerPlus != EXIT && answerPlus != CHANGE_BACKPACK &&
            answerPlus != SHOW_STATS) {
            cout << "This is not the option. Please, try again." << endl;
        } else if (answerPlus == TRADE) {
            cout << "Here are all people you can trade with:" << endl;
            this->showCharacters();
            cout << "Please, choose a person you'd like to trade with." << endl;
            // player chooses seller to trade with
            if (shared_ptr<GoodCharacter> personToTradeWith = this->choose<GoodCharacter>(m_characters)) {
                if (!this->trade(personToTradeWith)) {
                    return false;
                }
            } else {
                cout << "You have not chosen a person to trade with." << endl;
            }
        } else if (answerPlus == EXIT) {
            return false;
        } else if (answerPlus == CHANGE_BACKPACK) {
            m_hero->changeBackpack();
        } else if (answerPlus == SHOW_STATS) {
            m_hero->showStats();
        } else {
            this->storageInteraction(answerPlus.getLine());
        }
    }
    return true;
}

bool Village::trade(shared_ptr<GoodCharacter> &seller) {
    string choice = ANYTHING;
    while (choice != LEAVE) {
        cout << "Here are the options you can choose:" << endl
             << BUY << SEPARATOR << SELL << SEPARATOR << LEAVE << endl;
        cout << "Please, enter what you would like to do." << endl;
        // checks input
        if (!getline(cin, choice)) {
            return false;
        }
        StringPlus choicePlus(choice);
        // checks if player typed in one of the options
        if (choicePlus != BUY && choicePlus != SELL && choicePlus != LEAVE) {
            cout << "This is not one of the options. Please, try again." << endl;
        } else if (choicePlus == BUY) {
            if (!buy(seller)) {
                return false;
            }
        } else if (choicePlus == SELL) {
            if (!sell(seller)) {
                return false;
            }
        }
    }
    return true;
}

bool Village::buy(shared_ptr<GoodCharacter> &seller) {
    seller->showStorage();
    cout << "Enter item you'd like to buy." << endl;
    string itemName;
    // checks input
    if (!getline(cin, itemName)) {
        return false;
    }
    if (m_hero->buy(StringPlus(itemName).getLine(), seller)) {
        cout << "Your purchase is successful." << endl;
    }
    return true;
}

bool Village::sell(shared_ptr<GoodCharacter> &seller) {
    m_hero->showStorage();
    cout << "Enter item you'd like to sell." << endl;
    string itemName;
    // checks input
    if (!getline(cin, itemName)) {
        return false;
    }
    if (m_hero->sell(StringPlus(itemName).getLine(), seller)) {
        cout << "Your selling is successful." << endl;
    }
    return true;
}

string Village::getType() {
    return VILLAGE;
}
