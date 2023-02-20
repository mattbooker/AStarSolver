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

    // Convert so we can add color
    cv::cvtColor(drawn_map, drawn_map, cv::COLOR_GRAY2BGR);

    cv::Point start_point = cv::Point(start.x, start.y);
    cv::circle(drawn_map, start_point, 5, cv::Scalar(0, 255, 0), -1);

    cv::Point goal_point = cv::Point(goal.x, goal.y);
    cv::circle(drawn_map, goal_point, 5, cv::Scalar(0, 0, 255), -1);

    if (path.size() > 0)
    {
        for (int i = 0; i < path.size() - 2; i++)
        {
            cv::Point p1 = cv::Point(path[i].x, path[i].y);
            cv::Point p2 = cv::Point(path[i+1].x, path[i+1].y);
            cv::line(drawn_map, p1, p2, cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
        }
    }

    cv::imshow("Map with Drawings", drawn_map);
    cv::waitKey(0);
    cv::destroyAllWindows();
}