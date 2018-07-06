#ifndef MAZELOGIC_H
#define MAZELOGIC_H

#include<time.h>
#include "Maze.h"
#include "IRobot.h"
#include "ScreenDisplay.h"
#include "RobotController.h"
#include "PrimGenerator.h"
#include "RecursiveGenerator.h"

class MazeLogic
{
    public:
        MazeLogic();
        virtual ~MazeLogic();
        void start(void (*control)(IRobot& ));
    protected:

    private:
        Maze *maze;
        bool program_exist;
        ScreenDisplay *screen_display;
        IRobot *robot;
        RobotController *robot_controller;
        PrimGenerator *prim_generator;
        RecursiveGenerator *recursive_generator;
        int default_width;
        int default_height;
        void getUserInteract();
};

#endif // MAZELOGIC_H
