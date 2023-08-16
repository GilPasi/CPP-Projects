/* Assignment: 6
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/


#ifndef ASSIGNMENT_6_DATE_H
#define ASSIGNMENT_6_DATE_H

#include <iostream>
using std :: ostream;
using std :: istream;

class Date {
public://TODO make fields privare
    int day;
    int month;
    int year;
    //Define consts for tops and bottoms of day, month and year
    static int const BOT_DAY = 1, TOP_DAY = 30, BOT_MON = 1, TOP_MON = 12, BOT_YR = 1970, TOP_YR = 2099;



    //Constructors:
    Date( const int month = BOT_MON,const int day = BOT_DAY,const int year = BOT_YR);//Empty and parametric
    Date (const Date &other);//Copy
    //Ther is no need for a destructor since all fields are staticly allocated


    //Assistants:
    int strtoint(char*,int) const;
    int chartoint(char) const;
    bool legaldate(int,int,int)const;
    bool validdate(char*)const;


    //Operators:
    friend ostream& operator<<(ostream &out, const Date d);
    friend istream& operator>>(istream &in, Date &d);
    Date operator++();
    Date operator++(int);
    Date operator+=(int);
    bool operator>(Date otr);
    bool operator<(Date otr);
    bool operator==(Date otr);

};

#endif //ASSIGNMENT_6_DATE_H
