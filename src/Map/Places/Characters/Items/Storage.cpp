#include "Storage.h"


Storage::Storage(const string &filePath)
        : Item(filePath) {
    ifstream file(filePath);
    string line;
    while (getline(file, line)) {
        StringPlus linePlus(line, false);
        if (linePlus.firstWordIs(CAPACITY + ": ")) {
            m_capacity = stoi(linePlus.getSubString(CAPACITY + ": "));
            m_spaceLeft = m_capacity;
            break;
        }
    }
    if (getline(file, line)) { // Items:
        string flag;
        while (getline(file, line)) { //Subcategories
            //setting flag so, that we know what kind of items come next
            StringPlus linePlus(line, false);
            if (!linePlus.firstWordIs(SUBCATEGORY + SUBCATEGORY)) {
                flag = line.substr(string("\t").length(), line.length() - 2);
            } else { // adding items
                string filePath =
                        ITEMS_FILES + "/" + flag + "/" +
                        StringPlus(line, false).getSubString(SUBCATEGORY + SUBCATEGORY);
                if (flag == ARMOUR) {
                    m_items.push_back(make_shared<Armour>(Armour(filePath)));
                } else if (flag == HEALERS) {
                    m_items.push_back(make_shared<Healer>(Healer(filePath)));
                } else if (flag == WEAPONS) {
                    m_items.push_back(make_shared<Weapon>(Weapon(filePath)));
                } else if (flag == STORAGES) {
                    m_items.push_back(make_shared<Storage>(Storage(filePath)));
                }
            }
        }
    }
    file.close();
}

bool Storage::putIn(shared_ptr<Item> &item) {
    if (m_spaceLeft - item->getSize() >= 0) {
        m_spaceLeft -= item->getSize();
        m_items.push_back(item);
        return true;
    }
    return false;
}

void Storage::showItems() {
    for (auto &item : m_items) {
        item->showItem();
    }
}

bool Storage::deleteItem(shared_ptr<Item> &item) {
    for (auto iter = m_items.begin(); iter != m_items.end(); iter++) {
        if (*iter == item) {
            m_items.erase(iter);
            return true;
        }
    }
    return false;
}

shared_ptr<Item> Storage::getItemByName(const string &name) {
    for (auto &item : m_items) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

string Storage::getType() const {
    return STORAGE;
}

void Storage::setFilePath(const string &fileName) {
    m_filePath = fileName;
}

vector<shared_ptr<Item> > Storage::getItemsOfType(const string &type) {
    vector<shared_ptr<Item>> result;
    for (auto &item : m_items) {
        if (item->getType() == type) {
            result.push_back(item);
        }
    }
    return result;
}

int Storage::getSpaceLeft() const {
    return m_spaceLeft;
}

Storage &Storage::operator=(Storage &anotherStorage) {
    shared_ptr<Item> StorageAsItem = make_shared<Storage>(*this);
    if (this != &anotherStorage) {
        anotherStorage.m_items = this->m_items;
        anotherStorage.m_items.push_back(StorageAsItem);
        this->m_items.clear();
        this->m_items = anotherStorage.m_items;
        this->m_capacity = anotherStorage.m_capacity;
        this->m_spaceLeft = anotherStorage.m_spaceLeft;
        this->m_name = anotherStorage.m_name;
        this->m_cost = anotherStorage.m_cost;
        this->m_size = anotherStorage.m_size;
        this->m_filePath = anotherStorage.m_filePath;
    }
    return *this;
}

void Storage::changeTo(shared_ptr<Item> &anotherStorage) {
    int numOfItems = m_items.size();
    for (int i = 0; i < numOfItems; i++) {
        if (m_items[i] == anotherStorage) {
            deleteItem(m_items[i]);
        }
    }
    *this = *dynamic_pointer_cast<Storage>(anotherStorage);
}

void Storage::save() {
    ofstream file(m_filePath);
    file << NAME << ": " << m_name << endl
         << COST << ": " << m_cost << endl
         << SIZE << ": " << m_size << endl
         << CAPACITY << ": " << m_capacity << endl
         << ITEMS << ": " << endl;
    vector<string> categories = {ARMOUR, HEALER, WEAPON};
    for (int i = 0; i < NUM_OF_ITEM_CATEGORIES; i++) {
        vector<shared_ptr<Item>> itemsOfCategory = getItemsOfType(categories[i]);
        file << SUBCATEGORY << categories[i] << ":" << endl;
        for (auto &item : itemsOfCategory) {
            StringPlus filePathPlus(item->getFilePath());
            file << SUBCATEGORY << SUBCATEGORY << filePathPlus.getFileName() << endl;
        }
    }
    file.close();
}

void Storage::showItem() const {
    Item::showItem();
    cout << " " << CAPACITY << ": " << m_capacity << endl;
}

bool Storage::hasItemOfType(const string &type) const {
    for (auto &item : m_items) {
        if (item->getType() == type) {
            return true;
        }
    }
    return false;
}

int Storage::getSpecificParameter() const {
    return (int) m_capacity;
}