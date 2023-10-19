#pragma once
#include "arrangement_validity.h"


class Field
{
    std::vector<std::vector<bool>> location = std::vector<std::vector<bool>>(10, std::vector<bool>(10));
    std::vector<std::vector<bool>> shooting = std::vector<std::vector<bool>>(10, std::vector<bool>(10));
    std::vector<std::vector<bool>> occupied = std::vector<std::vector<bool>>(10, std::vector<bool>(10));

    void arrangeShipsRandomly();
    void markEmptyCellAsShot(int fieldX, int fieldY);
    void circleDeadShip(int x, int y, std::vector<char> sides);
public:
    int zeroCoordPointerX, zeroCoordPointerY;
    int deadCounter;
    bool aboutToFinishAShip;

    Field();
    bool wasShotAt(int x, int y) { return shooting[x][y]; }
    bool shootAt(int x, int y);
    void shipsArrangement_manual(const int indent, const int positionFromTop, const int consoleWidth);
    void shipsArrangement_automatic(int indentX, int indentY, int consoleWidth, int consoleHeight);
    void shipsArrangement_forComputer() {arrangeShipsRandomly();}
    void drawShips(int indentX, int indentY);
    void revealSurvivorsAfterLoss();
};

struct ClickInfo
{
    short x, y;
    char button;
    // 'l' - ЛКМ
    // 'r' - ПКМ
    // 'w' - колесико (wheel)
    bool outside_field;
};
