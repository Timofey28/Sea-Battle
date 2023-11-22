#pragma once
extern DWORD prev_mode;

struct ClickInfo;

class ClickCoordinates
{
    HANDLE Handle;
    INPUT_RECORD InputRecord;  // используется для возвращения информации о входных сообщениях в консольном входном буфере
    DWORD Events;  // unsigned long

    void EnableMouseInput();
public:
    ClickCoordinates() { Handle = GetStdHandle(STD_INPUT_HANDLE); }
    bool Get_GameModeSelection(int wallLeftEdgeCoordX);
    void Get_AnyClick();
    ClickInfo Get_ShipsArrangement(int indentX, int indentY);
    ClickInfo Get_PlayTime(int indentX, int indentY);
};

struct ClickInfo
{
    short x, y;
    char button;
    // 'l' - ЛКМ
    // 'r' - ПКМ
    // 'w' - колесико (wheel)
    bool outside_field;
    bool buttonHelp_isPressed,
         buttonBack_isPressed,
         buttonExit_isPressed,
         buttonAuto_isPressed,
         buttonClear_isPressed,
         buttonDone_isPressed;
};
