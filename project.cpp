#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> // for stringstream (used instead of to_string)

using namespace std;

struct Employee {
    int id;
    string name;
    float hoursWorked;
    float hourlyRate;
    float bonus;
    float deduction;
    float salary;
};

// Convert int to string (for Turbo C++)
string intToStr(int number) {
    stringstream ss;
    ss << number;
    return ss.str();
}

// Admin Registration
void registerAdmin() {
    string username, password;
    ofstream file("admin.txt");
    if (!file) {
        cout << "Error creating admin file.\n";
        return;
    }
    cout << "\n=== Admin Registration ===\n";
    cout << "Set Username: ";
    cin >> username;
    cout << "Set Password: ";
    cin >> password;
    file << username << " " << password;
    file.close();
    cout << "Registration successful!\n";
}

// Admin Login
bool loginAdmin() {
    string savedUser, savedPass;
    ifstream file("admin.txt");
    if (!file) {
        cout << "No admin found. Please register first.\n";
        return false;
    }
    file >> savedUser >> savedPass;
    file.close();

    string username, password;
    cout << "\n=== Admin Login ===\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == savedUser && password == savedPass) {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Incorrect login.\n";
        return false;
    }
}

// Salary Calculation
void calculateSalary(Employee &emp) {
    emp.salary = (emp.hoursWorked * emp.hourlyRate) + emp.bonus - emp.deduction;
}

// Generate Payslip
void generatePayslip(const Employee &emp) {
    string filename = "payslip_" + intToStr(emp.id) + ".txt";
    ofstream file(filename.c_str());
    if (!file) {
        cout << "Error creating payslip file.\n";
        return;
    }
    file << "===== Employee Payslip =====\n";
    file << "ID: " << emp.id << "\n";
    file << "Name: " << emp.name << "\n";
    file << "Hours Worked: " << emp.hoursWorked << "\n";
    file << "Hourly Rate: " << emp.hourlyRate << "\n";
    file << "Bonus: " << emp.bonus << "\n";
    file << "Deduction: " << emp.deduction << "\n";
    file << "Final Salary: " << emp.salary << "\n";
    file.close();
    cout << "Payslip saved as " << filename << "\n";
}

// Add Employee
void addEmployee(vector<Employee> &employees) {
    Employee emp;
    cout << "\nEnter Employee ID: ";
    cin >> emp.id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, emp.name);
    cout << "Enter Hours Worked: ";
    cin >> emp.hoursWorked;
    cout << "Enter Hourly Rate: ";
    cin >> emp.hourlyRate;
    cout << "Enter Bonus: ";
    cin >> emp.bonus;
    cout << "Enter Deduction: ";
    cin >> emp.deduction;

    calculateSalary(emp);
    employees.push_back(emp);
    generatePayslip(emp);
}

// View Employees
void viewEmployees(const vector<Employee> &employees) {
    cout << "\n--- Employee Records ---\n";
    for (int i = 0; i < employees.size(); i++) {
        cout << "ID: " << employees[i].id
             << " | Name: " << employees[i].name
             << " | Salary: " << employees[i].salary << "\n";
    }
}

// Edit Employee
void editEmployee(vector<Employee> &employees) {
    int id;
    cout << "Enter Employee ID to edit: ";
    cin >> id;

    for (int i = 0; i < employees.size(); i++) {
        if (employees[i].id == id) {
            cout << "Editing Employee: " << employees[i].name << "\n";
            cout << "Enter New Hours Worked: ";
            cin >> employees[i].hoursWorked;
            cout << "Enter New Hourly Rate: ";
            cin >> employees[i].hourlyRate;
            cout << "Enter New Bonus: ";
            cin >> employees[i].bonus;
            cout << "Enter New Deduction: ";
            cin >> employees[i].deduction;
            calculateSalary(employees[i]);
            generatePayslip(employees[i]);
            cout << "Employee record updated.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

// Main Function
int main() {
    vector<Employee> employees;
    int choice;

    cout << "========== EMPLOYEE PAYROLL SYSTEM ==========\n";
    cout << "1. Register Admin\n";
    cout << "2. Login\n";
    cout << "Choose Option (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        registerAdmin();
        cout << "Now run the program again and select Login.\n";
        return 0;
    }

    if (!loginAdmin()) {
        cout << "Access denied.\n";
        return 0;
    }

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Edit Employee\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(employees); break;
            case 2: viewEmployees(employees); break;
            case 3: editEmployee(employees); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (choice != 4);

    return 0;
}
