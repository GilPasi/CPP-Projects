/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#ifndef ASSIGNMENT5_PILE_H
#define ASSIGNMENT5_PILE_H

#include <iostream>
#include "Stone.h"

class Pile {

private:
    Stone *stones;
    int size;
    static const int MAX_VAL  = 6;//A stone's value cannot be greater than 6

public:
    //Constructors:
    Pile (int size);
    Pile ();


    //Accessors:
    Stone&  stoneAt (int index);//Also send a pointer so the adress can be accessed too
    void print_open();
    void print_close();
    int get_size();

    //Mutators:
    void fill (int start);
    void shuffle ();
    void add_top (Stone &added_stone);
    void add_bottom (Stone &added_stone);
    void remove_stone (int index);
    void reboot_size();


        //Assistants:
    void pilecpy(Stone *dst,Stone *src,int len );

    //Destructor:
    ~Pile ();


};


#endif //ASSIGNMENT_5_PILE_H
