#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <fstream>
#include "User.h"

using namespace std;

// Structure to store vaccination record
struct VaccinationRecord {
    string childID;
    string treatment;
    string vaccine;
    double weight;
    double height;
    string nurse;
    string clinic_date;
    string next_clinic;
    int age;
};

// Structure to store medication record
struct MedicationRecord {
    string childID;
    string treatment;
    string medication;
    double weight;
    double height;
    string doctor;
    string clinic;
    string consultationDate;
    string checkupDate;
};

// Structure to store consultation record
struct ConsultationRecord {
    string childID;
    string doctor;
    string clinic;
    string consultationDate;
    string checkupDate;
    VaccinationRecord vaccinationRecord;
    MedicationRecord medicationRecord;
};

// Function prototypes
string generateChildID(const string& firstName, const string& surname, const string& dob, int recordNumber);
bool isValidDate(const string& date);
void loadUsers(vector<User*>& users);
void saveUserToFile(const User* user);
void captureVaccinationRecord(const string& childID, vector<ConsultationRecord>& consultations);
void captureMedicationRecord(const string& childID, vector<ConsultationRecord>& consultations);
void displayVaccinationReport(const ConsultationRecord& consultation);
void displayMedicationReport(const ConsultationRecord& consultation);
void registerUser(vector<User*>& users, vector<ConsultationRecord>& consultations);
User* loginUser(vector<User*>& users);
void printReport(const vector<ConsultationRecord>& consultations);
void updateChildRecord(vector<User*>& users);
void deleteChildRecord(vector<User*>& users);

// Function implementations
string generateChildID(const string& firstName, const string& surname, const string& dob, int recordNumber) {
    string id_number;
    for (int i = 0; i < 3 && i < firstName.length(); i++) {
        id_number += toupper(firstName[i]);
    }
    id_number += "-";
    for (int i = 0; i < 3 && i < surname.length(); i++) {
        id_number += toupper(surname[i]);
    }
    id_number += "-";
    id_number += dob;
    id_number += "-" + to_string(recordNumber);
    return id_number;
}

bool isValidDate(const string& date) {
    regex dateRegex(R"((0[1-9]|1[0-2])(0[1-9]|[12][0-9]|3[01])[0-9]{4})");
    return regex_match(date, dateRegex);
}

