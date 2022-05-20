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


    //Interact methods:
    void print_game_status();
    void ask_for_side(int index);

    //Runners:
    void stone_handing_out ();
    void player_turn();
    void cpu_turn();
    void game_over (Player& winner);

    //Assistants:
    void find_first_turn();
    Player& find_current_player ();
    int validate_add(int input);
    bool validate_move(int index, bool mutate,Player& tested);
    bool is_game_over(Player& current, Player& next);
    bool can_play(Player& tested);
    bool take_card();

public:

    //Constructor
    Game(Player &p1 , Player &p2);

    //Runner
    void run_game();

    //Destructor
    ~Game();
};


#endif //ASSIGNMENT5_GAME_H
