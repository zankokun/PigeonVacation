#ifndef STONEMANAGER_H_INCLUDED
#define STONEMANAGER_H_INCLUDED

#include "Stone.h"
#include "MapManager.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include <vector>

class StoneManager{
private:
    std::string fileToStoneImage;
    std::vector<Stone> stones;

public:
    StoneManager(const std::string& pathToImage, MapManager& mapMgr);
    void draw(sf::RenderWindow& window);
    void update(sf::Time& time, MapManager& mapMgr);
    bool check(const Player& player) const;

};


#endif // STONEMANAGER_H_INCLUDED
