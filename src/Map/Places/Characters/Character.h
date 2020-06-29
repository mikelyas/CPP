#ifndef SEMESTRALKA_CHARACTER_H
#define SEMESTRALKA_CHARACTER_H


#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include "../../../usefullFunctions.h"
#include "../../../Constants.h"

using namespace std;

/**
 * @class Character
 * @brief base class for all the characters
 */
class Character {
public:
    /**
     * initialize character with such parameters as name and health
     * @param fileName where is stored all the information about the character
     */
    explicit Character(const string &filePath);

    /**
     * @return name of the character
     */
    string getName() const;

    /**
     * @return health of the character
     */
    int getHealth() const;

    /**
     * used in derived class to show the class name
     * @return name of the class
     */
    virtual string getType() const = 0;

protected:
    string m_name;
    int m_health;
    string m_filePath;
};

#endif //SEMESTRALKA_CHARACTER_H