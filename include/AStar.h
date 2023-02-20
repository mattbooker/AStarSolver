#ifndef ASTAR_H
#define ASTAR_H

#include "CostMap.h"
#include <vector>
#include <memory>

struct Node
{
    Point2 pos;
    int g;
    int h;
    int f;

    bool isClosed;
    std::shared_ptr<Node> parent;
};

typedef std::shared_ptr<Node> NodeSharedPtr;

class AStar
{
public:
    AStar(CostMap map);

    bool solve(Point2 start, Point2 goal);

    std::vector<Point2> getPath();

private:
    CostMap _costmap;
    std::vector<Point2> _path;
};

class NodeComparator
{
public:
    bool operator()(const NodeSharedPtr &a, const NodeSharedPtr &b) const
    {
        return a->f < b->f;
    }
};

class NodeHasher
{
public:
    // NOTE: Only works if width of costmap is less than 10000
    int operator()(const NodeSharedPtr &a) const
    {
        return a->pos.x * 10000 + a->pos.y;
    }
};

#endif