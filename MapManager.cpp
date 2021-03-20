#include "MapManager.h"
#include <fstream>

bool MapManager::load(std::string path)
{
    std::ifstream file(path);
    if (file.fail()){
        return false;
    }

    file >> blockSize.x >> blockSize.y;

    file >> width >> height;

    for(int i=0; i<width * height; ++i){
        int temp;
        file >> temp;
        level.push_back(temp);
    }
    return true;
}

bool MapManager::unload(std::string path)
{
    using std::endl;

    std::ofstream file(path);
    if (file.fail()){
        return false;
    }

    file << blockSize.x <<" "<< blockSize.y << endl;

    file << width <<" "<< height << endl;

    for(int i=0; i<height; ++i)
    {
        for(int j=0; j<width; ++j)
        {
            file << level[i*width + j] << " ";
        }
        file << endl;
    }

    file.close();

    return true;
}

sf::Vector2u MapManager::getBlockSize() const
{
    return blockSize;
}

int* MapManager::getLevel()
{
    return level.data();
}

int MapManager::getWidth() const
{
     return width;
}

int MapManager::getHeight() const
{
    return height;
}

void MapManager::updateBlock(int x, int y)
{
    if(x>=height || y>=width)
    {
        std::vector<int> new_level;
        int new_height = std::max(height, x+1);
        int new_width = std::max(width, y+1);
        new_level.resize(new_height*new_width);

        std::fill(new_level.begin(), new_level.end(), 0);
        for(int i=0; i<height; ++i)
        {
            for(int j=0; j<width; ++j)
                new_level[i*new_width+j] = level[i*width+j];
        }
        width = new_width;
        height = new_height;
        level.swap(new_level);
    }
    else
        level[x*width+y]=(level[x*width+y]+1)%4;
}

 MapManager::BlockType MapManager::getBlockType(int x, int y)
 {
     return BlockType(level[x*width+y]);
 }


