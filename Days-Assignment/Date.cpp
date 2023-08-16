/* Assignment: 6
Authors: Lior Poterman, ID: 315368035
		 Gil Pasi,      ID: 206500936
*/
#include "Date.h"
#include <iostream>

using std :: cout;
using std :: endl;
using std :: isdigit;

Date :: Date(int month,int day,int year){
    if (legaldate(month,day,year)){
        this->month = month;
        this->day = day;
        this->year = year;
        cout << "Date constructed"<<endl;
    }
}

Date :: Date(const Date &otr){*this = otr;/*All fields are static, shallow copy is enough */}

ostream& operator<<(ostream &out, const Date d){
    //Implement by the next format : <month>/<day>/<year>
    out << d.month <<"/"<< d.day << "/" << d.year << "\n";
    return out;
}

istream& operator>>(istream &in, Date &d){
    /**This method will take in a new data for an already built date.
     * Therefore it will opperate in the following order:
     *
     * STAGE 1: recive the data.
     * STAGE 2: Validate the format.
     * STAGE 3: legitimize the content.
     * STAGE 4: Change the date to the new given date.
     * */

    const int BUF_SZ = 12;
    /*There are only 11 chacarters needed : m m / d d / y y y y \0   The extra char will help to find invalid inputs
     *                                      1 2 3 4 5 6 7 8 9 10 11       */
    int month,day,year;
    char buf [BUF_SZ];
    buf[BUF_SZ-1] = '\0';//Define the extra char as null

    //STAGE 1
    cout << "Please enter the date by the following format:   mm/dd/yyyy \n";
    in >> buf;


    //STAGE 2
    if (d.validdate(buf)){//First check if the format is valid

        //Then conert each value
        month = d.strtoint(buf,2);//Convert the month
        day = d.strtoint(buf + 3,2 ); //Convert the day
        year = d.strtoint(buf + 6,4 );//Convert the year

        //STAGE 3
        if (d.legaldate(month,day,year)){

            //STAGE 4
            d.month = month;
            d.day = day;
            d.year = year;
        }

    }
    return in;
}
Date Date :: operator++(){
    /**Use a written operator.*/
    *this += 1;
    return *this;
}

Date Date :: operator++(int){
    /**Similarly to the prefix ++, This operator will increase one day but will return a value untouched.*/
    Date ret = *this;
    ++*this;// Use the already written operator
    return ret;
}

Date Date :: operator+=(int modi){
    /**This method will increase the date by a modifier.
     * At first it will dismantle the modifier into years, months and days.
     * For exmample 605 days are considered as one year (360 days), 8 months (240 days) and 5 days.
     * After this distribuition, the days will be addded first. If those will exceed the top limit, it will be transfered into months.
     * Then the proccesse will be reapeted.*/

    int yrs_prt = modi/( TOP_MON *TOP_DAY);//This will find out how many years embodied in the modi
    modi = modi -yrs_prt*(TOP_DAY*TOP_MON);//Get rid of the added years

    int mon_prt = modi / TOP_DAY;//This will find out how many months embodied in the modi
    modi = modi -mon_prt* TOP_DAY;//Get rid of the added months

    //At the moment the modifier cannot be greater than 30

    day += modi;
    if (day > TOP_DAY){//Exceed max capacity
        ++mon_prt;
        day %= TOP_DAY;
    }

    month += mon_prt;
    yrs_prt += month/TOP_MON;
    month %= TOP_MON;

    year += yrs_prt;
    return *this;
}

bool Date :: operator>(Date otr){
    //Compare years
    if (this->year > otr.year)
        return true;
    if (this->year < otr.year)
        return false;

    //Years are the same, compare months
    if (this->month > otr.month)
        return true;
    if (this->month < otr.month)
        return false;

    //Months are the same, compare days
    if (this->day > otr.day)
        return true;

    return false;// *this is not greater than otr any way
}
bool Date :: operator<(Date otr){
    return !(*this == otr) && !(*this > otr);
    //If the other date is not equal to the current one and not lesser, it is with no dout greater.
}


bool Date :: operator==(Date otr){
    return (
            this->year == otr.year
            &&
            this->month == otr.month
            &&
            this->day == otr.day
            );
}




bool Date :: validdate(char* input)const{
    /**This method return a boolean that reflects the validity of the user's input.
     * It will find out if the format was correct and if only digit were entered.
     * On contrary to 'legaldate()' method, it will not check if the date is correct by the 'human'
     * definition. For example the date 50/79/0000 will be compltely valid.*/
    const int BUF_SZ = 12;




    if (input[BUF_SZ-1] != '\0'){//The twelfth character has to be null. Otherwise the user enterd an input which is too large
        cout << "Could not take the input, too long for the format.\n";
        return false;
    }

    if (input[2] != '/' || input [5] !='/'){//Check for placing the slashes properly
        cout << "The input was not entered by the following format : mm/dd/yyyy could not proceed.\n";
        return false;
    }


    if (//Check if all the characters are digits
            !(isdigit(input[0]) && isdigit(input[1]) && isdigit(input[3]) && isdigit(input[4])&&
            isdigit(input[6]) && isdigit(input[7]) && isdigit(input[8]) && isdigit(input[9])
            )){
        cout << "Not all characters are digits, input could not be taken.\n";
        return false;
    }

    return true;
}

int Date :: strtoint(char* str,int len) const {
    /**This method will convert a whole string into an integer. it will not check if each character is a
     * digit. The invoking method should make sure those prerequisites*/
     int const MOD = 10;//A modifier
     int ret = 0;
    for (int i = 0;i < len; i++){
        ret *= MOD;
        ret += chartoint(str[i]);
    }
    return ret;
}


int Date :: chartoint(char c) const{
    /**This method converts characters into their int value by subtructing the matching ASCII value*/
    int const BOT = '0';
    return c-BOT;
}



bool Date ::  legaldate(int month, int day, int year)const{
    bool res = true;//True until "found guilty"

    //Check range
    if (month < BOT_MON || month > TOP_MON){
        cout << "ERROR MONTH\n";
        res = false;
    }

    //Check range
    if (day < BOT_DAY || day > TOP_DAY){
        cout << "ERROR DAY\n";
        res = false;
    }

    //Check range
    if (year < BOT_YR || year > TOP_YR){
        cout << "ERROR YEAR\n";
        res = false;
    }
    return res;
}
