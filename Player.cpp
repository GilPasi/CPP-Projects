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
        char name[] = "";
        set_name(name);//Anonymous name
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
            cout << "name is null"<<endl;
            delete [] this->name;
        }



       name = new char [strlen(player_name)+ 1];

        if (!name){//Report allocations errors
            cout << "Could not allocate memory" << endl;
            exit(EXIT_FAILURE);
        }

       strcpy(name,player_name);

    }




void Player :: print_hand(){

            //As requested: computer's print is close and the player's print is open
            if(is_PC)
                //TODO return to this : hand.print_close();
                hand.print_open();
            else
                hand.print_open();

            cout << "\n";
            for(int i = 1 ; i < hand.get_size() + 1; i++){
                cout << "\t |"<<i<<"|";
            }
            cout <<"\n";


    }

        char* Player :: get_name()  { return name;}
        bool Player :: get_is_PC()const{return is_PC;};
        Pile& Player :: get_hand() {return hand;}

        int Player :: get_START_SIZE(){return START_SIZE;};




Player :: ~Player(){
                    cout  <<name <<  " destructed!\n";
                        delete[] name;
                        name = nullptr;
             }



