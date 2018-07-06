#include "MazeLogic.h"

MazeLogic::MazeLogic()
{
    //ctor
    srand(time(0));
    screen_display = new ScreenDisplay();
    program_exist = true;
    default_width=default_height=20;
    maze = new Maze(default_height,default_width);

    robot = new IRobot();

    prim_generator = new PrimGenerator();

    recursive_generator = new RecursiveGenerator();

    robot_controller = new RobotController();

    prim_generator->generateMaze(*maze);
    robot->setMaze(*maze);
}

MazeLogic::~MazeLogic()
{
    //dtor
    delete maze;
    delete robot;
    delete prim_generator;
    delete recursive_generator;
    delete screen_display;
    delete robot_controller;

}

void MazeLogic:: start(void (*control)(IRobot& ))
{

    screen_display->displayDistruction();
    screen_display->drawBorder();
    screen_display->drawMaze(*maze);
    screen_display->drawRobot(*robot);
    while(program_exist)
    {
        getUserInteract();
        if(robot->getState())
        {
            if(robot_controller->getController())
                robot_controller->simpleController(*robot);
            else
                control(*robot);
            screen_display->drawRobot(*robot);
        }
    }

}

void MazeLogic::getUserInteract()
{
    if(GetAsyncKeyState(0x31)||GetAsyncKeyState(VK_NUMPAD1))
    {
            maze->setGenerator(false);
    }

    if(GetAsyncKeyState(0x32)||GetAsyncKeyState(VK_NUMPAD2))
    {
            maze->setGenerator(true);
    }

    if(GetAsyncKeyState(0x33)||GetAsyncKeyState(VK_NUMPAD3))
    {
        screen_display->deleteMaze();
        maze = new Maze("Maze.txt");
        robot->restart();
        robot->setMaze(*maze);
        screen_display->drawMaze(*maze);
        screen_display->drawRobot(*robot);

    }

    if(GetAsyncKeyState(0x34)||GetAsyncKeyState(VK_NUMPAD4))
    {
        maze->saveToFile();
    }

    if(GetAsyncKeyState(0x35)||GetAsyncKeyState(VK_NUMPAD5))
    {
        screen_display->deleteMaze();
        robot->restart();
        delete maze;
        maze = new Maze(default_height,default_width);

        if(maze->getGenerator())
        {
            prim_generator->generateMaze(*maze);
        }
        else
        {
            recursive_generator->generateMaze(*maze);
        }

        robot->setMaze(*maze);
        screen_display->drawMaze(*maze);
        screen_display->drawRobot(*robot);
    }

    if((GetAsyncKeyState(0x36)||GetAsyncKeyState(VK_NUMPAD6))&&!robot->getState())
    {
        robot_controller->setController(false);
    }

    if((GetAsyncKeyState(0x37)||GetAsyncKeyState(VK_NUMPAD7))&&!robot->getState())
    {
        robot_controller->setController(true);
    }

    if(GetAsyncKeyState(0x38)||GetAsyncKeyState(VK_NUMPAD8))
    {
        robot->restart();
        screen_display->deleteMaze();
        screen_display->drawMaze(*maze);
        screen_display->drawRobot(*robot);
    }

    if((GetAsyncKeyState(0x39)||GetAsyncKeyState(VK_NUMPAD9))&&!robot->getState())
    {
        robot->start();
    }

    if (GetAsyncKeyState(VK_ESCAPE))
    {
        program_exist = false;
    }

    if(GetAsyncKeyState(VK_UP)&&!robot->getState())
    {
        default_height++;
        if(default_height>20)
            default_height=1;
    }

    if(GetAsyncKeyState(VK_DOWN)&&!robot->getState())
    {
        default_width++;
        if(default_width>20)
            default_width=1;
    }

    screen_display->displayChoose(maze->getGenerator(),robot_controller->getController());
    return ;
}
