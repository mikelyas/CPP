#include "usefullFunctions.h"

StringPlus::StringPlus(const string &line, bool deleteSpaces) {
    if (deleteSpaces) {
        stringstream ss;
        ss << line;
        string result;
        while (!ss.eof()) {
            string temp;
            ss >> temp;
            if (!temp.empty())
                result += temp + " ";
        }
        m_line = result.substr(0, result.length() - 1);
    } else {
        m_line = line;
    }
}

bool StringPlus::firstWordIs(const string &word) const {
    return m_line.substr(0, word.length()) == word;
}

string StringPlus::getSubString(const string &firstWord) const {
    return m_line.substr(firstWord.length());
}

string StringPlus::wordBefore(const char &sign) {
    string result;
    for (auto &letter : m_line) {
        if (letter == sign) {
            break;
        }
        result += letter;
    }
    return result;
}

bool StringPlus::YesNoAnswer() {
    while (m_line != NO && m_line != YES) {
        cout << "Please, try again." << endl << "Yes/No" << endl;
        if (!getline(cin, m_line)) {
            return false;
        }
    }
    return true;
}

string StringPlus::getLine() {
    return m_line;
}

vector<string> StringPlus::wordsInLine() {
    string word;
    vector<string> words;
    for (auto &letter : m_line) {
        if (letter == ' ' || letter == '\t') {
            words.push_back(word);
            word = "";
        } else {
            word += letter;
        }
    }
    words.push_back(word);
    return words;
}

bool StringPlus::hasName(const string &name) {
    string fileName = getFileName();
    int len = fileName.length();
    string end = ".txt";
    if (len - end.length() <= name.length()) {
        return false;
    }
    string result;
    for (int i = len - end.length() - name.length(); i < len - end.length(); i++) {
        result += fileName[i];
    }
    return result == name;
}

void StringPlus::insertName(const string &name) {
    m_line = wordBefore('.') + name + ".txt";
}

string StringPlus::getFileName() {
    int lenLine = m_line.length();
    int lenFileName = 0;
    for (int i = lenLine - 1; i != -1; i--) {
        if (m_line[i] == '/')
            break;
        lenFileName++;
    }
    string result;
    for (int i = lenLine - lenFileName; i < lenLine; i++) {
        result += m_line[i];
    }
    return result;
}

bool StringPlus::nicknameOK() {
    for (auto &letter : m_line) {
        if (!isdigit(letter) && !isalpha(letter) && letter != '_') {
            return false;
        }
    }
    return true;
}

bool StringPlus::operator==(const string &anotherLine) {
    return m_line == anotherLine;
}

bool StringPlus::operator!=(const string &anotherLine) {
    return m_line != anotherLine;
}

StringPlus &StringPlus::operator=(const string &anotherLine) {
    *this = StringPlus(anotherLine);
    return *this;
}