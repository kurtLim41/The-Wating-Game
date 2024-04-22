#include "ServiceCenter.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

ServiceCenter::ServiceCenter(string inputFile){
    string line;

    //opens input file
    ifstream fin (inputFile);
    if(!fin){
        cerr << "cannot open inputFile"; //handles error if it cant open file
    }

    int inputNums[3];  //one spot in array for the first 3 lines
    int temp = 0;
    while(fin >> inputNums[temp] && temp < 3){  //while loop to get each line 
        temp++;
    }
    fin.close();  //closes file 

    registar = new Office("registar" , inputNums[0]);
    cashier = new Office("cashier" , inputNums[1]);
    financialAid = new Office("financialAid" , inputNums[2]);

    totalWaitTimeRegistar = 0;
    totalWaitTimeCashier = 0;
    totalWaitTimeFinancialAid = 0;

    longestWaitTimeRegistar = 0;
    longestWaitTimeCashier = 0;
    longestWaitTimeFinancialAid = 0;

    waiting10MinCount = 0;

    WindowIDLERegistar = 0;
    WindowIDLECashier = 0;
    WindowIDLEFinancialAid = 0;

    WindowLongestWaitRegistar = 0;
    WindowLongestWaitCashier = 0;
    WindowLongestWaitFinancialAid = 0;

}

ServiceCenter::~ServiceCenter(){
    delete registar;
    delete cashier;
    delete financialAid;
}

bool ServiceCenter::allQueuesEmpty(){
    if (registar->isQueueEmpty() && cashier->isQueueEmpty() && financialAid->isQueueEmpty())
        return true;
    return false;
}


void ServiceCenter::runSimulation( string& inputFile) {
    string line;
    ifstream fin(inputFile);
    if (!fin) {
        cerr << "Cannot open input file" << endl;
        return;
    }

    // Skip the initial setup lines that define the number of windows in each office
    for (int i = 0; i < 3; ++i) {
        getline(fin, line);  // This just reads the lines but does nothing with them yet
    }

    int arrivalTime, numStudents;
    int registrarTime, cashierTime, financialAidTime;
    char officeOrder1, officeOrder2, officeOrder3;

    // Main simulation loop
    int currentTime = 0;  // Start simulation time
    while (!allQueuesEmpty() || getline(fin, line)) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> arrivalTime >> numStudents;

            // Process each customer arriving at the current tick
            for (int i = 0; i < numStudents; ++i) {
                ss >> registrarTime >> cashierTime >> financialAidTime >> officeOrder1 >> officeOrder2 >> officeOrder3;
                
                Customer customer(registrarTime, cashierTime, financialAidTime, officeOrder1, officeOrder2, officeOrder3);
                switch (customer.getCurrentOffice()) {
                    case 'R':
                        registar->addCustomertoQueue(customer);
                        break;
                    case 'C':
                        cashier->addCustomertoQueue(customer);
                        break;
                    case 'F':
                        financialAid->addCustomertoQueue(customer);
                        break;
                    default:
                        cerr << "Invalid office" << endl;
                        break;
                }
            }
        }

        // Process each office at current time before moving to the next time
        if (currentTime == arrivalTime) {
            registar->updateOffice();
            cashier->updateOffice();
            financialAid->updateOffice();
            currentTime++;  // Increment time only when all events at current time are processed
        }
    }

    // Close file stream
    fin.close();

    // Optional: Output or collect final statistics
    // printStatistics();
}










