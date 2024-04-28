#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include <iostream>
#include "office.h"
using namespace std;

class ServiceCenter{

    private: 
        Office* registar;
        Office* cashier;
        Office* financialAid;

        

    public:
        ServiceCenter(string inputFile);
        ~ServiceCenter();

        void runSimulation(string inputFile);
        bool allWindowsEmpty();
        void displayStatistics(); // Method to display comprehensive statistics

        

        
};





#endif