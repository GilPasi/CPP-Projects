/* Assignment: 5
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#ifndef ASSIGNMENT5_STONE_H
#define ASSIGNMENT5_STONE_H

class Stone {

private:
    int r;
    int l;
    const int static DEFAULT_VAL = -1;
public:

    //Constructors:
    Stone();
    Stone(int l, int r);

    //Accessors:
    int get_l() const;
    int get_r() const;
    void print_open() const;
    static void print_close();
    bool match (Stone &stated_s, bool left_on_board, bool flip_allowed);
    bool equals (Stone &other) const;
    int get_points()const;

    //Mutators:
    void flip();
};
#endif //ASSIGNMENT5_STONE_H
