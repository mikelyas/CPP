#include "GoodCharacter.h"

GoodCharacter::GoodCharacter(const string &filePath)
        : Character(filePath) {
    ifstream file;
    file.open(filePath);
    string line;
    while (getline(file, line)) {
        StringPlus linePlus(line, false);
        if (linePlus.firstWordIs(AMOUNT_OF_MONEY + ": ")) {
            m_amountOfMoney = stoi(linePlus.getSubString(AMOUNT_OF_MONEY + ": "));
        }
        if (linePlus.firstWordIs(STORAGES + ":")) {
            while (getline(file, line) && StringPlus(line, false).firstWordIs(SUBCATEGORY)) {
                m_storages.push_back(Storage(STORAGE_FILES + "/" + StringPlus(line, false).getSubString(SUBCATEGORY)));
            }
            break;
        }
    }
    file.close();
}

bool GoodCharacter::buy(shared_ptr<Item> &item) {
    //checks if character has enough money
    if (m_amountOfMoney - (int) item->getCost() >= 0) {
        return this->putItemInStorage(item);
    }
    cout << "Sorry, but " << this->getName() << " has/have not enough money." << endl;
    return false;
}

bool GoodCharacter::sell(shared_ptr<Item> &item) {
    m_amountOfMoney += (int) item->getCost();
    return this->removeItem(item);
}

void GoodCharacter::showStorage() {
    for (auto &storage : m_storages) {
        storage.showItems();
    }
}

shared_ptr<Item> GoodCharacter::getItemByName(string name, const string &shouldBe) {
    shared_ptr<Item> searchedItem = nullptr;
    while (!searchedItem) {
        StringPlus namePlus(name);
        bool itemExists = false;
        // searches for an item and returns it, if it is of type shouldBe
        for (auto &storage : m_storages) {
            if (searchedItem = storage.getItemByName(namePlus.getLine())) {
                if (searchedItem->getType() != shouldBe && shouldBe != ANYTHING) {
                    itemExists = true;
                    break;
                }
                return searchedItem;
            }
        }
        // tells that item is not of type shouldBe, if it exists, or that it does not exist at all
        if (itemExists) {
            cout << "Sorry, but item you've entered is not " << shouldBe << ". " << TRY_AGAIN << endl;
        } else {
            cout << "Sorry, but item you've entered does not exist. " << TRY_AGAIN << endl;
        }
        // gets a yes/no answer, if the player wants to try again
        string answer;
        // checks for input
        if (!getline(cin, answer)) {
            return nullptr;
        }
        StringPlus linePlus(answer);
        // checks for input
        if (!linePlus.YesNoAnswer()) {
            return nullptr;
        }
        if (linePlus.getLine() == YES) {
            // checks for input
            if (!getline(cin, name)) {
                return nullptr;
            }
            searchedItem = nullptr;
        } else {
            cout << "You have NOT chosen any item." << endl;
            return nullptr;
        }
    }
    return nullptr; // should never happen
}

bool GoodCharacter::putItemInStorage(shared_ptr<Item> &item) {
    for (auto &storage : m_storages) {
        // checks if there is enough space for the item in any of the storages
        if (storage.getSpecificParameter() - item->getSize() >= 0) {
            storage.putIn(item);
            return true;
        }
    }
    cout << "Sorry, but " << this->getName() << " has/have no free place." << endl;
    return false;
}

bool GoodCharacter::removeItem(shared_ptr<Item> &item) {
    for (auto &storage : m_storages) {
        if (storage.deleteItem(item)) {
            return true;
        }
    }
    return false;
}

string GoodCharacter::getType() const {
    return "GoodCharacter";
}