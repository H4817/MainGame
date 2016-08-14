#ifndef MYPROJECT_MAPSIZE_H
#define MYPROJECT_MAPSIZE_H

#include <iostream>
#include <vector>

class LevelInfo {
public:
    static size_t currentLevel;
    const std::vector<std::pair<size_t, size_t >> mapSize = {{1920, 1200},
                                                             {3120, 3028}};
};




#endif //MYPROJECT_MAPSIZE_H
