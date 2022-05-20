/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
     Gil Pasi,      ID: 206500936
*/
#include <iostream>
#include "Stone.h"

using  namespace  std;

//Empty constructor creates a new stone NULL-like stone
Stone::Stone() {
    r = l = DEFAULT_VAL;
}

Stone::Stone(int l, int r) {//2 Parameters' constructor
    this->l = l;
    this->r = r;
}



int Stone :: get_l() const{return l;}
int  Stone :: get_r() const{return r;}

void Stone::print_open() const {
    std::cout << "[" << l << "][" << r << "]";//Matching values show
}

void Stone::print_close() {
    std::cout << "[ ][ ]";
}

bool Stone ::match(Stone &stated_s, bool check_right,bool flip_allowed){// Send the actual stone
    /*This method will check if 2 stones are connectable.The current stone (this) is already stated on the board.
     * Therefore, cannot be flipped. On the other hand, the stone "other" is flippable.
     * If the two are simply equal, a true boolean will be returned.
     * If the other stone is semi-equal, it will be flipped and then return a true boolean.*/

    if(check_right){// Check to the right by comparison to the stone

        if (this->l == stated_s.r)
            return true;

        if (this->r == stated_s.r){//The remote sides are equal

            if (flip_allowed)//flip the sides only if allowed
                this->flip();
            return true;
        }

    }
    else{//Check to the left of the stone
        if(this->r == stated_s.l)
            return true;

        if (this->l == stated_s.l){//The remote sides are equal

            if (flip_allowed)//flip the sides only if allowed
                this->flip();
            return true;
        }
    }



    return false;//Otherwise they are not equal
}

bool Stone:: equals (Stone &other) const{
    return l == other.l && r == other.r;

}
int Stone :: get_points() const {return l + r ;}



void Stone::flip() {
// This method flips the sides of each value
int temp = r;
r = l;
l = temp;
}