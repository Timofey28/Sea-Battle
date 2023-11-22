#pragma once
using namespace std;
extern void setPosition(int x, int y);
extern void setColor(int color);
extern int positionFromTop, nConsoleWidth, nConsoleHeight;

namespace draw
{

int wallLeftEdgeCoordX;
void GameModeSelection()
{
    system("cls");
    setColor(187);
    wallLeftEdgeCoordX = nConsoleWidth / 2 - 1;
    for(int y = 3; y < nConsoleHeight - 3; ++y) {
        setPosition(wallLeftEdgeCoordX, y);
        cout << "ww";
    }

    setColor(11);
    int indentY_number = nConsoleHeight / 2 - 9,
        indentY_word   = indentY_number + 5;
    int indentX_number1  = nConsoleWidth / 4 - 1,
        indentX_1player  = nConsoleWidth / 4 - 15,
        indentX_number2  = nConsoleWidth * 3 / 4 - 3,
        indentX_2players = nConsoleWidth * 3 / 4 - 17;

    int indentX = indentX_number1,
        indentY = indentY_number;
    setPosition(indentX, indentY + 0); cout << " _";
    setPosition(indentX, indentY + 1); cout << "/ |";
    setPosition(indentX, indentY + 2); cout << "| |";
    setPosition(indentX, indentY + 3); cout << "| |";
    setPosition(indentX, indentY + 4); cout << "|_|";
    indentX = indentX_1player;
    indentY = indentY_word;
    setPosition(indentX, indentY + 0); cout << "       _";
    setPosition(indentX, indentY + 1); cout << " _ __ | | __ _ _   _  ___ _ __";
    setPosition(indentX, indentY + 2); cout << "| '_ \\| |/ _` | | | |/ _ \\ '__|";
    setPosition(indentX, indentY + 3); cout << "| |_) | | (_| | |_| |  __/ |";
    setPosition(indentX, indentY + 4); cout << "| .__/|_|\\__,_|\\__, |\\___|_|";
    setPosition(indentX, indentY + 5); cout << "|_|            |___/";

    indentX = indentX_number2;
    indentY = indentY_number;
    setPosition(indentX, indentY + 0); cout << " ____";
    setPosition(indentX, indentY + 1); cout << "|___ \\";
    setPosition(indentX, indentY + 2); cout << "  __) |";
    setPosition(indentX, indentY + 3); cout << " / __/";
    setPosition(indentX, indentY + 4); cout << "|_____|";
    indentX = indentX_2players;
    indentY = indentY_word;
    setPosition(indentX, indentY + 0); cout << "       _";
    setPosition(indentX, indentY + 1); cout << " _ __ | | __ _ _   _  ___ _ __ ___";
    setPosition(indentX, indentY + 2); cout << "| '_ \\| |/ _` | | | |/ _ \\ '__/ __|";
    setPosition(indentX, indentY + 3); cout << "| |_) | | (_| | |_| |  __/ |  \\__ \\";
    setPosition(indentX, indentY + 4); cout << "| .__/|_|\\__,_|\\__, |\\___|_|  |___/";
    setPosition(indentX, indentY + 5); cout << "|_|            |___/";
}

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

void CoordinatesToRightField(int indentX, int indentY)
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

void CoordinatesToBothFields(int indentX1, int indentX2, int indentY)
{
    setColor(13);
    setPosition(indentX1, indentY - 1);
    cout << "   А     Б     В     Г     Д     Е     Ж     З     И     К";
    setPosition(indentX2, indentY - 1);
    cout << "   А     Б     В     Г     Д     Е     Ж     З     И     К";
    for(int i = 0; i < 10; ++i) {
        setPosition(nConsoleWidth / 2 - 1, (indentY + 2) + i * 3);
        if(i != 9) cout << ' ';
        cout << i + 1;
    }
    setColor(15);
}


namespace ships_arrangement
{

