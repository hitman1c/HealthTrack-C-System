#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

using namespace std;

// Base class for User
class User {
public:
    enum UserType { CHILD, DOCTOR, NURSE };

    UserType type;
    string username;
    string password;

    virtual void printInfo() const = 0; // Pure virtual function for polymorphism
};

// Derived class for Child
class Child : public User {
public:
    string title, firstName, middleName, surname, dateOfBirth, motherOrGuardian,
           father, village, chief, district, childID;

    Child() {
        type = CHILD;
    }
    
    string maskName(const string& name, bool isFirstName) const {
        if (isFirstName) {
            return name.length() > 1 ? name[0] + string(name.length() - 1, '*') : string(1, name[0]) + string(1, '*');
        } else {
            return name.length() > 3 ? string(name.length() - 3, '*') + name.substr(name.length() - 3) : string(name.length(), '*');
        }
    }

    string maskDOB(const string& dob) const {
        if (dob.length() >= 8) {
            return "****-**-" + dob.substr(6); // Mask day and month
        }
        return dob; // Return as-is if improperly formatted
    }

    string maskGuardian(const string& guardian) const {
        return guardian.length() > 1 ? guardian[0] + string(guardian.length() - 1, '*') : string(1, guardian[0]) + string(1, '*');
    }

    void printInfo() const override {
        cout << "Child Information:\n"
             << "ID: " << childID << ", Name: " << maskName(firstName, true) << " " << maskName(surname, false) << "\n"
             << "DOB: " << maskDOB(dateOfBirth) << ", Mother/Guardian: " << maskGuardian(motherOrGuardian) << ", Father: " << maskName(father, true) << "\n"
             << "Village: " << village << ", Chief: " << chief << ", District: " << district << endl;
    }
};

// Derived class for Doctor
class Doctor : public User {
public:
    string firstName, surname, practiceNumber, residentHospitalOrClinic, clinicAddress, cellphoneNumber;

    Doctor() {
        type = DOCTOR;
    }

    void printInfo() const override {
        cout << "Doctor Information:\n" 
             << "Name: " << firstName << " " << surname << ", Practice Number: " << practiceNumber << "\n"
             << "Hospital: " << residentHospitalOrClinic << ", Address: " << clinicAddress << ", Phone: " << cellphoneNumber << endl;
    }
};

// Derived class for Nurse
class Nurse : public User {
public:
    string title = "Sister", firstName, surname, cellphoneNumber;

    Nurse() {
        type = NURSE;
    }

    void printInfo() const override {
        cout << "Nurse Information:\n" 
             << "Name: " << firstName << " " << surname << ", Phone: " << cellphoneNumber << endl;
    }
};

#endif // USER_H