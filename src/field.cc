#include <bits/stdc++.h>
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
}

void Field::revealSurvivorsAfterLoss()
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

void Field::markEmptyCellAsShot(int fieldX, int fieldY)
{
    shooting[fieldX][fieldY] = 1;
    setPosition(zeroCoordPointerX + fieldX * 6, zeroCoordPointerY + fieldY * 3);
    cout << " x ";
}

bool Field::shootAt(int x, int y)
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
                        markEmptyCellAsShot(i, j);
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
                circleDeadShip(x, y, sides);
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

void Field::circleDeadShip(int x, int y, vector<char> sides)
{
    if(sides[0] == 'l' || sides[0] == 'r') { // если корабль горизонтальный, ставим точки сверху и снизу относительно x, y
        if(y > 0) markEmptyCellAsShot(x, y - 1);
        if(y < 9) markEmptyCellAsShot(x, y + 1);
        if(x > 0 && !location[x-1][y]) { // если слева нет продолжения корабля
            markEmptyCellAsShot(x - 1, y);
            if(y > 0) markEmptyCellAsShot(x - 1, y - 1);
            if(y < 9) markEmptyCellAsShot(x - 1, y + 1);
        }
        if(x < 9 && !location[x+1][y]) { // если справа нет продолжения корабля
            markEmptyCellAsShot(x + 1, y);
            if(y > 0) markEmptyCellAsShot(x + 1, y - 1);
            if(y < 9) markEmptyCellAsShot(x + 1, y + 1);
        }
    }
    if(sides[0] == 'u' || sides[0] == 'd') { // если корабль вертикальный, ставим точки слева и справа относительно x, y
        if(x > 0) markEmptyCellAsShot(x - 1, y);
        if(x < 9) markEmptyCellAsShot(x + 1, y);
        if(y > 0 && !location[x][y-1]) { // если сверху нет продолжения корабля
            markEmptyCellAsShot(x, y - 1);
            if(x > 0) markEmptyCellAsShot(x - 1, y - 1);
            if(x < 9) markEmptyCellAsShot(x + 1, y - 1);
        }
        if(y < 9 && !location[x][y+1]) { // если снизу нет продолжения корабля
            markEmptyCellAsShot(x, y + 1);
            if(x > 0) markEmptyCellAsShot(x - 1, y + 1);
            if(x < 9) markEmptyCellAsShot(x + 1, y + 1);
        }
    }
    int restX, restY;
    for(int i = 0; i < sides.size(); ++i) {
        switch(sides[i]) {
        case 'l':
            restX = x - 1;
            while(restX >= 0 && location[restX + 1][y]) {
                if(y > 0) markEmptyCellAsShot(restX, y - 1);
                if(y < 9) markEmptyCellAsShot(restX, y + 1);
                if(!location[restX][y]) markEmptyCellAsShot(restX, y);
                restX--;
            }
            break;
        case 'r':
            restX = x + 1;
            while(restX <= 9 && location[restX - 1][y]) {
                if(y > 0) markEmptyCellAsShot(restX, y - 1);
                if(y < 9) markEmptyCellAsShot(restX, y + 1);
                if(!location[restX][y]) markEmptyCellAsShot(restX, y);
                restX++;
            }
            break;
        case 'u':
            restY = y - 1;
            while(restY >= 0 && location[x][restY + 1]) {
                if(x > 0) markEmptyCellAsShot(x - 1, restY);
                if(x < 9) markEmptyCellAsShot(x + 1, restY);
                if(!location[x][restY]) markEmptyCellAsShot(x, restY);
                restY--;
            }
            break;
        case 'd':
            restY = y + 1;
            while(restY <= 9 && location[x][restY - 1]) {
                if(x > 0) markEmptyCellAsShot(x - 1, restY);
                if(x < 9) markEmptyCellAsShot(x + 1, restY);
                if(!location[x][restY]) markEmptyCellAsShot(x, restY);
                restY++;
            }
            break;
        }
    }
}

ClickInfo getClickCoords(int indentX, int indentY, bool has_done_button = 0)
{
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
    INPUT_RECORD InputRecord; // используется для возвращения информации о входных сообщениях в консольном входном буфере
    DWORD Events; // unsigned long
    COORD coord;

    // Запретить выдеение консоли
    DWORD prev_mode;
    GetConsoleMode(hin, &prev_mode);
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
            x = InputRecord.Event.MouseEvent.dwMousePosition.X - indentX;
            y = InputRecord.Event.MouseEvent.dwMousePosition.Y - indentY;
            if(x > 0 && x < 61 && (x % 6 != 0) && y > 0 && y <= 30) {
                x /= 6;
                y = (y-1) / 3;
                SetConsoleMode(hin, prev_mode);
                clickInfo.x = x;
                clickInfo.y = y;
                switch(buttonPressed) {
                    case FROM_LEFT_1ST_BUTTON_PRESSED: clickInfo.button = 'l'; break;
                    case RIGHTMOST_BUTTON_PRESSED:     clickInfo.button = 'r'; break;
                    case MOUSE_WHEELED:                clickInfo.button = 'w'; break;
                }
                clickInfo.outside_field = 0;
                return clickInfo;
            }
            else if(has_done_button) {
                clickInfo.outside_field = 1;
                clickInfo.x = x;
                clickInfo.y = y;
                return clickInfo;
            }
        }
    }
}

