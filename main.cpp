#include <bits/stdc++.h>
#include <conio.h>
#include <Windows.h>
#include "field.h"
#include "field.cpp"
using namespace std;

int consoleWidth, consoleHeight;
int positionFromTop = -3;
Field fMe, fEnemy;
clock_t startTime;

void setConsole();
void getConsoleWH();
int firstMenu();
void draw_shipsArrangement(int indent);
void draw_play(int indent2nd);
void playTime(int indent2nd);
pair<short, short> getClickCoords(int indentX, int indentY);
void victory();
void loss();
void draw_arrows(Field& field, string how);


int main()
{
    setlocale(0, "");
    setConsole();

    fEnemy.shipsArrangement_forComputer();

    backToFirstMenu:
    int choice = firstMenu();
    if(choice == 1) { // manual
//        goto backToFirstMenu;
        return 0;
    }
    else if(choice == 2) { // automatic
        int indent_1Field = (consoleWidth / 2 - 1) / 2 - 30; // длина поля == 61
        fMe.zeroCoordPointerX = indent_1Field + 2;
        fMe.zeroCoordPointerY = positionFromTop + 2;
        fEnemy.zeroCoordPointerY = positionFromTop + 2;

        draw_shipsArrangement(indent_1Field);
        fMe.shipsArrangement_automatic(indent_1Field + 2, positionFromTop + 2, consoleWidth, consoleHeight);
    }

    int indent_2ndField = consoleWidth / 4 * 3 - 30;
    fEnemy.zeroCoordPointerX = indent_2ndField + 2;

    draw_play(indent_2ndField);
    startTime = clock();
    playTime(indent_2ndField);

    return 0;
}

void playTime(int indent2nd)
{
    pair<int, int> xy;
    int fieldX, fieldY;
    vector<int> free(100);
    for(int i = 0; i < 100; ++i) free[i] = i;
    random_shuffle(free.begin(), free.end(), [](int i){return mersenne() % i;});
    int no = 0;
    int x0 = -1, y0, x1 = -1, y1; // finish...
    vector<char> sides;
    sides.reserve(4);
    bool hitAgain = false;

    setColor(11);
    while(1) {
        while(2) {
            if(!hitAgain) draw_arrows(fEnemy, "green");
            xy = getClickCoords(indent2nd, positionFromTop);
            if(clock() - startTime <= 1000) continue;
            fieldX = xy.first;
            fieldY = xy.second;
            bool result = fEnemy.shootAt(fieldX, fieldY);
            if(!result) {
                draw_arrows(fEnemy, "empty");
                hitAgain = 0;
                break;
            }

            if(fEnemy.deadCounter == 10) {
                victory();
                exit(0);
            }
            if(!hitAgain) {
                hitAgain = 1;
                draw_arrows(fEnemy, "red");
            }
        }

        while(2) {
            if(!hitAgain) draw_arrows(fMe, "green");
            this_thread::sleep_for(500ms);
            if(fMe.aboutToFinishAShip) {
                if(x1 == -1) { // выбор максимум из 4 сторон
                    sides.clear();
                    if(x0 > 0 && !fMe.wasShotAt(x0 - 1, y0)) sides.push_back('l');
                    if(x0 < 9 && !fMe.wasShotAt(x0 + 1, y0)) sides.push_back('r');
                    if(y0 > 0 && !fMe.wasShotAt(x0, y0 - 1)) sides.push_back('u');
                    if(y0 < 9 && !fMe.wasShotAt(x0, y0 + 1)) sides.push_back('d');
                    assert(sides.size());
                    switch(sides[mersenne() % sides.size()]) {
                        case 'l': fieldX = x0 - 1; fieldY = y0; break;
                        case 'r': fieldX = x0 + 1; fieldY = y0; break;
                        case 'u': fieldY = y0 - 1; fieldX = x0; break;
                        case 'd': fieldY = y0 + 1; fieldX = x0; break;
                    }
                }
                else { // выбор максимум из 2 сторон
                    sides.clear();
                    if(x0 != x1) { // корабль горизонтальный
                        if(x0 > 0 && !fMe.wasShotAt(x0 - 1, y0)) sides.push_back('l');
                        if(x1 < 9 && !fMe.wasShotAt(x1 + 1, y0)) sides.push_back('r');
                    }
                    else { // вертикальный
                        if(y0 > 0 && !fMe.wasShotAt(x0, y0 - 1)) sides.push_back('u');
                        if(y1 < 9 && !fMe.wasShotAt(x0, y1 + 1)) sides.push_back('d');
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
                }while(fMe.wasShotAt(fieldX, fieldY));
            }
            bool result = fMe.shootAt(fieldX, fieldY);
            if(!result) {
                draw_arrows(fMe, "empty");
                hitAgain = 0;
                break;
            }

            if(fMe.aboutToFinishAShip) {
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

            if(fMe.deadCounter == 10) {
                loss();
                fEnemy.revealSurvivorsAfterLoss();
                exit(0);
            }

            if(!hitAgain) {
                hitAgain = 1;
                draw_arrows(fMe, "red");
            }
        }
    }
    setColor(15);
}

pair<short, short> getClickCoords(int indentX, int indentY)
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
    while(1) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        if(InputRecord.Event.MouseEvent.dwButtonState == MOUSE_WHEELED ||
           InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            x = InputRecord.Event.MouseEvent.dwMousePosition.X - indentX;
            y = InputRecord.Event.MouseEvent.dwMousePosition.Y - indentY;
            if(x > 0 && x < 61 && (x % 6 != 0) && y > 0 && y <= 30) {
                x /= 6;
                y = (y-1) / 3;
                if(!fEnemy.wasShotAt(x, y)) {
//                    SetConsoleMode(hin, prev_mode);
                    return {x, y};
                }
            }
        }
    }
}

