#include "Customer.h"

Customer::Customer(){

}
Customer::Customer(int rt , int ct , int fat , char a , char b , char c){
    registerTime = rt;
    cashierTime = ct; 
    financialAidTime = fat;
    orderVisted[0] = a;
    orderVisted[1] = b;
    orderVisted[2] = c;
    currentOffice = orderVisted[0];
    currentOfficeIndex = 0;
    totalWaitTime = 0;
    waitTimeAtCurrentOffice = 0;
}

Customer::~Customer(){}

int Customer::getRegisterTime(){
    return registerTime;
}

int Customer::getCashierTime(){
    return cashierTime;
}

int Customer::getFinancialAidTime(){
    return financialAidTime;
}

bool Customer::updateToNextOffice(){
    //check to make sure they dont index out of bound 
    if(currentOfficeIndex > 2){
        cerr << "error, not in a office" << endl;
        return false;
    }
    currentOffice = orderVisted[++currentOfficeIndex];
    return true;

}

char Customer::getCurrentOffice(){
    return currentOffice;
}

void Customer::addToTotalWaitTime(int time) {
    totalWaitTime += time;
    waitTimeAtCurrentOffice += time;
}

int Customer::getTotalWaitTime() {
    return totalWaitTime;
}

void Customer::resetWaitTime() {
    totalWaitTime = 0;
    waitTimeAtCurrentOffice = 0;
}