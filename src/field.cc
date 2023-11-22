#include "field.h"
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

bool Field::ArrangeShipsForPerson(bool singleGame, bool firstPlayer, bool secondPlayer)
{
    system("cls");
    assert(singleGame == 1 && firstPlayer == 0 && secondPlayer == 0 ||
           singleGame == 0 && firstPlayer == 1 && secondPlayer == 0 ||
           singleGame == 0 && firstPlayer == 0 && secondPlayer == 1);
    namespace dsa = draw::ships_arrangement;
    if(singleGame)        dsa::Phrase_ArrangeYourShips("write");
    else if(firstPlayer)  dsa::Phrase_PlayerOnTheLeft("write");
    else if(secondPlayer) dsa::Phrase_PlayerOnTheRight("write");
    draw::EmptyField(indentX_LeftField, indentY_LeftField);
    dsa::Buttons("draw");
    dsa::ResetShipsAmounts();
    dsa::RemainingShips("draw");
    ClickInfo clickInfo;
    ArrangementValidity arrangementValidity;
    bool previousValidity = 1;
    while(1) {
        clickInfo = clickCoordinates.Get_ShipsArrangement(indentX_LeftField + 2, indentY_LeftField + 2);
        if(clickInfo.outside_field) {
            if(clickInfo.buttonExit_isPressed) {
                ReturnPreviousConsoleMode();
                exit(0);
            }

            if(clickInfo.buttonHelp_isPressed) {
                system("cls");
                dsa::InstructionText(indentX_LeftField, indentY_LeftField - 4, "write");
                clickCoordinates.Get_AnyClick();
                system("cls");
                if(singleGame)        dsa::Phrase_ArrangeYourShips("write");
                else if(firstPlayer)  dsa::Phrase_PlayerOnTheLeft("write");
                else if(secondPlayer) dsa::Phrase_PlayerOnTheRight("write");
                draw::EmptyField(indentX_LeftField, indentY_LeftField);
                DrawShips();
                dsa::Buttons("draw");
                if(previousValidity) dsa::RemainingShips("redraw");
                else dsa::Phrase_invalidSet("write");
            }

            if(clickInfo.buttonBack_isPressed) {
                for(int i = 0; i < 10; ++i) {
                    for(int j = 0; j < 10; ++j) {
                        location[i][j] = 0;
                    }
                }
                dsa::buttonClear_isActive = 0;
                dsa::buttonDone_isActive = 0;
                dsa::ResetShipsAmounts();
                return 1;
            }

            if(clickInfo.buttonAuto_isPressed) {
                ArrangeShipsRandomly();
                DrawShips();
                if(!dsa::buttonClear_isActive) {
                    dsa::buttonClear_isActive = 1;
                    dsa::ButtonClear(1);
                }
                if(!dsa::buttonDone_isActive) {
                    dsa::buttonDone_isActive = 1;
                    dsa::ButtonDone(1);
                }
                if(!previousValidity) {
                    dsa::Phrase_invalidSet("clear");
                    previousValidity = 1;
                }
                dsa::RemainingShips("draw", 0, 0, 0, 0);
            }

            else if(clickInfo.buttonClear_isPressed) {
                if(dsa::buttonClear_isActive) {
                    RemoveAllShipsFromField();
                    DrawShips();
                    dsa::buttonClear_isActive = 0;
                    dsa::ButtonClear(0);
                    if(dsa::buttonDone_isActive) {
                        dsa::buttonDone_isActive = 0;
                        dsa::ButtonDone(0);
                    }
                    if(!previousValidity) {
                        dsa::Phrase_invalidSet("clear");
                        previousValidity = 1;
                    }
                    dsa::RemainingShips("draw");
                }
            }

            else if(clickInfo.buttonDone_isPressed) {
                if(dsa::buttonDone_isActive) {
                    if(singleGame)        dsa::Phrase_ArrangeYourShips("clear");
                    else if(firstPlayer)  dsa::Phrase_PlayerOnTheLeft("clear");
                    else if(secondPlayer) dsa::Phrase_PlayerOnTheRight("clear");
                    dsa::Buttons("clear");
                    dsa::buttonClear_isActive = 0;
                    dsa::buttonDone_isActive = 0;
                    dsa::RemainingShips("draw", 0, 0, 0, 0);
                    return 0;
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
                setPosition(indentX_LeftField + 2 + clickInfo.x * 6, indentY_LeftField + 2 + clickInfo.y * 3);
                cout << "   ";
                setColor(15);
                arrangementValidity.IsValid(location);
                if(arrangementValidity.current_validity && !dsa::buttonDone_isActive) {
                    dsa::buttonDone_isActive = 1;
                    dsa::ButtonDone(1);
                }
                else if(!arrangementValidity.current_validity && dsa::buttonDone_isActive) {
                    dsa::buttonDone_isActive = 0;
                    dsa::ButtonDone(0);
                }
                if(FieldIsEmpty() && dsa::buttonClear_isActive) {
                    dsa::buttonClear_isActive = 0;
                    dsa::ButtonClear(0);
                }
                else if(!FieldIsEmpty() && !dsa::buttonClear_isActive) {
                    dsa::buttonClear_isActive = 1;
                    dsa::ButtonClear(1);
                }

                if(arrangementValidity.validity_of_those_already_on_the_field) {
                    int d1 = 4 - arrangementValidity.Get_1deckShipsAmount();
                    int d2 = 3 - arrangementValidity.Get_2deckShipsAmount();
                    int d3 = 2 - arrangementValidity.Get_3deckShipsAmount();
                    int d4 = 1 - arrangementValidity.Get_4deckShipsAmount();
                    if(!previousValidity) {
                        previousValidity = 1;
                        dsa::Phrase_invalidSet("clear");
                        dsa::ResetShipsAmounts();
                    }
                    dsa::RemainingShips("draw", d1, d2, d3, d4);
                }
                else if(previousValidity) {
                    dsa::RemainingShips("draw", 0, 0, 0, 0);
                    previousValidity = 0;
                    dsa::Phrase_invalidSet("write");
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

void Field::RevealSurvivorsAfterVictory()
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
            setPosition(indentX_LeftField + 2 + x * 6, indentY_LeftField + 2 + y * 3);
            if(location[x][y]) {
                setColor(102);
                cout << "   ";
                setColor(15);
            }
            else cout << "   ";
        }
    }
}

void Field::ClearFieldFromShips()
{
    setColor(0);
    for(int x = 0; x < 10; ++x) {
        for(int y = 0; y < 10; ++y) {
            setPosition(zeroCoordPointerX + x * 6, zeroCoordPointerY + y * 3);
            cout << "   ";
        }
    }
    setColor(15);
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
