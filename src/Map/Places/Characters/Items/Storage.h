#ifndef SEMESTRALKA_STORAGE_H
#define SEMESTRALKA_STORAGE_H

#include <vector>
#include <memory>
#include "Armour.h"
#include "Healer.h"
#include "Weapon.h"

/**
 * @class Storage
 * derived from Item
 */
class Storage : public Item {
public:
    /**
     * initializes Storage
     * @param filePath is where all the information is stored
     */
    explicit Storage(const string &filePath);

    /**
     * puts some item in a storage
     * @param item, that is put in
     * @return true, if there is enough space for an item, else false
     */
    bool putIn(shared_ptr<Item> &item);

    /**
     * show all the item in storage
     */
    void showItems();

    /**
     * deletes item from the storage
     * @param item to be deleted
     * @return true, if item is found, else false
     */
    bool deleteItem(shared_ptr<Item> &item);

    /**
     * searches for item in storage
     * @param name of an item
     * @return pointer on item, if it is found, else nullptr
     */
    shared_ptr<Item> getItemByName(const string &name);

    /**
     * derived from class Item
     * pure virtual method in class Item
     * @return name of the class, in this case Storage
     */
    string getType() const override;

    /**
     * saves all the information about the storage in file marked as m_filePath
     * used only for class Heroes, to save the information about players
     */
    void save();

    /**
     * sets m_filePath of the storage to filePath
     * @param filePath is to what changed m_filePath
     */
    void setFilePath(const string &filePath);

    /**
     * gets all the items of certain type from storage
     * @param type of items to search for
     * @return vector of pointers to items
     */
    vector<shared_ptr<Item>> getItemsOfType(const string &type);

    /**
     * @return amount of space left in the storage
     */
    int getSpaceLeft() const;

    /**
     * assignment operator
     * transfer all the items from this storage to anotherStorage
     * puts this storage in another storage and make this storage anotherStorage
     * @param anotherStorage is what should be this storage
     * @return new storage
     */
    Storage &operator=(Storage &anotherStorage);

    /**
     * changes this storage to anotherStorage
     * @param anotherStorage
     */
    void changeTo(shared_ptr<Item> &anotherStorage);

    /**
     * derived from class Item
     * pure virtual method in class Item
     * shows basic parameters from class Item, plus m_capacity of the storage
     */
    void showItem() const override;

    /**
     * shows if there is some item of type
     * @param type to search for in the storage
     * @return true, if there is at least one item of type
     */
    bool hasItemOfType(const string &type) const;

    /**
     * @return capacity of a storage
     */
    int getSpecificParameter() const override;

private:
    unsigned int m_capacity;
    int m_spaceLeft;
    vector<shared_ptr<Item>> m_items;
};

#endif //SEMESTRALKA_STORAGE_H
