#ifndef RECURSIVEGENERATOR_H
#define RECURSIVEGENERATOR_H
#include<stack>
#include"Maze.h"

using std::stack;

class RecursiveGenerator
{
    public:
        RecursiveGenerator();
        virtual ~RecursiveGenerator();
        void generateMaze(class Maze& input_maze);
    protected:

    private:
        struct Cell {
            bool top_wall;
            bool bottom_wall;
            bool left_wall;
            bool right_wall;
            bool visited;
            int display_num;
            Cell(){
                top_wall = true;
                bottom_wall = true;
                left_wall = true;
                right_wall = true;
                visited=false;
                display_num = WALL;
            }
        };

        void setGridValue(class Maze& ,const int & ,const int & ,int );

        stack<COORD> back_track_coord;
        int **recursive_grid;
        int maze_width;
        int maze_height;
};

#endif // RECURSIVEGENERATOR_H
