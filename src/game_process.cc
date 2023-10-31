#include "game_process.h"
using namespace std;

GameProcess::GameProcess()
{
    assert(positionFromTop != -1 && nConsoleWidth != -1 && nConsoleHeight != -1);
    fieldMe = make_unique<Field>();
    fieldEnemy = make_unique<Field>();
    indentX_1stField = nConsoleWidth * 1 / 4 - 30;
    indentX_2ndField = nConsoleWidth * 3 / 4 - 30;
    fieldMe->zeroCoordPointerX = indentX_1stField + 2;
    fieldMe->zeroCoordPointerY = positionFromTop + 2;
    fieldEnemy->zeroCoordPointerX = indentX_2ndField + 2;
    fieldEnemy->zeroCoordPointerY = positionFromTop + 2;
}

void GameProcess::ArrangeShips()
{
    fieldEnemy->ArrangeShipsRandomly();
    fieldMe->ArrangeShipsForPerson();
}

void GameProcess::Play()
{
    draw::EmptyField(indentX_2ndField, positionFromTop);
    draw::CoordinatesToField(indentX_2ndField, positionFromTop);

    int fieldX, fieldY;
    vector<int> free(100);
    for(int i = 0; i < 100; ++i) free[i] = i;
    random_shuffle(free.begin(), free.end(), [](int i){return mersenne() % i;});
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
            clickInfo = fieldEnemy->GetClickCoords_PlayTime();
            if(clock() - startTime <= 1000) continue;
            fieldX = clickInfo.x;
            fieldY = clickInfo.y;
            bool result = fieldEnemy->ShootAt(fieldX, fieldY);
            if(!result) {
                draw::MoveIndicatingArrows(indentX_2ndField, "empty");
                hitAgain = 0;
                break;
            }

            if(fieldEnemy->deadCounter == 10) {
                draw::MoveIndicatingArrows(indentX_1stField, "empty");
                draw::Victory();
                _getch();
                fieldEnemy->ReturnPreviousConsoleMode();
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
            if(fieldMe->aboutToFinishAShip) {
                if(x1 == -1) {  // выбор максимум из 4 сторон
                    sides.clear();
                    if(x0 > 0 && !fieldMe->WasShotAt(x0 - 1, y0)) sides.push_back('l');
                    if(x0 < 9 && !fieldMe->WasShotAt(x0 + 1, y0)) sides.push_back('r');
                    if(y0 > 0 && !fieldMe->WasShotAt(x0, y0 - 1)) sides.push_back('u');
                    if(y0 < 9 && !fieldMe->WasShotAt(x0, y0 + 1)) sides.push_back('d');
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
                        if(x0 > 0 && !fieldMe->WasShotAt(x0 - 1, y0)) sides.push_back('l');
                        if(x1 < 9 && !fieldMe->WasShotAt(x1 + 1, y0)) sides.push_back('r');
                    }
                    else {  // корабль вертикальный
                        if(y0 > 0 && !fieldMe->WasShotAt(x0, y0 - 1)) sides.push_back('u');
                        if(y1 < 9 && !fieldMe->WasShotAt(x0, y1 + 1)) sides.push_back('d');
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
                }while(fieldMe->WasShotAt(fieldX, fieldY));
            }
            bool result = fieldMe->ShootAt(fieldX, fieldY);
            if(!result) {
                draw::MoveIndicatingArrows(indentX_1stField, "empty");
                hitAgain = 0;
                break;
            }

            if(fieldMe->aboutToFinishAShip) {
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

            if(fieldMe->deadCounter == 10) {
                draw::MoveIndicatingArrows(indentX_2ndField, "empty");
                draw::Loss();
                fieldEnemy->RevealSurvivorsAfterLoss();
                _getch();
                fieldMe->ReturnPreviousConsoleMode();
                exit(0);
            }

            if(!hitAgain) {
                hitAgain = 1;
                draw::MoveIndicatingArrows(indentX_1stField, "red");
            }
        }
    }
}
