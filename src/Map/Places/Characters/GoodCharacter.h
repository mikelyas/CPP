#ifndef SEMESTRALKA_GOODCHARACTER_H
#define SEMESTRALKA_GOODCHARACTER_H


#include <vector>
#include <memory>
#include "Items/Weapon.h"
#include "Items/Armour.h"
#include "Items/Healer.h"
#include "Character.h"
#include "Items/Storage.h"

/**
 * @class GoodCharacter
 * used for all the villagers
 * also is a base class for hero
 * it is virtually derived, because class Hero is derived from two classes (another one is Warrior)
 */
class GoodCharacter : virtual public Character {
public:
    /**
     * initializes character
     * @param filePath is where all the information is stored
     */
    explicit GoodCharacter(const string &filePath);

    /**
     * buys the item
     * @param item that is bought
     * @return true, if the person can buy an item, else false
     */
    bool buy(shared_ptr<Item> &item);

    /**
     * sells the item
     * @param item which is sold
     * @return true, if item can be sold, else false
     */
    bool sell(shared_ptr<Item> &item);

    /**
     * shows all items in all storages
     */
    void showStorage();

    /**
     * gets item from the storages
     * @param name is the name of the item, not const intentionally
     * @param shouldBe is the type of an item
     * @return pointer to the item
     */
    shared_ptr<Item> getItemByName(string name, const string &shouldBe = ANYTHING);

    /**
     * puts item in storage
     * @param item to put in storage
     * @return true, if item put in storage successfully
     */
    bool putItemInStorage(shared_ptr<Item> &item);

    /**
     * removes item from the storage
     * @param item to remove
     * @return true, if item is removed successfully, else false
     */
    bool removeItem(shared_ptr<Item> &item);

    /**
     * derived from class Character
     * pure virtual class in Character
     * @return name of class, in this case GoodCharacter
     */
    string getType() const override;

protected:
    int m_amountOfMoney;
    vector<Storage> m_storages;
};

#endif //SEMESTRALKA_GOODCHARACTER_H