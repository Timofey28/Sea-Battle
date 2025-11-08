#include "game_process.h"

GameProcess::GameProcess()
{
    assert(positionFromTop != -1 && nConsoleWidth != -1 && nConsoleHeight != -1);
    fieldLeft = make_unique<Field>();
    fieldRight = make_unique<Field>();
    indentX_1stField = nConsoleWidth * 1 / 4 - 30;
    indentX_2ndField = nConsoleWidth * 3 / 4 - 30;
    fieldLeft->zeroCoordPointerX = indentX_1stField + 2;
    fieldLeft->zeroCoordPointerY = positionFromTop + 2;
    fieldRight->zeroCoordPointerX = indentX_2ndField + 2;
    fieldRight->zeroCoordPointerY = positionFromTop + 2;
    fieldLeft->SetLeftFieldIndents(indentX_1stField, positionFromTop);
    fieldRight->SetLeftFieldIndents(indentX_1stField, positionFromTop);
    goBack = 0;
}

void GameProcess::ArrangeShips(bool singleGame)
{
    if(singleGame) {  // одиночная игра
        fieldRight->ArrangeShipsRandomly();
        if(fieldLeft->ArrangeShipsForPerson(1, 0, 0)) {
            goBack = 1;
            return;
        }
    }
    else {  // совместная игра
        if(fieldLeft->ArrangeShipsForPerson(0, 1, 0)) {
            goBack = 1;
            return;
        }
        if(fieldRight->ArrangeShipsForPerson(0, 0, 1)) {
            goBack = 1;
            return;
        }
    }
}

bool GameProcess::GoBack()
{
    if(goBack) {
        goBack = 0;
        return 1;
    }
    else return 0;
}

void GameProcess::Play_1player()
{
    draw::EmptyField(indentX_2ndField, positionFromTop);
    draw::CoordinatesToRightField(indentX_2ndField, positionFromTop);

    int fieldX, fieldY;
    vector<int> free(100);
    for(int i = 0; i < 100; ++i) free[i] = i;
    shuffle(free.begin(), free.end(), mersenne);
    int no = 0;
    int x0 = -1, y0, x1 = -1, y1;  // to finish a ship...
    vector<char> sides;
    sides.reserve(4);
    bool hitAgain = false;
    ClickInfo clickInfo;

    setColor(11);
    clock_t startTime = clock();
    while(1) {
        while(2) {
            if(!hitAgain) draw::MoveIndicatingArrows(indentX_2ndField, "green");
            do clickInfo = fieldRight->clickCoordinates.Get_PlayTime(fieldRight->zeroCoordPointerX, fieldRight->zeroCoordPointerY);
            while(fieldRight->WasShotAt(clickInfo.x, clickInfo.y));
            if(clock() - startTime <= 500) continue;
            startTime = clock();
            fieldX = clickInfo.x;
            fieldY = clickInfo.y;
            bool success = fieldRight->ShootAt(fieldX, fieldY);
            if(!success) {
                draw::MoveIndicatingArrows(indentX_2ndField, "empty");
                hitAgain = 0;
                break;
            }

            if(fieldRight->deadCounter == 10) {
                draw::MoveIndicatingArrows(indentX_2ndField, "empty");
                draw::Victory(1);
                _getch();
                fieldRight->ReturnPreviousConsoleMode();
                exit(0);
            }
            if(!hitAgain) {
                hitAgain = 1;
                draw::MoveIndicatingArrows(indentX_2ndField, "red");
            }
        }

        while(2) {
            if(!hitAgain) draw::MoveIndicatingArrows(indentX_1stField, "green");
            this_thread::sleep_for(500ms);
            if(fieldLeft->aboutToFinishAShip) {
                if(x1 == -1) {  // выбор максимум из 4 сторон
                    sides.clear();
                    if(x0 > 0 && !fieldLeft->WasShotAt(x0 - 1, y0)) sides.push_back('l');
                    if(x0 < 9 && !fieldLeft->WasShotAt(x0 + 1, y0)) sides.push_back('r');
                    if(y0 > 0 && !fieldLeft->WasShotAt(x0, y0 - 1)) sides.push_back('u');
                    if(y0 < 9 && !fieldLeft->WasShotAt(x0, y0 + 1)) sides.push_back('d');
                    assert(sides.size());
                    switch(sides[mersenne() % sides.size()]) {
                        case 'l': fieldX = x0 - 1; fieldY = y0; break;
                        case 'r': fieldX = x0 + 1; fieldY = y0; break;
                        case 'u': fieldY = y0 - 1; fieldX = x0; break;
                        case 'd': fieldY = y0 + 1; fieldX = x0; break;
                    }
                }
                else {  // выбор максимум из 2 сторон
                    sides.clear();
                    if(x0 != x1) {  // корабль горизонтальный
                        if(x0 > 0 && !fieldLeft->WasShotAt(x0 - 1, y0)) sides.push_back('l');
                        if(x1 < 9 && !fieldLeft->WasShotAt(x1 + 1, y0)) sides.push_back('r');
                    }
                    else {  // корабль вертикальный
                        if(y0 > 0 && !fieldLeft->WasShotAt(x0, y0 - 1)) sides.push_back('u');
                        if(y1 < 9 && !fieldLeft->WasShotAt(x0, y1 + 1)) sides.push_back('d');
                    }
                    assert(sides.size());
                    switch(sides[mersenne() % sides.size()]) {
                        case 'l': fieldX = x0 - 1; fieldY = y0; break;
                        case 'r': fieldX = x1 + 1; fieldY = y0; break;
                        case 'u': fieldY = y0 - 1; fieldX = x0; break;
                        case 'd': fieldY = y1 + 1; fieldX = x0; break;
                    }
                }
            }
            else {
                do {
                    fieldX = free[no] / 10;
                    fieldY = free[no] % 10;
                    no++;
                }while(fieldLeft->WasShotAt(fieldX, fieldY));
            }
            bool success = fieldLeft->ShootAt(fieldX, fieldY);
            if(!success) {
                draw::MoveIndicatingArrows(indentX_1stField, "empty");
                hitAgain = 0;
                break;
            }

            if(fieldLeft->aboutToFinishAShip) {
                if(x0 == -1) {
                    x0 = fieldX;
                    y0 = fieldY;
                }
                else if(x1 == -1) {
                    if(fieldX > x0) {
                        x1 = fieldX;
                        y1 = y0;
                    }
                    else if(fieldX < x0) {
                        x1 = x0;
                        x0 = fieldX;
                        y1 = y0;
                    }
                    else if(fieldY > y0) {
                        x1 = x0;
                        y1 = fieldY;
                    }
                    else if(fieldY < y0) {
                        x1 = x0;
                        y1 = y0;
                        y0 = fieldY;
                    }
                }
                else {
                    if(fieldX < x0) x0 = fieldX;
                    else if(fieldX > x1) x1 = fieldX;
                    else if(fieldY < y0) y0 = fieldY;
                    else if(fieldY > y1) y1 = fieldY;
                }
            }
            else {
                x0 = -1;
                x1 = -1;
                sides.clear();
            }

            if(fieldLeft->deadCounter == 10) {
                draw::MoveIndicatingArrows(indentX_1stField, "empty");
                fieldRight->RevealSurvivorsAfterVictory();
                draw::Loss(1);
                _getch();
                fieldLeft->ReturnPreviousConsoleMode();
                exit(0);
            }

            if(!hitAgain) {
                hitAgain = 1;
                draw::MoveIndicatingArrows(indentX_1stField, "red");
            }
        }
    }
}

