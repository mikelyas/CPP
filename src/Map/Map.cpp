#include "Map.h"

Map::Map(const string &filePath, shared_ptr<Hero> &hero)
        : _hero(hero) {
    ifstream file(filePath);
    string startingPoint = _hero->getCheckPoint();
    string line;
    getline(file, line);
    // if player has launched a previous game
    if (!startingPoint.empty()) {
        while (line != startingPoint) {
            getline(file, line);
        }
    }
    do {
        vector<shared_ptr<Place>> nextLocations;
        StringPlus linePlus(line, false);
        if (linePlus.firstWordIs(VILLAGE)) {
            Village village(VILLAGES_FILES + "/" + line, _hero);
            nextLocations.push_back(make_shared<Village>(village));
        } else {
            vector<string> words = linePlus.wordsInLine();
            for (auto &word : words) {
                Arena arena(ARENAS_FILES + "/" + word, _hero);
                nextLocations.push_back(make_shared<Arena>(arena));
            }
        }
        _places.push_back(nextLocations);
    } while (getline(file, line));
    _currentLocation = _places[0][0];
}

bool Map::start() {
    for (auto &nextLocations : _places) {
        shared_ptr<Place> nextLocation;
        if (nextLocations.size() > 1) { // if several locations on the way
            if (!(nextLocation = chooseLocation(nextLocations))) {
                _hero->setCheckPoint(_currentLocation->getFilePath());
                return false;
            }
        } else { // if only one location on the way
            nextLocation = nextLocations[0];
        }
        _currentLocation = nextLocation;
        nextLocation->welcome();
        // check if hero got through the map
        if (!nextLocation->showOptions()) {
            if (!_hero->isDead()) {
                //sets checkpoint to save the game
                _hero->setCheckPoint(_currentLocation->getFilePath());
            }
            return false;
        }
    }
    return true;
}

shared_ptr<Place> Map::chooseLocation(const vector<shared_ptr<Place>> &locations) const {
    cout << "Please, choose next location." << endl
         << "Choose wisely, a lot depends on your choice!" << endl;
    for (auto &location : locations) {
        cout << location->getName() << endl;
    }
    cout << "Please, enter your choice." << endl;
    string line;
    while (true) {
        // checks input
        if (!getline(cin, line)) {
            return nullptr;
        }
        for (auto &location : locations) {
            if (location->getName() == StringPlus(line).getLine()) {
                return location;
            }
        }
        cout << "Location you've entered does not exist. Please, try again" << endl;
    }
}
