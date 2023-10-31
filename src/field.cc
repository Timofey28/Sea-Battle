#include "field.h"
using namespace std;
mt19937 mersenne(static_cast<unsigned int>(time(0)));

void setPosition(int x, int y);
void setColor(int color);

Field::Field()
{
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            location[i][j] = false;
            shooting[i][j] = false;
            occupied[i][j] = false;
        }
    }
    deadCounter = 0;
    zeroCoordPointerX = 0;
    zeroCoordPointerY = 0;
    aboutToFinishAShip = false;
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &prev_mode);
}

void Field::ArrangeShipsRandomly()
{
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            location[i][j] = false;
            occupied[i][j] = false;
        }
    }

    vector<int> free(100);
    for(int i = 0; i < 100; ++i) free[i] = i;
    random_shuffle(free.begin(), free.end(), [](int i){return mersenne() % i;});
    int x, y, x1, y1, no = 0;
    char randomSide;
    // ------------4-палубный-----------------
    x = free[no] / 10;
    y = free[no] % 10;
    no++;
    occupied[x][y] = 1;
    vector<char> sides;
    sides.reserve(4);
    if(x > 0) sides.push_back('l');
    if(x < 9) sides.push_back('r');
    if(y > 0) sides.push_back('u');
    if(y < 9) sides.push_back('d');
    x1 = x;
    y1 = y;
    switch(sides[mersenne() % sides.size()]) {
        case 'l': x--;  break;
        case 'r': x1++; break;
        case 'u': y--;  break;
        case 'd': y1++; break;
    }

    for(int i = 0; i < 2; ++i) {
        sides.clear();
        if(x != x1) {
            if(x > 0) sides.push_back('l');
            if(x1 < 9) sides.push_back('r');
        }
        else if(y != y1) {
            if(y > 0) sides.push_back('u');
            if(y1 < 9) sides.push_back('d');
        }
        randomSide = sides[mersenne() % sides.size()];
        switch(randomSide) {
            case 'l': x--;  break;
            case 'r': x1++; break;
            case 'u': y--;  break;
            case 'd': y1++; break;
        }
    }

    for(int i = x; i <= x1; ++i) location[i][y] = 1;
    for(int i = y; i <= y1; ++i) location[x][i] = 1;
    for(int i = x-1; i <= x1+1; ++i) {
        for(int j = y-1; j <= y1+1; ++j) {
            if(i >= 0 && i <= 9 && j >= 0 && j <= 9)
                occupied[i][j] = 1;
        }
    }
    // ------------3-палубные-----------------
    for(int amount = 0; amount < 2; ++amount) {
        anotherOne3d:
        do {
            x = free[no] / 10;
            y = free[no] % 10;
            no++;
        }while(occupied[x][y]);
        sides.clear();
        if(x > 0 && !occupied[x-1][y]) sides.push_back('l');
        if(x < 9 && !occupied[x+1][y]) sides.push_back('r');
        if(y > 0 && !occupied[x][y-1]) sides.push_back('u');
        if(y < 9 && !occupied[x][y+1]) sides.push_back('d');
        if(!sides.size()) goto anotherOne3d;
        x1 = x;
        y1 = y;
        randomSide = sides[mersenne() % sides.size()];
        switch(randomSide) {
            case 'l': x--;  break;
            case 'r': x1++; break;
            case 'u': y--;  break;
            case 'd': y1++; break;
        }

        sides.clear();
        if(x != x1) {
            if(x > 0 && !occupied[x-1][y]) sides.push_back('l');
            if(x1 < 9 && !occupied[x1+1][y]) sides.push_back('r');
        }
        else if(y != y1) {
            if(y > 0 && !occupied[x][y-1]) sides.push_back('u');
            if(y1 < 9 && !occupied[x][y1+1]) sides.push_back('d');
        }
        if(!sides.size()) goto anotherOne3d;
        randomSide = sides[mersenne() % sides.size()];
        switch(randomSide) {
            case 'l': x--;  break;
            case 'r': x1++; break;
            case 'u': y--;  break;
            case 'd': y1++; break;
        }

        for(int i = x; i <= x1; ++i) location[i][y] = 1;
        for(int i = y; i <= y1; ++i) location[x][i] = 1;
        for(int i = x-1; i <= x1+1; ++i) {
            for(int j = y-1; j <= y1+1; ++j) {
                if(i >= 0 && i <= 9 && j >= 0 && j <= 9)
                    occupied[i][j] = 1;
            }
        }
    }
    // ------------2-палубные-----------------
    for(int amount = 0; amount < 3; ++amount) {
        anotherOne2d:
        do {
            x = free[no] / 10;
            y = free[no] % 10;
            no++;
        }while(occupied[x][y]);
        sides.clear();
        if(x > 0 && !occupied[x-1][y]) sides.push_back('l');
        if(x < 9 && !occupied[x+1][y]) sides.push_back('r');
        if(y > 0 && !occupied[x][y-1]) sides.push_back('u');
        if(y < 9 && !occupied[x][y+1]) sides.push_back('d');
        if(!sides.size()) goto anotherOne2d;
        x1 = x;
        y1 = y;
        randomSide = sides[mersenne() % sides.size()];
        switch(randomSide) {
            case 'l': x--;  break;
            case 'r': x1++; break;
            case 'u': y--;  break;
            case 'd': y1++; break;
        }

        for(int i = x; i <= x1; ++i) location[i][y] = 1;
        for(int i = y; i <= y1; ++i) location[x][i] = 1;
        for(int i = x-1; i <= x1+1; ++i) {
            for(int j = y-1; j <= y1+1; ++j) {
                if(i >= 0 && i <= 9 && j >= 0 && j <= 9)
                    occupied[i][j] = 1;
            }
        }
    }
    // ------------1-палубные-----------------
    for(int amount = 0; amount < 4; ++amount) {
        do {
            x = free[no] / 10;
            y = free[no] % 10;
            no++;
        }while(occupied[x][y]);
        location[x][y] = 1;
        for(int i = x-1; i <= x+1; ++i) {
            for(int j = y-1; j <= y+1; ++j) {
                if(i >= 0 && i <= 9 && j >= 0 && j <= 9)
                    occupied[i][j] = 1;
            }
        }
    }
}

