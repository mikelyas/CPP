#include "Hero.h"

Hero::Hero(const string &filePath)
        : Character(filePath), GoodCharacter(filePath), Warrior(filePath) {
    ifstream file(filePath);
    string line;
    m_armour = nullptr;
    m_weapon = nullptr;
    while (getline(file, line)) {
        StringPlus linePlus(line, false);
        if (linePlus.firstWordIs(SEX + ": ")) {
            m_sex = linePlus.getSubString(SEX + ": ");
        } else if (linePlus.firstWordIs(HAIR_COLOUR + ": ")) {
            m_hairColour = linePlus.getSubString(HAIR_COLOUR + ": ");
        } else if (linePlus.firstWordIs(EYES_COLOUR + ": ")) {
            m_eyesColour = linePlus.getSubString(EYES_COLOUR + ": ");
        } else if (linePlus.firstWordIs(CHECKPOINT + ": ")) {
            m_checkPoint = linePlus.getSubString(CHECKPOINT + ": ");
        } else if (linePlus.firstWordIs(ARMOUR_ON + ": ")) {
            m_armour = make_shared<Armour>(
                    Armour(ITEMS_FILES + "/" + ARMOUR + "/" + linePlus.getSubString(ARMOUR_ON + ": ")));
        } else if (linePlus.firstWordIs(WEAPON + ": ")) {
            m_weapon = make_shared<Weapon>(
                    Weapon(ITEMS_FILES + "/" + WEAPONS + "/" + linePlus.getSubString(WEAPON + ": ")));
        }
    }
    m_maxHealth = m_health;
}

void Hero::save() {
    ofstream file(PLAYERS_FILES + "/" + m_name + ".txt");
    file << NAME << ": " << m_name << endl
         << HEALTH << ": " << m_health << endl
         << AMOUNT_OF_MONEY << ": " << m_amountOfMoney << endl
         << STRENGTH << ": " << m_strength << endl
         << ARMOUR << ": " << m_armourAmount << endl
         << SEX << ": " << m_sex << endl
         << HAIR_COLOUR << ": " << m_hairColour << endl
         << EYES_COLOUR << ": " << m_eyesColour << endl
         << CHECKPOINT << ": " << StringPlus(m_checkPoint).getFileName() << endl;
    // if there is any armour on a hero
    if (m_armour) {
        file << ARMOUR_ON << ": " << StringPlus(m_armour->getFilePath()).getFileName() << endl;
    }
    // if there is any weapon in hero's hand
    if (m_weapon) {
        file << WEAPON << ": " << StringPlus(m_weapon->getFilePath()).getFileName() << endl;
    }
    file << STORAGES << ":" << endl;
    for (auto &storage : m_storages) {
        StringPlus filePathPlus(storage.getFilePath(), false);
        if (!filePathPlus.hasName(m_name)) {
            filePathPlus.insertName(m_name);
            storage.setFilePath(filePathPlus.getLine());
        }
        storage.save();
        file << SUBCATEGORY << filePathPlus.getFileName() << endl;
    }
    file.close();
}

void Hero::setCheckPoint(const string &fileName) {
    m_checkPoint = fileName;
}

string Hero::getCheckPoint() {
    return m_checkPoint;
}

bool Hero::setName(const string &name) {
    m_name = name;
    return true;
}

string Hero::getName() {
    return m_name;
}

void Hero::changeSex() {
    if (m_sex == MALE) {
        m_sex = FEMALE;
    } else {
        m_sex = MALE;
    }
}

string Hero::getSex() {
    return m_sex;
}

bool Hero::setHairColour() {
    string hairColour;
    cout << "Please, choose one of the colours:" << endl
         << BLACK << SEPARATOR << BROWN << SEPARATOR << BLOND << SEPARATOR << GINGER << endl;
    // checks input
    if (!getline(cin, hairColour)) {
        return false;
    }
    StringPlus hairColourPlus(hairColour);
    // Error's block
    while (hairColourPlus != BLACK && hairColourPlus != BROWN &&
           hairColourPlus != BLOND && hairColourPlus != GINGER) {
        cout << "Sorry, but hair colour you've entered is none of the options. " << TRY_AGAIN << endl;
        // checks for Yes/No answer
        string answer;
        // checks input
        if (!getline(cin, answer)) {
            return false;
        }
        StringPlus linePlus(answer);
        // checks input
        if (!linePlus.YesNoAnswer()) {
            return false;
        }
        if (linePlus.getLine() == YES) {
            // checks input
            if (!getline(cin, hairColour)) {
                return false;
            }
            hairColourPlus = hairColour;
        } else {
            return true; // keeps default hairColor and return, if answer is No
        }
    }
    m_hairColour = hairColourPlus.getLine();
    return true;
}

