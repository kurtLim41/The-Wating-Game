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


bool ServiceCenter::allWindowsEmpty(){
    if(registar->allWindowsEmpty() && cashier->allWindowsEmpty() && financialAid->allWindowsEmpty())
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
        cout << line << endl;
    }

    int arrivalTime, numStudents;
    int registrarTime, cashierTime, financialAidTime;
    char officeOrder1, officeOrder2, officeOrder3;

    // Main simulation loop
    int currentTime = 0;  // Start simulation time
    while (!allWindowsEmpty() || !fin.eof()) {
        if (!line.empty()) {
            if (!getline(fin, line)) break;  // Safely attempt to read the next line for arrival time
            stringstream ss(line);
            ss >> arrivalTime;  // Parse arrival time

            if (!getline(fin, line)) break;  // Safely attempt to read the next line for number of students
            stringstream ssNumStudents(line);
            ssNumStudents >> numStudents;
            cout << "ArrivalTime: " << arrivalTime << " Number of Students: " << numStudents << endl;

            // Process each customer arriving at the current tick
            for (int i = 0; i < numStudents; ++i) {
                if (!getline(fin, line)) break;  // Read each student's detail line
                stringstream ssDetail(line);
                ssDetail >> registrarTime >> cashierTime >> financialAidTime >> officeOrder1 >> officeOrder2 >> officeOrder3;
                cout << registrarTime << cashierTime << financialAidTime <<  officeOrder1 << officeOrder2 << officeOrder3 << endl;
                
                Customer* customer = new Customer(registrarTime, cashierTime, financialAidTime, officeOrder1, officeOrder2, officeOrder3);
                //cout << customer.getCurrentOffice() << endl;
                switch (customer->getCurrentOffice()) {
                    case 'R':
                        registar->addCustomertoQueue(customer);
                        registar->increaseTotalCustomerCount();
                        break;
                    case 'C':
                        cashier->addCustomertoQueue(customer);
                        cashier->increaseTotalCustomerCount();
                        break;
                    case 'F':
                        financialAid->addCustomertoQueue(customer);
                        financialAid->increaseTotalCustomerCount();
                        break;
                    default:
                        cerr << "Invalid office" << endl;
                        break;
                }
            }
        }

        // Process each office at current time before moving to the next time
        
        // Collect customers needing further processing from all offices
        vector<Customer*> customersToRoute;
        vector<Customer*> temp;
        temp = registar->updateOffice();
        customersToRoute.insert(customersToRoute.end(), temp.begin(), temp.end());
        temp = cashier->updateOffice();
        customersToRoute.insert(customersToRoute.end(), temp.begin(), temp.end());
        temp = financialAid->updateOffice();
        customersToRoute.insert(customersToRoute.end(), temp.begin(), temp.end());

        // Route customers to the appropriate next office
        for (Customer* customer : customersToRoute) {
            switch (customer->getCurrentOffice()) {
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
                    cerr << "Invalid next office specified" << endl;
                    delete customer; // Cleanup if there's an invalid office
                    break;
            }
        }


        currentTime++;  // Increment time only when all events at current time are processed
        
    }

    // Close file stream
    fin.close();

    cout << "total Time: " << currentTime << endl;

    // Optional: Output or collect final statistics
    displayStatistics();
}


void ServiceCenter::displayStatistics() {
    // Cashier's Office Statistics
    cout << "Cashier's Office:" << endl;
    cout << "Mean student wait time: " << cashier->getMeanWaitTime() << " tick(s)" << endl;
    cout << "Mean window idle time: " << cashier->getMeanIdleTime() << " tick(s)" << endl;
    cout << "Longest student wait time: " << cashier->getLongestWaitTime() << " tick(s)" << endl;
    cout << "Longest window idle time: " << cashier->getLongestIdleTime() << " tick(s)\n" << endl;

    // Financial Aid Office Statistics
    cout << "Financial Aid Office:" << endl;
    cout << "Mean student wait time: " << financialAid->getMeanWaitTime() << " tick(s)" << endl;
    cout << "Mean window idle time: " << financialAid->getMeanIdleTime() << " tick(s)" << endl;
    cout << "Longest student wait time: " << financialAid->getLongestWaitTime() << " tick(s)" << endl;
    cout << "Longest window idle time: " << financialAid->getLongestIdleTime() << " tick(s)\n" << endl;

    // Registrar's Office Statistics
    cout << "Registrar's Office:" << endl;
    cout << "Mean student wait time: " << registar->getMeanWaitTime() << " tick(s)" << endl;
    cout << "Mean window idle time: " << registar->getMeanIdleTime() << " tick(s)" << endl;
    cout << "Longest student wait time: " << registar->getLongestWaitTime() << " tick(s)" << endl;
    cout << "Longest window idle time: " << registar->getLongestIdleTime() << " tick(s)\n" << endl;

    // Total counts across all offices
    int totalOver10Minutes = registar->getOver10MinutesCount() + cashier->getOver10MinutesCount() + financialAid->getOver10MinutesCount();
    int totalIdleOver5Minutes = registar->getOver5MinutesIdleCount() + cashier->getOver5MinutesIdleCount() + financialAid->getOver5MinutesIdleCount();
    cout << "Number of students waiting over 10 minutes across all offices: " << totalOver10Minutes << " tick(s)" << endl;
    cout << "Number of windows idle for over 5 minutes across all offices: " << totalIdleOver5Minutes << " tick(s)" << endl;
}











