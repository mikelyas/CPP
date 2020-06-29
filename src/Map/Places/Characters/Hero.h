#ifndef SEMESTRALKA_HERO_H
#define SEMESTRALKA_HERO_H


#include "GoodCharacter.h"
#include "Warrior.h"


class Hero : public GoodCharacter, public Warrior {
public:
    /**
     * initializes hero
     * @param filePath is where all the information is stored
     */
    explicit Hero(const string &filePath);

    /**
     * save all the information about hero in Players directory
     * file is name after the name of the player + .txt
     * @param PlayerExists tells if player exists or not, important for saving
     */
    void save();

    /**
     * sets a checkPoint, where character at
     * @param filePath is the path to the place, which is the new checkPoint
     */
    void setCheckPoint(const string &filePath);

    /**
     * gets checkPoint, where the Hero at
     * @return checkPoint
     */
    string getCheckPoint();

    /**
     * sets a name of a player, Player by default
     * @param name of a player
     * @return true, if name is set successfully
     */
    bool setName(const string &name);

    /**
     * @return name of a player
     */
    string getName();

    /**
     * changes sex of a hero
     * sex can be either Male or Female
     */
    void changeSex();

    /**
     * @return sex of a hero
     */
    string getSex();

    /**
     * sets color of hair
     * @return false, if program is interrupted
     */
    bool setHairColour();

    /**
     * @return color of hair
     */
    string getHairColour();

    /**
     * sets color of eyes
     * @param eyesColor of a hero
     * @return false, if program is interrupted
     */
    bool setEyesColour();

    /**
     * @return color of eyes
     */
    string getEyesColour();

    /**
     * chooses weapon to put in hand
     * let the hero choose out of all the weapon
     */
    void chooseWeapon();

    /**
     * put armour on a character
     * let the hero choose out of armour
     */
    void putOnArmour();

    /**
     * heals the hero
     * let the hero choose out of all the healers
     */
    void getHealing();

    /**
     * changes backpack on the hero
     * let the hero choose the backpack
     */
    void changeBackpack();

    /**
     * checks if the hero has item of certain type
     * @param type of an item
     * @return true, if hero have at least one item of type in the storage
     */
    bool hasItemOfType(const string &type) const;

    /**
     * buys from some character an item
     * @param itemName is the name of the item to buy
     * @param person from which item is bought
     * @return true, if item is bought successfully, else false
     */
    bool buy(const string &itemName, shared_ptr<GoodCharacter> &person);

    /**
     * sells some character an item
     * @param itemName is the name of an item to sell
     * @param person to which item is sold
     * @return true, if item is sold successfully
     */
    bool sell(const string &itemName, shared_ptr<GoodCharacter> &person);

    /**
     * derived from GoodCharacter and Warrior, which derived from Character
     * @return name of class, in this case Hero
     */
    string getType() const override;

    /**
     * plus money to hero for going through arena
     * @param reward - amount of money, that the hero get
     */
    void getReward(const int &reward);

    /**
     * shows stats of hero, such as
     * health, strength and armour
     */
    void showStats();

private:
    /**
     * chooses item of certain type
     * @param type of which an item should be
     * @return pointer to an item, if item is chosen successfully, else nullptr
     */
    shared_ptr<Item> chooseItem(const string &type = ANYTHING);

    /**
     * function to put some item on a hero
     * @param itemToPut, either weapon or armour
     * @param itemOnHero, either weapon or armour
     * @return true, if item is put on successfully, else false
     */
    bool putOnItem(shared_ptr<Item> &itemToPut, shared_ptr<Item> &itemOnHero);

    int m_maxHealth;
    string m_sex;
    string m_hairColour;
    string m_eyesColour;
    shared_ptr<Item> m_weapon;
    shared_ptr<Item> m_armour;
    string m_checkPoint;
};

#endif //SEMESTRALKA_HERO_H