int firstMenu()
{
    system("cls");
    int shipsIndent = consoleWidth / 2 - 12; // длина слова Ships == 25
    string indent1(shipsIndent, ' ');
    string indent2(shipsIndent - 19, ' ');
    cout << indent1 << " ____  _     _\
\n" << indent1 << "/ ___|| |__ (_)_ __  ___\
\n" << indent1 << "\\___ \\| '_ \\| | '_ \\/ __|\
\n" << indent1 << " ___) | | | | | |_) \\__ \\\
\n" << indent1 << "|____/|_| |_|_| .__/|___/\
\n" << indent1 << "              |_|\                        _\
\n" << indent2 << "  __ _ _ __ _ __ __ _ _ __   __ _  ___ _ __ ___   ___ _ __ | |_\
\n" << indent2 << " / _` | '__| '__/ _` | '_ \\ / _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|\
\n" << indent2 << "| (_| | |  | | | (_| | | | | (_| |  __/ | | | | |  __/ | | | |_\
\n" << indent2 << " \\__,_|_|  |_|  \\__,_|_| |_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__|\
\n" << indent2 << "                            |___/";

    setPosition(0, consoleHeight / 2);
    int manualIndent = (consoleWidth / 2 - 1) / 2 - 17   +1;
    string indent3(manualIndent, ' '); // длина слова Manual == 34
    string indent4(consoleWidth / 2 - 1 - manualIndent - 34 + 3 + (consoleWidth / 2 - 1) / 2 - 11   -1, ' ');
    setColor(4); cout << indent3 << " __  __                         _";      setColor(1); cout << indent4 << "     _         _\n";
    setColor(4); cout << indent3 << "|  \\/  | __ _ _ __  _   _  __ _| |   "; setColor(1); cout << indent4 << "/ \\  _   _| |_ ___\n";
    setColor(4); cout << indent3 << "| |\\/| |/ _` | '_ \\| | | |/ _` | |  "; setColor(1); cout << indent4 << "/ _ \\| | | | __/ _ \\\n";
    setColor(4); cout << indent3 << "| |  | | (_| | | | | |_| | (_| | | ";    setColor(1); cout << indent4 << "/ ___ \\ |_| | || (_) |\n";
    setColor(4); cout << indent3 << "|_|  |_|\\__,_|_| |_|\\__,_|\\__,_|_|";  setColor(1); cout << indent4 << "/_/   \\_\\__,_|\\__\\___/";

    setColor(187);
    for(int y = 13; y < consoleHeight - 2; ++y) {
        setPosition(consoleWidth / 2 - 1, y);
        cout << "ww";
    }
    setColor(15);

    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
    INPUT_RECORD InputRecord; // используется для возвращения информации о входных сообщениях в консольном входном буфере
    DWORD Events; // unsigned long
    COORD coord;

    // Запретить выдеение консоли
    DWORD prev_mode;
    GetConsoleMode(hin, &prev_mode);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
    SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку мыши

    while(1) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        if(InputRecord.Event.MouseEvent.dwButtonState == MOUSE_WHEELED ||
           InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            if(InputRecord.Event.MouseEvent.dwMousePosition.X < consoleWidth / 2 - 1) {
                return 1;
            }
            else if(InputRecord.Event.MouseEvent.dwMousePosition.X > consoleWidth / 2) {
                return 2;
            }
        }
    }
}

