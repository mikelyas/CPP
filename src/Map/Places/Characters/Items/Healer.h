#ifndef SEMESTRALKA_HEALER_H
#define SEMESTRALKA_HEALER_H

#include "Item.h"

/**
 * @class Healer
 * derived from Item
 */
class Healer : public Item {
public:
    /**
     * initializes healer
     * @param filePath is where all the information is stored
     */
    explicit Healer(const string &filePath);

    /**
     * derived from class Item
     * shows basic parameters of class Item, plus m_healing
     */
    void showItem() const override;

    /**
     * derived from class Item
     * a pure virtual method in class Item
     * @return name of class, in this case Healer
     */
    string getType() const override;

    /**
     * healing potential of an item
     * @return amount of healing
     */
    int getSpecificParameter() const override;

private:
    unsigned int m_healing;
};

#endif //SEMESTRALKA_HEALER_H
