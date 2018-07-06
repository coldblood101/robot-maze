#include "RobotController.h"

RobotController::RobotController()
{
    //ctor
    is_simple_controller = true;
}

RobotController::~RobotController()
{
    //dtor
}
void RobotController::simpleController(class IRobot&  robot)
{
    int randno;
    int direction;
    randno = rand()%3;
    if (randno == 0)
	    direction = robot.LEFT;
	else if (randno == 1)
	    direction = robot.RIGHT;
	else if (randno == 2)
	    direction = robot.BEHIND;
	else
	    direction = robot.AHEAD;

    robot.face(direction);
    robot.advance();
    return ;
}
void RobotController::studentController(class IRobot&  robot)
{
    robot.advance();
    return ;
}

bool RobotController::getController() const
{
    return is_simple_controller;
}

void RobotController::setController(const bool& is_simple_controller)
{
    this->is_simple_controller = is_simple_controller;
}
