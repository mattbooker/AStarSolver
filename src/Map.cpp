#include "Map.h"
#include <opencv2/imgproc/imgproc.hpp>

bool Map::loadMap(std::string file_name)
{
    cv::Mat img = cv::imread(file_name);

    if (!img.data)
    {
        return false;
    }

    cv::cvtColor(img, _map, cv::COLOR_BGR2GRAY);

    return true;
}

uint8_t Map::getCost(int x, int y)
{
    return _map.at<uint8_t>(x, y);
}

bool Map::inBounds(int x, int y)
{
    if (x < 0 || x >= _map.cols || y < 0 || y >= _map.rows)
    {
        return false;
    }

    return true;
}

void Map::showMap()
{
    cv::imshow("Map Window", _map);
    cv::waitKey(0);
    cv::destroyWindow("Map Window");
}