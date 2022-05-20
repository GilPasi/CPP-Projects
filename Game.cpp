/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#include <iostream>
#include "Game.h"

using  namespace std;

static bool player1_turn;
static bool deck_not_empty = true;

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
    cout << "\t\t\t\t\t\t\t\t\t\t{Deck: "<< deck.get_size() << "}\n\n\n\n";

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
    player1_turn = true;


    //TODO


    Player *current = &find_current_player();
    Player *next = nullptr;

    cout <<"\t\t____WELCOME TO DOMINO WORLD!____\n";
    cout << current->get_name() << " start!\n";

    while (is_game_over(*current,*next)){
        print_game_status();

        if (current->get_is_PC())
            cpu_turn();
        else
            player_turn();

        //Switch turns:
        player1_turn = !player1_turn;

        //Switch: next is the old current
        next = current;
        current = &find_current_player();


    }
}

void Game :: player_turn() {

    int result;
    int stone_index;
    Player *current = &find_current_player();


    cout << "Please chose a stone number to place on the board (0 for drawing a stone)\n";
    cin >> stone_index;

    stone_index --;//Convert from 'human' index into a machine index


    /*There are two possible problems with the player's input:
     * First, it could be out of bound, for instance stone_index == 8 while the player have 7 cards
     *Second, the index may be possible but the stone is not matching neither the left nor the right side
     * of the game deck.
     *
     * Therefore, the next loop will validate both conditions.*/

    do {
        result = validate_add(stone_index);

        switch (result) {

            case (1):
                cout << "Cannot draw a new stone from an empty deck, you must use your stones\n";
                break;

            case(2):
                cout <<"The stone is not on board, try again using the indexes below\n";
                break;

            case(3):
                cout << "The stone does not match the board, try something else\n";
                break;

            case(4):
                current->remove_stone(stone_index);

                //Reboot first and last pointers
                first = &game_deck.stoneAt(0);
                last = &game_deck.stoneAt(game_deck.get_size() - 1);
                break;

            case(5):
                break;

        }

        if (result < 4){
            cin >> stone_index;
            stone_index--;// Convert into a machine indexes
        }
    }
    while (result < 4);// 4 and 5 are legal requests
}

void Game ::  cpu_turn(){
    /*This method is the PC turn. The computer will always play the first stone that it can lay*/

    Player *current = &find_current_player();

    for (int i = 0; i < current->get_hand().get_size(); i++){

        if (validate_move(i,true, find_current_player())){//This method will add the stone if possible, otherwise a false value will be returned
            current->remove_stone(i);

            //Reboot first and last pointers
            first = &game_deck.stoneAt(0);
            last = &game_deck.stoneAt(game_deck.get_size() - 1);
            return;
        }

        //If no stone was found take a new on from the deck
        if (deck_not_empty)
            take_card();
    }
}

