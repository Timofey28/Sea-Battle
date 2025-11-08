#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <random>
#include <ctime>
#include <thread>
#include <conio.h>
#include <windows.h>

#include "draw.h"
#include "game_process.h"
#include "click_coordinates.h"

int nConsoleWidth = -1, nConsoleHeight = -1;
int positionFromTop = -1;
DWORD prev_mode;

void configureConsole();
void getConsoleWH();


int main()
{
    setlocale(0, "");
    configureConsole();

    GameProcess gameProcess;
    ClickCoordinates clickCoordinates;

    while(1) {
        draw::GameModeSelection();
        bool singleGame = clickCoordinates.Get_GameModeSelection(draw::wallLeftEdgeCoordX);
        gameProcess.ArrangeShips(singleGame);
        if(gameProcess.GoBack()) {
            SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ::prev_mode);
            continue;
        }
        if(singleGame) gameProcess.Play_1player();
        else           gameProcess.Play_2players();
    }

    return 0;
}

void configureConsole()
{
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &::prev_mode);

    int monitorHeight = GetSystemMetrics(SM_CYSCREEN);  // высота монитора компьютера в пикселях
    int suitableFontSize = monitorHeight / 40;

    // установка размера шрифта в консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
    fontInfo.dwFontSize.Y = suitableFontSize;
    SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);

    // установка размера буфера экрана равным текущему размеру окна
    getConsoleWH();
    COORD newScreenBufferSize;
    newScreenBufferSize.X = ::nConsoleWidth;
    newScreenBufferSize.Y = ::nConsoleHeight;
    if(!SetConsoleScreenBufferSize(hConsole, newScreenBufferSize)) {
        cout << "\nError in " << to_string(__LINE__) << " line: " << GetLastError();
        exit(-1);
    }

    // открытие консоли во весь экран
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    getConsoleWH();
    ::positionFromTop = ::nConsoleHeight / 2 - 14;  // высота игрового поля == 30

    // сделать курсор невидимым
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hConsole, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &structCursorInfo);
}

void getConsoleWH()
{
    HANDLE hWndConsole;
    if(hWndConsole = GetStdHandle(-12))
    {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if(GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
        {
            ::nConsoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
            ::nConsoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        }
        else exit(-1);
    }
    else exit(-1);
}
