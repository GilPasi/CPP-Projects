/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#include "Player.h"
#ifndef ASSIGNMENT5_GAME_H
#define ASSIGNMENT5_GAME_H


class Game {
private:
    Player player1;
    Player player2;

    Pile deck;

    Stone first;
    Stone last;

public:
    Game(Player player1,Player player);

    void turn();





};


#endif //ASSIGNMENT5_GAME_H
