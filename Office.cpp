#include "Office.h"


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

