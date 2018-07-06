#include "ScreenDisplay.h"
std::string to_string(int);
ScreenDisplay::ScreenDisplay()
{
    //ctor
    maze_width = maze_height=0;
    console_fix = ConsoleFix();
    console_fix.setConsoleSize(120,43);
}

ScreenDisplay::~ScreenDisplay()
{
    //dtor
}

void ScreenDisplay::drawBorder()
{
    COORD tmp_pos ;
    tmp_pos.X=tmp_pos.Y=0;
    console_fix.displayCharac(GRID_BLOCK,B_GREEN_B_WHITE,JUMP_STEP*((MAX+1)*2+1),tmp_pos);
    tmp_pos.Y=2*(MAX+1);
    console_fix.displayCharac(GRID_BLOCK,B_GREEN_B_WHITE,JUMP_STEP*((MAX+1)*2+1),tmp_pos);
    for(int i=0;i<(MAX+1)*2+1;i++)
    {
        tmp_pos.X=0;
        tmp_pos.Y=i;
        console_fix.displayCharac(GRID_BLOCK,B_GREEN_B_WHITE,JUMP_STEP,tmp_pos);
        tmp_pos.X=(MAX+1)*2*JUMP_STEP;
        tmp_pos.Y=i;
        console_fix.displayCharac(GRID_BLOCK,B_GREEN_B_WHITE,JUMP_STEP,tmp_pos);
    }
    return ;
}

void ScreenDisplay::drawMaze(const class Maze& maze)
{
    maze_height = maze.getHeight();
    maze_width = maze.getWidth();


    int** grid = maze.getGrid();
    start_pos.X=(1+(MAX*2+1-maze_width)/2)*JUMP_STEP;
    start_pos.Y=1+(MAX*2+1-maze_height)/2;
    COORD finish = maze.getFinish();
    for(int i=0;i<maze_height;i++)
    {
        for(int j=0;j<maze_width;j++){
            COORD tmp_pos=start_pos;
            tmp_pos.X+=j*JUMP_STEP;
            tmp_pos.Y+=i;
            if(grid[i][j]==WALL)
                console_fix.displayCharac(BLOCK,B_WHITE_B_WHITE,JUMP_STEP,tmp_pos);
            else
                console_fix.displayCharac(BLOCK,BACK_GROUND,JUMP_STEP,tmp_pos);

        }
    }

    finish.X *=JUMP_STEP;
    finish.X+=start_pos.X;
    finish.Y+=start_pos.Y;
    console_fix.displayCharac(BLOCK,B_CYAN_B_GREEN,JUMP_STEP,finish);

    return;
}

void ScreenDisplay::drawRobot(const class IRobot& robot)
{

    COORD location;
    location.X = robot.getLocation().X;
    location.Y = robot.getLocation().Y;
    location.X*=JUMP_STEP;
    location.X+=start_pos.X;
    location.Y+=start_pos.Y;
    int direction = robot.getDirection();
    int color_code = robot.getColorCode();
    int char_num=ARROW_DOWN;
    switch(direction)
    {
        case NORTH:
            char_num = ARROW_UP;
            break;
        case SOUTH:
            char_num = ARROW_DOWN;
            break;
        case WEST:
            char_num = ARROW_LEFT;
            break;
        case EAST:
            char_num = ARROW_RIGHT;
            break;
        default:
            break;
    }
    COORD pre_pos;
    pre_pos.X = robot.getPreLocation().X;
    pre_pos.Y = robot.getPreLocation().Y;
    if((pre_pos.X!=location.X || pre_pos.Y!=location.Y)&&robot.getState()){
        pre_pos.X*=JUMP_STEP;
        pre_pos.X+=start_pos.X;
        pre_pos.Y+=start_pos.Y;
        console_fix.displayCharac(BLOCK,GRAY,JUMP_STEP,pre_pos);
    }
    console_fix.displayCharac(char_num,color_code,JUMP_STEP,location);

    return ;
}

void ScreenDisplay::displayDistruction()
{
    console_fix.displayString("+--------------------------+",{90, 2});
    console_fix.displayString("|                          |",{90, 3});
    console_fix.displayString("|    ROBOT MAZE            |",{90, 4});
    console_fix.displayString("|            PATH FINDING  |",{90, 5});
    console_fix.displayString("|                          |",{90, 6});
    console_fix.displayString("+--------------------------+",{90, 7});

    console_fix.displayString("^ Increase       |Increase  ",{90, 10});
    console_fix.displayString("|       Height   v     Width",{90, 11});

    console_fix.displayString("+----------------+",          {90,15});
    console_fix.displayString("| Maze Generator |",          {90,16});
    console_fix.displayString("+----------------+---------+",{90,17});
    console_fix.displayString("| 1)Backtrack    | 2) Prim |",{90,18});
    console_fix.displayString("+----------------+---------+",{90,19});


    console_fix.displayString("+-----------------+",         {90,21});
    console_fix.displayString("|  Maze Function  |",         {90,22});
    console_fix.displayString("+--------+--------+--------+",{90,23});
    console_fix.displayString("| 3)Load | 4)Save | 5)New  |",{90,24});
    console_fix.displayString("+--------+--------+--------+",{90,25});


    console_fix.displayString("+----------------+",          {90,27});
    console_fix.displayString("|Robot Controller|",          {90,28});
    console_fix.displayString("+----------------+---------+",{90,29});
    console_fix.displayString("|6)Student define| 7)Simple|",{90,30});
    console_fix.displayString("+----------------+---------+",{90,31});


    console_fix.displayString("+----------------+",          {90,33});
    console_fix.displayString("| Robot Function |",          {90,34});
    console_fix.displayString("+----------------+---------+",{90,35});
    console_fix.displayString("|8)Restart Robot | 9)Start |",{90,36});
    console_fix.displayString("+----------------+---------+",{90,37});

    console_fix.displayString("ESC : Exit Program",{100,41});
    return;
}

void ScreenDisplay::deleteMaze()
{
    COORD start_point={1*JUMP_STEP,1};
    COORD end_point={MAX*2+2,MAX*2+1};
    console_fix.deleteConsoleRange(start_point,end_point);
    return ;
}
void ScreenDisplay::displayChoose(bool is_prim_generator, bool is_simple_controller)
{
    if(is_prim_generator)
        console_fix.displayString("                      ^     ",{90,20});
    else
        console_fix.displayString("         ^                  ",{90,20});
    if(is_simple_controller)
        console_fix.displayString("                      ^     ",{90,32});
    else
        console_fix.displayString("         ^                  ",{90,32});
    return ;

}

std::string to_string(int num)
{
    std::string tmp=" ";
    std::string rt_string="";
    do{
        tmp[0]= num%10+'0';
        num/=10;
        rt_string = tmp+rt_string;
    }while(num!=0);

    return rt_string;
}
