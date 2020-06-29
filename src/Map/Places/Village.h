#ifndef SEMESTRALKA_VILLAGE_H
#define SEMESTRALKA_VILLAGE_H

#include "Place.h"


class Village : public Place {
public:
    /**
     * initializes Village
     * @param filePath to file where all the information is stored
     * @param hero - player
     */
    explicit Village(const string &filePath, shared_ptr<Hero> &hero);

    /**
     * welcomes hero
     */
    void welcome() const override;

    /**
     * shows all the villagers
     */
    void showCharacters() const override;

    /**
     * shows what a player can do in the village
     * @return true, if player wants to leave the village, else false
     */
    bool showOptions() override;

    /**
     * @return name of class, in this case Village
     */
    string getType() override;

private:
    /**
     * buying process
     * @param seller from which hero is buying
     * @return false, if there is some mistake, else true
     */
    bool buy(shared_ptr<GoodCharacter> &seller);

    /**
     * selling process
     * @param seller to which hero is selling
     * @return false, if there is some mistake, else true
     */
    bool sell(shared_ptr<GoodCharacter> &seller);

    /**
     * hero trades with someone in the village
     * @param seller with which hero is trading
     * @return true, if trade if successful, else false
     */
    bool trade(shared_ptr<GoodCharacter> &seller);

    vector<shared_ptr<GoodCharacter>> m_characters;
};

#endif //SEMESTRALKA_VILLAGE_H
