#ifndef COSTMAP_H
#define COSTMAP_H

#include <string>
#include <memory>
#include <opencv2/opencv.hpp>

struct Point2
{
    int x;
    int y;

    bool operator== (const Point2& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
};

class CostMap
{
public:
    bool loadMap(std::string file_name);

    uint8_t getCost(const Point2& pos);

    bool inBounds(const Point2& pos);

    void showMap();

    void drawAndShowPath(const Point2& start, const Point2& goal, const std::vector<Point2>& path);

private:
    cv::Mat _map;
};

#endif