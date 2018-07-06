#include "RecursiveGenerator.h"

RecursiveGenerator::RecursiveGenerator()
{
    //ctor
    maze_width=maze_height=15;
}

RecursiveGenerator::~RecursiveGenerator()
{
    //dtor
}

void RecursiveGenerator::generateMaze(class Maze& input_maze)
{
    COORD rand_pos;
    int total_cells;
    int total_visiteds;
    maze_width = input_maze.getWidth();
    maze_height= input_maze.getHeight();
    if(maze_width<1||maze_height<1)
        return;
    int width = 2 * this->maze_width + 1;
	int height = 2 * this->maze_height + 1;

    Maze local_maze = Maze(height,width);
    local_maze.setStart(1,1);
    local_maze.setFinish(height-2,width-2);

    Cell grid[height][width];

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width ; j++)
        {
            grid[i][j]=Cell();
            if(i==1)
                grid[i][j].top_wall = false;
            if(i==height-2)
                grid[i][j].bottom_wall = false;
            if(j==1)
                grid[i][j].left_wall=false;
            if(j==width-2)
                grid[i][j].right_wall=false;
        }
    }

    rand_pos.X = ((2*rand())+1)%(width-1);
    rand_pos.Y = ((2*rand())+1)%(height-1);

    grid[rand_pos.Y][rand_pos.X].visited=true;
    grid[rand_pos.Y][rand_pos.X].display_num=PATH;
    setGridValue(local_maze,rand_pos.Y,rand_pos.X,PATH);
    total_cells=(height/2)*(width/2);
    total_visiteds=1;
    while(total_visiteds<total_cells)
    {
        COORD tmp_coord;
        if((!grid[rand_pos.Y-2][rand_pos.X].visited && grid[rand_pos.Y-2][rand_pos.X].bottom_wall && grid[rand_pos.Y][rand_pos.X].top_wall)   ||
           (!grid[rand_pos.Y+2][rand_pos.X].visited && grid[rand_pos.Y+2][rand_pos.X].top_wall    && grid[rand_pos.Y][rand_pos.X].bottom_wall)||
           (!grid[rand_pos.Y][rand_pos.X-2].visited && grid[rand_pos.Y][rand_pos.X-2].right_wall  && grid[rand_pos.Y][rand_pos.X].left_wall)  ||
           (!grid[rand_pos.Y][rand_pos.X+2].visited && grid[rand_pos.Y][rand_pos.X+2].left_wall   &&grid[rand_pos.Y][rand_pos.X].right_wall))
        {
            int rand_dir  = rand()%4;

            if(rand_dir==0 && rand_pos.Y-2>0)//go_up
            {
                if(!grid[rand_pos.Y-1][rand_pos.X].visited && !grid[rand_pos.Y-2][rand_pos.X].visited)
                {
                    setGridValue(local_maze,rand_pos.Y-2,rand_pos.X,PATH);
                    setGridValue(local_maze,rand_pos.Y-1,rand_pos.X,PATH);
                    grid[rand_pos.Y-1][rand_pos.X].visited=true;
                    grid[rand_pos.Y-2][rand_pos.X].visited=true;
                    grid[rand_pos.Y][rand_pos.X].top_wall=false;
                    grid[rand_pos.Y-2][rand_pos.X].bottom_wall=false;
                    grid[rand_pos.Y-1][rand_pos.X].display_num=PATH;
                    grid[rand_pos.Y-2][rand_pos.X].display_num=PATH;

                    tmp_coord.X=rand_pos.X;
                    tmp_coord.Y=rand_pos.Y;

                    back_track_coord.push(tmp_coord);

                    rand_pos.Y-=2;
                    total_visiteds+=1;
                }
                else
                    continue;
            }
            else if(rand_dir==1 && rand_pos.Y+2<height-1)//go_down
            {
                if(!grid[rand_pos.Y+1][rand_pos.X].visited && !grid[rand_pos.Y+2][rand_pos.X].visited)
                {
                    setGridValue(local_maze,rand_pos.Y+2,rand_pos.X,PATH);
                    setGridValue(local_maze,rand_pos.Y+1,rand_pos.X,PATH);
                    grid[rand_pos.Y+1][rand_pos.X].visited=true;
                    grid[rand_pos.Y+2][rand_pos.X].visited=true;
                    grid[rand_pos.Y][rand_pos.X].bottom_wall=false;
                    grid[rand_pos.Y+2][rand_pos.X].top_wall=false;
                    grid[rand_pos.Y+1][rand_pos.X].display_num=PATH;
                    grid[rand_pos.Y+2][rand_pos.X].display_num=PATH;

                    tmp_coord.X=rand_pos.X;
                    tmp_coord.Y=rand_pos.Y;

                    back_track_coord.push(tmp_coord);

                    rand_pos.Y+=2;
                    total_visiteds+=1;
                }
                else
                    continue;
            }
            else if(rand_dir==2 && rand_pos.X-2>0)//go_left
            {
                if(!grid[rand_pos.Y][rand_pos.X-1].visited && !grid[rand_pos.Y][rand_pos.X-2].visited)
                {
                    setGridValue(local_maze,rand_pos.Y,rand_pos.X-2,PATH);
                    setGridValue(local_maze,rand_pos.Y,rand_pos.X-1,PATH);
                    grid[rand_pos.Y][rand_pos.X-1].visited=true;
                    grid[rand_pos.Y][rand_pos.X-2].visited=true;
                    grid[rand_pos.Y][rand_pos.X].left_wall=false;
                    grid[rand_pos.Y][rand_pos.X-2].right_wall=false;
                    grid[rand_pos.Y][rand_pos.X-1].display_num=PATH;
                    grid[rand_pos.Y][rand_pos.X-2].display_num=PATH;

                    tmp_coord.X=rand_pos.X;
                    tmp_coord.Y=rand_pos.Y;

                    back_track_coord.push(tmp_coord);

                    rand_pos.X-=2;
                    total_visiteds+=1;
                }
                else
                    continue;
            }
            if(rand_dir==3 && rand_pos.X+2<width-1)//go_right
            {
                if(!grid[rand_pos.Y][rand_pos.X+1].visited && !grid[rand_pos.Y][rand_pos.X+2].visited)
                {
                    setGridValue(local_maze,rand_pos.Y,rand_pos.X+2,PATH);
                    setGridValue(local_maze,rand_pos.Y,rand_pos.X+1,PATH);
                    grid[rand_pos.Y][rand_pos.X+1].visited=true;
                    grid[rand_pos.Y][rand_pos.X+2].visited=true;
                    grid[rand_pos.Y][rand_pos.X].right_wall=false;
                    grid[rand_pos.Y][rand_pos.X+2].left_wall=false;
                    grid[rand_pos.Y][rand_pos.X+1].display_num=PATH;
                    grid[rand_pos.Y][rand_pos.X+2].display_num=PATH;

                    tmp_coord.X=rand_pos.X;
                    tmp_coord.Y=rand_pos.Y;

                    back_track_coord.push(tmp_coord);

                    rand_pos.X+=2;
                    total_visiteds+=1;
                }
                else
                    continue;
            }

        }
        else
        {
            tmp_coord = back_track_coord.top();
            back_track_coord.pop();
            rand_pos.X=tmp_coord.X;
            rand_pos.Y=tmp_coord.Y;
        }
    }
    input_maze=local_maze;
}

void RecursiveGenerator::setGridValue(Maze& local_maze,const int & y_pos ,const int & x_pos,int value)
{
    local_maze.setGridValue(y_pos,x_pos,value);
    return;
}
