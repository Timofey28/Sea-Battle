/*
    Данный класс содержит метод isValid(), который
    определяет валидность расстановки кораблей на поле

    Метод используется в классе Field -> shipsArrangement_manual()
*/

#pragma once

class ArrangementValidity
{
    int shipCoords_begin_x_, shipCoords_begin_y_;
    int shipCoords_end_x_,   shipCoords_end_y_;
    int decks_amount;
    int ships_1_deck, ships_2_deck, ships_3_deck, ships_4_deck;

    void LocateFoundShip(int x, int y, const std::vector<std::vector<bool>>& location_field);
    bool OtherShipsTooClose(std::vector<std::vector<bool>>& checkout, const std::vector<std::vector<bool>>& location_field);
    bool CoordsBelongToShip(int x, int y);
public:
    bool too_many_decks;
    bool current_validity;

    bool IsValid(const std::vector<std::vector<bool>>& location_field);
};