string Hero::getHairColour() {
    return m_hairColour;
}

bool Hero::setEyesColour() {
    string eyesColour;
    cout << "Please, choose one of the colours:" << endl
         << BLUE << SEPARATOR << BLACK << SEPARATOR << GREEN << SEPARATOR << GREY << endl;
    // checks input
    if (!getline(cin, eyesColour)) {
        return false;
    }
    StringPlus eyesColourPlus(eyesColour);
    // error's block
    while (eyesColourPlus != BLUE && eyesColourPlus != BLACK && eyesColourPlus != GREEN &&
           eyesColourPlus != GREY) {
        cout << "Sorry, but colour you've entered is not from the list. " << TRY_AGAIN << endl;
        //checks for Yes/No answer
        string answer;
        // checks input
        if (!getline(cin, answer)) {
            return false;
        }
        StringPlus linePlus(answer);
        // checks input
        if (!linePlus.YesNoAnswer()) {
            return false;
        }
        if (linePlus == YES) {
            if (!getline(cin, eyesColour)) {
                return false;
            }
            eyesColourPlus = eyesColour;
        } else {
            return true; // keep default eyesColor and return, if answer is No
        }
    }
    m_eyesColour = eyesColourPlus.getLine();
    return true;
}

string Hero::getEyesColour() {
    return m_eyesColour;
}

void Hero::chooseWeapon() {
    // checks if hero has any weapon at all
    if (!hasItemOfType(WEAPON)) {
        cout << "Sorry, but you don't have any weapons." << endl;
        return;
    }
    cout << "Choose a weapon you would like to put in hand:" << endl;
    shared_ptr<Item> weapon;
    // chooses weapon
    if (!(weapon = this->chooseItem(WEAPON))) {
        return; // return if player, hasn't chosen the weapon
    }
    int oldStrengthWeapon = 0;
    int difference;
    // check if the hero has a weapon in hand
    if (m_weapon) {
        oldStrengthWeapon = m_weapon->getSpecificParameter();
    }
    // checks if hero can put the weapon he chose in hand
    if (this->putOnItem(weapon, m_weapon)) {
        difference = m_weapon->getSpecificParameter() - oldStrengthWeapon;
        if (difference >= 0) {
            cout << "+";
        } else {
            cout << "-";
        }
        cout << difference << " " << STRENGTH << endl;
        m_strength += difference;
        cout << "Your strength now is " << m_strength << endl;
    }
}

void Hero::putOnArmour() {
    // checks if hero has armour at all
    if (!hasItemOfType(ARMOUR)) {
        cout << "Sorry, but you don't have any armour." << endl;
        return;
    }
    cout << "Choose an armour you would like to put on:" << endl;
    shared_ptr<Item> armour;
    // chooses armour
    if (!(armour = this->chooseItem(ARMOUR))) {
        return; // return, if player hasn't chosen any armour
    }
    int oldArmour = 0;
    int difference;
    // check if hero has an armour on him
    if (m_armour) {
        oldArmour = m_armour->getSpecificParameter();
    }
    // checks if hero can put on this armour
    if (this->putOnItem(armour, m_armour)) {
        difference = m_armour->getSpecificParameter() - oldArmour;
        if (difference >= 0) {
            cout << "+";
        } else {
            cout << "-";
        }
        cout << difference << " " << ARMOUR << endl;
        m_armourAmount += m_armour->getSpecificParameter() - oldArmour;
        cout << "Your amount of armour is now " << m_armourAmount << endl;
    }
}

