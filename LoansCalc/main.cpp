#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

// Structure to represent loan details
struct Loan {
    string loan_id; // Loan ID
    double principal_amount; // Principal amount
    double interest_rate; // Interest rate
    int loan_term; // Loan term
    long start_date; // Unix timestamp for start date
    int payment_frequency; // Payment frequency
    double monthly_payment; // Monthly payment
    double to_be_paid_depending_on_frequency; // Total to be paid depending on frequency
    long finish_date; // Unix timestamp for finish date
};

// Comparator for sorting loans based on start date (FCFS)
bool firstComeFirstServed(const Loan& a, const Loan& b) {
    return a.start_date < b.start_date;
}

// Comparator for sorting loans based on loan term (SJF)
bool shortestJobFirst(const Loan& a, const Loan& b) {
    return a.loan_term < b.loan_term;
}

// Function to calculate monthly payment for a loan
Loan calculate_monthly_payment(const Loan& loan) {
    Loan result = loan;
    double p = loan.principal_amount;
    double r = loan.interest_rate / 100.0;
    double t = loan.loan_term;

    // Calculate the total amount to be paid
    double total_to_be_paid = p * (1 + (r * t));

    // Calculate finish date based on start date and loan term
    result.finish_date = loan.start_date + loan.loan_term * 30 * 24 * 60 * 60;

    // Monthly payment is the total amount to be paid
    result.monthly_payment = total_to_be_paid;

    return result;
}

// Function to calculate total to be paid per month depending on payment frequency for a loan
Loan calculate_to_be_paid_per_month(const Loan& loan) {
    Loan result = loan;
    double p = loan.principal_amount;
    double r = loan.interest_rate / 100.0;
    double t = loan.loan_term;

    // Calculate the total amount to be paid
    double total_to_be_paid = p * (1 + (r * t));

    // Total payment depending on frequency is total amount to be paid divided by loan term
    result.to_be_paid_depending_on_frequency = total_to_be_paid / t;
    return result;
}

// Function to read loan data from a CSV file
vector<Loan> read_loan_data(const string& filename) {
    vector<Loan> loans;
    ifstream file(filename);
    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        Loan loan;
        int col = 0;

        while (getline(iss, token, ',')) {
            switch (col) {
                case 0:
                    loan.loan_id = token;
                    break;
                case 1:
                    loan.principal_amount = stod(token);
                    break;
                case 2:
                    loan.interest_rate = stod(token);
                    break;
                case 3:
                    loan.loan_term = stoi(token);
                    break;
                case 4:
                    loan.start_date = stol(token);
                    break;
                case 5:
                    loan.payment_frequency = stoi(token);
                    break;
                default:
                    break;
            }
            col++;
        }
        loans.push_back(loan);
    }
    return loans;
}

// Function to write loan order to a file
void write_loan_order(const string& filename, const vector<Loan>& loans) {
    ofstream file(filename);
    for (const auto& loan : loans) {
        file << loan.loan_id << "," << loan.finish_date << "\n";
    }
}

// Function to write loan data with monthly payments and total payment depending on frequency to a file
void write_loan_data(const string& filename, const vector<Loan>& loans) {
    ofstream file(filename);
    file << "Loan ID,Principal Amount,Interest Rate,Loan Term,Start Date,Payment Frequency,Finish Date,Total to be paid,Payment per month\n";
    for (const auto& loan : loans) {
        file << loan.loan_id << "," << loan.principal_amount << "," << loan.interest_rate << "," << loan.loan_term << ","
             << loan.start_date << "," << loan.payment_frequency << "," << loan.finish_date << ","
             << loan.monthly_payment << "," << loan.to_be_paid_depending_on_frequency << "\n";
    }
}

// Main function
int main() {
    string input_file = "loans.csv";
    string fcfs_output_file = "loan_order_fcfs.txt";
    string output_file = "loan_data_with_monthly_payment.csv";
    string sjf_output_file = "loan_order_sjf.txt";

    vector<Loan> loans = read_loan_data(input_file);

    for (auto& loan : loans) {
        loan = calculate_monthly_payment(loan);
        loan = calculate_to_be_paid_per_month(loan);
    }

    vector<Loan> fcfs_loans = loans;
    sort(fcfs_loans.begin(), fcfs_loans.end(), firstComeFirstServed);

    write_loan_order(fcfs_output_file, fcfs_loans);
    cout << "Loan order saved for FCFS." << endl;

    vector<Loan> sjf_loans = loans;
    sort(sjf_loans.begin(), sjf_loans.end(), shortestJobFirst);

    write_loan_order(sjf_output_file, sjf_loans);
    cout << "Loan order saved for SJF." << endl;

    write_loan_data(output_file, loans);
    cout << "Monthly payments and total payment depending on frequency calculated and written to " << output_file << endl;

    return 0;
}
