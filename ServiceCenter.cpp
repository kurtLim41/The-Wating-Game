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


void ServiceCenter::runSimulation( string inputFile) {
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
    while (!allQueuesEmpty() || !fin.eof()) {
        if (!line.empty()) {
            stringstream ssGetArrivalTime(line);
            ssGetArrivalTime >> arrivalTime;
            getline(fin,line);
            stringstream ssGetNum(line);
            ssGetNum >> numStudents;
            cout << "ArrivalTime: " << arrivalTime << " Number of Students: " << numStudents << endl;

            // Process each customer arriving at the current tick
            getline(fin, line);
            stringstream ssGetInfo(line);
            for (int i = 0; i < numStudents; ++i) {
                ssGetInfo >> registrarTime >> cashierTime >> financialAidTime >> officeOrder1 >> officeOrder2 >> officeOrder3;
                cout << registrarTime << cashierTime << financialAidTime << officeOrder1 << officeOrder2 << officeOrder3 << endl;
                
                Customer customer(registrarTime, cashierTime, financialAidTime, officeOrder1, officeOrder2, officeOrder3);
                //cout << customer.getCurrentOffice() << endl;
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
        
            registar->updateOffice();
            cashier->updateOffice();
            financialAid->updateOffice();


            currentTime++;  // Increment time only when all events at current time are processed
        
    }

    // Close file stream
    fin.close();

    // Optional: Output or collect final statistics
    displayStatistics();
}


void ServiceCenter::displayStatistics() {
    // Displaying wait time statistics
    cout << "Registrar Mean Wait Time: " << registar->getMeanWaitTime() << " minutes" << endl;
    cout << "Cashier Mean Wait Time: " << cashier->getMeanWaitTime() << " minutes" << endl;
    cout << "Financial Aid Mean Wait Time: " << financialAid->getMeanWaitTime() << " minutes" << endl;

    cout << "Registrar Longest Wait Time: " << registar->getLongestWaitTime() << " minutes" << endl;
    cout << "Cashier Longest Wait Time: " << cashier->getLongestWaitTime() << " minutes" << endl;
    cout << "Financial Aid Longest Wait Time: " << financialAid->getLongestWaitTime() << " minutes" << endl;

    // Total students waiting over 10 minutes across all offices
    cout << "Total Students Waiting Over 10 Minutes: " 
         << registar->getOver10MinutesCount() + cashier->getOver10MinutesCount() + financialAid->getOver10MinutesCount() << endl;

    // Displaying window idle time statistics
    cout << "Registrar Mean Window Idle Time: " << registar->getMeanIdleTime() << " minutes" << endl;
    cout << "Cashier Mean Window Idle Time: " << cashier->getMeanIdleTime() << " minutes" << endl;
    cout << "Financial Aid Mean Window Idle Time: " << financialAid->getMeanIdleTime() << " minutes" << endl;

    cout << "Registrar Longest Window Idle Time: " << registar->getLongestIdleTime() << " minutes" << endl;
    cout << "Cashier Longest Window Idle Time: " << cashier->getLongestIdleTime() << " minutes" << endl;
    cout << "Financial Aid Longest Window Idle Time: " << financialAid->getLongestIdleTime() << " minutes" << endl;

    cout << "Number of Windows Idle Over 5 Minutes (Registrar): " << registar->getOver5MinutesIdleCount() << endl;
    cout << "Number of Windows Idle Over 5 Minutes (Cashier): " << cashier->getOver5MinutesIdleCount() << endl;
    cout << "Number of Windows Idle Over 5 Minutes (Financial Aid): " << financialAid->getOver5MinutesIdleCount() << endl;
}










