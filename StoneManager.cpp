#include "StoneManager.h"


bool StoneManager::check(const Player& player) const
{
    for(const auto& stone: stones)
    {
        if(player.check(stone))
        {
            return true;
        }
    }
    return false;
}

void StoneManager::draw(sf::RenderWindow& window)
{
    for(auto& stone: stones)
    {
        window.draw(stone);
    }
}

StoneManager::StoneManager(const std::string& pathToImage, MapManager& mapMgr)
{
    fileToStoneImage = pathToImage;
    stones.emplace_back(fileToStoneImage, mapMgr);

    stones.emplace_back(fileToStoneImage, mapMgr);
    stones.emplace_back(fileToStoneImage, mapMgr);
    stones.emplace_back(fileToStoneImage, mapMgr);
    stones.emplace_back(fileToStoneImage, mapMgr);
    stones.emplace_back(fileToStoneImage, mapMgr);
    stones.emplace_back(fileToStoneImage, mapMgr);
    stones.emplace_back(fileToStoneImage, mapMgr);
    stones.emplace_back(fileToStoneImage, mapMgr);
    stones.emplace_back(fileToStoneImage, mapMgr);
}

void StoneManager::update(sf::Time& time, MapManager& mapMgr)
{
    for(auto& stone: stones)
    {
        stone.update(time, mapMgr);
    }
}
