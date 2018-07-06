#ifndef IROBOT_H
#define IROBOT_H

#include"Maze.h"
#include"ColorCode.h"

#define NORTH       10
#define EAST        11
#define SOUTH       12
#define WEST        13

class IRobot
{
    public:
        int LEFT =100;
        int RIGHT =101;
        int BEHIND =102;
        int AHEAD =103;

        IRobot();
        virtual ~IRobot();
        void face(const int& ) ;
        void advance();
        bool facingWall();
        COORD getLocation() const ;
        int getLocationX() const ;
        void setLocation(const int& , const int &);
        void setLocation(const COORD &);
        int getLocationY() const ;
        int getDirection() const;
        void setMaze(const class Maze& );
        COORD getTarget() const ;
        int getSleepTime() const ;
        void setSleepTime(const int &);
        int getSteps() const ;
        int getColisions() const;
        int getColorCode() const ;
        COORD getPreLocation() const;
        void restart();
        void start();
        bool getState() const ;


    protected:

    private:

        int color_code;
        int direction;
        int sleep_time;
        COORD location;
        COORD pre_location;
        COORD target;
        class Maze maze;
        bool active;
        bool **colision_track;
        int steps;
        int colisions;
        bool checkColision(const COORD &);
};

#endif // IROBOT_H
