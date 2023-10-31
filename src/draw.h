#pragma once
using namespace std;
extern void setPosition(int x, int y);
extern void setColor(int color);
extern int positionFromTop, nConsoleWidth, nConsoleHeight;

namespace draw
{

void EmptyField(int indentX, int indentY)
{
    setColor(11);
    setPosition(indentX, indentY);
    cout << " _____ _____ _____ _____ _____ _____ _____ _____ _____ _____";
    for(int i = 1; i <= 10; ++i) {
        setPosition(indentX, indentY + (i - 1) * 3 + 1);
        cout << "|";
        for(int j = 1; j <= 20; ++j) {
            if(j == 11) {
                setPosition(indentX, indentY + (i - 1) * 3 + 2);
                cout << "|";
            }
            cout << "     |";
        }
        setPosition(indentX, indentY + (i - 1) * 3 + 3);
        cout << "|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|";
    }
    setColor(15);
}

void CoordinatesToField(int indentX, int indentY)
{
    setColor(13);
    setPosition(indentX, indentY - 1);
    cout << "   А     Б     В     Г     Д     Е     Ж     З     И     К";
    for(int i = 0; i < 10; ++i) {
        setPosition(indentX - 4, (indentY + 2) + i * 3);
        if(i != 9) cout << ' ';
        cout << i + 1;
    }
    setColor(15);
}


namespace ships_arrangement
{

    int indentX_leftColumn, indentX_rightColumn, indentY_upper, indentY_middle, indentY_lower,
        width_leftColumn, width_rightColumn, heightOfCells, width_wordExit, width_wordAuto,
        width_wordClear, width_wordDone, indentX_wordExit, indentX_wordAuto, indentX_wordClear, indentX_wordDone;
    bool buttonClear_isActive, buttonDone_isActive;

    void setIndents()
    {
        indentX_leftColumn  = nConsoleWidth / 2;
        indentX_rightColumn = nConsoleWidth / 2 + 34;
        indentY_upper       = positionFromTop + 30 - 21;
        indentY_middle      = positionFromTop + 30 - 14;
        indentY_lower       = positionFromTop + 30 - 7;
        width_leftColumn    = 31;
        width_rightColumn   = 33;
        heightOfCells       = 8;
        width_wordExit      = 17;
        width_wordAuto      = 23;
        width_wordClear     = 25;
        width_wordDone      = 24;
        indentX_wordExit = indentX_leftColumn + (width_leftColumn / 2 - width_wordExit / 2);
        indentX_wordAuto = indentX_rightColumn + (width_rightColumn / 2 - width_wordAuto / 2);
        indentX_wordClear = indentX_rightColumn + (width_rightColumn / 2 - width_wordClear / 2);
        indentX_wordDone = indentX_rightColumn + (width_rightColumn / 2 - width_wordDone / 2);
        buttonClear_isActive = false;
        buttonDone_isActive = false;
    }

    void InstructionText(int indentX, int indentY, string write_or_clear)
    {
        assert(write_or_clear == "write" || write_or_clear == "clear");
        if(write_or_clear == "clear") setColor(0);
        else setColor(7);
        setPosition(indentX, indentY);
        cout << "Можно как расставить корабли вручную, так и довериться великому рандому. При ручной расстановке ";
        cout << "для добавления корабля необходимо";
        setPosition(indentX, indentY + 1);
        cout << "нажать левой кнопкой мыши на желаемое поле. Чтобы убрать корабль с клетки, нужно ";
        cout << "нажать на нее правой кнопкой мыши. Автоматической";
        setPosition(indentX, indentY + 2);
        cout << "расстановкой кораблей можно воспользоваться в любой момент (как и ручной), для этого следует ";
        cout << "нажать кнопку \"Auto\", воспользовавшись";
        setPosition(indentX, indentY + 3);
        cout << "мышкой. Чтобы начать игру, нажмите кнопку \"Done\". Данная кнопка будет неактивна, ";
        cout << "пока расположение кораблей не станет допустимым!";
        setColor(15);
    }

