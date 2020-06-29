#ifndef SEMESTRALKA_PLACE_H
#define SEMESTRALKA_PLACE_H

#include <string>
#include <memory>
#include <vector>
#include "../../usefullFunctions.h"
#include "../../Constants.h"
#include "Characters/Character.h"
#include "Characters/Warrior.h"
#include "Characters/GoodCharacter.h"
#include "Characters/Hero.h"


using namespace std;

class Place {
public:
    /**
     * initializes Place
     * @param filePath - where all the information is stored
     * @param hero - player
     */
    explicit Place(const string &filePath, shared_ptr<Hero> &hero);

    /**
     * @return name of the place
     */
    string getName();

    /**
     * @return filePath to the file, where is all the information
     */
    string getFilePath();

    /**
     * welcomes player in the place
     */
    virtual void welcome() const = 0;

    /**
     * shows all the characters in the place
     */
    virtual void showCharacters() const = 0;

    /**
     * shows all the options of interacting in this place
     * @return true, if the hero got through this place, else false
     */
    virtual bool showOptions() = 0;

    /**
     * choose the character to interact
     * @return pointer to this character
     */
    template<class personType>
    shared_ptr<personType> choose(const vector<shared_ptr<personType>> &persons) {
        string characterName;
        // keeps whiling before player chooses the character or rejects to choose
        do {
            // checks input
            if (!getline(cin, characterName)) {
                return nullptr;
            }
            for (auto &character : persons) {
                if (character->getName() == StringPlus(characterName).getLine()) {
                    return character;
                }
            }
            cout << "Sorry, but the character you've entered does not exists. Please, try again." << endl;
        } while (true);
    }

    /**
     * used in derived classes
     * @return name of class
     */
    virtual string getType() = 0;

    /**
     * interact with storage, based on action
     * @param action can be put on armour, put on weapon or get healing
     */
    void storageInteraction(const string &action);

protected:
    string m_filePath;
    string m_name;
    shared_ptr<Hero> m_hero;
};

#endif //SEMESTRALKA_PLACE_H
