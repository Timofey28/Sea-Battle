#pragma once
#include "arrangement_validity.h"
#include "click_coordinates.h"
#include "draw.h"
extern DWORD prev_mode;

class Field
{
    std::vector<std::vector<bool>> location = std::vector<std::vector<bool>>(10, std::vector<bool>(10));
    std::vector<std::vector<bool>> shooting = std::vector<std::vector<bool>>(10, std::vector<bool>(10));
    std::vector<std::vector<bool>> occupied = std::vector<std::vector<bool>>(10, std::vector<bool>(10));
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

    Field();
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
