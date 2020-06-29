#include "Item.h"

Item::Item(const string &filePath) {
    m_filePath = filePath;
    ifstream file(filePath);
    string line;
    getline(file, line);
    m_name = StringPlus(line, false).getSubString(NAME + ": ");
    getline(file, line);
    m_cost = stoi(StringPlus(line, false).getSubString(COST + ": "));
    getline(file, line);
    m_size = stoi(StringPlus(line, false).getSubString(SIZE + ": "));
    file.close();
}

unsigned int Item::getCost() const {
    return m_cost;
}

string Item::getName() const {
    return m_name;
}

unsigned int Item::getSize() const {
    return m_size;
}

void Item::showItem() const {
    cout << "Name: " << m_name << "; Cost: " << m_cost << "; Size: " << m_size;
}

string Item::getFilePath() const {
    return m_filePath;
}