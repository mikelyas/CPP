#ifndef SEMESTRALKA_USEFULLFUNCTIONS_H
#define SEMESTRALKA_USEFULLFUNCTIONS_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Constants.h"

using namespace std;


class StringPlus {
public:
    /**
     * initializes StringPlus with line
     * remove all unnecessary white spaces by default
     * @param line to work with
     * @param deleteSpaces is set to true by default
     * deleteSpaces is false only in constructors, where spaces are important
     */
    explicit StringPlus(const string &line, bool deleteSpaces = true);

    /**
     * gets string that goes after firstWord
     * @param firstWord
     * @return string that goes after first word
     */
    string getSubString(const string &firstWord) const;

    /**
     * checks if first word is word
     * @param word to compare with
     * @return true, if first word is word, given as a parameter, else false
     */
    bool firstWordIs(const string &word) const;

    /**
     * checks if m_line is either Yes or No
     * and keeps whiling, before player enters Yes or No
     * @return false, if interrupted
     */
    bool YesNoAnswer();

    /**
     * @return m_line
     */
    string getLine();

    /**
     * @param sign
     * @return string before sign
     */
    string wordBefore(const char &sign);

    /**
     * @return all the words in string separated with white spaces
     */
    vector<string> wordsInLine();

    /**
     * checks, if m_line has name in it
     * @param name to check for
     * @return true, if name is in m_line, else false
     */
    bool hasName(const string &name);

    /**
     * inserts a name in fileName only
     * @param name to insert before .txt
     */
    void insertName(const string &name);

    /**
     * @return fileName out of whole filePath
     */
    string getFileName();

    /**
     * checks if nickname entered by player is of right format
     * @return true, if nickname is of right format, else false
     */
    bool nicknameOK();

    /**
     * compare m_line and anotherLine
     * @param anotherLine to compare with
     * @return true, if identical, else false
     */
    bool operator==(const string &anotherLine);

    /**
     * compare m_line and anotherLine
     * @param anotherLine to compare with
     * @return true, if different, else false
     */
    bool operator!=(const string &anotherLine);

    /**
     * equate m_line with anotherLine and get rid of redundant spaces
     * @param anotherLine
     * @return new StringPlus
     */
    StringPlus &operator=(const string &anotherLine);

private:
    string m_line;
};

#endif //SEMESTRALKA_USEFULLFUNCTIONS_H