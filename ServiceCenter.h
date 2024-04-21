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

        //stats to keep track of for the mean wait time for each office
        double totalWaitTimeRegistar;
        double totalWaitTimeCashier;
        double totalWaitTimeFinancialAid;
        //stats to keep track of for the lognest wait time for each office
        int longestWaitTimeRegistar;
        int longestWaitTimeCashier;
        int longestWaitTimeFinancialAid;
        //stat to keep track of for students waiting over 10+ mins for all offices 
        int waiting10MinCount;
        //stats to keep track of for the mean IDLE time for the windows at each office
        double WindowIDLERegistar;
        double WindowIDLECashier;
        double WindowIDLEFinancialAid;
        //stats to keep track of for the longest window IDLE time for each office 
        int WindowLongestWaitRegistar;
        int WindowLongestWaitCashier;
        int WindowLongestWaitFinancialAid;

    public:
        ServiceCenter(string inputFile);
        ~ServiceCenter();

        void runSimulation(string inputFile);

        
};





#endif