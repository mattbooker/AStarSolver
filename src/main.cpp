#include <iostream>
#include "CostMap.h"

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
}