#include "StoneManager.h"
#include <iostream>

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
}

void StoneManager::update(sf::Time& time, MapManager& mapMgr)
{
    static sf::Time oneSec = sf::Time::Zero;
    static float timeToSpawn = 1.f;

    oneSec+=time;
    if(oneSec.asSeconds() > timeToSpawn ){
        stones.emplace_back(fileToStoneImage, mapMgr);
        oneSec = sf::Time::Zero;
    }

    for(auto& stone: stones)
    {
        stone.update(time, mapMgr);
    }

    int widthScreen = mapMgr.getWidth()*mapMgr.getBlockSize().x;
    int heightScreen = mapMgr.getHeight()*mapMgr.getBlockSize().y;

    std::cout << stones.size() << std::endl;

    for(auto stone=stones.begin(); stone!=stones.end(); stone++ )
    {
        auto position = stone->getPosition(); ///    (*stone).getPosition()

        if(position.y>heightScreen){
            /// speed up game
            static int removedStones=0;
            removedStones++;
            if(removedStones%3==0)
            {
                if (timeToSpawn>0.15f)
                {
                    timeToSpawn-=0.05f;
                }
            }
            /// removing stones
            stone = stones.erase(stone);
            if(stone == stones.end()) break;
        }

    }
}



