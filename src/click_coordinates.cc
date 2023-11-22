#include "click_coordinates.h"

void ClickCoordinates::Get_AnyClick()
{
    EnableMouseInput();
    while(1) {
        ReadConsoleInput(Handle, &InputRecord, 1, &Events);
        DWORD buttonPressed = InputRecord.Event.MouseEvent.dwButtonState;
        if(buttonPressed == MOUSE_WHEELED ||
           buttonPressed == FROM_LEFT_1ST_BUTTON_PRESSED ||
           buttonPressed == RIGHTMOST_BUTTON_PRESSED) return;
    }
}

bool ClickCoordinates::Get_GameModeSelection(int wallLeftEdgeCoordX)
{
    EnableMouseInput();
    short x;
    while(1) {
        ReadConsoleInput(Handle, &InputRecord, 1, &Events);
        DWORD buttonPressed = InputRecord.Event.MouseEvent.dwButtonState;
        if(buttonPressed == MOUSE_WHEELED ||
           buttonPressed == FROM_LEFT_1ST_BUTTON_PRESSED ||
           buttonPressed == RIGHTMOST_BUTTON_PRESSED)
        {
            x = InputRecord.Event.MouseEvent.dwMousePosition.X;
            if(x < wallLeftEdgeCoordX)          return 1;  // 1 player mode
            else if(x > wallLeftEdgeCoordX + 1) return 0;  // 2 players mode
            else continue;
        }
    }
}

ClickInfo ClickCoordinates::Get_ShipsArrangement(int indentX, int indentY)
{
    namespace dsa = draw::ships_arrangement;
    EnableMouseInput();
    short x, y;
    ClickInfo clickInfo;
    while(1) {
        ReadConsoleInput(Handle, &InputRecord, 1, &Events);
        DWORD buttonPressed = InputRecord.Event.MouseEvent.dwButtonState;
        if(buttonPressed == MOUSE_WHEELED ||
           buttonPressed == FROM_LEFT_1ST_BUTTON_PRESSED ||
           buttonPressed == RIGHTMOST_BUTTON_PRESSED)
        {
            x = InputRecord.Event.MouseEvent.dwMousePosition.X - (indentX - 2);
            y = InputRecord.Event.MouseEvent.dwMousePosition.Y - (indentY - 2);
            if(x > 0 && x < 61 && (x % 6 != 0) && y > 0 && y <= 30) {
                if(buttonPressed == MOUSE_WHEELED) continue;
                clickInfo.x = x / 6;
                clickInfo.y = (y - 1) / 3;
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                }
                clickInfo.outside_field = 0;
                return clickInfo;
            }
            x += indentX - 2;
            y += indentY - 2;
            if(x >= dsa::indentX_rightColumn + 2 && x < dsa::indentX_rightColumn + dsa::width_rightColumn - 2 &&
               y > dsa::indentY_wordHelp && y < dsa::indentY_upper)
            {
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                    case MOUSE_WHEELED:                clickInfo.button = 'w'; break;
                }
                clickInfo.outside_field = 1;
                clickInfo.buttonHelp_isPressed = 1;
                clickInfo.buttonBack_isPressed = 0;
                clickInfo.buttonExit_isPressed = 0;
                clickInfo.buttonAuto_isPressed = 0;
                clickInfo.buttonClear_isPressed = 0;
                clickInfo.buttonDone_isPressed = 0;
                return clickInfo;
            }
            if(x >= dsa::indentX_leftColumn + 2 && x < dsa::indentX_leftColumn + dsa::width_leftColumn - 2 &&
               y > dsa::indentY_middle && y < dsa::indentY_lower)
            {
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                    case MOUSE_WHEELED:                clickInfo.button = 'w'; break;
                }
                clickInfo.outside_field = 1;
                clickInfo.buttonHelp_isPressed = 0;
                clickInfo.buttonBack_isPressed = 1;
                clickInfo.buttonExit_isPressed = 0;
                clickInfo.buttonAuto_isPressed = 0;
                clickInfo.buttonClear_isPressed = 0;
                clickInfo.buttonDone_isPressed = 0;
                return clickInfo;
            }
            if(x >= dsa::indentX_leftColumn + 2 && x < dsa::indentX_leftColumn + dsa::width_leftColumn - 2 &&
               y > dsa::indentY_lower && y < dsa::indentY_lower + dsa::heightOfCells - 1)
            {
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                    case MOUSE_WHEELED:                clickInfo.button = 'w'; break;
                }
                clickInfo.outside_field = 1;
                clickInfo.buttonHelp_isPressed = 0;
                clickInfo.buttonBack_isPressed = 0;
                clickInfo.buttonExit_isPressed = 1;
                clickInfo.buttonAuto_isPressed = 0;
                clickInfo.buttonClear_isPressed = 0;
                clickInfo.buttonDone_isPressed = 0;
                return clickInfo;
            }
            if(x >= dsa::indentX_rightColumn + 2 && x < dsa::indentX_rightColumn + dsa::width_rightColumn - 2 &&
               y > dsa::indentY_upper && y < dsa::indentY_upper + dsa::heightOfCells - 1)
            {
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                    case MOUSE_WHEELED:                clickInfo.button = 'w'; break;
                }
                clickInfo.outside_field = 1;
                clickInfo.buttonHelp_isPressed = 0;
                clickInfo.buttonBack_isPressed = 0;
                clickInfo.buttonExit_isPressed = 0;
                clickInfo.buttonAuto_isPressed = 1;
                clickInfo.buttonClear_isPressed = 0;
                clickInfo.buttonDone_isPressed = 0;
                return clickInfo;
            }
            if(x >= dsa::indentX_rightColumn + 2 && x < dsa::indentX_rightColumn + dsa::width_rightColumn - 2 &&
               y > dsa::indentY_middle && y < dsa::indentY_middle + dsa::heightOfCells - 1)
            {
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                    case MOUSE_WHEELED:                clickInfo.button = 'w'; break;
                }
                clickInfo.outside_field = 1;
                clickInfo.buttonHelp_isPressed = 0;
                clickInfo.buttonBack_isPressed = 0;
                clickInfo.buttonExit_isPressed = 0;
                clickInfo.buttonAuto_isPressed = 0;
                clickInfo.buttonClear_isPressed = 1;
                clickInfo.buttonDone_isPressed = 0;
                return clickInfo;
            }
            if(x >= dsa::indentX_rightColumn + 2 && x < dsa::indentX_rightColumn + dsa::width_rightColumn - 2 &&
               y > dsa::indentY_lower && y < dsa::indentY_lower + dsa::heightOfCells - 1)
            {
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                    case MOUSE_WHEELED:                clickInfo.button = 'w'; break;
                }
                clickInfo.outside_field = 1;
                clickInfo.buttonHelp_isPressed = 0;
                clickInfo.buttonBack_isPressed = 0;
                clickInfo.buttonExit_isPressed = 0;
                clickInfo.buttonAuto_isPressed = 0;
                clickInfo.buttonClear_isPressed = 0;
                clickInfo.buttonDone_isPressed = 1;
                return clickInfo;
            }
        }
    }
}

