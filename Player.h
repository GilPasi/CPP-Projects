/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/


#ifndef ASSIGNMENT5_PLAYER_H
#define ASSIGNMENT5_PLAYER_H

#include "Pile.h"

class Player {
private:
    bool is_PC;//This boolean value is vital for the print method
    static int const START_SIZE = 7;
    char* name = nullptr;
    Pile hand = Pile(0); // cannot postpone initialization to the constructing part


public:

    //Constructors:
    Player (char* name, bool is_PC);
    Player();

    //Accessors:
    void print_hand();
    char* get_name() ;
    Pile& get_hand() ;
    bool get_is_PC()const;
    int get_START_SIZE();

    //Mutators:
    void add_stone ( Stone &added_stone);
    void remove_stone (int index);
    void set_name (char* name);


    //Destructor:
    ~Player();


};


#endif //ASSIGNMENT5_PLAYER_H
