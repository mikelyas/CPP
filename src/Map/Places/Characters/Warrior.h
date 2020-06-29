#ifndef SEMESTRALKA_WARRIOR_H
#define SEMESTRALKA_WARRIOR_H

#include "Character.h"


/**
 * is used for enemies and a hero
 * it is virtually derived, because class Hero is derived from two classes(another is GoodCharacter)
 */
class Warrior : virtual public Character {
public:
    /**
     * initializes warrior
     * @param filePath is where all the information is stored
     */
    explicit Warrior(const string &filePath);

    /**
     * @return armour of character
     */
    unsigned int getArmour() const;

    /**
     * @return strength of a character
     */
    unsigned int getStrength() const;

    /**
     * subtract damage from overall health of a character
     * @param damage which is taken
     */
    void getDamage(const unsigned int &damage);

    /**
     * show if character is dead
     * @return true, if character is dead, else false
     */
    bool isDead() const;

    /**
     * derived from Character
     * @return name of class, in this case Warrior
     */
    string getType() const override;

protected:
    unsigned int m_strength;
    unsigned int m_armourAmount;
};

#endif //SEMESTRALKA_WARRIOR_H