void Hero::getHealing() {
    // checks if hero has any healers
    if (!hasItemOfType(HEALER)) {
        cout << "Sorry, but you don't have any healers." << endl;
        return;
    }
    cout << "Choose a healer you want to use:" << endl;
    shared_ptr<Item> healer;
    // chooses healer
    if (!(healer = this->chooseItem(HEALER))) {
        return; // return, if player hasn't chosen any healer
    }
    m_health += healer->getSpecificParameter();
    // balancing health
    if (m_health > m_maxHealth) {
        m_health = m_maxHealth;
    }
    cout << "Your health now is " << m_health << endl;
}

void Hero::changeBackpack() {
    // checks if hero has any other storages in storage
    if (!hasItemOfType(STORAGE)) {
        cout << "Sorry, but you don't have any other backpacks." << endl;
        return;
    }
    cout << "Choose a backpack you want to use:" << endl;
    shared_ptr<Item> backpack;
    // chooses backpack
    if (!(backpack = this->chooseItem(STORAGE))) {
        return; // if, player hasn't chosen any storage
    }
    // checks, if there is enough space in a new backpack to put all the items in it
    if (backpack->getSpecificParameter() <
        m_storages[0].getSpecificParameter() - m_storages[0].getSpaceLeft()) {
        cout << "Sorry, but this is impossible." << endl
             << "Backpack you've chosen is not big enough to contain items you have." << endl;
        return;
    }
    m_storages[0].changeTo(backpack);
    cout << "You have changed your backpack to " << m_storages[0].getName() << "." << endl;
}

bool Hero::buy(const string &itemName, shared_ptr<GoodCharacter> &person) {
    shared_ptr<Item> itemToBuy;
    /**
     * Errors's block
     * checks if there is item with that name in person's storage
     */
    if (!(itemToBuy = person->getItemByName(itemName))) {
        return false;
    }
    // checks if the hero can afford this item
    if (this->GoodCharacter::buy(itemToBuy)) {
        if (person->sell(itemToBuy))
            return true;
    }
    return false;
}

bool Hero::sell(const string &itemName, shared_ptr<GoodCharacter> &person) {
    shared_ptr<Item> itemToSell;
    // checks if there is item with name itemName in hero's storage
    if (!(itemToSell = this->getItemByName(itemName))) {
        return false;
    }
    // checks if the person can buy this item
    if (person->buy(itemToSell)) {
        if (this->GoodCharacter::sell(itemToSell))
            return true;
    }
    return false;
}

shared_ptr<Item> Hero::chooseItem(const string &type) {
    this->showStorage();
    string itemName;
    if (!getline(cin, itemName)) {
        return nullptr;
    }
    shared_ptr<Item> item;
    if (!(item = this->getItemByName(StringPlus(itemName).getLine(), type))) {
        return nullptr;
    }
    return item;
}

bool Hero::putOnItem(shared_ptr<Item> &itemToPut, shared_ptr<Item> &itemOnHero) {
    // removes item from storage
    this->removeItem(itemToPut);
    // checks if there is item on hero
    if (itemOnHero) {
        // checks if there is enough space to put item in storage
        if (!this->putItemInStorage(itemOnHero)) {
            if (itemToPut->getType() == WEAPON) {
                cout << "Would you like to get rid of the weapon in hand?" << endl;
            } else if (itemToPut->getType() == ARMOUR) {
                cout << "Would you like to get rid of the armour on you?" << endl;
            }
            string answer;
            // checks input
            if (!getline(cin, answer)) {
                return false;
            }
            StringPlus linePlus(answer);
            // checks input
            if (!linePlus.YesNoAnswer()) {
                return false;
            }
            if (linePlus == YES) {
                itemOnHero = nullptr;
            } else {
                // puts item back in storage
                this->putItemInStorage(itemToPut);
                return false;
            }
        }
    }
    itemOnHero = itemToPut;
    return true;
}

string Hero::getType() const {
    return "Hero";
}


bool Hero::hasItemOfType(const string &type) const {
    for (auto &storage : m_storages) {
        if (storage.hasItemOfType(type)) {
            return true;
        }
    }
    return false;
}

void Hero::getReward(const int &reward) {
    m_amountOfMoney += reward;
}

void Hero::showStats() {
    cout << HEALTH << ": " << m_health << SEPARATOR
         << ARMOUR << ": " << m_armourAmount << SEPARATOR
         << STRENGTH << ": " << m_strength << SEPARATOR
         << AMOUNT_OF_MONEY << ": " << m_amountOfMoney << endl;
}