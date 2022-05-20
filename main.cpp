/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#include <iostream>
#include "Stone.cpp"
#include "Pile.cpp"
#include "Player.cpp"
#include "Game.cpp"


int main() {
    int const BUF_SIZE = 100;
    char computer_name [] = "Mac";
    char* buffer = new char [BUF_SIZE];

    cout << "Welcome to game! enter your name please : \n";
    cin >>buffer;

    char* user_name = new char [strlen(buffer) + 1];
    strcpy(user_name,buffer);

    delete [] buffer;

    Player p1(user_name, false);
    Player p2(computer_name, true);

    Game game_1 (p1, p2);
    game_1.run_game();

    delete [] user_name;

    return 0;
}



