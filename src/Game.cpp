#include "Game.h"

Game::Game() :
        m_hero(make_shared<Hero>(Hero(PLAYERS_FILES + "/PlayerTemplate.txt"))),
        m_map(MAP_FILE, m_hero) {
    m_fileNameStory = STORY;
}

void Game::run() {
    mainMenu();
}

void Game::showStory() {
    ifstream file(m_fileNameStory);
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
}

void Game::mainMenu() {
    string line;
    while (line != EXIT) {
        cout << ">>>Main menu<<<" << endl
             << "Here are the options you can choose:" << endl
             << NEW_GAME << SEPARATOR << LOAD << SEPARATOR << EXIT << endl
             << "Please type in some of the options" << endl;
        if (!getline(cin, line)) {
            return;
        }
        StringPlus linePlus(line);
        // checks if player entered one of the options
        while (linePlus != NEW_GAME && linePlus != LOAD && linePlus != EXIT) {
            cout << "This is none of the options. Please, try again." << endl;
            // checks input
            if (!getline(cin, line)) {
                return;
            }
            linePlus = line;
        }
        if (linePlus == EXIT) {
            break;
        }
        // starts new game or load existing
        if (linePlus == NEW_GAME) {
            showStory();
            setHero();
        } else if (linePlus == LOAD) {
            if (!load(GAME_FILE)) {
                continue;
            }
        }
        if (m_map.start()) { // hero got trough map
            cout << "Congratulations, you've made it." << endl;
        } else {
            // ends the game if hero is dead, else save it
            if (m_hero->isDead()) {
                cout << "Game Over" << endl
                     << "Your hero is dead" << endl;
            } else {
                save();
            }
        }
    }
}

void Game::setHero() {
    if (!setNickname()) {
        return;
    }
    // change sex?
    if (!setSex()) {
        return;
    }
    // set hair colour
    cout << "Now choose the colour of your hair." << endl;
    m_hero->setHairColour();
    // set eyes colour
    cout << "At last, choose the colour of your eyes." << endl;
    m_hero->setEyesColour();
}

bool Game::setNickname() {
    string nickname;
    StringPlus nicknamePlus("");
    cout << "Please, type in your nickname." << endl
         << "You can only use letters, numbers and underscore." << endl;
    while (true) {
        // checks input
        if (!getline(cin, nickname)) {
            return false;
        }
        nicknamePlus = nickname;
        // checks if player exists and if nickname is of the good format
        if (playerExists(nicknamePlus.getLine())) {
            cout << "This name is in use. Try another one." << endl;
        } else if (!nicknamePlus.nicknameOK()) {
            cout << "Format is incorrect. Please, try again." << endl;
        } else {
            break;
        }
    }
    m_hero->setName(nicknamePlus.getLine());
    return true;
}

bool Game::setSex() {
    string sex;
    cout << "Your character is " << m_hero->getSex() << " by default." << endl
         << "Would you like to change sex of your hero? Yes/No" << endl;
    if (!getline(cin, sex)) {
        return false;
    }
    StringPlus sexPlus(sex);
    if (!sexPlus.YesNoAnswer()) {
        return false;
    }
    if (sexPlus == YES) {
        m_hero->changeSex();
    }
    return true;
}

bool Game::load(const string &fileName) {
    cout << "Here are all the previous savings:" << endl;
    string name;
    ifstream file(fileName);
    int numOfPlayers = 0;
    // shows all players
    while (getline(file, name)) {
        if (name == "PlayerTemplate") {
            continue;
        }
        numOfPlayers++;
        cout << name << SEPARATOR;
    }
    if (numOfPlayers == 0) {
        cout << "Sorry, but there is no previous savings." << endl;
        return false;
    }
    cout << endl
         << "Please, type in one of the above." << endl;
    while (getline(cin, name)) {
        StringPlus namePlus(name);
        // checks if player with this name exists, if yes initializes hero and map
        if (playerExists(namePlus.getLine())) {
            m_hero = make_shared<Hero>(Hero(PLAYERS_FILES + "/" + namePlus.getLine() + ".txt"));
            m_map = Map(MAP_FILE, m_hero);
            return true;
        }
        cout << "This is not the option. " << TRY_AGAIN;
        // checks for Yes/No answer
        string answer;
        // checks input
        if (!getline(cin, answer)) {
            return false;
        }
        StringPlus answerPlus(answer);
        // checks input
        if (!answerPlus.YesNoAnswer()) {
            return false;
        }
        if (answerPlus == NO) {
            return false;
        }
    }
    return false;
}

void Game::save() {
    string name;
    bool savingExists = false;
    fstream file(GAME_FILE, ios::in | ios::out | ios::app);
    while (getline(file, name)) {
        if (name == m_hero->getName()) {
            savingExists = true;
            break;
        }
    }
    file.clear();
    if (!savingExists) {
        file << endl << m_hero->getName();
    }
    file.close();
    m_hero->save();
}

bool Game::playerExists(const string &name) {
    ifstream file(GAME_FILE);
    vector<string> players;
    string playerName;
    while (getline(file, playerName)) {
        if (name == playerName) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
