# Loan Payment Scheduler with File Input

This project aims to develop a C++ program capable of efficiently managing loan details parsed from CSV files, scheduling monthly loan payments based on financial parameters, and presenting the payment schedule through a command-line interface.

The objective of the project is to develop a program that reads loan details from a CSV file, schedules monthly loan payments, and displays the payment schedule in the command-line interface. This involves parsing CSV files, calculating payment schedules based on financial parameters, and presenting the schedule effectively.

## Libraries

### Common Libraries 
- `<iostream>`: Handles input and output.
- `<fstream>`: Manages file input/output.

### Main Project
    
- `<sstream>`: Manipulates string streams efficiently.
- `<vector>`: Implements dynamic arrays.
- `<string>`: Offers string manipulation functions.
- `<cmath>`: Provides mathematical operations.

### Side Project

- `faker-cxx/Date.h`: Provides functionality for generating fake dates.
- `faker-cxx/Finance.h`: Offers functionality for generating fake financial data.
- [faker-cxx](https://github.com/cieslarmichal/faker-cxx): Source for the data generating library.

## Formulas

### Monthly Payment Calculation Formula

The monthly payment (M) for a loan can be calculated using the formula:

```
A = p * (1+(r*t))
```

Where:
- `A` Total to be paid with the intrest.
- `p` is the principal loan amount.
- `r` is the monthly interest rate (expressed as a decimal).
- `t` is the time in months.

This formula helps in determining the amount to be paid towards a loan, considering factors like principal amount, interest rate, and duration of the loan.
