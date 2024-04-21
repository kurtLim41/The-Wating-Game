#ifndef OFFICE_H
#define OFFICE_H

#include "ListQueue.h"
#include "Window.h"
#include "Customer.h"
#include <iostream>
#include <array>
using namespace std;

class Office{
    private:
        string officeName;
        unsigned int numWindows;
        unsigned int totalOpenWindows;
        ListQueue<Customer> *officeQueue;  //change type class to customer once i create that <Customer> 
        Window *officeWindows;

    
    public:
        Office(); //no gonna be used 
        Office(string name , int w);
        ~Office();

        //core functions 
        bool hasOpenWindow();
        void addCustomertoQueue(Customer newCustomer);



};

#endif 
