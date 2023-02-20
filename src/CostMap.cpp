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

    // Need white to have cost of 0 and black to have cost of 255
    cv::bitwise_not(_map, _map);

    return true;
}

uint8_t CostMap::getCost(const Point2& pos)
{
    return _map.at<uint8_t>(pos.x, pos.y);
}

bool CostMap::inBounds(const Point2& pos)
{
    if (pos.x < 0 || pos.x >= _map.cols || pos.y < 0 || pos.y >= _map.rows)
    {
        return false;
    }

    return true;
}

void CostMap::showMap()
{
    cv::Mat output;
    cv::bitwise_not(_map, output);
    cv::imshow("Map Window", output);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

void CostMap::drawAndShowPath(const Point2& start, const Point2& goal, const std::vector<Point2>& path)
{
    cv::Mat drawn_map;
    cv::bitwise_not(_map, drawn_map);

    cv::Point start_point = cv::Point(start.x, start.y);
    cv::circle(drawn_map, start_point, 5, cv::Scalar(0, 0, 0), -1);

    cv::Point goal_point = cv::Point(goal.x, goal.y);
    cv::circle(drawn_map, goal_point, 5, cv::Scalar(0, 0, 0), -1);


    cv::imshow("Map with Drawings", drawn_map);
    cv::waitKey(0);
    cv::destroyAllWindows();
}