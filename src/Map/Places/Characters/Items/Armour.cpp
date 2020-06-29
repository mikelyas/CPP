#include "Armour.h"


Armour::Armour(const string &filePath)
        : Item(filePath) {
    ifstream file(filePath);
    string line;
    while (getline(file, line)) {
        if (StringPlus(line, false).firstWordIs(ARMOUR + ": ")) {
            m_armour = stoi(StringPlus(line, false).getSubString(ARMOUR + ": "));
            break;
        }
    }
    file.close();
}

void Armour::showItem() const {
    Item::showItem();
    cout << "; Armour: " << m_armour << endl;
}

string Armour::getType() const {
    return ARMOUR;
}

int Armour::getSpecificParameter() const {
    return (int) m_armour;
}