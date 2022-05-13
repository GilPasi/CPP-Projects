/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/

#include "Pile.h"
#include <iostream>


Pile :: Pile(int size){
    //Dynamic allocation as requested
    stones = new Stone[size];
    this->size = size;
}

Stone Pile :: stoneAt (int index){
    if(index >= size || index < 0){
        cout << "Index out of bound, method crash"<<endl;
        exit(EXIT_FAILURE);
    }


    //This function returns the stone in the requested index
    return stones[index];
}

void Pile :: print_open(){
    //This method print all the stones in their opened form
    for (int i = 0; i < size; i++){
        std :: cout << "  ";
        stones[i].print_open();
    }
}

void Pile ::  print_close(){
    //This method print all the stones in their closed form
    for (int i = 0; i < size; i++){
        stones[i].print_close();
    }
}

void Pile :: fill (int start = 0){//start from the zero as a default
    int place = start;
    bool stay_in_loop = true;

    for (int i = 0; i <= MAX_VAL && stay_in_loop; i++){
        for (int j = i; j <= MAX_VAL && stay_in_loop; j++){

            Stone current (i,j);//Create the right stone
            stones[place ++] = current;

            if(place == size)//Avoid memory leak
                stay_in_loop = false;
        }
    }
}

void Pile :: shuffle (){
    Stone disqualify_stone(-1,-1);//These stone represent an empty cell
    Stone temp[size];
    srand(time(0));
    int index = 0;
    int random_place;
    //random_place = 1;


    while (index != size){
        random_place = rand() % size;
        Stone *current = &stones[random_place];

        while (current->is_null()){
            random_place = (random_place + 1) % size;//Search for the next
            current = &stones[random_place];
        }
        temp[index ++].transfer_data(*current);
        stones [random_place].make_null();
    }

    //After the order was made, it will be copied to the actual array:

    for (int i = 0; i < size; i ++)
        stones [i] = temp [i];
}

void Pile :: add_top (Stone &added_stone){
    //This method add a stone at the top of the pile
    stones[size ++] = added_stone;//Increase size in order to avoid further problems in other methods
}

void Pile :: add_bottom (Stone &added_stone){
    //This method add a stone at the bottom of the pile
    stones[-1] = added_stone;//Add at bottom
    stones = &stones[-1];//Redefine the first index of the array
    size ++;//Increase size in order to avoid further problems in other methods
}

void Pile :: remove_stone (int index){
    /*This method will override the stone in the given index and diminish the gap.
    In this way the array will be kept continuous*/

    for (int i = index; i < size; i++)
        stones[i].transfer_data(stones[i + 1]);
    //reveres all elements one step back

    stones[size].make_null();//Delete the last cell

    size --;
}

Pile :: ~Pile (){
    delete [] stones;
}