void loadUsers(vector<User*>& users) {
    ifstream file("user_table.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type, username, password, firstName, middleName, surname, dateOfBirth, motherOrGuardian, father, village, chief, district;
        getline(ss, type, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        if (type == "CHILD") {
            Child* child = new Child();
            child->username = username;
            child->password = password;
            getline(ss, child->firstName, ',');
            getline(ss, child->middleName, ',');
            getline(ss, child->surname, ',');
            getline(ss, child->dateOfBirth, ',');
            getline(ss, child->motherOrGuardian, ',');
            getline(ss, child->father, ',');
            getline(ss, child->village, ',');
            getline(ss, child->chief, ',');
            getline(ss, child->district);
            child->childID = generateChildID(child->firstName, child->surname, child->dateOfBirth, users.size() + 1);
            users.push_back(child);
        }
        // Add other user types if needed
    }
}

void saveUserToFile(const User* user) {
    ofstream file("user_table.csv", ios::app);
    if (file.is_open()) {
        if (user->type == User::CHILD) {
            const Child* child = static_cast<const Child*>(user);
            file << "CHILD," << child->username << "," << child->password << "," 
                 << child->firstName << "," << child->middleName << "," 
                 << child->surname << "," << child->dateOfBirth << "," 
                 << child->motherOrGuardian << "," << child->father << ","
                 << child->village << "," << child->chief << "," << child->district << "\n";
        }
        // Add similar conditionals for DOCTOR and NURSE
        file.close();
    }
}

void captureVaccinationRecord(const string& childID, vector<ConsultationRecord>& consultations) {
    VaccinationRecord record;
    ConsultationRecord consultation;

    consultation.childID = childID;

    // Capture Vaccine Information
    cout << "Enter treatment administered: ";
    getline(cin, record.treatment);

    cout << "Enter vaccine administered: ";
    getline(cin, record.vaccine);
    
    cout << "Enter date of vaccination (mmddyyyy): ";
    while (true) {
        getline(cin, record.clinic_date);
        if (isValidDate(record.clinic_date)) {
            break;
        } else {
            cout << "Invalid date format. Please use mmddyyyy." << endl;
        }
    }

    cout << "Enter Nurse's Name: "; 
    getline(cin, record.nurse);

    cout << "Enter child's weight (kg): ";
    while (!(cin >> record.weight) || record.weight <= 0) {
        cin.clear();
        cin.ignore();
        cout << "Please enter a valid weight (positive number): ";
    }

    cout << "Enter child's height (cm): ";
    while (!(cin >> record.height) || record.height <= 0) {
        cin.clear();
        cin.ignore();
        cout << "Please enter a valid height (positive number): ";
    }

    cout << "Enter child's age (years): ";
    while (!(cin >> record.age) || record.age < 0) {
        cin.clear();
        cin.ignore();
        cout << "Please enter a valid age (non-negative number): ";
    }

    consultation.vaccinationRecord = record;

    cin.ignore();  // Clear the newline character after numeric input
    cout << "Enter doctor's name: ";
    getline(cin, consultation.doctor);
    
    cout << "Enter clinic name: ";
    getline(cin, consultation.clinic);
    
    cout << "Enter consultation date (mmddyyyy): ";
    while (true) {
        getline(cin, consultation.consultationDate);
        if (isValidDate(consultation.consultationDate)) {
            break;
        } else {
            cout << "Invalid date format. Please use mmddyyyy." << endl;
        }
    }

    cout << "Enter checkup date (mmddyyyy): ";
    while (true) {
        getline(cin, consultation.checkupDate);
        if (isValidDate(consultation.checkupDate)) {
            break;
        } else {
            cout << "Invalid date format. Please use mmddyyyy." << endl;
        }
    }

    consultations.push_back(consultation);
    
    displayVaccinationReport(consultation);
}

void captureMedicationRecord(const string& childID, vector<ConsultationRecord>& consultations) {
    MedicationRecord record;
    ConsultationRecord consultation;

    consultation.childID = childID;

    cout << "Enter treatment administered: ";
    getline(cin, record.treatment);
    
    cout << "Enter medication administered: ";
    getline(cin, record.medication);
    
    cout << "Enter child's weight (kg): ";
    while (!(cin >> record.weight) || record.weight <= 0) {
        cin.clear();
        cin.ignore();
        cout << "Please enter a valid weight (positive number): ";
    }

    cout << "Enter child's height (cm): ";
    while (!(cin >> record.height) || record.height <= 0) {
        cin.clear();
        cin.ignore();
        cout << "Please enter a valid height (positive number): ";
    }

    cin.ignore(); // Clear the newline left in the buffer
    cout << "Enter doctor's name: ";
    getline(cin, record.doctor);
    
    cout << "Enter clinic name: ";
    getline(cin, record.clinic);
    
    cout << "Enter consultation date (mmddyyyy): ";
    while (true) {
        getline(cin, record.consultationDate);
        if (isValidDate(record.consultationDate)) {
            break;
        } else {
            cout << "Invalid date format. Please use mmddyyyy." << endl;
        }
    }

    cout << "Enter checkup date (mmddyyyy): ";
    while (true) {
        getline(cin, record.checkupDate);
        if (isValidDate(record.checkupDate)) {
            break;
        } else {
            cout << "Invalid date format. Please use mmddyyyy." << endl;
        }
    }

    consultation.medicationRecord = record;

    consultations.push_back(consultation);
    
    displayMedicationReport(consultation);
}

void displayVaccinationReport(const ConsultationRecord& consultation) {
    cout << "================================================================================" << endl;
    cout << "                                 VACCINATION REPORT" << endl;
    cout << "================================================================================" << endl;

    cout << "Child ID:                     " << consultation.childID << endl;
    cout << "Treatment Administered:       **********" << endl; // Masked
    cout << "Vaccine Administered:         **********" << endl; // Masked
    cout << "Nurse:                       " << consultation.vaccinationRecord.nurse << endl; 
    cout << "Date of Vaccination:          " << consultation.vaccinationRecord.clinic_date << endl; 
    cout << "Next Clinic Date:             " << consultation.vaccinationRecord.next_clinic << endl; 
    cout << "Weight:                      " << consultation.vaccinationRecord.weight << " kg" << endl; 
    cout << "Height:                      " << consultation.vaccinationRecord.height << " cm" << endl; 
    cout << "Age:                         " << consultation.vaccinationRecord.age << " years." << endl; 
    cout << "Doctor:                      " << consultation.doctor << endl; 
    cout << "Clinic:                     " << consultation.clinic << endl; 
    cout << "Consultation Date:           " << consultation.consultationDate << endl; 
    cout << "Checkup Date:                " << consultation.checkupDate << endl; 
    cout << "================================================================================" << endl;

    char saveOption;
    cout << "Do you want to save this report to a file? (y/n): ";
    cin >> saveOption;
    cin.ignore();  // Clear the newline

    if (tolower(saveOption) == 'y') {
        ofstream reportFile("vaccination_report_" + consultation.childID + ".txt");
        if (reportFile.is_open()) {
            reportFile << "================================================================================\n";
            reportFile << "                                 VACCINATION REPORT\n";
            reportFile << "================================================================================\n";
            reportFile << "Child ID:                     " << consultation.childID << "\n";
            reportFile << "Treatment Administered:       **********\n"; 
            reportFile << "Vaccine Administered:         **********\n"; 
            reportFile << "Nurse:                       " << consultation.vaccinationRecord.nurse << "\n"; 
            reportFile << "Date of Vaccination:          " << consultation.vaccinationRecord.clinic_date << "\n"; 
            reportFile << "Next Clinic Date:             " << consultation.vaccinationRecord.next_clinic << "\n"; 
            reportFile << "Weight:                      " << consultation.vaccinationRecord.weight << " kg\n"; 
            reportFile << "Height:                      " << consultation.vaccinationRecord.height << " cm\n"; 
            reportFile << "Age:                         " << consultation.vaccinationRecord.age << " years.\n"; 
            reportFile << "Doctor:                      " << consultation.doctor << "\n"; 
            reportFile << "Clinic:                     " << consultation.clinic << "\n"; 
            reportFile << "Consultation Date:           " << consultation.consultationDate << "\n"; 
            reportFile << "Checkup Date:                " << consultation.checkupDate << "\n"; 
            reportFile << "================================================================================\n";
            reportFile.close();
            cout << "Report saved successfully!" << endl;
        } else {
            cout << "Error saving report." << endl;
        }
    }
}

void displayMedicationReport(const ConsultationRecord& consultation) {
    cout << "================================================================================" << endl;
    cout << "                                 MEDICATION REPORT" << endl;
    cout << "================================================================================" << endl;

    cout << "Child ID:                     " << consultation.childID << endl;
    cout << "Treatment Administered:       **********" << endl; // Masked
    cout << "Medication Administered:      **********" << endl; // Masked
    cout << "Weight:                      " << consultation.medicationRecord.weight << " kg" << endl; 
    cout << "Height:                      " << consultation.medicationRecord.height << " cm" << endl; 
    cout << "Doctor:                      " << consultation.medicationRecord.doctor << endl; 
    cout << "Clinic:                     " << consultation.medicationRecord.clinic << endl; 
    cout << "Consultation Date:           " << consultation.medicationRecord.consultationDate << endl; 
    cout << "Checkup Date:                " << consultation.medicationRecord.checkupDate << endl; 
    cout << "================================================================================" << endl;

    char saveOption;
    cout << "Do you want to save this report to a file? (y/n): ";
    cin >> saveOption;
    cin.ignore();  // Clear the newline

    if (tolower(saveOption) == 'y') {
        ofstream reportFile("medication_report_" + consultation.childID + ".txt");
        if (reportFile.is_open()) {
            reportFile << "================================================================================\n";
            reportFile << "                                 MEDICATION REPORT\n";
            reportFile << "================================================================================\n";
            reportFile << "Child ID:                     " << consultation.childID << "\n";
            reportFile << "Treatment Administered:       **********\n"; // Masked
            reportFile << "Medication Administered:      **********\n"; // Masked
            reportFile << "Weight:                      " << consultation.medicationRecord.weight << " kg\n"; // Show actual weight
            reportFile << "Height:                      " << consultation.medicationRecord.height << " cm\n"; // Show actual height
            reportFile << "Doctor:                      " << consultation.medicationRecord.doctor << "\n"; // Show actual doctor's name
            reportFile << "Clinic:                     " << consultation.medicationRecord.clinic << "\n"; // Show actual clinic name
            reportFile << "Consultation Date:           " << consultation.medicationRecord.consultationDate << "\n"; // Show actual consultation date
            reportFile << "Checkup Date:                " << consultation.medicationRecord.checkupDate << "\n"; // Show actual checkup date
            reportFile << "================================================================================\n";
            reportFile.close();
            cout << "Report saved successfully!" << endl;
        } else {
            cout << "Error saving report." << endl;
        }
    }
}

void registerUser(vector<User*>& users, vector<ConsultationRecord>& consultations) {
    int userType;
    cout << "Enter user type (0 for CHILD, 1 for DOCTOR, 2 for NURSE): ";
    cin >> userType;
    cin.ignore();

    User* newUser = nullptr;
    if (userType == User::CHILD) {
        newUser = new Child();
        Child* child = static_cast<Child*>(newUser);
        
        cout << "Enter username: ";
        getline(cin, child->username);
        
        cout << "Enter password: ";
        getline(cin, child->password);
        
        cout << "Enter child's first name: ";
        getline(cin, child->firstName);
        
        cout << "Enter child's middle name: ";
        getline(cin, child->middleName);
        
        cout << "Enter child's surname: ";
        getline(cin, child->surname);
        
        cout << "Enter child's date of birth (mmddyyyy): ";
        getline(cin, child->dateOfBirth);
        
        cout << "Enter mother's or guardian's name: ";
        getline(cin, child->motherOrGuardian);
        
        cout << "Enter father's name: ";
        getline(cin, child->father);
        
        cout << "Enter village: ";
        getline(cin, child->village);
        
        cout << "Enter chief's name: ";
        getline(cin, child->chief);
        
        cout << "Enter district: ";
        getline(cin, child->district);
        
        child->childID = generateChildID(child->firstName, child->surname, child->dateOfBirth, users.size() + 1);
        cout << "Child ID generated: " << child->childID << endl;

        // Save user to files
        saveUserToFile(child);

        // Prompt for vaccination and medication records
        char captureOption;
        cout << "Do you want to capture vaccination record for this child? (y/n): ";
        cin >> captureOption;
        cin.ignore(); // Clear the newline character

        if (tolower(captureOption) == 'y') {
            captureVaccinationRecord(child->childID, consultations);
        }

        cout << "Do you want to capture medication record for this child? (y/n): ";
        cin >> captureOption;
        cin.ignore(); // Clear the newline character

        if (tolower(captureOption) == 'y') {
            captureMedicationRecord(child->childID, consultations);
        }

    } else if (userType == User::DOCTOR) {
        newUser = new Doctor();
        Doctor* doctor = static_cast<Doctor*>(newUser);
        
        cout << "Enter username: ";
        getline(cin, doctor->username);
        
        cout << "Enter password: ";
        getline(cin, doctor->password);
        
        cout << "Enter doctor's first name: ";
        getline(cin, doctor->firstName);
        
        cout << "Enter doctor's surname: ";
        getline(cin, doctor->surname);
        
        cout << "Enter practice number: ";
        getline(cin, doctor->practiceNumber);
        
        cout << "Enter resident hospital/clinic: ";
        getline(cin, doctor->residentHospitalOrClinic);
        
        cout << "Enter clinic/hospital address: ";
        getline(cin, doctor->clinicAddress);
        
        cout << "Enter cellphone number: ";
        getline(cin, doctor->cellphoneNumber);

        // Save user to files
        saveUserToFile(doctor);

    } else if (userType == User::NURSE) {
        newUser = new Nurse();
        Nurse* nurse = static_cast<Nurse*>(newUser);
        
        cout << "Enter username: ";
        getline(cin, nurse->username);
        
        cout << "Enter password: ";
        getline(cin, nurse->password);
        
        cout << "Enter nurse's first name: ";
        getline(cin, nurse->firstName);
        
        cout << "Enter nurse's surname: ";
        getline(cin, nurse->surname);
        
        cout << "Enter cellphone number: ";
        getline(cin, nurse->cellphoneNumber);

        // Save user to files
        saveUserToFile(nurse);
    }

    users.push_back(newUser);
    cout << "User registered successfully!" << endl;
}

User* loginUser(vector<User*>& users) {
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    for (auto& user : users) {
        if (user->username == username && user->password == password) {
            cout << "Login successful!" << endl;
            return user; 
        }
    }
    cout << "Invalid username or password." << endl;
    return nullptr; 
}

void printReport(const vector<ConsultationRecord>& consultations) {
    cout << "Select report type:" << endl;
    cout << "1. Print Vaccination Report" << endl;
    cout << "2. Print Medication Report" << endl;

    int reportType;
    cin >> reportType;
    cin.ignore(); 

    if (reportType == 1) {
        string childID;
        cout << "Enter child's Record ID to print Vaccination Report: ";
        getline(cin, childID);
        
        for (const auto& consultation : consultations) {
            if (consultation.childID == childID) {
                displayVaccinationReport(consultation); 
                return;
            }
        }
        cout << "No records found for Child ID: " << childID << endl;

    } else if (reportType == 2) {
        string childID;
        cout << "Enter child's Record ID to print Medication Report: ";
        getline(cin, childID);

        for (const auto& consultation : consultations) {
            if (consultation.childID == childID) {
                displayMedicationReport(consultation); 
                return;
            }
        }
        cout << "No records found for Child ID: " << childID << endl;

    } else {
        cout << "Invalid option." << endl;
    }
}

void updateChildRecord(vector<User*>& users) {
    string childID;
    cout << "Enter Child ID to update: ";
    getline(cin, childID);

    for (auto& user : users) {
        if (user->type == User::CHILD && static_cast<Child*>(user)->childID == childID) {
            Child* child = static_cast<Child*>(user);
            cout << "Updating record for Child ID: " << child->childID << endl;
            cout << "Current Details: " << endl;
            child->printInfo(); 

            cout << "\nEnter new details (leave blank to keep current):" << endl;
            string input;

            cout << "First Name: ";
            getline(cin, input);
            if (!input.empty()) child->firstName = input;

            cout << "Middle Name: ";
            getline(cin, input);
            if (!input.empty()) child->middleName = input;

            cout << "Surname: ";
            getline(cin, input);
            if (!input.empty()) child->surname = input;

            cout << "Date of Birth: ";
            getline(cin, input);
            if (!input.empty()) child->dateOfBirth = input;

            cout << "Mother/Guardian: ";
            getline(cin, input);
            if (!input.empty()) child->motherOrGuardian = input;

            cout << "Father: ";
            getline(cin, input);
            if (!input.empty()) child->father = input;

            cout << "Village: ";
            getline(cin, input);
            if (!input.empty()) child->village = input;

            cout << "Chief: ";
            getline(cin, input);
            if (!input.empty()) child->chief = input;

            cout << "District: ";
            getline(cin, input);
            if (!input.empty()) child->district = input;

            cout << "Child's record updated!" << endl;
            child->printInfo();
            return;
        }
    }
    cout << "No child found with the given ID." << endl;
}

void deleteChildRecord(vector<User*>& users) {
    string childID;
    cout << "Enter Child ID to delete: ";
    getline(cin, childID);

    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->type == User::CHILD && static_cast<Child*>(*it)->childID == childID) {
            Child* child = static_cast<Child*>(*it);
            cout << "Deleting record for Child ID: " << child->childID << endl;
            cout << "Current Details: " << endl;
            child->printInfo(); 

            char confirm;
            cout << "Are you sure you want to delete this record? (y/n): ";
            cin >> confirm;
            cin.ignore(); 

            if (tolower(confirm) == 'y') {
                delete child; 
                users.erase(it); 
                cout << "Child record deleted successfully!" << endl;
            } else {
                cout << "Child record not deleted." << endl;
            }
            return;
        }
    }
    cout << "No child found with the given ID." << endl;
}

