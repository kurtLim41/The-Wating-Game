#include "ServiceCenter.h"
#include <fstream>
#include <string>

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

void ServiceCenter::runSimulation(string inputFile){
    string line;

    //opens input file
    ifstream fin (inputFile);
    if(!fin){
        cerr << "cannot open inputFile"; //handles error if it cant open file
        return;
    }

    //skip the first 3 lines that set up simulation 
    for (int i = 0; i < 3; ++i) {
        getline(fin, line);
    }

    //set up variables for reading rest of txt
    int arrivalTime , numStudents;
    //run through rest of lines
    while(getline(fin,line)){
        fin >> arrivalTime >> numStudents;
        

    }





}

