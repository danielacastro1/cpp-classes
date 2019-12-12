//Daniela Castro
//
//Dr. Taiwoo Park
//CSC2340 - Spring 2019
//
//In this lab we will rework with Lab2 using C++ classes.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#include "calldb2.h"

void printCALL(CALL& call) {
    cout
    << left << setw(10) << call.getFormattedStart()
    << left << setw(9)  << call.getCountryCode()
    << left << setw(16) << call.getLocalPhone()
    << call.getFormattedDuration()
    << endl;
}

void printHEAD() {
    cout
    << left << setw(10) << "Time"
    << left << setw(9)  << "Country"
    << left << setw(16) << "Phone Number"
    << "Duration"
    << endl;
}

void printDB(CALLDB& calldb) {
    unsigned int numCalls = calldb.getCountCalls();
    if (numCalls == 0) {
        cout << "No records" << endl;
        return;
    }
    
    printHEAD();
    
    for (unsigned int i = 0; i < numCalls; i++) {
        CALL call;
        calldb.getCall(i, call);
        printCALL(call);
    }
}

void search(CALLDB& mainDB, string prefix) {
    int index = 0;
    int count = 0;
    
    // Find the matching prefix till FindByPhonePrefixInCallDB returns -1
    while(true) {
        index = mainDB.findByPrefix(index, prefix);
        if (index == -1) {
            break;
        }
        
        if (count == 0) {
            printHEAD();
        }
        
        CALL call;
        mainDB.getCall(index, call);
        printCALL(call);
        
        count++;
        index++;
    }
    
    if (count == 0) {
        std::cout << "No Records" << std::endl;
    }
}

int main() {
    CALLDB mainDB = CALLDB();
    string filename;
    ifstream filestream;
    
    // Prompt the user for file input
    cout << "File Name:" << endl;
    cin >> filename;
    
    // Start file IO operations
    filestream.open(filename);
    if (!filestream.is_open()) {
        std::cout << "Can't open '" << filename << "'" << std::endl;
        return 1;
    }
    
    // Load the database and log the numbers
    int dropped = mainDB.load(filestream);
    int added = mainDB.getCountCalls();
    cout << "Log successfully read into database, " << added << " records added, " << dropped << " dropped\n" << endl;
    filestream.close();
    
    
    // Print out the records
    std::cout << "Contents of Call Database" << std::endl;
    printDB(mainDB);
    
    // Search by matching prefix
    while(true) {
        string prefix;
        std::cout << "\nE164 prefix for query:" << std::endl;
        std::cin >> prefix;
        
        if (prefix == "-1") {
            break;
        }
        
        search(mainDB, prefix);
    }
    
    return 0;
}
