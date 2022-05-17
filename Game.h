/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#include "Player.h"
#ifndef ASSIGNMENT5_GAME_H
#define ASSIGNMENT5_GAME_H


class Game {
private:

    //In order to save memory resources, the players defined by a pointer
    Player *player1;
    Player *player2;

    //The empty constructor of the pile class will initiate the deck with 28 stones
    Pile deck;
    Pile game_deck = Pile (0);//Before the game has started, there are no stones on the board

    Stone *first = NULL;
    Stone *last = NULL;



    void print_game_status();
    void player_turn();
    void cpu_turn();
    bool add_to_game_deck(int index );/* A boolean valur is returned as a determination of a legal move*/
    void init_turn_determine();
    void stone_handing_out ();
    void find_first_turn();
    void win();
    void lose();

    Player& find_current_player ();




public:

    //Constructor
    Game(Player &p1 , Player &p2);


    //Runner
    void run_game();


    //Destructor
    ~Game();
};


#endif //ASSIGNMENT5_GAME_H
