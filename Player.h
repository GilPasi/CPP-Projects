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
    int hand_size = 7;
    char* name = NULL;
    Pile hand = Pile(hand_size); // cannot postpone initialization to the constructing part


public:

    //Constructors:
    Player (char* name, bool is_PC);

    //Accessors:
    void print();
    char* get_name() const;

    //Mutators:
    void add_stone (Stone added_stone);
    void remove_stone (int index);
    void set_name (char* name);


    //Destructor:
    ~Player();

//No dynamic allocations, no need for a destructor
};


#endif //ASSIGNMENT5_PLAYER_H
