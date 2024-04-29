#ifndef OFFICE_H
#define OFFICE_H

#include "ListQueue.h"
#include "Window.h"
#include "Customer.h"
#include <iostream>
#include <array>
#include <vector>
using namespace std;

class Office{
    private:
        string officeName;
        unsigned int numWindows;
        unsigned int totalOpenWindows;
        ListQueue<Customer> *officeQueue;  //change type class to customer once i create that <Customer> 
        Window *officeWindows;

        // Statistics tracking
        double totalWaitTime;
        int longestWaitTime;
        int over10MinutesCount;
        double totalIdleTime;
        int longestIdleTime;
        int over5MinutesIdleCount;
        int totalCustomers;

    
    public:
        Office(); //no gonna be used 
        Office(string name , int w);
        ~Office();

        //core functions 
        bool hasOpenWindow();
        void addCustomertoQueue(Customer *newCustomer);
        bool sendToWindow(Customer *customer);
        bool isQueueEmpty();
        bool allWindowsEmpty();
        vector<Customer*> updateOffice();

        double getMeanWaitTime() const;
        int getLongestWaitTime() const;
        int getOver10MinutesCount() const;
        double getMeanIdleTime() const;
        int getLongestIdleTime() const;
        int getOver5MinutesIdleCount() const;
        void increaseTotalCustomerCount();




};

#endif 
