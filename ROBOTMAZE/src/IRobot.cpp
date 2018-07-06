#include "IRobot.h"

#include<iostream>


IRobot::IRobot()
{
    //ctor
    steps =0;
    colisions=0;
    active=false;
    sleep_time=0;//1000;
    color_code = B_GREEN;
    direction = 10+rand()%4;
}

IRobot::~IRobot()
{
    //dtor
    this->maze.~Maze();
}

void IRobot::restart()
{
    steps =0;
    colisions=0;
    active = false;
    color_code = B_GREEN;
    direction = 10+rand()%4;
    int maze_height = this->maze.getHeight();
    int maze_width = this->maze.getWidth();
    this->setLocation(this->maze.getStart());
    this->pre_location.X = this->maze.getStart().X;
    this->pre_location.Y= this->maze.getStart().Y;
    this->target.X  = this->maze.getFinish().X;
    this->target.Y  = this->maze.getFinish().Y;
    for(int i=0;i<maze_height;i++)
        for(int j=0;j<maze_width;j++)
            colision_track[i][j]=false;
    this->colision_track[this->maze.getStart().Y][this->maze.getStart().X]=true;

}

void IRobot::start()
{
    active = true;
}

void IRobot::face(const int& facing)
{
    if(active){
        switch(facing)
        {
        case 100:
            switch(this->direction)
            {
            case NORTH:
                this->direction=WEST;
                break;
            case SOUTH:
                this->direction=EAST;
                break;
            case WEST:
                this->direction=SOUTH;
                break;
            case EAST:
                this->direction=NORTH;
                break;
            default:
                break;
            }
            break;
        case 101:
            switch(this->direction)
            {
            case NORTH:
                this->direction=EAST;
                break;
            case SOUTH:
                this->direction=WEST;
                break;
            case WEST:
                this->direction=NORTH;
                break;
            case EAST:
                this->direction=SOUTH;
                break;
            default:
                break;
            }
            break;
        case 103:
            break;
        case 102:
            switch(this->direction)
            {
            case NORTH:
                this->direction=SOUTH;
                break;
            case SOUTH:
                this->direction=NORTH;
                break;
            case WEST:
                this->direction=EAST;
                break;
            case EAST:
                this->direction=WEST;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void IRobot::advance()
{
    if(location.X==target.X && location.Y==target.Y&&this->active)
    {
        active=false;
        this->color_code = B_GREEN_B_YELLOW;
    }
    if(active)
    {
        pre_location.X=location.X;
        pre_location.Y=location.Y;
        color_code =B_GREEN;
        if(!facingWall())
        {
            if(direction==NORTH)
            {
                if(location.Y>1)
                location.Y-=1;
                steps++;
            }
            else if(direction==SOUTH)
            {

                if(location.Y<maze.getHeight()-2)
                    location.Y+=1;
                steps++;
            }
            else if(direction==WEST)
            {
                if(location.X>1)
                    location.X-=1;
                steps++;
            }
            else if(direction==EAST)
            {
                if(location.X<maze.getWidth()-2)
                    location.X+=1;
                steps++;
            }
            if(checkColision(location)){
                    this->color_code = B_GREEN_GRAY;
                    colisions++;
            }
            colision_track[location.Y][location.X]=true;
        }
        else{
            color_code = B_GREEN_B_RED;
        }
    }
    Sleep(sleep_time);
    return ;
}

int IRobot::getDirection() const
{
    return this->direction;
}

COORD IRobot::getLocation() const
{
    return location;
}

int IRobot::getLocationX() const
{
    return this->location.X;
}

int IRobot::getLocationY() const
{
    return this->location.Y;
}

void IRobot::setMaze(const class Maze& maze)
{
    this->maze = maze;
    int maze_height = this->maze.getHeight();
    int maze_width = this->maze.getWidth();
    this->setLocation(this->maze.getStart());
    this->pre_location.X = this->maze.getStart().X;
    this->pre_location.Y= this->maze.getStart().Y;
    this->target.X  = this->maze.getFinish().X;
    this->target.Y  = this->maze.getFinish().Y;

    this->colision_track = (bool**)malloc(maze_height*sizeof(bool*));
    for(int i=0;i<maze_height;i++)
        this->colision_track[i] = (bool*)malloc(maze_width*sizeof(bool));
    for(int i=0;i<maze_height;i++)
        for(int j=0;j<maze_width;j++)
            colision_track[i][j]=false;
    this->colision_track[this->maze.getStart().Y][this->maze.getStart().X]=true;

    return ;
}

 bool IRobot::facingWall()
{
     switch(this->direction)
     {
     case NORTH:
        return (this->maze.getGridValue(location.Y-1,location.X))==2;
        break;
     case SOUTH:
        return (this->maze.getGridValue(location.Y+1,location.X))==2;
        break;
     case EAST:
        return (this->maze.getGridValue(location.Y,location.X+1))==2;
        break;
     case WEST:
        return (this->maze.getGridValue(location.Y,location.X-1))==2;
        break;
     }
     return true;
 }

 bool IRobot::checkColision(const COORD & location)
{
     return this->colision_track[location.Y][location.X];
 }

void IRobot::setLocation(const int& y_pos, const int &x_pos)
{
    this->location.X=x_pos;
    this->location.Y= y_pos;
    return;
}

void IRobot::setLocation(const COORD & location)
{
    this->location.X = location.X;
    this->location.Y=location.Y;
}

COORD IRobot::getTarget() const
{
    return this->maze.getFinish();
}

int IRobot::getSleepTime() const
{
    return this->sleep_time;
}

void IRobot::setSleepTime(const int & sleep_time)
{
    this->sleep_time = sleep_time;
}

int IRobot::getSteps() const
{
    return this->steps;
}

int IRobot::getColisions() const
{
    return this->colisions;
}

int IRobot::getColorCode() const
{
    return this->color_code;
}

COORD IRobot::getPreLocation() const
{
    return this->pre_location;
}

bool IRobot::getState() const
{
    return this->active;
}

