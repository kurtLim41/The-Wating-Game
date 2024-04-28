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
        int totalWaitTime; // Total wait time across all offices
        int waitTimeAtCurrentOffice; // Wait time at the current office

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
        void addToTotalWaitTime(int time); // Adds wait time
        int getTotalWaitTime(); // Retrieves total wait time
        void resetWaitTime(); // Resets wait time counters for a new day or scenario
        

};
#endif 