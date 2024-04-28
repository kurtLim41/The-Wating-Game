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
        int idleTime; // Added to track how long the window has been idle

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
        int getIdleTime(); // Retrieves the idle time of the window
        void resetIdleTime(); // Resets the idle time counter 
        void updateIdleTime();
};
#endif 
