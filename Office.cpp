#include "Office.h"
#include "ServiceCenter.h"


Office::Office(){ //default constructor, never really gonna use this 

}

Office::Office(string name, int w){
    officeName = name;
    numWindows = w;
    totalOpenWindows = numWindows;
    officeQueue = new ListQueue<Customer>; 
    officeWindows = new Window[numWindows];

    totalWaitTime = 0; 
    longestWaitTime = 0;
    over10MinutesCount = 0;
    totalIdleTime = 0;
    longestIdleTime = 0;
    over5MinutesIdleCount = 0;
    totalCustomers = 0;
    
    
    //fill officeWindow array with windows 
    for (int i = 0; i < numWindows; ++i){
        officeWindows[i] = Window();
    }

}

Office::~Office(){
    delete[] officeWindows;
    delete officeQueue;
}

bool Office::hasOpenWindow(){
    for (int i = 0; i < numWindows; ++i){
        if(officeWindows[i].getIsOpen()){
            return true;
        }
    }
    return false;
}

void Office::addCustomertoQueue(Customer *newCustomer){
    officeQueue->insert(newCustomer);
}

bool Office::sendToWindow(Customer *customer){
    for(int i = 0; i < numWindows; ++i){
        if(officeWindows[i].getIsOpen()){
            int serviceTime = 0;
            // Determine the required service time based on the office type
            if (customer->getCurrentOffice() == 'R') {
                serviceTime = customer->getRegisterTime();
            } else if (customer->getCurrentOffice() == 'C') {
                serviceTime = customer->getCashierTime();
            } else if (customer->getCurrentOffice() == 'F') {
                serviceTime = customer->getFinancialAidTime();
            }

            // Get the total wait time from the customer
            int waitTime = customer->getTotalWaitTime();
            totalWaitTime += waitTime;  // Update total wait time for the office
            if (waitTime > longestWaitTime) {
                longestWaitTime = waitTime;  // Update longest wait time if this one is longer
            }
            if (waitTime > 10) {
                over10MinutesCount++;  // Increment the count of customers who waited over 10 minutes
            }

            officeWindows[i].assignCustomer(customer , serviceTime);
            officeQueue->remove();
            return true;
        }
    }
    return false;
}

bool Office::isQueueEmpty(){
    return officeQueue->isEmpty();
}

vector<Customer*> Office::updateOffice() {
    std::vector<Customer*> completedCustomers;
    cout << "here" << endl;

    // First check the queue and try to send customers to any available open window
    while (!isQueueEmpty()) {
        bool assigned = false;
        for (int i = 0; i < numWindows && !assigned; i++) {
            if (officeWindows[i].getIsOpen()) {
                Customer *customer = officeQueue->peek(); // Peek at the front customer
                sendToWindow(customer);
                officeQueue->remove(); // Remove from queue only if sent to window
                assigned = true; // Stop looking for an open window after assigning the customer
            }
        }
        if (!assigned) break; // If no windows are open, break out of the loop
    }

    for (int i = 0; i < numWindows; i++) {
        if (!officeWindows[i].getIsOpen()) { //runs if there is a person at the window 
            officeWindows[i].update(); // Decrement time at window

            if (officeWindows[i].getIsOpen()) {
                Customer* customer = officeWindows[i].releaseCustomer();

                // Track the idle time statistics
                int idleTime = officeWindows[i].getIdleTime();
                totalIdleTime += idleTime;  // Aggregate total idle time for statistical purposes
                if (idleTime > longestIdleTime) {
                    longestIdleTime = idleTime;  // Check and update longest idle time
                }
                if (idleTime > 5) {
                    over5MinutesIdleCount++;  // Increment count of windows idle over 5 minutes
                }
                officeWindows[i].resetIdleTime(); 

                if (customer->updateToNextOffice()) { // Check if they have more offices to visit
                    completedCustomers.push_back(customer);
                } else {
                     // Here we can collect final statistics before deleting the customer
                    int totalWaitTimeCustomer = customer->getTotalWaitTime();
                    totalWaitTime += totalWaitTimeCustomer; // Update office's total wait time
                    if (totalWaitTimeCustomer > longestWaitTime) {
                        longestWaitTime = totalWaitTimeCustomer; // Check and update longest wait time
                    }
                    if (totalWaitTimeCustomer > 10) {
                        over10MinutesCount++;  // Increment count of customers who waited over 10 minutes
                    }
                    // Handle completion directly if no further offices to visit
                    delete customer; // Or collect statistics before deleting
                }
            }
        }
        else {
            // Update idle time for open windows
            officeWindows[i].updateIdleTime(); 
        }
    }
    return completedCustomers;
}


double Office::getMeanWaitTime() const {
    return numWindows > 0 ? totalWaitTime / totalCustomers : 0;
}

int Office::getLongestWaitTime() const {
    return longestWaitTime;
}

int Office::getOver10MinutesCount() const {
    return over10MinutesCount;
}

double Office::getMeanIdleTime() const {
    return numWindows > 0 ? totalIdleTime / numWindows : 0;
}

int Office::getLongestIdleTime() const {
    return longestIdleTime;
}

int Office::getOver5MinutesIdleCount() const {
    return over5MinutesIdleCount;
}

bool Office::allWindowsEmpty(){
    bool temp = true;
    for (int i = 0; i < numWindows; ++i){
        if(!officeWindows[i].getIsOpen()){
            temp = false;
        }
    }
    return temp;
}

void Office::increaseTotalCustomerCount(){
    totalCustomers++;
}

