#include "PrimGenerator.h"
using std::vector;
using namespace std;

PrimGenerator::PrimGenerator()
{
	//ctor
	maze_height = maze_width = 15;
}

PrimGenerator::~PrimGenerator()
{
	//dtor
}

void PrimGenerator::generateMaze(class Maze& input_maze)
{
	maze_height=input_maze.getHeight();
	maze_width =input_maze.getWidth();

	if (this->maze_height<1 || this->maze_width<1)
		return ;
	int width = 2 * this->maze_width + 1;
	int height = 2 * this->maze_height + 1;
	Maze local_maze = Maze(height, width);
	local_maze.setStart(1, 1);
	local_maze.setFinish(height - 2, width - 2);

	this->prim_grid = (int**)malloc(height * sizeof(int*));
	for (int i = 0; i<height; i++)
		this->prim_grid[i] = (int*)malloc(width * sizeof(int));

	for (int m = 0; m<height; m++)
	{
		for (int n = 0; n<width; n++)
		{
			this->prim_grid[m][n] = OUTSIDE ;
		}
	}
	COORD rand_pos;
	rand_pos.X = (width - 2);
	rand_pos.Y = (height - 2);
	frontier_list.clear();
	setPrimGridValue(local_maze, rand_pos.Y, rand_pos.X, INSIDE);


	if (rand_pos.Y-2>0 && prim_grid[rand_pos.Y - 2][rand_pos.X] == OUTSIDE )
		setPrimGridValue(local_maze, rand_pos.Y - 2, rand_pos.X, FRONTER);
	if (rand_pos.Y+2<height - 1 && prim_grid[rand_pos.Y + 2][rand_pos.X] == OUTSIDE )
		setPrimGridValue(local_maze, rand_pos.Y + 2, rand_pos.X, FRONTER);
	if (rand_pos.X+2<width - 1 && prim_grid[rand_pos.Y][rand_pos.X + 2] == OUTSIDE )
		setPrimGridValue(local_maze, rand_pos.Y, rand_pos.X + 2, FRONTER);
	if (rand_pos.X - 2>0 && prim_grid[rand_pos.Y][rand_pos.X - 2] == OUTSIDE )
		setPrimGridValue(local_maze, rand_pos.Y, rand_pos.X - 2, FRONTER);
	int array_of_int[4];
	for (int i = 0; i < 4; i++)
		array_of_int[i] = 0;

	while (this->frontier_list.size()>0)
	{
		int rand_index = rand() % (frontier_list.size());
		rand_pos = frontier_list.at(rand_index);
		setPrimGridValue(local_maze, rand_pos.Y, rand_pos.X, INSIDE);

		if (rand_pos.Y - 2>0 && prim_grid[rand_pos.Y - 2][rand_pos.X] == OUTSIDE )
			setPrimGridValue(local_maze, rand_pos.Y - 2, rand_pos.X, FRONTER);
		if (rand_pos.Y + 2<height - 1 && prim_grid[rand_pos.Y + 2][rand_pos.X] == OUTSIDE )
			setPrimGridValue(local_maze, rand_pos.Y + 2, rand_pos.X, FRONTER);
		if (rand_pos.X + 2<width - 1 && prim_grid[rand_pos.Y][rand_pos.X + 2] == OUTSIDE )
			setPrimGridValue(local_maze, rand_pos.Y, rand_pos.X + 2, FRONTER);
		if (rand_pos.X - 2>0 && prim_grid[rand_pos.Y][rand_pos.X - 2] == OUTSIDE )
			setPrimGridValue(local_maze, rand_pos.Y, rand_pos.X - 2, FRONTER);
		int k = 0;

		if (rand_pos.Y - 2>0 && prim_grid[rand_pos.Y - 2][rand_pos.X] == INSIDE)
		{
			array_of_int[k] = NORTH;
			k+=1;
		}
		if (rand_pos.X - 2>0 && prim_grid[rand_pos.Y][rand_pos.X - 2] == INSIDE)
		{
			array_of_int[k] = WEST;
			k+=1;
		}
		if (rand_pos.X+2<width - 1 && prim_grid[rand_pos.Y][rand_pos.X + 2] == INSIDE)
		{
			array_of_int[k] = EAST;
			k+=1;
		}
		if (rand_pos.Y+2<height - 1 && prim_grid[rand_pos.Y + 2][rand_pos.X] == INSIDE)
		{
			array_of_int[k] = SOUTH;
			k+=1;
		}
		int dir_index=0;
		int rand_dir;
		dir_index = rand()%k;
		rand_dir = array_of_int[dir_index];


		switch (rand_dir)
		{
		case NORTH:
			setPrimGridValue(local_maze, rand_pos.Y - 1, rand_pos.X, INSIDE);
			break;
		case SOUTH:
			setPrimGridValue(local_maze, rand_pos.Y + 1, rand_pos.X, INSIDE);
			break;
		case WEST:
			setPrimGridValue(local_maze, rand_pos.Y, rand_pos.X - 1, INSIDE);
			break;
		case EAST:
			setPrimGridValue(local_maze, rand_pos.Y, rand_pos.X + 1, INSIDE);
			break;
		}
		frontier_list.erase(frontier_list.begin() + rand_index);
	}
	input_maze = local_maze;
	return;
}


void PrimGenerator::setPrimGridValue(class Maze& local_maze, int y_pos, int x_pos, int value)
{
	if (value == 1)
	{
		local_maze.setGridValue(y_pos, x_pos, INSIDE);
	}
	if (value == 2)
	{
		COORD tmp_COORD = { x_pos,y_pos };
		this->frontier_list.push_back(tmp_COORD);
	}
	this->prim_grid[y_pos][x_pos] = value;
}
