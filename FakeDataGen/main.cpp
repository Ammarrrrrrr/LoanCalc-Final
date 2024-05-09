#include <iostream>
#include <fstream> 
#include "faker-cxx/Date.h"
#include "faker-cxx/Finance.h"

int main()
{
    // Open a file to write the loan data in CSV format
    std::ofstream outputFile("loans.csv");

    // Write the header row
    outputFile << "Loan ID,Principal Amount,Interest Rate,Loan Term,Start Date,Payment Frequency\n";

    // Generate data for 10 loans
    for (int i = 0; i < 10; ++i) {
        // Generate loan details
        const auto loanId = i + 1; 
        const auto principalAmount = faker::Finance::amount(100, 10000); 
        const auto interestRate = faker::Finance::amount(1, 20); 
        const auto loanTerm = faker::Finance::amount(6, 24); 
        const auto startDate = faker::Date::futureDate(5, faker::Date::DateFormat::Timestamp); 
        const auto paymentFrequency = faker::Finance::amount(3, 12); 
        
        // Write loan data to the CSV file
        outputFile << loanId << "," << principalAmount << "," << interestRate << ","
                   << loanTerm << "," << startDate << "," << paymentFrequency <<  "\n";
    }

    // Close the file
    outputFile.close();

    // Print a message indicating successful file generation
    std::cout << "CSV file 'loans.csv' has been generated.\n";

    return 0;
}
