#pragma once


class Field
{
    std::vector<std::vector<bool>> location = std::vector<std::vector<bool>>(10, std::vector<bool>(10));
    std::vector<std::vector<bool>> shooting = std::vector<std::vector<bool>>(10, std::vector<bool>(10));
    std::vector<std::vector<bool>> occupied = std::vector<std::vector<bool>>(10, std::vector<bool>(10));

    void arrangeShipsRandomly();
    void markEmptyCellAsShot(int fieldX, int fieldY);
public:
    int zeroCoordPointerX, zeroCoordPointerY;
    int deadCounter;
    bool aboutToFinishAShip;

    Field();
//    bool hasShipAt(int x, int y) {return location[x][y];}
    bool wasShotAt(int x, int y) {return shooting[x][y];}
    bool shootAt(int x, int y);
    void shipsArrangement_manual();
    void shipsArrangement_automatic(int indentX, int indentY, int consoleWidth, int consoleHeight);
    void shipsArrangement_forComputer() {arrangeShipsRandomly();}
    void drawShips(int indentX, int indentY);
    void revealSurvivorsAfterLoss();
};
