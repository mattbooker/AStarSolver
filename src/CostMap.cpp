#include "CostMap.h"
#include <opencv2/imgproc/imgproc.hpp>

bool CostMap::loadMap(std::string file_name)
{
    cv::Mat img = cv::imread(file_name);

    if (!img.data)
    {
        return false;
    }

    cv::cvtColor(img, _map, cv::COLOR_BGR2GRAY);

    return true;
}

uint8_t CostMap::getCost(Point2 pos)
{
    return _map.at<uint8_t>(pos.x, pos.y);
}

bool CostMap::inBounds(Point2 pos)
{
    if (pos.x < 0 || pos.x >= _map.cols || pos.y < 0 || pos.y >= _map.rows)
    {
        return false;
    }

    return true;
}

void CostMap::showMap()
{
    cv::imshow("Map Window", _map);
    cv::waitKey(0);
    cv::destroyAllWindows();
}