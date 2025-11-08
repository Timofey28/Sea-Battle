#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <random>
#include <conio.h>
#include <thread>

#include "field.h"

extern int positionFromTop, nConsoleWidth, nConsoleHeight;
extern std::mt19937 mersenne;


class GameProcess
{
    std::unique_ptr<Field> fieldLeft, fieldRight;
    int indentX_1stField, indentX_2ndField;
    bool goBack;
public:
    ClickCoordinates clickCoordinates;

    GameProcess();
    void ArrangeShips(bool singleGame);
    bool GoBack();
    void Play_1player();
    void Play_2players();
};