void draw_shipsArrangement(int indent)
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

    setColor(187);
    int horizontalLineLength;
    for(int y = 0; y < 30; ++y) {
        setPosition(consoleWidth / 2 - 1, consoleHeight / 2 - 15 + y);
        cout << "ww";
        horizontalLineLength = consoleWidth / 2 - 1   -2;
        if(y == 15) cout << string(horizontalLineLength, 'w');
    }

    setColor(14);
    int changeCoordX = consoleWidth / 2 + 1 + horizontalLineLength / 2 - 18,
        changeCoordY = positionFromTop + 5;
    setPosition(changeCoordX, changeCoordY); cout << "  ____ _";
    setPosition(changeCoordX, changeCoordY + 1); cout << " / ___| |__   __ _ _ __   __ _  ___";
    setPosition(changeCoordX, changeCoordY + 2); cout << "| |   | '_ \\ / _` | '_ \\ / _` |/ _ \\";
    setPosition(changeCoordX, changeCoordY + 3); cout << "| |___| | | | (_| | | | | (_| |  __/";
    setPosition(changeCoordX, changeCoordY + 4); cout << " \\____|_| |_|\\__,_|_| |_|\\__, |\\___|";
    setPosition(changeCoordX, changeCoordY + 5); cout << "                         |___/";

    setColor(2);
    int okCoordX = consoleWidth / 2 + 1 + horizontalLineLength / 2 - 20,
        okCoordY = positionFromTop + 21;
    setPosition(okCoordX, okCoordY); cout << "    _    _ _                         _ _";
    setPosition(okCoordX, okCoordY + 1); cout << "   / \\  | | |   __ _  ___   ___   __| | |";
    setPosition(okCoordX, okCoordY + 2); cout << "  / _ \\ | | |  / _` |/ _ \\ / _ \\ / _` | |";
    setPosition(okCoordX, okCoordY + 3); cout << " / ___ \\| | | | (_| | (_) | (_) | (_| |_|";
    setPosition(okCoordX, okCoordY + 4); cout << "/_/   \\_\\_|_|  \\__, |\\___/ \\___/ \\__,_(_)";
    setPosition(okCoordX, okCoordY + 5); cout << "               |___/";

    setColor(15);
}

void draw_play(int indent2nd)
{
    int horizontalLineLength;
    for(int y = 0; y < 30; ++y) {
        setPosition(consoleWidth / 2 - 1, consoleHeight / 2 - 15 + y);
        cout << "  ";
        horizontalLineLength = consoleWidth / 2 - 1   -2;
        if(y == 15) cout << string(horizontalLineLength, ' ');
    }

    setColor(13);
    setPosition(indent2nd, positionFromTop - 1);
    cout << "   А     Б     В     Г     Д     Е     Ж     З     И     К";
    for(int i = 0; i < 10; ++i) {
        setPosition(indent2nd - 4, positionFromTop + 2 + i * 3);
        if(i != 9) cout << ' ';
        cout << i + 1;
    }

    setColor(11);
    setPosition(indent2nd, positionFromTop);
    cout << " _____ _____ _____ _____ _____ _____ _____ _____ _____ _____";
    for(int i = 1; i <= 10; ++i) {
        setPosition(indent2nd, positionFromTop + (i - 1) * 3 + 1);
        cout << "|";
        for(int j = 1; j <= 20; ++j) {
            if(j == 11) {
                setPosition(indent2nd, positionFromTop + (i - 1) * 3 + 2);
                cout << "|";
            }
            cout << "     |";
        }
        setPosition(indent2nd, positionFromTop + (i - 1) * 3 + 3);
        cout << "|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|";
    }
    setColor(15);
}

