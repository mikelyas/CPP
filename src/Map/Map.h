#ifndef SEMESTRALKA_MAP_H
#define SEMESTRALKA_MAP_H

#include "../usefullFunctions.h"
#include "../Constants.h"
#include "Places/Place.h"
#include "Places/Village.h"
#include "Places/Arena.h"
#include <vector>
#include <memory>


class Map {
public:
    /**
     * initializes map
     * @param filePath - path to file, where all the information is stored
     * @param hero - player
     */
    explicit Map(const string &filePath, shared_ptr<Hero> &hero);

    /**
     * starts the map
     * @return true, if hero got through the whole map
     */
    bool start();

    /**
     * if there are several locations on the way, let hero choose one of them
     * @param locations on the way
     * @return pointer to a location, which has been chosen by hero
     */
    shared_ptr<Place> chooseLocation(const vector<shared_ptr<Place>> &locations) const;

private:
    shared_ptr<Place> _currentLocation;
    vector<vector<shared_ptr<Place>>> _places;
    shared_ptr<Hero> _hero;
};

#endif //SEMESTRALKA_MAP_H
