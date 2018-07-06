#ifndef SCREENDISPLAY_H
#define SCREENDISPLAY_H

#include<string>
#include"Maze.h"
#include"IRobot.h"
#include"ConsoleFix.h"
#include"ColorCode.h"

class ScreenDisplay
{
    public:
        ScreenDisplay();
        virtual ~ScreenDisplay();
        void drawBorder();
        void drawMaze(const class Maze& );
        void drawRobot(const class IRobot&);
        void displayDistruction();
        void deleteMaze() ;
        void displayChoose(bool, bool );
    protected:

    private:
        ConsoleFix console_fix;
        int ARROW_UP = 30;//NORTH
        int ARROW_DOWN =31;//SOUTH
        int ARROW_RIGHT = 16;//EAST
        int ARROW_LEFT =17;//WEST
        int maze_height;
        int maze_width;
        COORD start_pos ;
};

#endif // SCREENDISPLAY_H