    int indentX_leftColumn, indentX_rightColumn, indentY_upper, indentY_middle, indentY_lower, width_leftColumn,
        width_rightColumn, heightOfCells, indentX_wordBack, width_wordBack, width_wordExit, width_wordAuto,
        width_wordClear, width_wordDone, indentX_wordExit, indentX_wordAuto, indentX_wordClear, indentX_wordDone,
        width_wordHelp, indentX_wordHelp, indentY_wordHelp, indentX_remainingShips, indentY_remainingShips,
        previousAmount_1deckShips, previousAmount_2deckShips, previousAmount_3deckShips, previousAmount_4deckShips,
        deckSize, widthBetweenShips, localIndentX_4deckShipLine, localIndentX_3deckShipsLine,
        localIndentX_2deckShipsLine, localIndentX_1deckShipsLine;
    bool buttonClear_isActive = false,
         buttonDone_isActive  = false;

    int getShipsWidth(int decksAmount, int shipsAmount);

    void setIndents()
    {
        indentX_leftColumn  = nConsoleWidth / 2;
        indentX_rightColumn = nConsoleWidth / 2 + 34;
        indentY_wordHelp    = positionFromTop + 1;
        indentY_upper       = positionFromTop + 30 - 21;
        indentY_middle      = positionFromTop + 30 - 14;
        indentY_lower       = positionFromTop + 30 - 7;
        width_leftColumn    = 31;
        width_rightColumn   = 33;
        heightOfCells       = 8;
        width_wordHelp      = 20;
        width_wordBack      = 23;
        width_wordExit      = 17;
        width_wordAuto      = 23;
        width_wordClear     = 25;
        width_wordDone      = 24;
        indentX_wordHelp = indentX_rightColumn + (width_rightColumn / 2 - width_wordHelp / 2);
        indentX_wordBack = indentX_leftColumn + (width_leftColumn / 2 - width_wordBack / 2);
        indentX_wordExit = indentX_leftColumn + (width_leftColumn / 2 - width_wordExit / 2);
        indentX_wordAuto = indentX_rightColumn + (width_rightColumn / 2 - width_wordAuto / 2);
        indentX_wordClear = indentX_rightColumn + (width_rightColumn / 2 - width_wordClear / 2);
        indentX_wordDone = indentX_rightColumn + (width_rightColumn / 2 - width_wordDone / 2);
        indentX_remainingShips = indentX_leftColumn;
        indentY_remainingShips = 10;
        deckSize = 3;
        widthBetweenShips = 4;
        int widestShipLine = max(getShipsWidth(4, 1), max(getShipsWidth(3, 2), max(getShipsWidth(2, 3), getShipsWidth(1, 4))));
        localIndentX_4deckShipLine = widestShipLine / 2 - getShipsWidth(4, 1) / 2;
        localIndentX_3deckShipsLine = widestShipLine / 2 - getShipsWidth(3, 2) / 2;
        localIndentX_2deckShipsLine = widestShipLine / 2 - getShipsWidth(2, 3) / 2;
        localIndentX_1deckShipsLine = widestShipLine / 2 - getShipsWidth(1, 4) / 2;
    }

    void ResetShipsAmounts(int d1 = 0, int d2 = 0, int d3 = 0, int d4 = 0)
    {
        previousAmount_1deckShips = d1;
        previousAmount_2deckShips = d2;
        previousAmount_3deckShips = d3;
        previousAmount_4deckShips = d4;
    }

    int getShipsWidth(int decksAmount, int shipsAmount)
    {
        assert(decksAmount == 1 || decksAmount == 2 || decksAmount == 3 || decksAmount == 4);
        if(!shipsAmount) return 0;
        return (decksAmount * deckSize + decksAmount - 1) * shipsAmount + (shipsAmount - 1) * widthBetweenShips;
    }

