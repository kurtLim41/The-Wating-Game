#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
using namespace std;

class Customer{
    private:
        int registerTime;
        int cashierTime;
        int financialAidTime;
        char orderVisted[3];
        char currentOffice;
        int currentOfficeIndex;

    public:
        Customer();
        Customer(int rt , int ct , int fat , char a , char b , char c);
        ~Customer();

        //core functions 
        bool updateToNextOffice();

        //aux functions 
        int getRegisterTime();
        int getCashierTime();
        int getFinancialAidTime();
        char getCurrentOffice();
        

};
#endif 