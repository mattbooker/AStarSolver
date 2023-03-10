#include "AStar.h"
#include <queue>

/* 
Defines connectivity of neighbourhood
 4 or 8 works but 8 is always better
 NOTE: If you change to 4, need to change
 heuristic as well.
*/
#define NBR_CONNECTEDNESS 8

#define OBS_THRESHOLD 127

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

    std::unordered_map<int, NodeSharedPtr> visited;

    NodeSharedPtr root = std::make_shared<Node>();
    root->f = root->g = root->h = 0.0f;
    root->pos = start;

    open_list.push(root);
    visited.insert({computeHash(start), root});

    while (!open_list.empty())
    {
        NodeSharedPtr cur = open_list.top();
        open_list.pop();

        if (cur->pos == goal)
        {
            computePath(cur);
            return true;
        }

        cur->isClosed = true;

        for (int dir = 0; dir < NBR_CONNECTEDNESS; dir++)
        {
            Point2 nbr_pos = Point2{cur->pos.x + _dx[dir], cur->pos.y + _dy[dir]};

            // Skip if out of bounds
            if (!_costmap.inBounds(nbr_pos))
                continue;

            uint8_t map_cost = _costmap.getCost(nbr_pos);

            // Skip if cost is high enough to be an obstacle
            if (map_cost >= OBS_THRESHOLD)
                continue;

            int hash = computeHash(nbr_pos);

            // Check if a node already exists
            if (visited.find(hash) != visited.end())
            {
                NodeSharedPtr existing_node = visited[hash];

                // If node is in closed list we cant do better, so skip
                if (existing_node->isClosed)
                    continue;

                float cur_travel_cost = cur->g + _travel_cost[dir] + map_cost;

                // If current path to existing node is shorter, then edit existing node
                if (cur_travel_cost < existing_node->g)
                {
                    existing_node->g = cur_travel_cost;
                    existing_node->f = existing_node->h + cur_travel_cost;
                    existing_node->parent = cur;
                    
                    // We need to update the nodes position in the prio queue but 
                    // either we create a duplicate (and suffer overhead of re-expanding
                    // node) or we heapify the current priority queue (and suffer overhead
                    // of O(N) for elements in priority queue)
                    open_list.push(existing_node);
                }
            }
            else
            {
                // Node doesn't exist so just add it
                NodeSharedPtr nbr_node = std::make_shared<Node>();
                nbr_node->pos = nbr_pos;
                nbr_node->g = cur->g + _travel_cost[dir] + map_cost;
                nbr_node->h = computeHeuristic(nbr_pos, goal);
                nbr_node->f = nbr_node->g + nbr_node->h;
                nbr_node->parent = cur;

                // Add to visited
                visited.insert({hash, nbr_node});

                open_list.push(nbr_node);
            }
        }
    }

    return false;
}


void AStar::computePath(NodeSharedPtr goal)
{
    std::vector<Point2> results;
    NodeSharedPtr cur = goal;
    while(cur != nullptr)
    {
        results.push_back(cur->pos);
        cur = cur->parent;
    }

    // Reverse path so we have from start to goal
    std::reverse(results.begin(), results.end());

    _path = results;
}


float AStar::computeHeuristic(const Point2& start, const Point2& goal)
{
    // Use octile distance since its an exact heuristic for 8 connected grids
    int dx = abs(start.x - goal.x);
    int dy = abs(start.y - goal.y);
    return std::max(dx, dy) - std::min(dx, dy) + sqrt(2) * std::min(dx, dy);
}


int AStar::computeHash(const Point2& pos)
{
    // Only works for maps with a height less than 100000
    return pos.x * 100000 + pos.y;
}