    void RemainingShips(string draw_or_clear_or_redraw, int amount_1deckShips = 4, int amount_2deckShips = 3,
                        int amount_3deckShips = 2, int amount_4deckShips = 1)
    {
        assert(draw_or_clear_or_redraw == "draw" || draw_or_clear_or_redraw == "clear" || draw_or_clear_or_redraw == "redraw");
        int shipsColor = 102;
        if(draw_or_clear_or_redraw == "clear") {
            setColor(0);
            setPosition(indentX_remainingShips + localIndentX_4deckShipLine, indentY_remainingShips);
            cout << string(getShipsWidth(4, 1), ' ');
            setPosition(indentX_remainingShips + localIndentX_3deckShipsLine, indentY_remainingShips + 2);
            cout << string(getShipsWidth(3, 2), ' ');
            setPosition(indentX_remainingShips + localIndentX_2deckShipsLine, indentY_remainingShips + 4);
            cout << string(getShipsWidth(2, 3), ' ');
            setPosition(indentX_remainingShips + localIndentX_1deckShipsLine, indentY_remainingShips + 6);
            cout << string(getShipsWidth(1, 4), ' ');
        }
        else if(draw_or_clear_or_redraw == "redraw") {
            setColor(shipsColor);
            if(previousAmount_4deckShips) {
                int startFrom = indentX_remainingShips + localIndentX_4deckShipLine;
                setPosition(startFrom, indentY_remainingShips);
                cout << string(deckSize, 'd');
                setPosition(startFrom + deckSize + 1, indentY_remainingShips);
                cout << string(deckSize, 'd');
                setPosition(startFrom + (deckSize + 1) * 2, indentY_remainingShips);
                cout << string(deckSize, 'd');
                setPosition(startFrom + (deckSize + 1) * 3, indentY_remainingShips);
                cout << string(deckSize, 'd');
            }
            for(int i = 0; i < previousAmount_3deckShips; ++i) {
                int startFrom = indentX_remainingShips + getShipsWidth(3, i+1) - getShipsWidth(3, 1) + localIndentX_3deckShipsLine;
                setPosition(startFrom, indentY_remainingShips + 2);
                cout << string(deckSize, 'd');
                setPosition(startFrom + deckSize + 1, indentY_remainingShips + 2);
                cout << string(deckSize, 'd');
                setPosition(startFrom + (deckSize + 1) * 2, indentY_remainingShips + 2);
                cout << string(deckSize, 'd');
            }
            for(int i = 0; i < previousAmount_2deckShips; ++i) {
                int startFrom = indentX_remainingShips + getShipsWidth(2, i+1) - getShipsWidth(2, 1) + localIndentX_2deckShipsLine;
                setPosition(startFrom, indentY_remainingShips + 4);
                cout << string(deckSize, 'd');
                setPosition(startFrom + deckSize + 1, indentY_remainingShips + 4);
                cout << string(deckSize, 'd');
            }
            for(int i = 0; i < previousAmount_1deckShips; ++i) {
                int startFrom = indentX_remainingShips + getShipsWidth(1, i+1) - getShipsWidth(1, 1) + localIndentX_1deckShipsLine;
                setPosition(startFrom, indentY_remainingShips + 6);
                cout << string(deckSize, 'd');
            }
        }
        else {
            if(amount_4deckShips != previousAmount_4deckShips) {
                if(amount_4deckShips) {
                    setColor(shipsColor);
                    int startFrom = indentX_remainingShips + localIndentX_4deckShipLine;
                    setPosition(startFrom, indentY_remainingShips);
                    cout << string(deckSize, 'd');
                    setPosition(startFrom + deckSize + 1, indentY_remainingShips);
                    cout << string(deckSize, 'd');
                    setPosition(startFrom + (deckSize + 1) * 2, indentY_remainingShips);
                    cout << string(deckSize, 'd');
                    setPosition(startFrom + (deckSize + 1) * 3, indentY_remainingShips);
                    cout << string(deckSize, 'd');
                }
                else {
                    setColor(0);
                    setPosition(indentX_remainingShips + localIndentX_4deckShipLine, indentY_remainingShips);
                    cout << string(getShipsWidth(4, 1), ' ');
                }
            }

            if(amount_3deckShips != previousAmount_3deckShips) {
                if(amount_3deckShips > previousAmount_3deckShips) {
                    setColor(shipsColor);
                    int startFrom = indentX_remainingShips + getShipsWidth(3, previousAmount_3deckShips) + localIndentX_3deckShipsLine;
                    if(previousAmount_3deckShips) startFrom += widthBetweenShips;
                    for(int i = 0; i < amount_3deckShips - previousAmount_3deckShips; ++i) {
                        setPosition(startFrom + getShipsWidth(3, i+1) - getShipsWidth(3, 1), indentY_remainingShips + 2);
                        cout << string(deckSize, 'd');
                        setPosition(startFrom + getShipsWidth(3, i+1) - getShipsWidth(3, 1) + deckSize + 1, indentY_remainingShips + 2);
                        cout << string(deckSize, 'd');
                        setPosition(startFrom + getShipsWidth(3, i+1) - getShipsWidth(3, 1) + (deckSize + 1) * 2, indentY_remainingShips + 2);
                        cout << string(deckSize, 'd');
                    }
                }
                else {
                    setColor(0);
                    int startFrom = indentX_remainingShips + getShipsWidth(3, amount_3deckShips) + localIndentX_3deckShipsLine;
                    if(amount_3deckShips) startFrom += widthBetweenShips;
                    setPosition(startFrom, indentY_remainingShips + 2);
                    int spacesAmount = getShipsWidth(3, previousAmount_3deckShips - amount_3deckShips);
                    cout << string(spacesAmount, ' ');
                }
            }

            if(amount_2deckShips != previousAmount_2deckShips) {
                if(amount_2deckShips > previousAmount_2deckShips) {
                    setColor(shipsColor);
                    int startFrom = indentX_remainingShips + getShipsWidth(2, previousAmount_2deckShips) + localIndentX_2deckShipsLine;
                    if(previousAmount_2deckShips) startFrom += widthBetweenShips;
                    for(int i = 0; i < amount_2deckShips - previousAmount_2deckShips; ++i) {
                        setPosition(startFrom + getShipsWidth(2, i+1) - getShipsWidth(2, 1), indentY_remainingShips + 4);
                        cout << string(deckSize, 'd');
                        setPosition(startFrom + getShipsWidth(2, i+1) - getShipsWidth(2, 1) + deckSize + 1, indentY_remainingShips + 4);
                        cout << string(deckSize, 'd');
                    }
                }
                else {
                    setColor(0);
                    int startFrom = indentX_remainingShips + getShipsWidth(2, amount_2deckShips) + localIndentX_2deckShipsLine;
                    if(amount_2deckShips) startFrom += widthBetweenShips;
                    setPosition(startFrom, indentY_remainingShips + 4);
                    int spacesAmount = getShipsWidth(2, previousAmount_2deckShips - amount_2deckShips);
                    cout << string(spacesAmount, ' ');
                }
            }

            if(amount_1deckShips != previousAmount_1deckShips) {
                if(amount_1deckShips > previousAmount_1deckShips) {
                    setColor(shipsColor);
                    int startFrom = indentX_remainingShips + getShipsWidth(1, previousAmount_1deckShips) + localIndentX_1deckShipsLine;
                    if(previousAmount_1deckShips) startFrom += widthBetweenShips;
                    for(int i = 0; i < amount_1deckShips - previousAmount_1deckShips; ++i) {
                        setPosition(startFrom + getShipsWidth(1, i+1) - getShipsWidth(1, 1), indentY_remainingShips + 6);
                        cout << string(deckSize, 'd');
                    }
                }
                else {
                    setColor(0);
                    int startFrom = indentX_remainingShips + getShipsWidth(1, amount_1deckShips) + localIndentX_1deckShipsLine;
                    if(amount_1deckShips) startFrom += widthBetweenShips;
                    setPosition(startFrom, indentY_remainingShips + 6);
                    int spacesAmount = getShipsWidth(1, previousAmount_1deckShips - amount_1deckShips);
                    cout << string(spacesAmount, ' ');
                }
            }
        }
        if(draw_or_clear_or_redraw == "draw") {
            previousAmount_1deckShips = amount_1deckShips;
            previousAmount_2deckShips = amount_2deckShips;
            previousAmount_3deckShips = amount_3deckShips;
            previousAmount_4deckShips = amount_4deckShips;
        }
        setColor(15);
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

    void Phrase_invalidSet(string write_or_clear)
    {
        assert(write_or_clear == "write" || write_or_clear == "clear");
        int indentX = indentX_leftColumn + 1,
            indentY = 9;
        if(write_or_clear == "clear") setColor(0);
        else setColor(4);
        setPosition(indentX, indentY + 0); cout << " _                 _ _     _";
        setPosition(indentX, indentY + 1); cout << "(_)_ ____   ____ _| (_) __| |";
        setPosition(indentX, indentY + 2); cout << "| | '_ \\ \\ / / _` | | |/ _` |";
        setPosition(indentX, indentY + 3); cout << "| | | | \\ V / (_| | | | (_| |";
        setPosition(indentX, indentY + 4); cout << "|_|_| |_|\\_/ \\__,_|_|_|\\__,_|";
        setPosition(indentX, indentY + 5); cout << "        ___  ___| |_";
        setPosition(indentX, indentY + 6); cout << "       / __|/ _ \\ __|";
        setPosition(indentX, indentY + 7); cout << "       \\__ \\  __/ |_";
        setPosition(indentX, indentY + 8); cout << "       |___/\\___|\\__|";
        setColor(15);
    }

    void Phrase_ArrangeYourShips(string write_or_clear)
    {
        int phraseWidth = 92;
        int indentX = nConsoleWidth / 2 - phraseWidth / 2, indentY = 0;
        assert(write_or_clear == "write" || write_or_clear == "clear" || write_or_clear == "draw");
        if(write_or_clear == "clear") setColor(0);
        else setColor(6);
        setPosition(indentX, indentY + 0); cout << "    _                                                                   _     _           _";
        setPosition(indentX, indentY + 1); cout << "   / \\   _ __ _ __ __ _ _ __   __ _  ___   _   _  ___  _   _ _ __   ___| |__ (_)_ __  ___| |";
        setPosition(indentX, indentY + 2); cout << "  / _ \\ | '__| '__/ _` | '_ \\ / _` |/ _ \\ | | | |/ _ \\| | | | '__| / __| '_ \\| | '_ \\/ __| |";
        setPosition(indentX, indentY + 3); cout << " / ___ \\| |  | | | (_| | | | | (_| |  __/ | |_| | (_) | |_| | |    \\__ \\ | | | | |_) \\__ \\_|";
        setPosition(indentX, indentY + 4); cout << "/_/   \\_\\_|  |_|  \\__,_|_| |_|\\__, |\\___|  \\__, |\\___/ \\__,_|_|    |___/_| |_|_| .__/|___(_)";
        setPosition(indentX, indentY + 5); cout << "                              |___/        |___/                               |_|";
    }

    void Phrase_PlayerOnTheLeft(string write_or_clear)
    {
        int phraseWidth = 79;
        int indentX = nConsoleWidth / 2 - phraseWidth / 2, indentY = 0;
        assert(write_or_clear == "write" || write_or_clear == "clear" || write_or_clear == "draw");
        if(write_or_clear == "clear") setColor(0);
        else setColor(6);
        setPosition(indentX, indentY + 0); cout << " ____  _                                       _   _            _       __ _";
        setPosition(indentX, indentY + 1); cout << "|  _ \\| | __ _ _   _  ___ _ __    ___  _ __   | |_| |__   ___  | | ___ / _| |_";
        setPosition(indentX, indentY + 2); cout << "| |_) | |/ _` | | | |/ _ \\ '__|  / _ \\| '_ \\  | __| '_ \\ / _ \\ | |/ _ \\ |_| __|";
        setPosition(indentX, indentY + 3); cout << "|  __/| | (_| | |_| |  __/ |    | (_) | | | | | |_| | | |  __/ | |  __/  _| |_";
        setPosition(indentX, indentY + 4); cout << "|_|   |_|\\__,_|\\__, |\\___|_|     \\___/|_| |_|  \\__|_| |_|\\___| |_|\\___|_|  \\__|";
        setPosition(indentX, indentY + 5); cout << "               |___/";
    }

    void Phrase_PlayerOnTheRight(string write_or_clear)
    {
        int phraseWidth = 88;
        int indentX = nConsoleWidth / 2 - phraseWidth / 2, indentY = 0;
        assert(write_or_clear == "write" || write_or_clear == "clear" || write_or_clear == "draw");
        if(write_or_clear == "clear") setColor(0);
        else setColor(6);
        setPosition(indentX, indentY + 0); cout << " ____  _                                       _   _                 _       _     _";
        setPosition(indentX, indentY + 1); cout << "|  _ \\| | __ _ _   _  ___ _ __    ___  _ __   | |_| |__   ___   _ __(_) __ _| |__ | |_";
        setPosition(indentX, indentY + 2); cout << "| |_) | |/ _` | | | |/ _ \\ '__|  / _ \\| '_ \\  | __| '_ \\ / _ \\ | '__| |/ _` | '_ \\| __|";
        setPosition(indentX, indentY + 3); cout << "|  __/| | (_| | |_| |  __/ |    | (_) | | | | | |_| | | |  __/ | |  | | (_| | | | | |_";
        setPosition(indentX, indentY + 4); cout << "|_|   |_|\\__,_|\\__, |\\___|_|     \\___/|_| |_|  \\__|_| |_|\\___| |_|  |_|\\__, |_| |_|\\__|";
        setPosition(indentX, indentY + 5); cout << "               |___/                                                   |___/";
    }

    void Buttons(string draw_or_clear)
    {
        assert(draw_or_clear == "draw" || draw_or_clear == "clear");
        setIndents();
        setColor(0);

        // walls
        if(draw_or_clear == "draw") setColor(68);  // red
        setPosition(indentX_leftColumn, indentY_middle);
        cout << string(width_leftColumn, 'w');
        setPosition(indentX_leftColumn, indentY_lower);
        cout << string(width_leftColumn, 'w');
        setPosition(indentX_leftColumn, indentY_lower + 7);
        cout << string(width_leftColumn, 'w');
        for(int y = indentY_middle + 1; y < indentY_lower + 7; ++y) {
            setPosition(indentX_leftColumn, y); cout << "ww";
            setPosition(indentX_leftColumn + width_leftColumn - 2, y); cout << "ww";
        }

        if(draw_or_clear == "draw") setColor(153);  // blue
        setPosition(indentX_rightColumn, indentY_wordHelp);
        cout << string(width_rightColumn, 'w');
        for(int y = indentY_wordHelp + 1; y < indentY_upper; ++y) {
            setPosition(indentX_rightColumn, y); cout << "ww";
            setPosition(indentX_rightColumn + width_rightColumn - 2, y); cout << "ww";
        }

        if(draw_or_clear == "draw") setColor(34);  // green
        setPosition(indentX_rightColumn, indentY_upper);
        cout << string(width_rightColumn, 'w');
        setPosition(indentX_rightColumn, indentY_middle);
        cout << string(width_rightColumn, 'w');
        for(int y = indentY_upper + 1; y < indentY_middle; ++y) {
            setPosition(indentX_rightColumn, y); cout << "ww";
            setPosition(indentX_rightColumn + width_rightColumn - 2, y); cout << "ww";
        }

        if(draw_or_clear == "draw") {
            if(buttonClear_isActive) setColor(34);  // green
            else setColor(136);  // grey
        }
        setPosition(indentX_rightColumn, indentY_lower);
        cout << string(width_rightColumn, 'w');
        for(int y = indentY_middle + 1; y < indentY_lower; ++y) {
            setPosition(indentX_rightColumn, y); cout << "ww";
            setPosition(indentX_rightColumn + width_rightColumn - 2, y); cout << "ww";
        }
        if(draw_or_clear == "draw") {
            if(buttonDone_isActive) setColor(34);  // green
            else setColor(136);  // grey
        }
        setPosition(indentX_rightColumn, indentY_lower + 7);
        cout << string(width_rightColumn, 'w');
        for(int y = indentY_lower + 1; y < indentY_lower + 7; ++y) {
            setPosition(indentX_rightColumn, y); cout << "ww";
            setPosition(indentX_rightColumn + width_rightColumn - 2, y); cout << "ww";
        }

        // captions
        int indentX, indentY;
        if(draw_or_clear == "draw") setColor(4);  // red
        indentX = indentX_wordBack;
        indentY = indentY_middle + 1;
        setPosition(indentX, indentY + 0); cout << " _                _";
        setPosition(indentX, indentY + 1); cout << "| |__   __ _  ___| | __";
        setPosition(indentX, indentY + 2); cout << "| '_ \\ / _` |/ __| |/ /";
        setPosition(indentX, indentY + 3); cout << "| |_) | (_| | (__|   <";
        setPosition(indentX, indentY + 4); cout << "|_.__/ \\__,_|\\___|_|\\_\\";
        indentX = indentX_wordExit;
        indentY = indentY_lower + 1;
        setPosition(indentX, indentY + 0); cout << "           _ _";
        setPosition(indentX, indentY + 1); cout << "  _____  _(_) |_";
        setPosition(indentX, indentY + 2); cout << " / _ \\ \\/ / | __|";
        setPosition(indentX, indentY + 3); cout << "|  __/>  <| | |_";
        setPosition(indentX, indentY + 4); cout << " \\___/_/\\_\\_|\\__|";
        if(draw_or_clear == "draw") setColor(9);  // blue
        indentX = indentX_wordHelp;
        indentY = indentY_wordHelp + 1;
        setPosition(indentX, indentY + 0); cout << " _          _";
        setPosition(indentX, indentY + 1); cout << "| |__   ___| |_ __";
        setPosition(indentX, indentY + 2); cout << "| '_ \\ / _ \\ | '_ \\";
        setPosition(indentX, indentY + 3); cout << "| | | |  __/ | |_) |";
        setPosition(indentX, indentY + 4); cout << "|_| |_|\\___|_| .__/";
        setPosition(indentX, indentY + 5); cout << "             |_|";
        if(draw_or_clear == "draw") setColor(10);  // green
        indentX = indentX_wordAuto;
        indentY = indentY_upper + 1;
        setPosition(indentX, indentY + 0); cout << "    _         _";
        setPosition(indentX, indentY + 1); cout << "   / \\  _   _| |_ ___";
        setPosition(indentX, indentY + 2); cout << "  / _ \\| | | | __/ _ \\";
        setPosition(indentX, indentY + 3); cout << " / ___ \\ |_| | || (_) |";
        setPosition(indentX, indentY + 4); cout << "/_/   \\_\\__,_|\\__\\___/";
        if(draw_or_clear == "draw") {
            if(buttonClear_isActive) setColor(10);  // green
            else setColor(8);  // grey
        }
        indentX = indentX_wordClear;
        indentY = indentY_middle + 1;
        setPosition(indentX, indentY + 0); cout << "  ____ _";
        setPosition(indentX, indentY + 1); cout << " / ___| | ___  __ _ _ __";
        setPosition(indentX, indentY + 2); cout << "| |   | |/ _ \\/ _` | '__|";
        setPosition(indentX, indentY + 3); cout << "| |___| |  __/ (_| | |";
        setPosition(indentX, indentY + 4); cout << " \\____|_|\\___|\\__,_|_|";
        if(draw_or_clear == "draw") {
            if(buttonDone_isActive) setColor(10); // green
            else setColor(8);  // grey
        }
        indentX = indentX_wordDone;
        indentY = indentY_lower + 1;
        setPosition(indentX, indentY + 0); cout << " ____";
        setPosition(indentX, indentY + 1); cout << "|  _ \\  ___  _ __   ___";
        setPosition(indentX, indentY + 2); cout << "| | | |/ _ \\| '_ \\ / _ \\";
        setPosition(indentX, indentY + 3); cout << "| |_| | (_) | | | |  __/";
        setPosition(indentX, indentY + 4); cout << "|____/ \\___/|_| |_|\\___|";
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

}  // namespace ships_arrangement


void MoveIndicatingArrows(int fieldIndentX, string how, bool gameForTwo = 0)
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
        if(gameForTwo) {
            string phrase;
            if(fieldIndentX < nConsoleWidth / 2) phrase = "Ходит игрок справа ";
            else phrase = " Ходит игрок слева ";
            setPosition(fieldIndentX + 30 - phrase.size() / 2, positionFromTop - 3);
            cout << phrase;
        }
        setColor(11);
    }
}

void Victory(bool singleGame, int whoWon = 0)
{
    assert(singleGame == true  && whoWon == 0 ||
           singleGame == false && (whoWon == 1 || whoWon == 2));
    int indentX, indentY;
    if(singleGame) {
        indentX = nConsoleWidth / 2 - 19;  // ширина слова == 38
        indentY = nConsoleHeight / 3;
    }
    else {
        if(whoWon == 1) indentX = nConsoleWidth / 4 - 19;
        else indentX = nConsoleWidth * 3 / 4 - 19;
        indentY = 2;
    }
    setColor(10);
    setPosition(indentX, indentY); cout << "__     ___      _                   _";
    setPosition(indentX, indentY + 1); cout << "\\ \\   / (_) ___| |_ ___  _ __ _   _| | ";
    setPosition(indentX, indentY + 2); cout << " \\ \\ / /| |/ __| __/ _ \\| '__| | | | | ";
    setPosition(indentX, indentY + 3); cout << "  \\ V / | | (__| || (_) | |  | |_| |_| ";
    setPosition(indentX + 1, indentY + 4); cout << "  \\_/  |_|\\___|\\__\\___/|_|   \\__, (_)  ";
    setPosition(indentX + 2, indentY + 5); cout << "                            |___/ ";
    if(singleGame) setPosition(indentX, indentY + 6); cout << string(36, ' ');
    setColor(15);
}

void Loss(bool singleGame, int whoLost = 0)
{
    assert(singleGame == true  && whoLost == 0 ||
           singleGame == false && (whoLost == 1 || whoLost == 2));
    int indentX, indentY;
    if(singleGame) {
        indentX = nConsoleWidth / 2 - 16;  // ширина слова == 32
        indentY = nConsoleHeight / 3;
    }
    else {
        if(whoLost == 1) indentX = nConsoleWidth / 4 - 16;
        else indentX = nConsoleWidth * 3 / 4 - 16;
        indentY = 2;
    }
    setColor(4);
    setPosition(indentX, indentY); cout << "  _     ___  ____  _____ ____ ";
    setPosition(indentX, indentY + 1); cout << " | |   / _ \\/ ___|| ____|  _ \\ ";
    setPosition(indentX, indentY + 2); cout << " | |  | | | \\___ \\|  _| | |_) | ";
    setPosition(indentX, indentY + 3); cout << " | |__| |_| |___) | |___|  _ < ";
    setPosition(indentX, indentY + 4); cout << " |_____\\___/|____/|_____|_| \\_\\ ";
    setColor(15);
}

}  // namespace draw
