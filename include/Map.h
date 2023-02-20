#ifndef MAP_H
#define MAP_H

#include <string>
#include <memory>
#include <opencv2/opencv.hpp>

class Map
{
public:
    bool loadMap(std::string file_name);

    uint8_t getCost(int x, int y);

    bool inBounds(int x, int y);

    void showMap();

private:
    cv::Mat _map;
};

#endif