void Field::shipsArrangement_manual(const int indent, const int positionFromTop, const int consoleWidth)
{
    system("cls");
    setColor(11);
    setPosition(0, positionFromTop);
    string ind(indent, ' ');
    cout << ind << " _____ _____ _____ _____ _____ _____ _____ _____ _____ _____";
    for(int i = 1; i <= 10; ++i) {
        cout << "\n" << ind << "|";
        for(int j = 1; j <= 20; ++j) {
            if(j == 11) cout << "\n" << ind << "|";
            cout << "     |";
        }
        cout << "\n" << ind << "|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|";
    }

    const int kCaptionIndent = consoleWidth / 4 * 3 - 16;
    setColor(136);
    setPosition(kCaptionIndent, positionFromTop + 22);
    cout << string(32, 'w');
    for(int y = positionFromTop + 23; y <= positionFromTop + 29; ++y) {
        setPosition(kCaptionIndent, y); cout << "ww";
        setPosition(kCaptionIndent + 30, y); cout << "ww";
    }
    setPosition(kCaptionIndent, positionFromTop + 30);
    cout << string(32, 'w');

    setColor(8);
    setPosition(kCaptionIndent + 4, positionFromTop + 24); cout << " ____";
    setPosition(kCaptionIndent + 4, positionFromTop + 25); cout << "|  _ \\  ___  _ __   ___";
    setPosition(kCaptionIndent + 4, positionFromTop + 26); cout << "| | | |/ _ \\| '_ \\ / _ \\";
    setPosition(kCaptionIndent + 4, positionFromTop + 27); cout << "| |_| | (_) | | | |  __/";
    setPosition(kCaptionIndent + 4, positionFromTop + 28); cout << "|____/ \\___/|_| |_|\\___|";

    ClickInfo clickInfo;
    ArrangementValidity av;
    while(1) {
        clickInfo = getClickCoords(indent, positionFromTop, 1);
        if(clickInfo.outside_field) {
            if(clickInfo.x >= kCaptionIndent - 11 && clickInfo.x < kCaptionIndent + 17 &&
               clickInfo.y > positionFromTop + 16 && clickInfo.y < positionFromTop + 24)
            {
                if(av.current_validity) return;
                else {
                    // сообщение об ошибке расстановки (?)
                }
            }
        }
        else {
            if(clickInfo.button == 'l') {
                setColor(102);
                location[clickInfo.x][clickInfo.y] = 1;
            }
            else {
                setColor(0);
                location[clickInfo.x][clickInfo.y] = 0;
            }
            setPosition(zeroCoordPointerX + clickInfo.x * 6, zeroCoordPointerY + clickInfo.y * 3);
            cout << "   ";

            if(av.current_validity != av.IsValid(location)) {
                if(av.current_validity) setColor(119);
                else setColor(136);
                setPosition(kCaptionIndent, positionFromTop + 22);
                cout << string(32, 'w');
                for(int y = positionFromTop + 23; y <= positionFromTop + 29; ++y) {
                    setPosition(kCaptionIndent, y); cout << "ww";
                    setPosition(kCaptionIndent + 30, y); cout << "ww";
                }
                setPosition(kCaptionIndent, positionFromTop + 30);
                cout << string(32, 'w');

                if(av.current_validity) setColor(7);
                else setColor(8);
                setPosition(kCaptionIndent + 4, positionFromTop + 24); cout << " ____";
                setPosition(kCaptionIndent + 4, positionFromTop + 25); cout << "|  _ \\  ___  _ __   ___";
                setPosition(kCaptionIndent + 4, positionFromTop + 26); cout << "| | | |/ _ \\| '_ \\ / _ \\";
                setPosition(kCaptionIndent + 4, positionFromTop + 27); cout << "| |_| | (_) | | | |  __/";
                setPosition(kCaptionIndent + 4, positionFromTop + 28); cout << "|____/ \\___/|_| |_|\\___|";
            }
        }
    }
}

void Field::shipsArrangement_automatic(int indentX, int indentY, int consoleWidth, int consoleHeight)
{
    assert(indentY > 0);
    bool goForward;

    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD InputRecord;
    DWORD Events;
    COORD coord;

    while(1) {
        arrangeShipsRandomly();
        drawShips(indentX, indentY);

        DWORD prev_mode;
        GetConsoleMode(hin, &prev_mode);
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
        SetConsoleMode(hin, ENABLE_MOUSE_INPUT);
        while(1) {
            ReadConsoleInput(hin, &InputRecord, 1, &Events);
            if(InputRecord.Event.MouseEvent.dwButtonState == MOUSE_WHEELED ||
               InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                if(InputRecord.Event.MouseEvent.dwMousePosition.X > consoleWidth / 2) {
                    if(InputRecord.Event.MouseEvent.dwMousePosition.Y < consoleHeight / 2) {
                        goForward = 0;
                        break;
                    }
                    else if(InputRecord.Event.MouseEvent.dwMousePosition.Y > consoleHeight / 2) {
                        goForward = 1;
                        break;
                    }
                }
            }
        }
        if(goForward) return;
    }
}

void Field::drawShips(int indentX, int indentY)
{
    for(int x = 0; x < 10; ++x) {
        for(int y = 0; y < 10; ++y) {
            setPosition(indentX + x * 6, indentY + y * 3);
            if(location[x][y]) {
                setColor(170);
                cout << "   ";
                setColor(15);
            }
            else cout << "   ";
        }
    }
}

void Field::arrangeShipsRandomly()
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
