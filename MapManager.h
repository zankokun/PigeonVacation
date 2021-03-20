#ifndef MAPMANAGER_H_INCLUDED
#define MAPMANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

class MapManager {
private:
    std::string pathToFile;
    int height, width;
    std::vector<int> level;
    sf::Vector2u blockSize;

public:
    enum class BlockType{
        Grass,
        Water,
        Tree,
        Stone
    };
    MapManager(std::string path):pathToFile(path) {};
    ~MapManager()
    {
        unload(pathToFile);
    }
    bool load()
    {
        return load(pathToFile);
    }
    bool load(std::string path);
    bool unload(std::string path);

    sf::Vector2u getBlockSize() const;
    int* getLevel();
    int getWidth() const;
    int getHeight() const;
    /// to fix
    void updateBlock(int x, int y);
    /// to fix
    BlockType getBlockType(int x, int y);
};

#endif // MAPMANAGER_H_INCLUDED
