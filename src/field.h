#pragma once

#include <vector>
#include <random>
#include <algorithm>

#include "arrangement_validity.h"
#include "click_coordinates.h"
#include "draw.h"

extern DWORD prev_mode;
extern std::mt19937 mersenne;


class Field
{
    std::vector<std::vector<bool>> location, shooting, occupied;
    int indentX_LeftField, indentY_LeftField;

    void MarkEmptyCellAsShot(int fieldX, int fieldY);
    void CircleDeadShip(int x, int y, std::vector<char> sides);
    void RemoveAllShipsFromField();
    bool FieldIsEmpty();

public:
    int zeroCoordPointerX, zeroCoordPointerY;
    int deadCounter;
    bool aboutToFinishAShip;
    ClickCoordinates clickCoordinates;

    Field() :
        location(10, std::vector<bool>(10, false)),
        shooting(10, std::vector<bool>(10, false)),
        occupied(10, std::vector<bool>(10, false)),
        deadCounter(0),
        zeroCoordPointerX(0),
        zeroCoordPointerY(0),
        aboutToFinishAShip(false)
    {}
    void ArrangeShipsRandomly();
    bool ArrangeShipsForPerson(bool singleGame, bool firstPlayer, bool secondPlayer);
    bool ShootAt(int x, int y);
    bool WasShotAt(int x, int y) { return shooting[x][y]; }
    void DrawShips();
    void ClearFieldFromShips();
    void RevealSurvivorsAfterVictory();
    void ReturnPreviousConsoleMode() { SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ::prev_mode); }
    void SetLeftFieldIndents(int indentX, int indentY) { indentX_LeftField = indentX; indentY_LeftField = indentY; }
};
