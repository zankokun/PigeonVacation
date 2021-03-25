#include "Stone.h"

Stone::Stone(const std::string &filePath, const MapManager& mapMgr)
{
    static sf::Image img;
    if(img.getSize().x==0){
       if(!img.loadFromFile(filePath)){
        throw;
       }
    }
    static sf::Texture tex;
    if(tex.getSize().x==0){
        tex.loadFromImage(img);
    }

    sprite.setTexture(tex);
    sprite.setTextureRect(sf::IntRect(0,0,mapMgr.getBlockSize().x,mapMgr.getBlockSize().y));

    int x = mapMgr.getWidth();
    int y = mapMgr.getHeight();

    sprite.setPosition(mapMgr.getBlockSize().x *(rand()%x), int(mapMgr.getBlockSize().y) * -1);
    sprite.setOrigin(mapMgr.getBlockSize().x/2,mapMgr.getBlockSize().y/2);
    speed = sf::Vector2f(mapMgr.getBlockSize());
    dir = sf::Vector2f((float(rand()%1000) / 10.f) - 50.f , 5*mapMgr.getBlockSize().y );    ///  678  0.678  0.345

}

void Stone::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &texture;

    // draw the vertex array
    target.draw(sprite, states);
}

void Stone::updateSprite(sf::Time &time, MapManager& mapMgr)
{
    static float texturePosition = 1.f;
    static float s=5;
    texturePosition += s * time.asSeconds();
    sprite.setTextureRect(sf::IntRect(int(texturePosition) * mapMgr.getBlockSize().x,
                                          0,
                                          mapMgr.getBlockSize().x,
                                          mapMgr.getBlockSize().y)
                              );

    if(texturePosition>=2.5f || texturePosition<=0.5f) s *= -1;
    texturePosition = std::min(2.5f, std::max(texturePosition,0.5f));
}

void Stone::update(sf::Time &time, MapManager& mapMgr)
{
    updateSprite(time, mapMgr);

    sprite.move(time.asSeconds() * dir);
}
