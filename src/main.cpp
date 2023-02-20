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
    Point2 start = {70, 25};
    Point2 goal = {600, 500};

    
    bool solution_found = solver.solve(start, goal);

    if (solution_found)
    {
        printf("Solution Found\n");
        std::vector<Point2> solution = solver.getPath();

        printf("Solution len = %d\n", solution.size());
        map.drawAndShowPath(start, goal, solution); 
    }
    else
        printf("Solution not found\n");
    
}