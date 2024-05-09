#include <iostream> // Input/output stream operations
#include <fstream> // File stream operations
#include <sstream> // String stream operations
#include <vector> // Vector container
#include <string> // String operations
#include <cmath> // Math functions
#include <algorithm> // Algorithms for sorting

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
};

// Comparator for sorting loans based on start date (FCFS)
bool firstComeFirstServed(const Loan& a, const Loan& b) {
    return a.start_date < b.start_date; // Compare start dates
}

// Comparator for sorting loans based on loan term (SJF)
bool shortestJobFirst(const Loan& a, const Loan& b) {
    return a.loan_term < b.loan_term; // Compare loan terms
}

// Function to calculate monthly payment for a loan
Loan calculate_monthly_payment(const Loan& loan) {
    Loan result = loan;
    double p = loan.principal_amount; // Principal amount
    double r = loan.interest_rate / 100.0; // Convert interest rate to decimal
    double t = loan.loan_term; // Loan term

    // Calculate the total amount to be paid
    double total_to_be_paid = p * (1 + (r * t));

    // Monthly payment is the total amount to be paid
    result.monthly_payment = total_to_be_paid;

    return result;
}

// Function to calculate total to be paid per month depending on payment frequency for a loan
Loan calculate_to_be_paid_per_month(const Loan& loan) {
    Loan result = loan;
    double p = loan.principal_amount; // Principal amount
    double r = loan.interest_rate / 100.0; // Convert interest rate to decimal
    double t = loan.loan_term; // Loan term

    // Calculate the total amount to be paid
    double total_to_be_paid = p * (1 + (r * t));

    // Total payment depending on frequency is total amount to be paid divided by loan term
    result.to_be_paid_depending_on_frequency = total_to_be_paid / t;
    return result;
}

// Function to read loan data from a CSV file
vector<Loan> read_loan_data(const string& filename) {
    vector<Loan> loans; // Vector to store loans
    ifstream file(filename); // Open file for reading
    string line;
    getline(file, line); // Skip header

    // Parse each line of the CSV file
    while (getline(file, line)) {
        istringstream iss(line); // Create string stream for line
        string token;
        Loan loan;
        int col = 0;

        // Tokenize each line by comma and assign values to loan struct members
        while (getline(iss, token, ',')) {
            switch (col) {
                case 0:
                    loan.loan_id = token; // Assign loan ID
                    break;
                case 1:
                    loan.principal_amount = stod(token); // Convert and assign principal amount
                    break;
                case 2:
                    loan.interest_rate = stod(token); // Convert and assign interest rate
                    break;
                case 3:
                    loan.loan_term = stoi(token); // Convert and assign loan term
                    break;
                case 4:
                    loan.start_date = stol(token); // Convert and assign start date
                    break;
                case 5:
                    loan.payment_frequency = stoi(token); // Parse as int and assign payment frequency
                    break;
                default:
                    break;
            }
            col++;
            /*
            _LIBCPP_FUNC_VIS int                stoi  (const string& __str, size_t* __idx = nullptr, int __base = 10);
            _LIBCPP_FUNC_VIS long               stol  (const string& __str, size_t* __idx = nullptr, int __base = 10);
            _LIBCPP_FUNC_VIS unsigned long      stoul (const string& __str, size_t* __idx = nullptr, int __base = 10);
            _LIBCPP_FUNC_VIS long long          stoll (const string& __str, size_t* __idx = nullptr, int __base = 10);
            _LIBCPP_FUNC_VIS unsigned long long stoull(const string& __str, size_t* __idx = nullptr, int __base = 10);*/
        }
        loans.push_back(loan); // Add loan to vector
    }
    return loans; // Return vector of loans
}

// Function to write loan order to a file
void write_loan_order(const string& filename, const vector<Loan>& loans) {
    ofstream file(filename); // Open file for writing
    for (const auto& loan : loans) {
        file << loan.loan_id << "\n"; // Write loan ID to file
    }
}

// Function to write loan data with monthly payments and total payment depending on frequency to a file
void write_loan_data(const string& filename, const vector<Loan>& loans) {
    ofstream file(filename); // Open file for writing
    file << "Loan ID,Principal Amount,Interest Rate,Loan Term,Start Date,Payment Frequency,Total to be paid,Payment per month\n"; // Write header
    for (const auto& loan : loans) {
        file << loan.loan_id << "," << loan.principal_amount << "," << loan.interest_rate << "," << loan.loan_term << ","
             << loan.start_date << "," << loan.payment_frequency << ","  << loan.monthly_payment << ","
             << loan.to_be_paid_depending_on_frequency << "\n"; // Write loan data to file
    }
}

// Main function
int main() {
    // File names for input and output
    string input_file = "loans.csv";
    string fcfs_output_file = "loan_order_fcfs.txt";
    string output_file = "loan_data_with_monthly_payment.csv";
    string sjf_output_file = "loan_order_sjf.txt";

    // Read loan data from CSV file
    vector<Loan> loans = read_loan_data(input_file);

    // Calculate monthly payments and total payment depending on frequency for each loan
    for (auto& loan : loans) {
        loan = calculate_monthly_payment(loan);
        loan = calculate_to_be_paid_per_month(loan);
    }

    // Sort loans for FCFS scheduling
    vector<Loan> fcfs_loans = loans;
    sort(fcfs_loans.begin(), fcfs_loans.end(), firstComeFirstServed);

    // Write FCFS loan order to file
    write_loan_order(fcfs_output_file, fcfs_loans);
    cout << "Loan order saved for FCFS." << endl;

    // Sort loans for SJF scheduling
    vector<Loan> sjf_loans = loans;
    sort(sjf_loans.begin(), sjf_loans.end(), shortestJobFirst);

    // Write SJF loan order to file
    write_loan_order(sjf_output_file, sjf_loans);
    cout << "Loan order saved for SJF." << endl;

    // Write loan data with monthly payments and total payment depending on frequency to file
    write_loan_data(output_file, loans);
    cout << "Monthly payments and total payment depending on frequency calculated and written to " << output_file << endl;

    return 0; // Return success
}
