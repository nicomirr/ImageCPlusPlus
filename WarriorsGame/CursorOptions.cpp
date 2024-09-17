#include "CursorOptions.h"
#include<Windows.h>

CursorOptions::CursorOptions() {}

void CursorOptions::SetCursorPosition(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos;

    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(hConsole, pos);
}
