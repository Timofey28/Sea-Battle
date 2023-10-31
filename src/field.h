#pragma once
#include "arrangement_validity.h"
#include "draw.h"

struct ClickInfo;

class Field
{
    std::vector<std::vector<bool>> location = std::vector<std::vector<bool>>(10, std::vector<bool>(10));
    std::vector<std::vector<bool>> shooting = std::vector<std::vector<bool>>(10, std::vector<bool>(10));
    std::vector<std::vector<bool>> occupied = std::vector<std::vector<bool>>(10, std::vector<bool>(10));
    DWORD prev_mode;

    ClickInfo GetClickCoords_ShipsArrangement();
    void MarkEmptyCellAsShot(int fieldX, int fieldY);
    void CircleDeadShip(int x, int y, std::vector<char> sides);
    void RemoveAllShipsFromField();
    bool FieldIsEmpty();
public:
    int zeroCoordPointerX, zeroCoordPointerY;
    int deadCounter;
    bool aboutToFinishAShip;

    Field();
    void ArrangeShipsRandomly();
    void ArrangeShipsForPerson();
    ClickInfo GetClickCoords_PlayTime();
    bool ShootAt(int x, int y);
    bool WasShotAt(int x, int y) { return shooting[x][y]; }
    void DrawShips();
    void RevealSurvivorsAfterLoss();
    void ReturnPreviousConsoleMode() { SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), prev_mode); }
};

struct ClickInfo
{
    short x, y;
    char button;
    // 'l' - ЛКМ
    // 'r' - ПКМ
    // 'w' - колесико (wheel)
    bool outside_field;
    bool buttonExit_isPressed,
         buttonAuto_isPressed,
         buttonClear_isPressed,
         buttonDone_isPressed;
};
