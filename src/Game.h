#ifndef SEMESTRALKA_GAME_H
#define SEMESTRALKA_GAME_H


#include <string>
#include "Map/Places/Characters/Hero.h"
#include "Map/Map.h"

using namespace std;

/**
 * @class Game
 * @brief game implementation, no gui implemented, will be run trough terminal
 */
class Game {
public:
    /**
     * initialize Hero with basic parameters, which can be then changed
     */
    Game();

    /**
     * starts the game
     */
    void run();

    /**
     * loads the game from file filePath,
     * where is a name of the hero
     * @param filePath represents the name of a player
     * @return true, if game is loaded successfully
     */
    bool load(const string &filePath);

    /**
     * saves the game
     */
    void save();

    /**
     * shows the story in the beginning
     */
    void showStory();

    /**
     * starts mainMenu
     */
    void mainMenu();

    /**
     * sets all the parameters of hero
     */
    void setHero();

    /**
     * checks if player with name name exists
     * used in method load
     * @param name of player
     * @return true, if player exists, else false
     */
    bool playerExists(const string &name);

private:
    /**
     * sets nickname of a player
     * @return true, if nickname is set successfully, else false
     */
    bool setNickname();

    /**
     * asks player if he wants to change the default sex of the hero
     * @return true, if sex is set successfully, else false
     */
    bool setSex();

    string m_fileNameStory;
    shared_ptr<Hero> m_hero;
    Map m_map;
};


#endif //SEMESTRALKA_GAME_H