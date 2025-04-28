#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
    int id;
    string name;
    string position;
    float salary;
};

// Add a new employee
void addEmployee() {
    ofstream outFile("employees.txt", ios::app);
    Employee emp;

    cout << "Enter ID: ";
    cin >> emp.id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, emp.name);
    cout << "Enter Position: ";
    getline(cin, emp.position);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    outFile << emp.id << " " << emp.name << " " << emp.position << " " << emp.salary << endl;
    outFile.close();

    cout << "Employee added successfully.\n";
}

// Display all employees
void displayEmployees() {
    ifstream inFile("employees.txt");
    Employee emp;
    bool found = false;

    cout << "\n--- Employee Records ---\n";
    while (inFile >> emp.id >> emp.name >> emp.position >> emp.salary) {
        cout << "ID: " << emp.id << ", Name: " << emp.name << ", Position: " << emp.position << ", Salary: " << emp.salary << endl;
        found = true;
    }
    inFile.close();

    if (!found) {
        cout << "No employee records found.\n";
    }
}

// Search for an employee by ID
void searchEmployee() {
    ifstream inFile("employees.txt");
    Employee emp;
    int searchId;
    bool found = false;

    cout << "Enter ID to search: ";
    cin >> searchId;

    while (inFile >> emp.id >> emp.name >> emp.position >> emp.salary) {
        if (emp.id == searchId) {
            cout << "\nEmployee found:\n";
            cout << "ID: " << emp.id << ", Name: " << emp.name << ", Position: " << emp.position << ", Salary: " << emp.salary << endl;
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found) {
        cout << "Employee with ID " << searchId << " not found.\n";
    }
}

// Delete an employee by ID
void deleteEmployee() {
    ifstream inFile("employees.txt");
    ofstream outFile("temp.txt");
    Employee emp;
    int deleteId;
    bool found = false;

    cout << "Enter ID to delete: ";
    cin >> deleteId;

    while (inFile >> emp.id >> emp.name >> emp.position >> emp.salary) {
        if (emp.id != deleteId) {
            outFile << emp.id << " " << emp.name << " " << emp.position << " " << emp.salary << endl;
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("employees.txt");
    rename("temp.txt", "employees.txt");

    if (found) {
        cout << "Employee deleted successfully.\n";
    } else {
        cout << "Employee with ID " << deleteId << " not found.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n--- Employee Management System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Delete Employee\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
