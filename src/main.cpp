#include <iostream>
#include <sstream>
#include <chrono>
#include "CostMap.h"
#include "AStar.h"
#include <string>

struct ParsedArgs
{
    std::string file_path = "";
    Point2 start;
    Point2 goal;
};

std::string removeQuote(std::string input)
{
    if (input.length() > 0 && input.front() == '\"')
        return input.substr(1, input.length() - 2);
    return input;
}

Point2 convertToPoint(std::string input)
{
    std::vector<int> result;
    std::stringstream stream(input);

    for (int i; stream >> i;)
    {
        result.push_back(i);

        if (result.size() == 2)
            break;

        if (stream.peek() == ',')
            stream.ignore();
    }

    return Point2{result[0], result[1]};
}

ParsedArgs parseOptions(int argc, const char **argv)
{
    ParsedArgs args;

    for (int i = 1; i < argc; i++)
    {
        if (i < argc - 1)
        {
            if (strcmp(argv[i], "-i") == 0)
                args.file_path = removeQuote(argv[i + 1]);
            else if (strcmp(argv[i], "-s") == 0)
                args.start = convertToPoint(argv[i + 1]);
            else if (strcmp(argv[i], "-g") == 0)
                args.goal = convertToPoint(argv[i + 1]);
        }
    }
    return args;
}

int main(int argc, const char **argv)
{
    ParsedArgs args = parseOptions(argc, argv);

    CostMap map;
    bool success = map.loadMap(args.file_path);

    if (!success)
    {
        printf("Error: Could not load image\n");
        return -1;
    }

    map.showMap();

    AStar solver(map);

    auto begin = std::chrono::high_resolution_clock::now();
    bool solution_found = solver.solve(args.start, args.goal);
    auto end = std::chrono::high_resolution_clock::now();

    if (solution_found)
    {
        printf("Solution Found in %.1fms\n", std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin) * 1e-6);
        std::vector<Point2> solution = solver.getPath();

        printf("Solution len = %ld\n", solution.size());
        map.drawAndShowPath(args.start, args.goal, solution);
    }
    else
        printf("Solution not found\n");

    return 0;
}