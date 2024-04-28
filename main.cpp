#include "LinkedList.h"
#include "ListQueue.h"
#include "ServiceCenter.h"
#include "Customer.h"

int main(){
    
    ListQueue<Customer> *test  = new ListQueue<Customer>;

    test->insert(Customer(1,2,3,'a','b','c'));
    test->insert(Customer(2,2,3,'a','b','c'));
    test->insert(Customer(3,2,3,'a','b','c'));

    cout << test->getSize() << endl;

    test->remove();

    cout << test->getSize() << endl;

    

    ServiceCenter chapman("input.txt");
    chapman.runSimulation("input.txt");


}