// Main function
int main() {
    vector<User*> users; // Use vector of pointers for dynamic polymorphism
    vector<ConsultationRecord> consultations;

    // Load users from file
    loadUsers(users);

    int choice;
    do {
        cout << "_________________________________________________________"<< endl;
        cout << "|WELCOME TO THE SYSTEM OF SECHABA HOSPITAL:               |" << endl;
        cout << "|_________________________________________________________|" << endl;
        cout << "|1. Register User                                         |" << endl;
        cout << "|2. Login                                                 |"<< endl;
        cout << "|3. Update Child Record                                   |" << endl;
        cout << "|4. Delete Child Record                                   |" << endl;
        cout << "|5. Exit                                                  |" << endl;
        cout << "|_________________________________________________________|" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                registerUser(users, consultations);
                break;
            case 2: {
                User* loggedInUser = loginUser(users);
                if (loggedInUser) {
                    int userChoice;
                    do {
                        cout << "\n1. Capture Vaccination Record" << endl;
                        cout << "2. Capture Medication Record" << endl;
                        cout << "3. Print Report" << endl;
                        cout << "4. Logout" << endl;
                        
                        cout << "Enter your choice: ";
                        cin >> userChoice;
                        cin.ignore(); 

                        switch (userChoice) {
                            case 1:
                                {
                                    string childID = static_cast<Child*>(loggedInUser)->childID;
                                    captureVaccinationRecord(childID, consultations);
                                }
                                break;
                            case 2:
                                {
                                    string childID = static_cast<Child*>(loggedInUser)->childID;
                                    captureMedicationRecord(childID, consultations);
                                }
                                break;
                            case 3:
                                printReport(consultations);
                                break;
                            case 4:
                                cout << "Logging out..." << endl;
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                                break;
                        }
                    } while (userChoice != 4);
                }
                break;
            }
            case 3:
                updateChildRecord(users);
                break;
            case 4:
                deleteChildRecord(users);
                break;
            case 5:
                cout << "Exiting program." << endl;

                // Free allocated memory for users
                for (auto& user : users) {
                    delete user;
                }
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}