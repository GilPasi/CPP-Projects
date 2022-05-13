/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#include <iostream>
#include <cstring>
#include "Player.h"
using namespace std;

    Player :: Player (char* player_name, bool is_PC){

        set_name(player_name);

        this->is_PC = &is_PC;

        cout << "Player constructed"<< endl;
    }

    void Player :: add_stone (Stone added_stone){
        hand.add_top(added_stone);//Use the written method
        hand_size ++;
    }

    void Player :: remove_stone (int index){
        hand.remove_stone(index);//Use the written method
        hand_size--;
    }

    void Player ::set_name(char *player_name ) {
        //make space for the new value

        if (name != NULL ){
            cout << "name is null"<<endl;
            delete [] this->name;
        }



        name = new char [strlen(player_name) + 1];

        if (!name){//Report allocations errors
            cout << "Could not allocate memory" << endl;
            exit(EXIT_FAILURE);
        }

        strcpy(name,player_name);

    }

    void Player :: print(){

        //As requested: computer's print is close and the player's print is open
        if(is_PC)
            hand.print_close();
        else
            hand.print_open();
    }

    char* Player :: get_name() const {return name;}


    Player :: ~Player(){
            delete[] name;
            cout << "Player destructed"<<endl;
        }

