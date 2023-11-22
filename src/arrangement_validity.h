/*
    Данный класс содержит метод isValid(), который
    определяет валидность расстановки кораблей на поле

    Метод используется в классе Field -> ArrangeShipsForPerson()
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
    bool current_validity;
    bool validity_of_those_already_on_the_field;

    bool IsValid(const std::vector<std::vector<bool>>& location_field);
    int Get_1deckShipsAmount() { return ships_1_deck; }
    int Get_2deckShipsAmount() { return ships_2_deck; }
    int Get_3deckShipsAmount() { return ships_3_deck; }
    int Get_4deckShipsAmount() { return ships_4_deck; }
};
