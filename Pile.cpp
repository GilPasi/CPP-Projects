/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/

#include "Pile.h"
#include <iostream>
static const Stone DISQ_STONE (-1,-1);// This represents a NULL-like stone


Pile :: Pile(int size){
    this->size = size;


    if (size == 0){//If there are no stones, the first stone still needs to be taken
        stones = new Stone[1];
        return;
    }
    //Dynamic allocation as requested
    stones = new Stone[size];
}

Pile :: Pile(){
    //Dynamic allocation as requested
    stones = new Stone[DEF_SIZE];
    this->size = DEF_SIZE;

}

Stone& Pile :: stoneAt (int index){

    if(index >= size || index < 0){
        cout << "Index is : " << index<< "Index out of bound, program crash \n";
        exit(EXIT_FAILURE);
    }
    //This function returns the stone in the requested index

    return stones[index];
}

void Pile :: print_open(){
    //This method print all the stones in their opened form
    for (int i = 0; i < size; i++){
        cout << "\t";
        stones[i].print_open();
    }
}

void Pile ::  print_close(){
    //This method print all the stones in their closed form
    for (int i = 0; i < size; i++){
        cout << "\t";
        stones[i].print_close();
    }
}

int Pile ::get_size() const {return size;}

void Pile :: fill (int start = 0){//start from the zero as a default
    int place = start;

    for (int i = 0; i <= MAX_VAL; i++){
        for (int j = i; j <= MAX_VAL ; j++){

            if(place == size)//Avoid memory leak
                return;

            Stone current (i,j);//Create the right stone
            stones[place ++] = current;


        }
    }
}

void Pile :: shuffle (){
    int random_place;
    int const ORIGINAL_SIZE = size;
    /*'size' is decreased when 'remove_stone' method is used.
     * For this reason, the original size is preserved in a const value*/


    Stone *temp = new Stone[size];
    srand(time(nullptr));


    for (int i = 0 ; i < ORIGINAL_SIZE ; i++){

        random_place = rand() % size;


        temp[i] = stones[random_place];
        this->remove_stone(random_place);// Avoid repeating the same stone
    }
    //After the order was made, it will be copied to the actual array:
    delete stones;
    stones = temp;
    size = ORIGINAL_SIZE;
}

void Pile :: add_top ( Stone &added_stone){
    /*This method add a stone at the top of the pile*/

    if (size == 0){//If the pile is empty, there is still one empty place
        *stones = added_stone;
        ++size;
        return;
    }


    Stone *new_stones = new Stone [++size];//Allocate a new place with larger space

    pilecpy(new_stones,stones,size -1 );//copy all the stones
    new_stones [size - 1] = added_stone;

    stones = new_stones;//Redefine
    //There is no reason to deallocate the array, it is already done.

}

void Pile :: add_bottom (Stone &added_stone){

    //This method add a stone at the bottom of the pile
    if (size++ == 0){//If the pile is empty, there is still one empty place
        *stones = added_stone;

        return;
    }



    Stone *new_stones = new Stone [size];//Allocate a new place with larger space

    pilecpy(new_stones + 1,stones,size -1 );//stones + 1 , leave a space for the bottom stone
    new_stones [0] = added_stone;//Copy data into the new cell

    stones = new_stones;//Redefine
    //There is no reason to deallocate the array, it is already done.


}

void Pile :: remove_stone (int index){
    /*This method will override the stone in the given index and diminish the gap.
    In this way the array will be kept continuous*/


    if (index >= size || index < 0){
        cout << "Index is : " << index<<" size is:"<< size << " Index out of bound, program crash \n";
        exit(EXIT_FAILURE);
    }


    for (int i = index; i < size; i++)
        stones[i] = stones[i + 1];
    //reveres all elements one step back

    stones[size-1] = DISQ_STONE;//Delete the last cell

    size --;
}

int Pile :: sum(){
    int ret  = 0 ;
    for (int i = 0; i < size; i++){
        ret += stones[i].get_points();
    }
    return ret;
}


 void Pile ::pilecpy(Stone *dst,Stone *src, int len ){

    for (int i = 0 ; i < len; i++){
        dst[i] = src[i];
    }

}




Pile :: ~Pile (){
    delete [] stones;
    stones = nullptr;
}


