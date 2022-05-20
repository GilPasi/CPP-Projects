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
        set_r(r);
        set_l(l);

    }

    Stone::Stone(Stone &other) {//Copy constructor
        set_r(other.r);
        set_l(other.l);
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

    bool Stone::is_null() const {
        return l == DEFAULT_VAL;//-1 is a disqualify value
    }

    bool Stone:: equals (Stone other){
        return l == other.l && r == other.r;;

    }

    void Stone::flip() {
        // This method flips the sides of each value
        int temp = r;
        r = l;
        l = temp;
    }



    void Stone::set_l(int l_updated) {
        l = l_updated;
    }

    void Stone::set_r(int r_updated) {
        r = r_updated;
    }

    void Stone::make_null() {
        l = r = DEFAULT_VAL; // This method disqualify a stone
    }

    void Stone::transfer_data(Stone &other) {
        this->l = other.l;
        this->r = other.r;
    }

    int Stone :: get_points(){return l + r ;}

