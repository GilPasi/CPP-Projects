#include <iostream>
#include "Stone.cpp"
#include "Pile.cpp"
#include "Player.cpp"
#include "Game.cpp"


int main() {


    Player p1("Aka" , false);

    Player p2("Mac", true);

    Game game_1 (p1, p2);


    game_1.run_game();


    return 0;
}



