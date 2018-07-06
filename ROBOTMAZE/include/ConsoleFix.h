#ifndef CONSOLEFIX_H
#define CONSOLEFIX_H
#pragma once

//#define _WIN32_WINNT 0x0601// define the window edition


#include<windows.h>
#include<cwchar>
#include<iostream>
#include"ColorCode.h"

#define JUMP_STEP 2
#define BLOCK 219
#define GRID_BLOCK 176
const int BACK_GROUND = BLACK;


class ConsoleFix
{
    public:
        ConsoleFix();
        virtual ~ConsoleFix();
        //change a color of a charac                        characColor+backgroundColor
        void displayCharac(int ,int  ,int ,COORD );
        //Write string to console
        void displayString(std::string ,COORD pos );
        //change the cursor pos
        void gotoXY(const short & ,const short &);
        //change the size of the console
        void setConsoleSize(const int & ,const int &);
        // Delete a range of console or a pixel
        void deleteConsoleRange(const COORD& , const COORD&);
        // delete a pixel
        void deleteConsoleRange(const COORD&);
    protected:
        HANDLE hConsoleOutput;

    private:
};

#endif // CONSOLEFIX_H