    void Buttons(string draw_or_clear)
    {
        assert(draw_or_clear == "draw" || draw_or_clear == "clear");
        setIndents();

        // walls
        if(draw_or_clear == "draw") setColor(68);
        else setColor(0);
        setPosition(indentX_leftColumn, indentY_lower);
        cout << string(width_leftColumn, 'w');
        setPosition(indentX_leftColumn, indentY_lower + 7);
        cout << string(width_leftColumn, 'w');
        for(int y = 0; y < heightOfCells; ++y) {
            setPosition(indentX_leftColumn, indentY_lower + y); cout << "ww";
            setPosition(indentX_leftColumn + width_leftColumn - 2, indentY_lower + y); cout << "ww";
        }
        if(draw_or_clear == "draw") setColor(34);
        else setColor(0);
        setPosition(indentX_rightColumn, indentY_upper);
        cout << string(width_rightColumn, 'w');
        setPosition(indentX_rightColumn, indentY_middle);
        cout << string(width_rightColumn, 'w');
        for(int y = indentY_upper + 1; y < indentY_middle; ++y) {
            setPosition(indentX_rightColumn, y); cout << "ww";
            setPosition(indentX_rightColumn + width_rightColumn - 2, y); cout << "ww";
        }
        if(draw_or_clear == "draw") setColor(136);
        else setColor(0);
        setPosition(indentX_rightColumn, indentY_lower);
        cout << string(width_rightColumn, 'w');
        setPosition(indentX_rightColumn, indentY_lower + 7);
        cout << string(width_rightColumn, 'w');
        for(int y = indentY_middle + 1; y < indentY_lower + 7; ++y) {
            setPosition(indentX_rightColumn, y); cout << "ww";
            setPosition(indentX_rightColumn + width_rightColumn - 2, y); cout << "ww";
        }

        // captions
        if(draw_or_clear == "draw") setColor(4);
        else setColor(0);
        setPosition(indentX_wordExit, indentY_lower + 1); cout << "           _ _";
        setPosition(indentX_wordExit, indentY_lower + 2); cout << "  _____  _(_) |_";
        setPosition(indentX_wordExit, indentY_lower + 3); cout << " / _ \\ \\/ / | __|";
        setPosition(indentX_wordExit, indentY_lower + 4); cout << "|  __/>  <| | |_";
        setPosition(indentX_wordExit, indentY_lower + 5); cout << " \\___/_/\\_\\_|\\__|";
        if(draw_or_clear == "draw") setColor(10);
        else setColor(0);
        setPosition(indentX_wordAuto, indentY_upper + 1); cout << "    _         _";
        setPosition(indentX_wordAuto, indentY_upper + 2); cout << "   / \\  _   _| |_ ___";
        setPosition(indentX_wordAuto, indentY_upper + 3); cout << "  / _ \\| | | | __/ _ \\";
        setPosition(indentX_wordAuto, indentY_upper + 4); cout << " / ___ \\ |_| | || (_) |";
        setPosition(indentX_wordAuto, indentY_upper + 5); cout << "/_/   \\_\\__,_|\\__\\___/";
        if(draw_or_clear == "draw") setColor(8);
        else setColor(0);
        setPosition(indentX_wordClear, indentY_middle + 1); cout << "  ____ _";
        setPosition(indentX_wordClear, indentY_middle + 2); cout << " / ___| | ___  __ _ _ __";
        setPosition(indentX_wordClear, indentY_middle + 3); cout << "| |   | |/ _ \\/ _` | '__|";
        setPosition(indentX_wordClear, indentY_middle + 4); cout << "| |___| |  __/ (_| | |";
        setPosition(indentX_wordClear, indentY_middle + 5); cout << " \\____|_|\\___|\\__,_|_|";
        setPosition(indentX_wordDone, indentY_lower + 1); cout << " ____";
        setPosition(indentX_wordDone, indentY_lower + 2); cout << "|  _ \\  ___  _ __   ___";
        setPosition(indentX_wordDone, indentY_lower + 3); cout << "| | | |/ _ \\| '_ \\ / _ \\";
        setPosition(indentX_wordDone, indentY_lower + 4); cout << "| |_| | (_) | | | |  __/";
        setPosition(indentX_wordDone, indentY_lower + 5); cout << "|____/ \\___/|_| |_|\\___|";
        setColor(15);
    }

