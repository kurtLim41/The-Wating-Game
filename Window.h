#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include "Customer.h"
using namespace std;

class Window{
    private:
        Customer *currentCustomer;
        bool isOpen;
        int timeRemaining;

    public:
        Window();
        ~Window();

        //core functions 
        bool openWindow();
        bool occupiedWindow();
        void assignCustomer(Customer *customer, int serviceTime); 
        void update();
        Customer* releaseCustomer();
        

        //aux functions 
        bool getIsOpen();  
};
#endif 
