#ifndef MAZE_H
#define MAZE_H
#pragma once

#include<windows.h>
#include<fstream>
#include<iostream>
#include<malloc.h>

#define MAX 20
#define WALL 2
#define PATH 1
using std::string;

class Maze
{
    public:
        Maze();
        Maze(std::string );
        Maze(const int &, const int &);
        virtual ~Maze();

        int getWidth () const ;
        int getHeight () const ;
        int getGridValue (int ,int );
        int getGridValue (COORD );
        void saveToFile();
        void setGridValue (int ,int ,const int& );
        void setGridType (COORD , const int& );
        void setStart(const int& , const int&);
        void setFinish(const int& , const int&);
        COORD getStart() const;
        COORD getFinish() const;
        int** getGrid() const ;
        bool getGenerator() const ;
        void setGenerator(bool )  ;
        Maze& operator =(const Maze&);
    protected:

    private:
        int **grid;
        int width;
        int height;
        COORD start_point;
        COORD finish_point;
        bool isPrimGenerator;

};

#endif // MAZE_H
