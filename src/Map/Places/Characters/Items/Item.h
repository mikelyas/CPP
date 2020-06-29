#ifndef SEMESTRALKA_ITEM_H
#define SEMESTRALKA_ITEM_H

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include "../../../../usefullFunctions.h"
#include "../../../../Constants.h"

using namespace std;

/**
 * @class Item
 * base class for Armour, Storage, Healer, Weapon
 */
class Item {
public:
    /**
     * initialize item
     * @param filePath - where is stored all the info about the item
     */
    explicit Item(const string &filePath);

    /**
     * @return cost of the item
     */
    unsigned int getCost() const;

    /**
     * @return name of the item
     */
    string getName() const;

    /**
     * @return filePath of the item
     */
    string getFilePath() const;

    /**
     * @return size of the item
     */
    unsigned int getSize() const;

    /**
     * shows m_name, m_cost and m_size of the item
     * further is overridden in derived classes to show specific parameters
     */
    virtual void showItem() const;

    /**
     * used for getting names of derived classes
     * @return type of a class
     */
    virtual string getType() const = 0;

    /**
     * @return specific parameter of derived class
     */
    virtual int getSpecificParameter() const = 0;

protected:
    string m_filePath;
    string m_name;
    unsigned int m_cost;
    unsigned int m_size;
};

#endif //SEMESTRALKA_ITEM_H