void Game :: stone_handing_out (){
    /*This method will distribute the stones between the two players. */

    int const SIZE = player1->get_START_SIZE();
    Stone *s_ptr1;
    Stone *s_ptr2;

    for (int i = 0 ; i < SIZE; i++){

        //Take two stones
        s_ptr1 = first;
        s_ptr2 = first + 1;

        //Give it to players
        player1->add_stone(*s_ptr1);
        player2->add_stone(*s_ptr2);


        //Remove from the original deck
        deck.remove_stone(0);
        deck.remove_stone(0);
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


void Game :: ask_for_side(int index){
    int input;
    Player *current_p = &find_current_player();
    Stone *current_s  = &current_p->get_hand().stoneAt(index);
    cout << "It is possible to add the stone for both sides of the game-deck\n"
            <<"Do you prefer to add it to the right side(enter 1) or the left side (enter 2)? \n";

    cin >> input;
    input --;//Convert to boolean value

    while (input != 1 && input != 0){//Validate the value
        cout << "The answer was not valid, please enter 1 or 2 again"<< endl;
        cin >> input;
        input --;//Convert to boolean value

    }

    if (input){
        //Flip if necessary:
        if (current_s->get_l() == first->get_l())
            current_s->flip();

        game_deck.add_top(*current_s);
    }
    else{
        //Flip if necessary:
        if (current_s->get_r() == last->get_r())
            current_s->flip();

        game_deck.add_top(*current_s);
    }
    //Reboot first and last pointers
    first = &game_deck.stoneAt(0);
    last = &game_deck.stoneAt(game_deck.get_size()-1);
}

int Game :: validate_add(int input){
    /*This method checks if the requested action is legal.If it is, then the act will be executed.
     * It also returns an integer that reflects each possible problem that occurred.
     * This way the invoking method will know how to treat the issue.
     * 1 = Player ask for drawing a stone while the deck is empty.
     * 2 = Player try to place a stone that does not exist.
     * 3 = Player try to place an existing stone while there are no legal places for it.
     * 4 = A successful move.
     * 5 = A successful stone take.
     * */

    if (input == -1 ){
        if (deck_not_empty){
            take_card();
            return 5 ;
        }
        return 1;
    }

    if (input < 0 || input >= find_current_player().get_hand().get_size())
        return 2;

    if(!validate_move(input, true,find_current_player()))// Allow to mutate
        return 3;

    return 4;
}

bool Game :: validate_move(int index, bool mutate, Player& tested) {
    /*This method is checking if the selected stone is matchable with the chain.
     * If the invoking method will allow (by sending mutate == true)
     * The method not only check if the change is possible but also execute it.*/

    Player *current_p = &tested;
    Stone *current_s = &current_p->get_hand().stoneAt(index);// Get the address of the current player's stone

    //At first turn, any move is legal
    if (game_deck.get_size() == 0){
        if(mutate)
            game_deck.add_top(*current_s);
        return true;
    }


    /*If the human player can add his stone to both sides he/she needs to be asked what side does
 * he or she prefer.*/

    bool cond1, cond2,cond3;

    cond1 = !current_p->get_is_PC();//It needs to be human
    cond2 = current_s->match(*first, false, false);//can add to the left
    cond3 = current_s->match(*last, true, false);

    if (cond3 && cond2 && cond1 && mutate){
        ask_for_side(index);
        return true;
    }



    if (current_s->match(*first,false,mutate)){//If the stone match the right side, add it at top
        if (mutate)
            game_deck.add_bottom(*current_s);
        return true;
    }


    if (current_s->match(*last,true,mutate)){//If the stone match the left side, add it at top
        if (mutate)
            game_deck.add_top(*current_s);
        return true;
    }

    return false;
}

    bool Game :: take_card(){

    if (!deck_not_empty){
        cout << "Cannot draw a new stone, deck is empty\n";
        return false; //Report failure
    }

    int position = deck.get_size() - 1;

        find_current_player().add_stone(deck.stoneAt(position));
        deck.remove_stone(position);

        deck_not_empty = !deck.get_size() == 0;//change if deck is empty
        return true; // Report success
    }


    bool Game :: is_game_over(Player &current, Player& next) {

    //If one of the players finished their cards, the loop must break
        if (player1->get_hand().get_size() == 0) {
                game_over(*player1);
        return false;
        }

        if (player2->get_hand().get_size() == 0) {
            game_over(*player2);
            return false;
        }

        if(deck_not_empty)// As long as there are stones in the deck, it is possible to play
            return true;

        if (can_play(current))// As long as the current player can play, the game proceed
            return true;

        //If the current player cannot play, the game is over

        if (can_play(next))//If the second player can still play, then he is the winner
            game_over(next);

        else{//Otherwise, the winner will be determined by comparing the piles' sums
            if( current.get_hand().sum() - next.get_hand().sum() > 0)
                game_over(current);
            else
                game_over(next);
        }


        return false;//Do not continue the game
}

bool Game :: can_play(Player& tested){

    for (int i = 0; i < tested.get_hand().get_size(); i++)
        if (validate_move(i, false, tested))
            return true;
    return false;
}


void Game :: game_over (Player& winner){
    print_game_status();
    cout << "There are no left moves! \n";

    cout << "\t\t________________________________\n";
    cout << "\t\t|\tGAME IS OVER\t\t|\n";
    cout << "\t\t|\tThe winner is \t";

    cout << winner.get_name();


    cout << "!\t|\n\t\t________________________________\n";

}







Game:: ~Game(){
        //All pointers to null values
        player1 = nullptr;
        player2 = nullptr;

        first = nullptr;
        last = nullptr;

    }