void Field::ArrangeShipsForPerson()
{
    system("cls");
    draw::EmptyField(zeroCoordPointerX - 2, zeroCoordPointerY - 2);
    draw::ships_arrangement::InstructionText(zeroCoordPointerX - 2, zeroCoordPointerY - 6, "write");
    draw::ships_arrangement::Buttons("draw");
    ClickInfo clickInfo;
    ArrangementValidity arrangementValidity;
    while(1) {
        clickInfo = GetClickCoords_ShipsArrangement();
        if(clickInfo.outside_field) {
            if(clickInfo.buttonExit_isPressed) {
                SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), prev_mode);
                exit(0);
            }

            if(clickInfo.buttonAuto_isPressed) {
                ArrangeShipsRandomly();
                DrawShips();
                if(!draw::ships_arrangement::buttonClear_isActive) {
                    draw::ships_arrangement::buttonClear_isActive = 1;
                    draw::ships_arrangement::ButtonClear(1);
                }
                if(!draw::ships_arrangement::buttonDone_isActive) {
                    draw::ships_arrangement::buttonDone_isActive = 1;
                    draw::ships_arrangement::ButtonDone(1);
                }
            }

            else if(clickInfo.buttonClear_isPressed) {
                if(draw::ships_arrangement::buttonClear_isActive) {
                    RemoveAllShipsFromField();
                    DrawShips();
                    draw::ships_arrangement::buttonClear_isActive = 0;
                    draw::ships_arrangement::ButtonClear(0);
                    if(draw::ships_arrangement::buttonDone_isActive) {
                        draw::ships_arrangement::buttonDone_isActive = 0;
                        draw::ships_arrangement::ButtonDone(0);
                    }
                }
            }

            else if(clickInfo.buttonDone_isPressed) {
                if(draw::ships_arrangement::buttonDone_isActive) {
                    draw::ships_arrangement::InstructionText(zeroCoordPointerX - 2, zeroCoordPointerY - 6, "clear");
                    draw::ships_arrangement::Buttons("clear");
                    return;
                }
            }
        }
        else {
            bool shouldChangeSomething = 0;
            if(clickInfo.button == 'l' && !location[clickInfo.x][clickInfo.y]) {
                location[clickInfo.x][clickInfo.y] = 1;
                setColor(102);
                shouldChangeSomething = 1;
            }
            else if(clickInfo.button == 'r' && location[clickInfo.x][clickInfo.y]) {
                location[clickInfo.x][clickInfo.y] = 0;
                setColor(0);
                shouldChangeSomething = 1;
            }
            if(shouldChangeSomething) {
                setPosition(zeroCoordPointerX + clickInfo.x * 6, zeroCoordPointerY + clickInfo.y * 3);
                cout << "   ";
                setColor(15);
                arrangementValidity.IsValid(location);
                if(arrangementValidity.current_validity && !draw::ships_arrangement::buttonDone_isActive) {
                    draw::ships_arrangement::buttonDone_isActive = 1;
                    draw::ships_arrangement::ButtonDone(1);
                }
                else if(!arrangementValidity.current_validity && draw::ships_arrangement::buttonDone_isActive) {
                    draw::ships_arrangement::buttonDone_isActive = 0;
                    draw::ships_arrangement::ButtonDone(0);
                }
                if(FieldIsEmpty() && draw::ships_arrangement::buttonClear_isActive) {
                    draw::ships_arrangement::buttonClear_isActive = 0;
                    draw::ships_arrangement::ButtonClear(0);
                }
                else if(!FieldIsEmpty() && !draw::ships_arrangement::buttonClear_isActive) {
                    draw::ships_arrangement::buttonClear_isActive = 1;
                    draw::ships_arrangement::ButtonClear(1);
                }
            }
        }
    }
}

