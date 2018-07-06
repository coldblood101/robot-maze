#include "Maze.h"
using std::endl;
using std::ofstream;
using std::ifstream;

Maze::Maze()
{
    //ctor
}

Maze::Maze(std::string file_link )
{
    ifstream my_file;
    my_file.open(file_link.c_str());

    my_file>>this->isPrimGenerator;
    my_file>>this->width;
    my_file>>this->height;
    this->setStart(1,1);
    this->setFinish(height-2,width-2);

    grid = (int**)malloc(height*sizeof(int*));
    for(int i=0;i<height;i++)
        grid[i]=(int*)malloc(width*sizeof(int));

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            my_file>>grid[i][j];
}

Maze::Maze(const int &height, const int &width)
{
    isPrimGenerator = true;
    this->width = width;
    if(this->width<1)
        this->width=1;
    if(this->width>41)
        this->width=41;
    this->height = height;
    if(this->height<1)
        this->height =1;
    if(this->height>41)
        this->height=41;
    //Initialize the grid
    grid = (int**)malloc(height*sizeof(int*));
    for(int i=0;i<height;i++)
        grid[i]=(int*)malloc(width*sizeof(int));

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            grid[i][j]=WALL;

}

Maze::~Maze()
{
    //dtor
    for(int i=0;i<height;i++)
        delete [] grid[i];
    delete [] grid;

}

void Maze::saveToFile()
{
    /*file format
    width
    height
    maze information*/

    ofstream my_file;
    my_file.open("Maze.txt");
    my_file<< this->isPrimGenerator<<endl;
    my_file<<this->width<<endl;
    my_file<<this->height<<endl;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            my_file<<grid[i][j]<<" ";
        }
        my_file<<endl;
    }
    my_file.close();
    return ;
}

int Maze::getWidth () const
{
    return this->width;
}

int Maze::getHeight () const
{
    return this->height;
}

int Maze::getGridValue (int y_pos,int x_pos)
{
    return this->grid[y_pos][x_pos];
}

void Maze::setGridValue (int y_pos,int x_pos ,const int& value )
{
    this->grid[y_pos][x_pos]=value;
    return;
}

int Maze::getGridValue (COORD xy_pos)
{
    return this->grid[xy_pos.Y][xy_pos.X];
}

void Maze::setGridType (COORD xy_pos, const int& value)
{
    this->grid[xy_pos.Y][xy_pos.X]=value;
    return ;
}

COORD Maze::getStart() const
{
    return start_point;
}

void Maze::setStart(const int& y_pos,const int& x_pos)
{
    this->start_point.X=x_pos;
    this->start_point.Y = y_pos;
    return;
}

COORD Maze::getFinish() const
{
    return this->finish_point;
}

void Maze::setFinish(const int & y_pos, const int& x_pos)
{
    this->finish_point.X=x_pos;
    this->finish_point.Y=y_pos;
    return;
}

Maze& Maze::operator =(const Maze& new_maze)
{
    this->width = new_maze.getWidth();
    this->height = new_maze.getHeight();
    this->start_point = new_maze.getStart();
    this->finish_point = new_maze.getFinish();
    this->isPrimGenerator = new_maze.isPrimGenerator;
    int** input_grid = new_maze.getGrid();

    this->grid = (int**)malloc(this->height*sizeof(int*));
    for(int i=0;i<this->height;i++)
        this->grid[i]=(int*)malloc(this->width*sizeof(int));

    for(int i=0;i<this->height;i++)
        for(int j=0;j<this->width;j++)
            this->grid[i][j]=input_grid[i][j];
    return *this;
}

int** Maze::getGrid() const
{
    return this->grid;
}

bool Maze::getGenerator() const
{
    return this->isPrimGenerator;
}

void Maze::setGenerator(bool is_prim)
{
    this->isPrimGenerator = is_prim;
}
