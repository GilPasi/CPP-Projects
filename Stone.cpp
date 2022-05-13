/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#include <iostream>
#include "Stone.h"

using  namespace  std;

//Constructors section:

//Empty constructor creates a new stone NULL-like stone
Stone::Stone() {
    r = l = DEFAULT_VAL;
}

Stone::Stone(int l, int r) {//2 Parameters' constructor
    set_r(r);
    set_l(l);

}

Stone::Stone(Stone &other) {//Copy constructor
    set_r(other.r);
    set_l(other.l);
}

void Stone::flip() {
    // This method flips the sides of each value
    int temp = r;
    r = l;
    l = temp;
}

void Stone::print_open() const {
    std::cout << "[" << l << "][" << r << "]";//Matching values show
}

void Stone::print_close() {
    std::cout << "[ ][ ]\n";
}

void Stone::set_l(int l_updated) {
    l = l_updated;
}

void Stone::set_r(int r_updated) {
    r = r_updated;
}

bool Stone::is_null() const {
    return l == DEFAULT_VAL;//-1 is a disqualify value
}

void Stone::make_null() {
    l = r = DEFAULT_VAL; // This method disqualify a stone
}

void Stone::transfer_data(Stone &other) {
    this->l = other.l;
    this->r = other.r;
}