void GameProcess::Play_2players()
{
    fieldLeft->ClearFieldFromShips();
    draw::EmptyField(indentX_2ndField, positionFromTop);
    draw::CoordinatesToBothFields(indentX_1stField, indentX_2ndField, positionFromTop);
    int fieldX, fieldY;
    bool hitAgain = false;
    ClickInfo clickInfo;

    setColor(11);
    int whoGoesFirst = mersenne() % 2;
    if(whoGoesFirst) goto playerOnRight;
    while(1) {
        while(2) {  // игрок слева бьет по правому полю
            if(!hitAgain) draw::MoveIndicatingArrows(indentX_2ndField, "green", 1);
            do clickInfo = fieldRight->clickCoordinates.Get_PlayTime(fieldRight->zeroCoordPointerX, fieldRight->zeroCoordPointerY);
            while(fieldRight->WasShotAt(clickInfo.x, clickInfo.y));
            fieldX = clickInfo.x;
            fieldY = clickInfo.y;
            bool success = fieldRight->ShootAt(fieldX, fieldY);
            if(!success) {
                draw::MoveIndicatingArrows(indentX_2ndField, "empty", 1);
                hitAgain = 0;
                break;
            }

            if(fieldRight->deadCounter == 10) {
                draw::MoveIndicatingArrows(indentX_2ndField, "empty", 1);
                fieldLeft->RevealSurvivorsAfterVictory();
                draw::Victory(0, 1);
                draw::Loss(0, 2);
                _getch();
//                fieldRight->ReturnPreviousConsoleMode();
                return;
            }
            if(!hitAgain) {
                hitAgain = 1;
                draw::MoveIndicatingArrows(indentX_2ndField, "red", 1);
            }
        }

        playerOnRight:
        while(2) {  // игрок справа бьет по левому полю
            if(!hitAgain) draw::MoveIndicatingArrows(indentX_1stField, "green", 1);
            do clickInfo = fieldLeft->clickCoordinates.Get_PlayTime(fieldLeft->zeroCoordPointerX, fieldLeft->zeroCoordPointerY);
            while(fieldLeft->WasShotAt(clickInfo.x, clickInfo.y));
            fieldX = clickInfo.x;
            fieldY = clickInfo.y;
            bool success = fieldLeft->ShootAt(fieldX, fieldY);
            if(!success) {
                draw::MoveIndicatingArrows(indentX_1stField, "empty", 1);
                hitAgain = 0;
                break;
            }

            if(fieldLeft->deadCounter == 10) {
                draw::MoveIndicatingArrows(indentX_1stField, "empty", 1);
                fieldRight->RevealSurvivorsAfterVictory();
                draw::Victory(0, 2);
                draw::Loss(0, 1);
                _getch();
//                fieldLeft->ReturnPreviousConsoleMode();
                return;
            }
            if(!hitAgain) {
                hitAgain = 1;
                draw::MoveIndicatingArrows(indentX_1stField, "red", 1);
            }
        }
    }
}
