# 🎓 College Management System (C++)

A **feature-rich College Management System built in C++** using **STL, file handling, and modular design**.
This project simulates a real-world college administration platform for managing **students, faculty, courses, attendance, results, and fees**.

It is a **menu-driven CLI application** designed to demonstrate **Object-Oriented Programming, Data Structures, and File Persistence** in C++.

---

# 📌 Features

### 👨‍🎓 Student Management

* Add new students
* View all students
* Search students (ID / name / department)
* Update student information
* Delete student records
* View full student profile

### 👨‍🏫 Faculty Management

* Add faculty members
* View faculty list
* Search faculty
* Update faculty information
* Remove faculty

### 📚 Course Management

* Add courses
* View all courses
* Update course details
* Delete courses

### 📝 Enrollment System

* Enroll students in courses
* Drop course enrollments
* View enrollments by student or course

### 📅 Attendance Management

* Mark daily attendance (Present / Absent / Leave)
* Attendance reports by student
* Attendance reports by course
* Percentage calculations

### 📊 Results & CGPA System

* Add internal and external marks
* Automatic grade calculation
* CGPA computation
* Student result card
* Class result analysis

### 💰 Fee Management

* Add fee records
* Mark fees as paid
* View pending fees
* Revenue and payment summaries

### 📢 Notice Board

* Post notices
* View notices
* Delete notices
* Category-based announcements

### 📈 Dashboard & Reports

* College statistics
* Department-wise student count
* Fee summaries
* Top students by CGPA

---

# 🛠 Technologies Used

* **C++ (C++17)**
* **STL (Standard Template Library)**

  * `vector`
  * `map`
  * `algorithm`
  * `numeric`
  * `set`
* **File Handling (CSV persistence)**
* **ANSI Terminal UI formatting**

---

# 🧠 Concepts Demonstrated

This project demonstrates:

* Object-Oriented Programming
* Data Structures
* STL containers & algorithms
* File-based data persistence
* Modular CLI application design
* Search and sorting algorithms
* Data aggregation and analytics

---

# 📂 Project Structure

```
CollegeManagementSystem
│
├── college_management_system.cpp
├── students.csv
├── faculty.csv
├── courses.csv
├── enrollments.csv
├── attendance.csv
├── results.csv
├── fees.csv
├── notices.csv
└── README.md
```

The `.csv` files act as a **lightweight database** storing all application data.

---

# ⚙️ How to Compile

Make sure you have **g++ installed**.

```bash
g++ -std=c++17 college_management_system.cpp -o cms
```

---

# ▶️ How to Run

```bash
./cms
```

Windows:

```bash
cms.exe
```

---

# 🖥 Example Menu

```
COLLEGE MANAGEMENT SYSTEM

[1] Student Management
[2] Faculty Management
[3] Course Management
[4] Enrollment Management
[5] Attendance Management
[6] Results Management
[7] Fee Management
[8] Notice Board
[9] Dashboard & Reports
[0] Exit
```

---

# 📊 Example Dashboard Output

```
COLLEGE OVERVIEW

Total Students  : 120
Total Faculty   : 18
Total Courses   : 25
Enrollments     : 340
Attendance Rec. : 2200
Result Records  : 300

Average CGPA    : 7.82
```

---

# 🚀 Future Improvements

Potential upgrades:

* Authentication system (Admin / Faculty / Student login)
* Replace vectors with `unordered_map` for faster lookups
* Modular multi-file architecture
* GUI version using Qt or ImGui
* REST API backend integration

---

# 📚 Learning Outcomes

Through this project I learned:

* Building large-scale CLI applications in C++
* Using STL effectively
* Designing modular systems
* Implementing data persistence with file storage
* Creating real-world management systems

---

# 👨‍💻 Author

**Atul Anand**

Computer Science Student
Aspiring Software Engineer

---

# ⭐ If you like this project

Give it a **star ⭐ on GitHub** and feel free to fork and improve it!
