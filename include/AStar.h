#ifndef ASTAR_H
#define ASTAR_H

#include "CostMap.h"
#include <vector>
#include <memory>

struct Node
{
    Point2 pos;
    float g;
    float h;
    float f;

    bool isClosed;
    std::shared_ptr<Node> parent;
};

typedef std::shared_ptr<Node> NodeSharedPtr;

class AStar
{
public:
    AStar(CostMap map);

    bool solve(Point2 start, Point2 goal);

    std::vector<Point2> getPath()
    {
        return _path;
    }

private:
    void computePath(NodeSharedPtr goal);
    float computeHeuristic(const Point2& start, const Point2& goal);
    int computeHash(const Point2& pos);

    CostMap _costmap;
    std::vector<Point2> _path;

    const int _dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int _dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    const float _travel_cost[8] = {1, 1, 1, 1, sqrt(2), sqrt(2), sqrt(2), sqrt(2)};
};

class NodeComparator
{
public:
    bool operator()(const NodeSharedPtr &a, const NodeSharedPtr &b) const
    {
        return a->f > b->f;
    }
};

#endif