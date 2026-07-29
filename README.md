# 🏥 Child Health Tracker – C++ Clinic Management System

<p align="center">
  <img src="images/banner.png" alt="Child Health Tracker Banner" width="100%">
</p>

<p align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17-blue?style=for-the-badge&logo=cplusplus)
![OOP](https://img.shields.io/badge/Object--Oriented-Programming-success?style=for-the-badge)
![File Storage](https://img.shields.io/badge/File%20Storage-CSV-orange?style=for-the-badge)
![Console](https://img.shields.io/badge/UI-Console-purple?style=for-the-badge)
![License](https://img.shields.io/badge/License-Educational-lightgrey?style=for-the-badge)

</p>

---

# 📖 Overview

The **Child Health Tracker** is a C++ console-based clinic management system developed to help healthcare professionals efficiently manage children's medical records.

The application provides a secure and organized way to register patients, manage healthcare providers, record vaccinations and medications, maintain consultation histories, and generate detailed reports.

By replacing paper-based record keeping with a digital solution, the system improves accuracy, accessibility, and accountability while supporting better healthcare services for children.

---

# ✨ Key Features

## 👤 User Management

- Register children, doctors, and nurses
- Secure login and authentication
- Role-based system access
- Automatic Child ID generation
- View registered users

---

## 💉 Medical Records

- Record vaccinations
- Record prescribed medications
- Track treatments
- Store consultation history
- Record child information including:
  - Age
  - Height
  - Weight
  - Gender
  - Medical conditions

---

## 📊 Reports

Generate professional reports including:

- Vaccination Report
- Medication Report
- Consultation Report
- Child Medical History

Features include:

- Privacy masking of sensitive information
- Export reports as `.txt` files
- Easy-to-read summaries

---

## 🗂️ Record Management

- Update child information
- Delete records
- Search for patients
- View medical history
- Maintain complete healthcare records

---

## 🔒 Security & Validation

- Login authentication
- Role-based permissions
- Input validation
- Date validation
- Numeric validation
- Secure file handling

---

# 🛠️ Technologies Used

| Technology | Purpose |
|------------|---------|
| C++ | Core Programming Language |
| Object-Oriented Programming | System Design |
| STL | Data Structures |
| File Handling (`fstream`) | Data Storage |
| CSV Files | Persistent Storage |
| Regex | Input Validation |
| Console Interface | User Interaction |

---

# 📁 Project Structure

```text
ChildHealthTracker/
│
├── src/
│   ├── main.cpp
│   ├── User.cpp
│   ├── Child.cpp
│   ├── Doctor.cpp
│   ├── Nurse.cpp
│   ├── Authentication.cpp
│   ├── MedicalRecord.cpp
│   ├── Vaccination.cpp
│   ├── Medication.cpp
│   ├── Consultation.cpp
│   └── ReportGenerator.cpp
│
├── include/
│   ├── User.h
│   ├── Child.h
│   ├── Doctor.h
│   ├── Nurse.h
│   ├── MedicalRecord.h
│   ├── Authentication.h
│   └── ReportGenerator.h
│
├── data/
│   ├── children.csv
│   ├── users.csv
│   ├── vaccinations.csv
│   ├── medications.csv
│   └── consultations.csv
│
├── reports/
│
├── images/
│
└── README.md
```

---

# 🏗️ System Architecture

```text
                   +---------------------+
                   |      Login System   |
                   +----------+----------+
                              |
                +-------------+-------------+
                |                           |
        +-------+-------+           +-------+-------+
        |   Doctors     |           |     Nurses    |
        +-------+-------+           +-------+-------+
                |                           |
                +-------------+-------------+
                              |
                    Child Health Records
                              |
      +-----------------------+----------------------+
      |            |             |                   |
 Vaccinations   Medications   Consultations   Reports
```

---

# 📸 Screenshots

### Login

![](images/login.png)

---

### Main Menu

![](images/main-menu.png)

---

### Patient Registration

![](images/register-child.png)

---

### Medical Records

![](images/medical-records.png)

---

### Reports

![](images/reports.png)

---

# 🚀 Installation

Clone the repository

```bash
git clone https://github.com/hitman1c/Child-Health-Tracker.git
```

Navigate into the project

```bash
cd Child-Health-Tracker
```

Compile

```bash
g++ *.cpp -o ChildHealthTracker
```

Run

```bash
./ChildHealthTracker
```

---

# 📂 Data Storage

The application stores data using CSV files.

Examples include:

- users.csv
- children.csv
- vaccinations.csv
- medications.csv
- consultations.csv

This allows records to persist even after the application is closed.

---

# 🎯 Learning Objectives

This project demonstrates knowledge of:

- Object-Oriented Programming (OOP)
- Classes & Objects
- Inheritance
- Encapsulation
- Polymorphism
- File Handling
- Data Validation
- Authentication
- Modular Programming
- Software Design Principles

---

# 🔮 Future Improvements

- GUI using Qt
- MySQL database integration
- Appointment scheduling
- Email reminders
- PDF report generation
- Dashboard analytics
- Cloud backup
- Role management
- Encryption of medical records

---

# 🤝 Contributing

Contributions are welcome!

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to your branch
5. Open a Pull Request

---

# 📜 License

This project was developed for educational purposes.

---

# 👨‍💻 Developer

## Seabata Jeremiah Sechaba

**Software Engineering Student**  
Botho University – Bachelor of Science (Honours) in Computing

🌐 GitHub: https://github.com/hitman1c

💼 Portfolio: https://sechabaseabataportfolio.netlify.app

---

<p align="center">

⭐ If you found this project helpful, please consider giving it a star!

</p>