void draw_arrows(Field& field, string how)
{
    assert(how == "empty" || how == "green" || how == "red");
    if(how == "empty") {
        setPosition(field.zeroCoordPointerX - 2, positionFromTop - 3);
        cout << string(61, ' ');
    }
    else {
        char arrow = 25;
        int color;
        if(how == "green") color = 10;
        else if(how == "red") color = 4;
        setColor(color);
        setPosition(field.zeroCoordPointerX - 2, positionFromTop - 3);
        string arrows(61, arrow);
        for(int i = 0; i < arrows.size(); ++i) {
            if(i % 3) arrows[i] = ' ';
        }
        cout << arrows;
        setColor(11);
    }
}

void victory()
{
    draw_arrows(fEnemy, "empty");
    int indentX = consoleWidth / 2 - 18; // ширина слова == 36
    int indentY = consoleHeight / 3;
    setColor(10);
    setPosition(indentX, indentY); cout << "__     ___      _";
    setPosition(indentX, indentY + 1); cout << "\\ \\   / (_) ___| |_ ___  _ __ _   _";
    setPosition(indentX, indentY + 2); cout << " \\ \\ / /| |/ __| __/ _ \\| '__| | | |";
    setPosition(indentX, indentY + 3); cout << "  \\ V / | | (__| || (_) | |  | |_| |";
    setPosition(indentX, indentY + 4); cout << "   \\_/  |_|\\___|\\__\\___/|_|   \\__, |";
    setPosition(indentX, indentY + 5); cout << "                              |___/";
    setColor(15);
    _getch();
}

void loss()
{
    draw_arrows(fMe, "empty");
    int indentX = consoleWidth / 2 - 15; // ширина слова == 30
    int indentY = consoleHeight / 3;
    setColor(4);
    setPosition(indentX, indentY); cout << " _     ___  ____  _____ ____";
    setPosition(indentX, indentY + 1); cout << "| |   / _ \\/ ___|| ____|  _ \\";
    setPosition(indentX, indentY + 2); cout << "| |  | | | \\___ \\|  _| | |_) |";
    setPosition(indentX, indentY + 3); cout << "| |__| |_| |___) | |___|  _ <";
    setPosition(indentX, indentY + 4); cout << "|_____\\___/|____/|_____|_| \\_\\";
    setColor(15);
    _getch();
}

