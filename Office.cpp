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

void Office::addCustomertoQueue(Customer newCustomer){
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

            officeWindows[i].assignCustomer(customer , serviceTime);
            return true;
        }
    }
    return false;
}

bool Office::isQueueEmpty(){
    officeQueue->isEmpty();
}

vector<Customer*> Office::updateOffice() {
    std::vector<Customer*> completedCustomers;

    for (int i = 0; i < numWindows; i++) {
        if (!officeWindows[i].getIsOpen()) {
            officeWindows[i].update(); // Decrement time at window

            if (officeWindows[i].getIsOpen()) {
                Customer* customer = officeWindows[i].releaseCustomer();
                if (customer->updateToNextOffice()) { // Check if they have more offices to visit
                    completedCustomers.push_back(customer);
                } else {
                    // Handle completion directly if no further offices to visit
                    delete customer; // Or collect statistics before deleting
                }
            }
        }
    }
    return completedCustomers;
}

