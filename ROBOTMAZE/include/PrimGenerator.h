#ifndef PRIMGENERATOR_H
#define PRIMGENERATOR_H

#include<vector>
#include"Maze.h"
#include<malloc.h>

using std::vector;


#define INSIDE      1
#define FRONTER     2
#define OUTSIDE     3

#define NORTH       10
#define EAST        11
#define SOUTH       12
#define WEST        13

class PrimGenerator
{
    public:
        PrimGenerator();
        virtual ~PrimGenerator();
        void generateMaze(class Maze& );
    protected:

    private:
        int maze_width;
        int maze_height;
        int **prim_grid;
        vector<COORD> frontier_list;

        void setPrimGridValue(class Maze&, int ,int ,int);
};

#endif // PRIMGENERATOR_H
