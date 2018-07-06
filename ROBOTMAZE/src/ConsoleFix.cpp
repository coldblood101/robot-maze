
#include "ConsoleFix.h"

//reDeclaration of the structure and window funtion

typedef struct _CONSOLE_SCREEN_BUFFER_INFOEX {
  ULONG      cbSize;
  COORD      dwSize;
  COORD      dwCursorPosition;
  WORD       wAttributes;
  SMALL_RECT srWindow;
  COORD      dwMaximumWindowSize;
  WORD       wPopupAttributes;
  BOOL       bFullscreenSupported;
  COLORREF   ColorTable[16];
} CONSOLE_SCREEN_BUFFER_INFOEX, *PCONSOLE_SCREEN_BUFFER_INFOEX;


//the function declaration begins
#ifdef __cplusplus
//tell the compiler to find the funtion define
extern "C" {
#endif
    BOOL WINAPI GetConsoleScreenBufferInfoEx(HANDLE hConsoleOutput,PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx);
    BOOL WINAPI WriteConsoleOutputCharacter(HANDLE  hConsoleOutput,LPCTSTR lpCharacter,DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfCharsWritten);
#ifdef __cplusplus
}
#endif


ConsoleFix::ConsoleFix()
{
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    hConsoleOutput  = GetStdHandle(STD_OUTPUT_HANDLE);


}

ConsoleFix::~ConsoleFix()
{
    //dtor
}

void ConsoleFix::gotoXY(const short &xPos ,const short &yPos)
{
    COORD tmpPos;
    tmpPos.X=xPos;
    tmpPos.Y=yPos;
    //moving cursor function
    SetConsoleCursorPosition(hConsoleOutput,tmpPos);
    return;
}

void ConsoleFix::setConsoleSize(const int & width,const int &height)
{
    COORD newSize;
    newSize.X = width;
    newSize.Y = height;
    //get the largest size can fix of window
    COORD maxSize = GetLargestConsoleWindowSize(hConsoleOutput);
    newSize.X = (newSize.X > maxSize.X ? maxSize.X : newSize.X);
    //adjust the max size of the console
    newSize.Y = (newSize.Y > maxSize.Y ? maxSize.Y : newSize.Y);
    SMALL_RECT winRect={(short)0,(short)0,(short)newSize.X-1,(short)newSize.Y-1};
    //chanfe the size of the window
    SetConsoleWindowInfo(hConsoleOutput,TRUE,&winRect);
    //change the size of the console
    SetConsoleScreenBufferSize(hConsoleOutput,newSize);
}

void ConsoleFix::displayCharac(int characNum,int colorCode,int JumpStep,COORD pos)
{

    DWORD NumberOfAttrsWritten;
    //set tthe color
    FillConsoleOutputAttribute(hConsoleOutput,(unsigned char )colorCode,JumpStep,pos,&NumberOfAttrsWritten);
    FillConsoleOutputCharacter(hConsoleOutput,(unsigned char )characNum,JumpStep,pos,&NumberOfAttrsWritten);
    return ;
}

void ConsoleFix::displayString(std::string inpString,COORD pos)
{
    DWORD lpNumberOfCharsWritten;
    int Length= inpString.length();
    const char * basicString= inpString.c_str();
    WriteConsoleOutputCharacter(hConsoleOutput,basicString,Length,pos,&lpNumberOfCharsWritten);
    return ;
}

void ConsoleFix::deleteConsoleRange(const COORD& upper_left, const COORD & lower_right)
{
    int height = ((lower_right.Y-upper_left.Y) > 0 ? (lower_right.Y-upper_left.Y):(-1)*(lower_right.Y-upper_left.Y))+1;
    int width  = ((lower_right.X-upper_left.X) > 0 ? (lower_right.X-upper_left.X):(-1)*(lower_right.X-upper_left.X))+1;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
                COORD tmp_pos = upper_left;
                tmp_pos.X +=j*JUMP_STEP;
                tmp_pos.Y +=i;
                displayCharac(BLOCK,BACK_GROUND,JUMP_STEP,tmp_pos);
        }
    }
    return ;
}

void ConsoleFix::deleteConsoleRange(const COORD& pixel_pos)
{
    displayCharac(BLOCK,BACK_GROUND,JUMP_STEP,pixel_pos);
    return ;
}