ClickInfo ClickCoordinates::Get_PlayTime(int indentX, int indentY)
{
    EnableMouseInput();
    FlushConsoleInputBuffer(Handle);
    short x, y;
    ClickInfo clickInfo;
    while(1) {
        ReadConsoleInput(Handle, &InputRecord, 1, &Events);
        DWORD buttonPressed = InputRecord.Event.MouseEvent.dwButtonState;
        if(buttonPressed == MOUSE_WHEELED ||
           buttonPressed == FROM_LEFT_1ST_BUTTON_PRESSED ||
           buttonPressed == RIGHTMOST_BUTTON_PRESSED)
        {
            x = InputRecord.Event.MouseEvent.dwMousePosition.X - (indentX - 2);
            y = InputRecord.Event.MouseEvent.dwMousePosition.Y - (indentY - 2);
            if(x > 0 && x < 61 && (x % 6 != 0) && y > 0 && y <= 30) {
                clickInfo.x = x / 6;
                clickInfo.y = (y - 1) / 3;
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                    case MOUSE_WHEELED:                clickInfo.button = 'w'; break;
                }
                return clickInfo;
            }
        }
    }
}

void ClickCoordinates::EnableMouseInput()
{
    // Запрещаем выдеение консоли
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (::prev_mode & ~ENABLE_QUICK_EDIT_MODE));
    SetConsoleMode(Handle, ENABLE_MOUSE_INPUT);  // разрешаем обработку мыши
}