void Field::RemoveAllShipsFromField()
{
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
            location[i][j] = 0;
}

bool Field::FieldIsEmpty()
{
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
            if(location[i][j])
                return 0;
    return 1;
}

ClickInfo Field::GetClickCoords_ShipsArrangement()
{
    namespace dsa = draw::ships_arrangement;
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
    INPUT_RECORD InputRecord; // используется для возвращения информации о входных сообщениях в консольном входном буфере
    DWORD Events; // unsigned long
    COORD coord;

    // Запретить выдеение консоли
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
    SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку мыши

    short x, y;
    ClickInfo clickInfo;
    while(1) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        DWORD buttonPressed = InputRecord.Event.MouseEvent.dwButtonState;
        if(buttonPressed == MOUSE_WHEELED ||
           buttonPressed == FROM_LEFT_1ST_BUTTON_PRESSED ||
           buttonPressed == RIGHTMOST_BUTTON_PRESSED)
        {
            x = InputRecord.Event.MouseEvent.dwMousePosition.X - (zeroCoordPointerX - 2);
            y = InputRecord.Event.MouseEvent.dwMousePosition.Y - (zeroCoordPointerY - 2);
            if(x > 0 && x < 61 && (x % 6 != 0) && y > 0 && y <= 30) {
                if(buttonPressed == MOUSE_WHEELED) continue;
                x /= 6;
                y = (y-1) / 3;
                clickInfo.x = x;
                clickInfo.y = y;
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                }
                clickInfo.outside_field = 0;
                return clickInfo;
            }
            x += zeroCoordPointerX - 2;
            y += zeroCoordPointerY - 2;
            if(x >= dsa::indentX_leftColumn + 2 && x < dsa::indentX_leftColumn + dsa::width_leftColumn - 2 &&
               y > dsa::indentY_lower && y < dsa::indentY_lower + dsa::heightOfCells - 1)
            {
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                    case MOUSE_WHEELED:                clickInfo.button = 'w'; break;
                }
                clickInfo.outside_field = 1;
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
                clickInfo.buttonExit_isPressed = 0;
                clickInfo.buttonAuto_isPressed = 0;
                clickInfo.buttonClear_isPressed = 0;
                clickInfo.buttonDone_isPressed = 1;
                return clickInfo;
            }
        }
    }
}

