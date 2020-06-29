#ifndef SEMESTRALKA_WEAPON_H
#define SEMESTRALKA_WEAPON_H

#include "Item.h"


/**
 * @class Weapon
 * derived from Item
 */
class Weapon : public Item {
public:
    /**
     * initializes weapon
     * @param filePath is where all the information is stored
     */
    explicit Weapon(const string &filePath);

    /**
     * derived from class Item
     * shows all the basic parameters of class Item, plus m_attack of the weapon
     */
    void showItem() const override;

    /**
     * derived from class Item
     * pure virtual method in class Item
     * @return name of class, in this case Weapon
     */
    string getType() const override;

    /**
     * attack of a weapon
     * @return m_attack
     */
    int getSpecificParameter() const override;

private:
    unsigned int m_attack;
};

#endif //SEMESTRALKA_WEAPON_H