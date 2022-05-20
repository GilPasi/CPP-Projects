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

        this->is_PC = is_PC;
    }

    Player :: Player (){
        char default_name []= "";
        set_name(default_name);//Anonymous name
        is_PC = true;//For simplicity reasons, a player is computer by default
    }

    char* Player :: get_name()  { return name;}
    bool Player :: get_is_PC()const{return is_PC;}
    Pile& Player :: get_hand() {return hand;}
    void Player :: print_hand(){

        //As requested: computer's print is close and the player's print is open
        if(is_PC)
            hand.print_close();
        else
            hand.print_open();

        cout << "\n";
        for(int i = 1 ; i < hand.get_size() + 1; i++){
            cout << "\t |"<<i<<"|";
        }
        cout <<"\n";


    }


    void Player :: add_stone ( Stone &added_stone){
        hand.add_top( added_stone);//Use the written method
    }

    void Player :: remove_stone (int index){
        hand.remove_stone(index);//Use the written method
    }

    void Player ::set_name(char *player_name) {
        //make space for the new value

        if (name != nullptr ){
            cout << "name is null\n";
            delete [] this->name;
        }

       name = new char [strlen(player_name)+ 1];

        if (!name){//Report allocations errors
            cout << "Could not allocate memory\n";
            exit(EXIT_FAILURE);
        }

       strcpy(name,player_name);

    }

    Player :: ~Player(){
        delete[] name;
        name = nullptr;
     }



