#ifndef SEMESTRALKA_ARENA_H
#define SEMESTRALKA_ARENA_H

#include "Place.h"
#include <stdlib.h>
#include <time.h>

class Arena : public Place {
public:
    /**
     * @param filePath - where is all the information about the arena
     * @param hero - player
     */
    explicit Arena(const string &filePath, shared_ptr<Hero> &hero);

    /**
     * welcomes player in the arena
     */
    void welcome() const override;

    /**
     * shows all the enemies in the arena
     */
    void showCharacters() const override;

    /**
     * shows all the options player can choose(fight, get healing, choose weapon, choose armour, exit)
     * if player chose fightWithEnemy, he can not exit it
     * @return true, if hero got through, else false (hero is dead)
     */
    bool showOptions() override;

    /**
     * @return name of class, in this case Arena
     */
    string getType() override;

    /**
     * exits arena
     * @return false, if player wants to exit or there is some mistake, else true
     */
    bool exit() const;

private:
    /**
     * starts the fight and let the player choose the opponent
     * @return true, if fight is over and hero is alive, else false
     */
    bool fight();

    /**
     * starts the fight with a certain enemy
     * @param enemy, with which hero is fighting
     */
    void fightWithEnemy(shared_ptr<Warrior> &enemy);

    /**
     * deletes character from vector of characters
     * used in fight to delete enemies
     * @param characterToDelete
     * @param characters - vector of all enemies
     */
    void deleteCharacter(shared_ptr<Warrior> characterToDelete, vector<shared_ptr<Warrior>> &characters);

    vector<shared_ptr<Warrior>> m_characters;
};

#endif //SEMESTRALKA_ARENA_H
