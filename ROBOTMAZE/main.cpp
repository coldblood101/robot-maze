#include <iostream>
#include"MazeLogic.h"
#include"IRobot.h"
using namespace std;
void control(IRobot& );
int main()
{
    MazeLogic maze_logic = MazeLogic();
    maze_logic.start(control);
    return 0;
}
void control(IRobot& robot)
{
    robot.advance();
}
