#include <iostream>
#include <iomanip>  // For formatting output
#include <string>
#include <fstream>  // For file handling
using namespace std;

// Struct to represent an employee
struct Employee {
    string name;
    int id;
    double hourlyRate;
    double totalHours;
    double taxDeduction;

    // Function to input employee details
    void inputDetails() {
        cout << "Enter Employee Name: ";
        getline(cin, name);
        cout << "Enter Employee ID: ";
        cin >> id;
        cout << "Enter Rupees per Hour: ";
        cin >> hourlyRate;
        cout << "Enter Total Hours Worked: ";
        cin >> totalHours;
        cout << "Enter Tax Deduction (%): ";
        cin >> taxDeduction;
        cin.ignore();  // Clear the input buffer
    }

    // Function to calculate gross salary
    double calculateGrossSalary() const {
        return hourlyRate * totalHours;
    }

    // Function to calculate net salary
    double calculateNetSalary() const {
        double grossSalary = calculateGrossSalary();
        double tax = grossSalary * (taxDeduction / 100.0);
        return grossSalary - tax;
    }

    // Function to generate and display payslip
    void generatePayslip() const {
        cout << "\n===== PAYSLIP =====\n";
        cout << "Employee Name: " << name << '\n';
        cout << "Employee ID: " << id << '\n';
        cout << "Hourly Rate: Rs. " << hourlyRate << '\n';
        cout << "Total Hours Worked: " << totalHours << '\n';
        cout << "Gross Salary: Rs. " << calculateGrossSalary() << '\n';
        cout << "Tax Deduction (" << taxDeduction << "%): Rs. "
             << calculateGrossSalary() * (taxDeduction / 100.0) << '\n';
        cout << "Net Salary: Rs. " << calculateNetSalary() << '\n';
        cout << "===================\n";
    }

    // Function to save payslip to a file
    void savePayslipToFile(ofstream& outFile) const {
        if (outFile.is_open()) {
            outFile << "===== PAYSLIP =====\n";
            outFile << "Employee Name: " << name << '\n';
            outFile << "Employee ID: " << id << '\n';
            outFile << "Hourly Rate: Rs. " << hourlyRate << '\n';
            outFile << "Total Hours Worked: " << totalHours << '\n';
            outFile << "Gross Salary: Rs. " << calculateGrossSalary() << '\n';
            outFile << "Tax Deduction (" << taxDeduction << "%): Rs. "
                    << calculateGrossSalary() * (taxDeduction / 100.0) << '\n';
            outFile << "Net Salary: Rs. " << calculateNetSalary() << '\n';
            outFile << "===================\n\n";
        } else {
            cerr << "Error: Unable to open file for writing.\n";
        }
    }
};

int main() {
    const int MAX_EMPLOYEES = 10;  // Maximum number of employees
    Employee employees[MAX_EMPLOYEES];
    int numEmployees;

    cout << "=== Payroll System ===\n";
    cout << "Enter the number of employees (max " << MAX_EMPLOYEES << "): ";
    cin >> numEmployees;
    cin.ignore();  // Clear the input buffer

    if (numEmployees > MAX_EMPLOYEES || numEmployees <= 0) {
        cerr << "Invalid number of employees. Exiting program.\n";
        return 1;
    }

    // Input details for all employees
    for (int i = 0; i < numEmployees; ++i) {
        cout << "\nEnter details for Employee " << (i + 1) << ":\n";
        employees[i].inputDetails();
    }

    // Generate and display payslips for all employees
    ofstream outFile("Employee_Payslips.txt", ios::app);  // Open file in append mode
    for (int i = 0; i < numEmployees; ++i) {
        cout << "\nPayslip for Employee " << (i + 1) << ":\n";
        employees[i].generatePayslip();
        employees[i].savePayslipToFile(outFile);
    }
    outFile.close();
    cout << "\nAll payslips saved to 'Employee_Payslips.txt'.\n";

    return 0;
}

