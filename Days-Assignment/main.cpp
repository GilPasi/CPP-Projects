/* Assignment: 6
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#include <iostream>
#include "Date.h"
using std :: cin;
using std :: cout;
using std :: endl;
int main() {

    Date d(5,15,2000);
    Date  b(10,18,2015);

    if (b < d)
        cout << "YES";
    else
        cout << "NO";







    return 0;
}
