#include "Healer.h"

Healer::Healer(const string &filePath)
        : Item(filePath) {
    ifstream file(filePath);
    string line;
    while (getline(file, line)) {
        if (StringPlus(line, false).firstWordIs(HEALING + ": ")) {
            m_healing = stoi(StringPlus(line, false).getSubString(HEALING + ": "));
            break;
        }
    }
    file.close();
}

void Healer::showItem() const {
    Item::showItem();
    cout << "; Healing: " << m_healing << endl;
}

string Healer::getType() const {
    return HEALER;
}

int Healer::getSpecificParameter() const {
    return (int) m_healing;
}