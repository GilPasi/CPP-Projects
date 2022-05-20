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
    static const int DEF_SIZE = 28;

public:
    //Constructors:
     explicit Pile (int size);
    Pile ();


    //Accessors:
    Stone&  stoneAt (int index);//Also send a pointer so the address can be accessed too
    void print_open();
    void print_close();
    int get_size () const;
    int sum();

    //Mutators:
    void fill (int start);
    void shuffle ();
    void add_top (Stone &added_stone);
    void add_bottom (Stone &added_stone);
    void remove_stone (int index);



        //Assistants:
    static void pilecpy(Stone *dst,Stone *src,int len );

    //Destructor:
    ~Pile ();


};


#endif //ASSIGNMENT5_PILE_H
