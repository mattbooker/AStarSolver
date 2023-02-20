#include "AStar.h"
#include <queue>

AStar::AStar(CostMap map) : _costmap(map)
{
}

bool AStar::solve(Point2 start, Point2 goal)
{
    if (!_costmap.inBounds(start))
    {
        printf("AStar Failed: Start position not in bounds\n");
        return false;
    }
    else if (!_costmap.inBounds(goal))
    {
        printf("AStar Failed: Goal position not in bounds\n");
        return false;
    }

    // Create open list and visited map
    std::priority_queue <NodeSharedPtr, 
                         std::vector<NodeSharedPtr>, 
                         NodeComparator 
                        > open_list;

    std::unordered_map<Point2, NodeSharedPtr, NodeHasher> visited;

    NodeSharedPtr root = std::make_shared<Node>();
    root->f = root->g = root->h = 0;
    root->pos = start;

    open_list.push(root);

    return true;
}