ClickInfo Field::GetClickCoords_PlayTime()
{
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
    INPUT_RECORD InputRecord; // используется для возвращения информации о входных сообщениях в консольном входном буфере
    DWORD Events; // unsigned long
    COORD coord;

    short x, y;
    ClickInfo clickInfo;
    while(1) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        DWORD buttonPressed = InputRecord.Event.MouseEvent.dwButtonState;
        if(buttonPressed == MOUSE_WHEELED ||
           buttonPressed == FROM_LEFT_1ST_BUTTON_PRESSED ||
           buttonPressed == RIGHTMOST_BUTTON_PRESSED)
        {
            x = InputRecord.Event.MouseEvent.dwMousePosition.X - (zeroCoordPointerX - 2);
            y = InputRecord.Event.MouseEvent.dwMousePosition.Y - (zeroCoordPointerY - 2);
            if(x > 0 && x < 61 && (x % 6 != 0) && y > 0 && y <= 30) {
                x /= 6;
                y = (y-1) / 3;
                if(shooting[x][y]) continue;
                clickInfo.x = x;
                clickInfo.y = y;
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

void Field::RevealSurvivorsAfterLoss()
{
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            if(!shooting[i][j] && location[i][j]) {
                setPosition(zeroCoordPointerX + i * 6, zeroCoordPointerY + j * 3);
                setColor(170);
                cout << "lox";
                setColor(15);
            }
        }
    }
}

void Field::MarkEmptyCellAsShot(int fieldX, int fieldY)
{
    shooting[fieldX][fieldY] = 1;
    setPosition(zeroCoordPointerX + fieldX * 6, zeroCoordPointerY + fieldY * 3);
    cout << " x ";
}

bool Field::ShootAt(int x, int y)
{
    assert(!shooting[x][y]);
    setPosition(zeroCoordPointerX + x * 6, zeroCoordPointerY + y * 3);

    if(location[x][y]) {
        shooting[x][y] = 1;
        setColor(68);
        cout << "   ";
        setColor(11);
        vector<char> sides;
        sides.reserve(2);
        if(x > 0 && location[x-1][y]) sides.push_back('l');
        if(x < 9 && location[x+1][y]) sides.push_back('r');
        if(y > 0 && location[x][y-1]) sides.push_back('u');
        if(y < 9 && location[x][y+1]) sides.push_back('d');

        if(!sides.size()) { // попал в однопалубный
            for(int i = x-1; i <= x+1; ++i) {
                for(int j = y-1; j <= y+1; ++j) {
                    if(!(i == x && j == y) && i >= 0 && i <= 9 && j >= 0 && j <= 9) {
                        MarkEmptyCellAsShot(i, j);
                    }
                }
            }
            deadCounter++;
            aboutToFinishAShip = 0;
        }
        else {
            int aliveDecks = 0;
            int restX, restY;
            for(int i = 0; i < sides.size(); ++i) { // проверяем мертв ли корабль и нужно ли его обводить точками
                switch(sides[i]) {
                case 'l':
                    restX = x - 1;
                    restY = y;
                    while(restX >= 0 && location[restX][restY]) {
                        if(!shooting[restX][restY]) aliveDecks++;
                        restX--;
                    }
                    break;
                case 'r':
                    restX = x + 1;
                    restY = y;
                    while(restX <= 9 && location[restX][restY]) {
                        if(!shooting[restX][restY]) aliveDecks++;
                        restX++;
                    }
                    break;
                case 'u':
                    restX = x;
                    restY = y - 1;
                    while(restY >= 0 && location[restX][restY]) {
                        if(!shooting[restX][restY]) aliveDecks++;
                        restY--;
                    }
                    break;
                case 'd':
                    restX = x;
                    restY = y + 1;
                    while(restY <= 9 && location[restX][restY]) {
                        if(!shooting[restX][restY]) aliveDecks++;
                        restY++;
                    }
                    break;
                }
            }
            if(aliveDecks == 0) { // обводим точками мертвый корабль
                deadCounter++;
                aboutToFinishAShip = 0;
                CircleDeadShip(x, y, sides);
            }
            else aboutToFinishAShip = 1;
        }
        return true; // попал
    }
    else {
        shooting[x][y] = 1;
        cout << " x ";
        return false; // не попал
    }
}

void Field::CircleDeadShip(int x, int y, vector<char> sides)
{
    if(sides[0] == 'l' || sides[0] == 'r') { // если корабль горизонтальный, ставим точки сверху и снизу относительно x, y
        if(y > 0) MarkEmptyCellAsShot(x, y - 1);
        if(y < 9) MarkEmptyCellAsShot(x, y + 1);
        if(x > 0 && !location[x-1][y]) { // если слева нет продолжения корабля
            MarkEmptyCellAsShot(x - 1, y);
            if(y > 0) MarkEmptyCellAsShot(x - 1, y - 1);
            if(y < 9) MarkEmptyCellAsShot(x - 1, y + 1);
        }
        if(x < 9 && !location[x+1][y]) { // если справа нет продолжения корабля
            MarkEmptyCellAsShot(x + 1, y);
            if(y > 0) MarkEmptyCellAsShot(x + 1, y - 1);
            if(y < 9) MarkEmptyCellAsShot(x + 1, y + 1);
        }
    }
    if(sides[0] == 'u' || sides[0] == 'd') { // если корабль вертикальный, ставим точки слева и справа относительно x, y
        if(x > 0) MarkEmptyCellAsShot(x - 1, y);
        if(x < 9) MarkEmptyCellAsShot(x + 1, y);
        if(y > 0 && !location[x][y-1]) { // если сверху нет продолжения корабля
            MarkEmptyCellAsShot(x, y - 1);
            if(x > 0) MarkEmptyCellAsShot(x - 1, y - 1);
            if(x < 9) MarkEmptyCellAsShot(x + 1, y - 1);
        }
        if(y < 9 && !location[x][y+1]) { // если снизу нет продолжения корабля
            MarkEmptyCellAsShot(x, y + 1);
            if(x > 0) MarkEmptyCellAsShot(x - 1, y + 1);
            if(x < 9) MarkEmptyCellAsShot(x + 1, y + 1);
        }
    }
    int restX, restY;
    for(int i = 0; i < sides.size(); ++i) {
        switch(sides[i]) {
        case 'l':
            restX = x - 1;
            while(restX >= 0 && location[restX + 1][y]) {
                if(y > 0) MarkEmptyCellAsShot(restX, y - 1);
                if(y < 9) MarkEmptyCellAsShot(restX, y + 1);
                if(!location[restX][y]) MarkEmptyCellAsShot(restX, y);
                restX--;
            }
            break;
        case 'r':
            restX = x + 1;
            while(restX <= 9 && location[restX - 1][y]) {
                if(y > 0) MarkEmptyCellAsShot(restX, y - 1);
                if(y < 9) MarkEmptyCellAsShot(restX, y + 1);
                if(!location[restX][y]) MarkEmptyCellAsShot(restX, y);
                restX++;
            }
            break;
        case 'u':
            restY = y - 1;
            while(restY >= 0 && location[x][restY + 1]) {
                if(x > 0) MarkEmptyCellAsShot(x - 1, restY);
                if(x < 9) MarkEmptyCellAsShot(x + 1, restY);
                if(!location[x][restY]) MarkEmptyCellAsShot(x, restY);
                restY--;
            }
            break;
        case 'd':
            restY = y + 1;
            while(restY <= 9 && location[x][restY - 1]) {
                if(x > 0) MarkEmptyCellAsShot(x - 1, restY);
                if(x < 9) MarkEmptyCellAsShot(x + 1, restY);
                if(!location[x][restY]) MarkEmptyCellAsShot(x, restY);
                restY++;
            }
            break;
        }
    }
}

void Field::DrawShips()
{
    for(int x = 0; x < 10; ++x) {
        for(int y = 0; y < 10; ++y) {
            setPosition(zeroCoordPointerX + x * 6, zeroCoordPointerY + y * 3);
            if(location[x][y]) {
                setColor(102);
                cout << "   ";
                setColor(15);
            }
            else cout << "   ";
        }
    }
}

void setPosition(int x, int y)
{
    static COORD coord;
    coord.X = x;
    coord.Y = y;
    if(!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord)) {
        cout << GetLastError();
        exit(-1);
    }
}

void setColor(int color)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD) color);
}