//void loss()
//{
//    int indentX = consoleWidth / 2 - 58; // ширина слова == 117
//    int indentY = consoleHeight / 2 - 12;
//    setColor(4);
//    setPosition(indentX + 10, indentY); cout << "_____           _______                   _____                    _____                    _____";
//    setPosition(indentX + 9, indentY + 1); cout << "/\\    \\         /::\\    \\                 /\\    \\                  /\\    \\                  /\\    \\";
//    setPosition(indentX + 8, indentY + 2); cout << "/::\\____\\       /::::\\    \\               /::\\    \\                /::\\    \\                /::\\    \\";
//    setPosition(indentX + 7, indentY + 3); cout << "/:::/    /      /::::::\\    \\             /::::\\    \\              /::::\\    \\              /::::\\    \\";
//    setPosition(indentX + 6, indentY + 4); cout << "/:::/    /      /::::::::\\    \\           /::::::\\    \\            /::::::\\    \\            /::::::\\    \\";
//    setPosition(indentX + 5, indentY + 5); cout << "/:::/    /      /:::/~~\\:::\\    \\         /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\";
//    setPosition(indentX + 4, indentY + 6); cout << "/:::/    /      /:::/    \\:::\\    \\       /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\";
//    setPosition(indentX + 3, indentY + 7); cout << "/:::/    /      /:::/    / \\:::\\    \\      \\:::\\   \\:::\\    \\      /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\";
//    setPosition(indentX + 2, indentY + 8); cout << "/:::/    /      /:::/____/   \\:::\\____\\   ___\\:::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\";
//    setPosition(indentX + 1, indentY + 9); cout << "/:::/    /      |:::|    |     |:::|    | /\\   \\:::\\   \\:::\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/\\:::\\   \\:::\\____\\";
//    setPosition(indentX, indentY + 10); cout << "/:::/____/       |:::|____|     |:::|    |/::\\   \\:::\\   \\:::\\____\\/:::/__\\:::\\   \\:::\\____\\/:::/  \\:::\\   \\:::|    |";
//    setPosition(indentX, indentY + 11); cout << "\\:::\\    \\        \\:::\\    \\   /:::/    / \\:::\\   \\:::\\   \\::/    /\\:::\\   \\:::\\   \\::/    /\\::/   |::::\\  /:::|____|";
//    setPosition(indentX + 1, indentY + 12); cout << "\\:::\\    \\        \\:::\\    \\ /:::/    /   \\:::\\   \\:::\\   \\/____/  \\:::\\   \\:::\\   \\/____/  \\/____|:::::\\/:::/    /";
//    setPosition(indentX + 2, indentY + 13); cout << "\\:::\\    \\        \\:::\\    /:::/    /     \\:::\\   \\:::\\    \\       \\:::\\   \\:::\\    \\            |:::::::::/    /";
//    setPosition(indentX + 3, indentY + 14); cout << "\\:::\\    \\        \\:::\\__/:::/    /       \\:::\\   \\:::\\____\\       \\:::\\   \\:::\\____\\           |::|\\::::/    /";
//    setPosition(indentX + 4, indentY + 15); cout << "\\:::\\    \\        \\::::::::/    /         \\:::\\  /:::/    /        \\:::\\   \\::/    /           |::| \\::/____/";
//    setPosition(indentX + 5, indentY + 16); cout << "\\:::\\    \\        \\::::::/    /           \\:::\\/:::/    /          \\:::\\   \\/____/            |::|  ~|";
//    setPosition(indentX + 6, indentY + 17); cout << "\\:::\\    \\        \\::::/    /             \\::::::/    /            \\:::\\    \\                |::|   |";
//    setPosition(indentX + 7, indentY + 18); cout << "\\:::\\____\\        \\::/____/               \\::::/    /              \\:::\\____\\               \\::|   |";
//    setPosition(indentX + 8, indentY + 19); cout << "\\::/    /         ~~                      \\::/    /                \\::/    /                \\:|   |";
//    setPosition(indentX + 9, indentY + 20); cout << "\\/____/                                   \\/____/                  \\/____/                  \\|___|";
//    setColor(15);
//}

void setConsole()
{
    // открытие консоли во весь экран
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    // установка размера текста в консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    CONSOLE_FONT_INFOEX fontInfo;
//    fontInfo.cbSize = sizeof(fontInfo);
//    GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
//    fontInfo.dwFontSize.Y = 24;
//    SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);

    getConsoleWH();
    positionFromTop = consoleHeight / 2 - 15   -1; // высота игрового поля == 30

    // установка размера буфера экрана равным текущему размеру окна
    COORD newScreenBufferSize;
    newScreenBufferSize.X = consoleWidth;
    newScreenBufferSize.Y = consoleHeight;
    if(!SetConsoleScreenBufferSize(hConsole, newScreenBufferSize)) {
        cout << "\nError in " << to_string(__LINE__) << " line: " << GetLastError();
        exit(-1);
    }

    // сделать курсор невидимым
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hConsole, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &structCursorInfo);
}

void getConsoleWH()
{
    HANDLE hWndConsole;
    if(hWndConsole = GetStdHandle(-12))
    {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if(GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
        {
            consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
            consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        }
        else exit(-1);
    }
    else exit(-1);
}
