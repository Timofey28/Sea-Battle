#include "arrangement_validity.h"
using namespace std;

bool ArrangementValidity::IsValid(const vector<vector<bool>>& location_field)
{
    current_validity = false;
    validity_of_those_already_on_the_field = false;
    vector<vector<bool>> checkout = vector<vector<bool>>(10, vector<bool>(10));
    ships_1_deck = 0;
    ships_2_deck = 0;
    ships_3_deck = 0;
    ships_4_deck = 0;

    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            if(!checkout[i][j] && location_field[i][j]) {
                LocateFoundShip(i, j, location_field);
                if(decks_amount > 4 || OtherShipsTooClose(checkout, location_field)) return 0;
                if(decks_amount == 1) ships_1_deck++;
                else if(decks_amount == 2) ships_2_deck++;
                else if(decks_amount == 3) ships_3_deck++;
                else ships_4_deck++;
            }
        }
    }

    if(ships_1_deck <= 4 && ships_2_deck <= 3 && ships_3_deck <= 2 && ships_4_deck <= 1)
        validity_of_those_already_on_the_field = true;

    if(ships_1_deck != 4 || ships_2_deck != 3 || ships_3_deck != 2 || ships_4_deck != 1) return 0;
    else {
        current_validity = true;
        return 1;
    }
}

void ArrangementValidity::LocateFoundShip(int x, int y, const vector<vector<bool>>& location_field)
{
    shipCoords_begin_x_ = x;
    shipCoords_begin_y_ = y;
    if(x + 1 < 10 && location_field[x + 1][y]) {  // либо корабль продолжается вправо
        shipCoords_end_y_ = y;
        while(x + 1 < 10 && location_field[++x][y])
            shipCoords_end_x_ = x;
        decks_amount = shipCoords_end_x_ - shipCoords_begin_x_ + 1;
    }
    else if(y + 1 < 10 && location_field[x][y + 1]) {  // либо вниз
        shipCoords_end_x_ = x;
        while(y + 1 < 10 && location_field[x][++y])
            shipCoords_end_y_ = y;
        decks_amount = shipCoords_end_y_ - shipCoords_begin_y_ + 1;
    }
    else {  // либо он однопалубный
        shipCoords_end_x_ = x;
        shipCoords_end_y_ = y;
        decks_amount = 1;
    }
}

bool ArrangementValidity::OtherShipsTooClose(vector<vector<bool>>& checkout, const vector<vector<bool>>& location_field)
{
    for(int i = shipCoords_begin_x_ - 1; i <= shipCoords_end_x_ + 1; ++i) {
        for(int j = shipCoords_begin_y_ - 1; j <= shipCoords_end_y_ + 1; ++j) {
            if(i < 0 || i > 9 || j < 0 || j > 9) continue;
            if(location_field[i][j] && !CoordsBelongToShip(i, j)) return 1;
            checkout[i][j] = 1;
        }
    }
    return 0;
}

bool ArrangementValidity::CoordsBelongToShip(int x, int y)
{
    if(x >= shipCoords_begin_x_ && x <= shipCoords_end_x_ &&
       y >= shipCoords_begin_y_ && y <= shipCoords_end_y_) return 1;
    else return 0;
}
