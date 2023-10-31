#pragma once
extern int positionFromTop, nConsoleWidth, nConsoleHeight;

class GameProcess
{
    std::unique_ptr<Field> fieldMe, fieldEnemy;
    int indentX_1stField, indentX_2ndField;
public:
    GameProcess();
    void ArrangeShips();
    void Play();
};
