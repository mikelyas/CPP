#ifndef SEMESTRALKA_ARMOUR_H
#define SEMESTRALKA_ARMOUR_H

#include "Item.h"

/**
 * @class Armour
 * derived from Item
 */
class Armour : public Item {
public:
    /**
     *  sets all the parameters of an armour
     * @param filePath - name of file where is stored information about armour
     */
    explicit Armour(const string &filePath);

    /**
     * derived from Item class
     * show base parameters of class Item, plus m_armour
     */
    void showItem() const override;

    /**
     * derived from Item class
     * in Item class is a pure virtual method
     * @return name of a class, Armour in this case
     */
    string getType() const override;

    /**
     * @return m_armour
     */
    int getSpecificParameter() const override;

private:
    unsigned int m_armour;
};

#endif //SEMESTRALKA_ARMOUR_H