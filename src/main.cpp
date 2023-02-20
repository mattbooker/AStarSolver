#include <iostream>
#include "CostMap.h"
#include "AStar.h"

int main(int argc, char *argv[])
{
    CostMap map;

    bool success = map.loadMap("../example.png");

    if (!success)
    {
        printf("Error: Could not load image");
        return -1;
    }

    map.showMap();

    AStar solver(map);
    Point2 start = {50, 50};
    Point2 goal = {500, 300};

    bool sol = solver.solve(start, goal);

    if (sol)
        printf("Solution Found\n");
    else
        printf("Solution not found\n");

    std::vector<Point2> solution = solver.getPath();

    printf("Solution len = %d\n", solution.size());
    map.drawAndShowPath(start, goal, solution);
}