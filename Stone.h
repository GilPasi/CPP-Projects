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
    Stone(Stone &other);
    Stone();
    Stone(int l, int r);

    //Accessors:
    void print_open() const;
    static void print_close() ;
    bool is_null()const;

    //Mutators:
    void flip();
    void set_l(int l);
    void set_r(int r);
    void make_null();
    void transfer_data(Stone &other);
};
#endif //ASSIGNMENT_5_STONE_H
