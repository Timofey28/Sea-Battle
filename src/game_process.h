#pragma once
extern int positionFromTop, nConsoleWidth, nConsoleHeight;

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
