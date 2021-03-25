#include "TileMap.h"
#include "MapManager.h"
#include "Player.h"
#include "StoneManager.h"

int main()
{
    srand(time(0));
    /// create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tilemap");

    MapManager mapMgr("res/level_1.txt");
    if (!mapMgr.load()){
        return -1;
    }

    Player ping("res/ping.png", mapMgr);

    StoneManager stoneMgr("res/rock.png", mapMgr);

    /// create the tilemap from the level definition
    TileMap map;
    if (!map.load("res/tilemap.png",
                  mapMgr.getBlockSize(),
                  mapMgr.getLevel(),
                  mapMgr.getWidth(),
                  mapMgr.getHeight()
                 )
        ){

        return -1;
    }

    sf::Clock clock;
    /// run the main loop
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        if(deltaTime.asSeconds() > 1 ) deltaTime = sf::Time::Zero;

        /// handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Resized)
            {
                deltaTime = sf::Time::Zero;
            }
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            /// ловим нажатие по карте
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int x = event.mouseButton.x / mapMgr.getBlockSize().x;
                    int y = event.mouseButton.y / mapMgr.getBlockSize().y;
                    mapMgr.updateBlock(y, x);
                    map.updateTileMap(mapMgr);
                }
            }
            ping.handleEvent(event);
        }



        ping.update(deltaTime, mapMgr);
        stoneMgr.update(deltaTime, mapMgr);

        if (stoneMgr.check(ping)){
            /// Game over
            return 1;
        }

        /// draw the map
        window.clear();
        window.draw(map);

        window.draw(ping);

        stoneMgr.draw(window);

        window.display();
    }
    return 0;
}
