#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H
#pragma once
#include"IRobot.h"

class RobotController
{
    public:
        RobotController();
        virtual ~RobotController();
        void simpleController(class IRobot&  );
        void studentController(class IRobot&  );
        bool getController() const ;
        void setController(const bool& );
    protected:

    private:
        bool is_simple_controller;
};

#endif // ROBOTCONTROLLER_H