    void ButtonClear(bool activate)
    {
        // wall
        if(activate) setColor(34);
        else setColor(136);
        for(int y = indentY_middle + 1; y < indentY_lower; ++y) {
            setPosition(indentX_rightColumn, y); cout << "ww";
            setPosition(indentX_rightColumn + width_rightColumn - 2, y); cout << "ww";
        }
        if(!buttonDone_isActive) {
            setPosition(indentX_rightColumn, indentY_lower);
            cout << string(width_rightColumn, 'w');
        }
        //caption
        if(activate) setColor(10);
        else setColor(8);
        setPosition(indentX_wordClear, indentY_middle + 1); cout << "  ____ _";
        setPosition(indentX_wordClear, indentY_middle + 2); cout << " / ___| | ___  __ _ _ __";
        setPosition(indentX_wordClear, indentY_middle + 3); cout << "| |   | |/ _ \\/ _` | '__|";
        setPosition(indentX_wordClear, indentY_middle + 4); cout << "| |___| |  __/ (_| | |";
        setPosition(indentX_wordClear, indentY_middle + 5); cout << " \\____|_|\\___|\\__,_|_|";
        setColor(15);
    }

    void ButtonDone(bool activate)
    {
        // wall
        if(activate) setColor(34);
        else setColor(136);
        if(!buttonClear_isActive) {
            setPosition(indentX_rightColumn, indentY_lower);
            cout << string(width_rightColumn, 'w');
        }
        for(int y = indentY_lower + 1; y < indentY_lower + 7; ++y) {
            setPosition(indentX_rightColumn, y); cout << "ww";
            setPosition(indentX_rightColumn + width_rightColumn - 2, y); cout << "ww";
        }
        setPosition(indentX_rightColumn, indentY_lower + 7);
        cout << string(width_rightColumn, 'w');
        //caption
        if(activate) setColor(10);
        else setColor(8);
        setPosition(indentX_wordDone, indentY_lower + 1); cout << " ____";
        setPosition(indentX_wordDone, indentY_lower + 2); cout << "|  _ \\  ___  _ __   ___";
        setPosition(indentX_wordDone, indentY_lower + 3); cout << "| | | |/ _ \\| '_ \\ / _ \\";
        setPosition(indentX_wordDone, indentY_lower + 4); cout << "| |_| | (_) | | | |  __/";
        setPosition(indentX_wordDone, indentY_lower + 5); cout << "|____/ \\___/|_| |_|\\___|";
        setColor(15);
    }

} // namespace ships_arrangement


void MoveIndicatingArrows(int fieldIndentX, string how)
{
    assert(how == "empty" || how == "green" || how == "red");
    if(how == "empty") {
        setPosition(fieldIndentX, positionFromTop - 3);
        cout << string(61, ' ');
    }
    else {
        char arrow = 25;
        int color = 0;
        if(how == "green") color = 10;
        else if(how == "red") color = 4;
        setColor(color);
        setPosition(fieldIndentX, positionFromTop - 3);
        string arrows(61, arrow);
        for(int i = 0; i < arrows.size(); ++i) {
            if(i % 3) arrows[i] = ' ';
        }
        cout << arrows;
        setColor(11);
    }
}

void Victory()
{
    int indentX = nConsoleWidth / 2 - 19;  // ширина слова == 38
    int indentY = nConsoleHeight / 3;
    setColor(10);
    setPosition(indentX, indentY); cout << "__     ___      _                   _";
    setPosition(indentX, indentY + 1); cout << "\\ \\   / (_) ___| |_ ___  _ __ _   _| | ";
    setPosition(indentX, indentY + 2); cout << " \\ \\ / /| |/ __| __/ _ \\| '__| | | | | ";
    setPosition(indentX, indentY + 3); cout << "  \\ V / | | (__| || (_) | |  | |_| |_| ";
    setPosition(indentX, indentY + 4); cout << "   \\_/  |_|\\___|\\__\\___/|_|   \\__, (_) ";
    setPosition(indentX, indentY + 5); cout << "                              |___/";
    setPosition(indentX, indentY + 6); cout << string(36, ' ');
    setColor(15);
}

void Loss()
{
    int indentX = nConsoleWidth / 2 - 16;  // ширина слова == 32
    int indentY = nConsoleHeight / 3;
    setColor(4);
    setPosition(indentX, indentY); cout << "  _     ___  ____  _____ ____ ";
    setPosition(indentX, indentY + 1); cout << " | |   / _ \\/ ___|| ____|  _ \\ ";
    setPosition(indentX, indentY + 2); cout << " | |  | | | \\___ \\|  _| | |_) | ";
    setPosition(indentX, indentY + 3); cout << " | |__| |_| |___) | |___|  _ < ";
    setPosition(indentX, indentY + 4); cout << " |_____\\___/|____/|_____|_| \\_\\ ";
    setColor(15);
}

}  // namespace draw
