/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#include <iostream>
#include "Game.h"

using  namespace std;

static bool player1_turn;

Game :: Game(Player &player1, Player &player2){

        this->player1 = &player1;
        this->player2 = &player2;

        deck.fill();

        //First at the first of the deck and last at last
        first = &deck.stoneAt(0);
        last = &deck.stoneAt(0);

    cout << "\nA game constructed!\n";

}



void Game::print_game_status() {

    cout << "Player 2: "<< player2->get_name() <<"\n";
    player2->print_hand();
    cout << "\n***********************************************************************************\n";//border

    cout << "\n\n\n\nSTART=>";
    game_deck.print_open();
    cout << "\n\n\n\n";

    cout << "\nPlayer 1: "<< player1->get_name() <<"\n";
    player1->print_hand();
    cout << "\n***********************************************************************************\n";//border

}



void Game :: run_game(){

    cout << "running game \n";

    //deck.shuffle();
    stone_handing_out();
    find_first_turn();


    //TODO delete later
    Stone s (0,6);
    player1_turn = true;
    player2->add_stone(s);
    //TODO


    Player *current = &find_current_player();



    cout <<"\t\t____WELCOME TO DOMINO WORLD!____\n";
    print_game_status();
    cout << current->get_name() << " start!\n";


    while (player1->get_hand().get_size() > 0 && player2->get_hand().get_size() > 0){
        if (current->get_is_PC())
            cpu_turn();
        else
            player_turn();

        //TODO screen clean
        //system("cls");
        print_game_status();



        player1_turn = ! player1_turn;// Change turn
        current = &find_current_player();

    }



}

void Game :: player_turn(){

    int stone_index;

    cout << "Please chose a stone number to place on the board\n";
    cin >> stone_index;

    stone_index --;//Match human index into machine index





    while (!add_to_game_deck(stone_index)){//If the turn completed successfully, reduce the player's stone

        cout << "The stone does not match the board, try again (0 to forfeit)\n";
            cin >> stone_index;

            if (stone_index == 0){
                lose();
                //break;
            }
            stone_index --;//Match human index into machine index
    }

    Player *current = &find_current_player();
    current->remove_stone(stone_index);
    current = nullptr;

}


void Game ::  cpu_turn(){
    /*This method is the PC turn. The computer will always play the first stone that it can lay*/

    Player *current = &find_current_player();

    for (int i = 0; i < current->get_hand().get_size(); i++){
        if (add_to_game_deck(i))//This method will add the stone if possible, otherwise a false value will be returned
            return;
    }

    //If not returned by now, The computer has no matching stones and therefore the other player won
    win();


}


bool Game ::add_to_game_deck(int index ) {
    /*This method is checking if the selected stone is matchable with the chain.If it does, the former will be added*/

    //First determine who's turn it is
    Player *current_p = &find_current_player();
    Stone *current_s = &current_p->get_hand().stoneAt(index);// Get the address of the current player's stpne

    //At first turn, any move is legal
    if (game_deck.get_size() == 0){
        //TODO delete cout
        cout <<"FIRST STONE";
        game_deck.add_top(*current_s);
        last = first = &game_deck.stoneAt(0);// Update both edge pointers
        return true;


    }

    if (current_s->match(*first,false)){//If the stone match the right side, add it at top
        //TODO delete cout
        cout <<"MATCH LEFT";
        game_deck.add_bottom(*current_s);
        current_p->remove_stone(index);
        first = &game_deck.stoneAt(0);
        last = &game_deck.stoneAt(game_deck.get_size() - 1);
        return  true;
    }

    if (current_s->match(*last,true)){//If the stone match the right side, add it at top
        //TODO delete cout
        cout <<"MATCH RIGHT";
        game_deck.add_top(*current_s);
        current_p->remove_stone(index);
        first = &game_deck.stoneAt(0);
        last = &game_deck.stoneAt(game_deck.get_size() - 1);
        return  true;
    }

    return false;
}

void Game :: stone_handing_out (){
    /*This method will distribute the stones between the two players. */

    int const SIZE = player1->get_START_SIZE();
    Stone *s_ptr1;
    Stone *s_ptr2;

    for (int i = 0 ; i < SIZE; i++){

        //Take two stones
        s_ptr1 = &deck.stoneAt(i);
        s_ptr2 = &deck.stoneAt(i + SIZE);

        //Give it to players
        player1->add_stone(*s_ptr1);
        player2->add_stone(*s_ptr2);


        //Remove from the original deck
        deck.remove_stone(i);
        deck.remove_stone(i + SIZE);
    }
}

void Game :: find_first_turn(){
    /*This method find the player with the [6][6] stone and thus determine whose starting the game.*/
    int const SIZE = player1->get_hand().get_size();
    Stone START_STONE (6,6);
    Stone *s_ptr1;

    player1_turn = false;

    for (int i = 0; i < SIZE ; i++){

        s_ptr1 = &(player1->get_hand()).stoneAt(i);

        // The only scenario where the first player starts is when he owns the stone [6][6]
        if (s_ptr1->equals(START_STONE)){

            player1_turn = true;
            return;
        }
    }

}

Player& Game :: find_current_player (){
    if (player1_turn)
        return *player1;
    return *player2;
}

void Game :: win(){

    //Set sizes to zero in order the end the game loop
    player1->get_hand().reboot_size();
    player2->get_hand().reboot_size();


    cout << "\n\n\n\t\t_________________________\n";
    cout << "\t\t|   YOU WON!   |\n";
    cout << "\t\t_________________________\n";

}
void Game :: lose(){
    system("cls");

    //Set sizes to zero in order the end the game loop
    player1->get_hand().reboot_size();
    player2->get_hand().reboot_size();


    cout << "\n\n\n\t\t_________________________\n";
    cout << "\t\t|   YOU LOST!   |\n";
    cout << "\t\t_________________________\n";


}



Game:: ~Game(){
        //All pointers to null values
        Player *player1 = nullptr;
        Player *player2 = nullptr;

        Stone *first = nullptr;
        Stone *last = nullptr;

    }