#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <limits>
#include <numeric>
#include <set>
#include <cstdlib>
#include <cctype>

using namespace std;

#define RST   "\033[0m"
#define BOLD  "\033[1m"
#define RED   "\033[31m"
#define GRN   "\033[32m"
#define YLW   "\033[33m"
#define BLU   "\033[34m"
#define MAG   "\033[35m"
#define CYN   "\033[36m"

void clearScreen() { system("clear || cls"); }

void pressEnter() {
    cout << YLW << "\n  Press Enter to continue..." << RST;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void drawLine(char c = '-', int n = 68) {
    cout << CYN;
    for (int i = 0; i < n; i++) cout << c;
    cout << RST << "\n";
}

void printHeader(const string& title) {
    clearScreen();
    drawLine('=');
    int pad = (68 - (int)title.size()) / 2;
    cout << BOLD << CYN << string(pad, ' ') << title << RST << "\n";
    drawLine('=');
    cout << "\n";
}

string getInput(const string& prompt) {
    cout << YLW << "  " << prompt << RST;
    string val;
    getline(cin, val);
    return val;
}

int getInt(const string& prompt, int lo = 0, int hi = 999999) {
    while (true) {
        cout << YLW << "  " << prompt << RST;
        string s;
        getline(cin, s);
        try {
            int v = stoi(s);
            if (v >= lo && v <= hi) return v;
        } catch (...) {}
        cout << RED << "  Invalid! Enter a number between " << lo << " and " << hi << ".\n" << RST;
    }
}

double getDouble(const string& prompt, double lo = 0.0, double hi = 100.0) {
    while (true) {
        cout << YLW << "  " << prompt << RST;
        string s;
        getline(cin, s);
        try {
            double v = stod(s);
            if (v >= lo && v <= hi) return v;
        } catch (...) {}
        cout << RED << "  Invalid! Enter a decimal between " << lo << " and " << hi << ".\n" << RST;
    }
}

string currentDate() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    char buf[12];
    strftime(buf, sizeof(buf), "%Y-%m-%d", t);
    return string(buf);
}

string gradeFromMarks(double marks) {
    if (marks >= 90) return "O  (Outstanding)";
    if (marks >= 80) return "A+ (Excellent)";
    if (marks >= 70) return "A  (Very Good)";
    if (marks >= 60) return "B+ (Good)";
    if (marks >= 50) return "B  (Average)";
    if (marks >= 40) return "C  (Pass)";
    return "F  (Fail)";
}

double gradePoint(double marks) {
    if (marks >= 90) return 10.0;
    if (marks >= 80) return 9.0;
    if (marks >= 70) return 8.0;
    if (marks >= 60) return 7.0;
    if (marks >= 50) return 6.0;
    if (marks >= 40) return 5.0;
    return 0.0;
}

vector<string> splitCSV(const string& line) {
    vector<string> fields;
    stringstream ss(line);
    string tok;
    while (getline(ss, tok, ',')) fields.push_back(tok);
    return fields;
}

struct Student {
    int    id;
    string name, email, phone, address, dob, gender, department, batch, enrollDate;
    double cgpa = 0.0;

    string toCSV() const {
        return to_string(id) + "," + name + "," + email + "," + phone + "," +
               address + "," + dob + "," + gender + "," + department + "," +
               batch + "," + to_string(cgpa) + "," + enrollDate;
    }
    static Student fromCSV(const string& line) {
        auto f = splitCSV(line);
        Student s{};
        if (f.size() < 11) return s;
        s.id = stoi(f[0]); s.name = f[1]; s.email = f[2]; s.phone = f[3];
        s.address = f[4]; s.dob = f[5]; s.gender = f[6]; s.department = f[7];
        s.batch = f[8]; s.cgpa = stod(f[9]); s.enrollDate = f[10];
        return s;
    }
};

struct Faculty {
    int    id;
    string name, email, phone, department, designation, qualification, joinDate;
    double salary = 0.0;

    string toCSV() const {
        return to_string(id) + "," + name + "," + email + "," + phone + "," +
               department + "," + designation + "," + qualification + "," +
               joinDate + "," + to_string(salary);
    }
    static Faculty fromCSV(const string& line) {
        auto f = splitCSV(line);
        Faculty fc{};
        if (f.size() < 9) return fc;
        fc.id = stoi(f[0]); fc.name = f[1]; fc.email = f[2]; fc.phone = f[3];
        fc.department = f[4]; fc.designation = f[5]; fc.qualification = f[6];
        fc.joinDate = f[7]; fc.salary = stod(f[8]);
        return fc;
    }
};

struct Course {
    int    id, credits;
    string code, name, department, facultyName;

    string toCSV() const {
        return to_string(id) + "," + code + "," + name + "," + department + "," +
               to_string(credits) + "," + facultyName;
    }
    static Course fromCSV(const string& line) {
        auto f = splitCSV(line);
        Course c{};
        if (f.size() < 6) return c;
        c.id = stoi(f[0]); c.code = f[1]; c.name = f[2]; c.department = f[3];
        c.credits = stoi(f[4]); c.facultyName = f[5];
        return c;
    }
};

struct Enrollment {
    int studentId, courseId;
    string studentName, courseName, date, semester;

    string toCSV() const {
        return to_string(studentId) + "," + to_string(courseId) + "," +
               studentName + "," + courseName + "," + date + "," + semester;
    }
    static Enrollment fromCSV(const string& line) {
        auto f = splitCSV(line);
        Enrollment e{};
        if (f.size() < 6) return e;
        e.studentId = stoi(f[0]); e.courseId = stoi(f[1]);
        e.studentName = f[2]; e.courseName = f[3]; e.date = f[4]; e.semester = f[5];
        return e;
    }
};

struct Attendance {
    int studentId, courseId;
    string studentName, courseName, date, status;

    string toCSV() const {
        return to_string(studentId) + "," + to_string(courseId) + "," +
               studentName + "," + courseName + "," + date + "," + status;
    }
    static Attendance fromCSV(const string& line) {
        auto f = splitCSV(line);
        Attendance a{};
        if (f.size() < 6) return a;
        a.studentId = stoi(f[0]); a.courseId = stoi(f[1]);
        a.studentName = f[2]; a.courseName = f[3]; a.date = f[4]; a.status = f[5];
        return a;
    }
};

struct Result {
    int studentId, courseId;
    string studentName, courseName, semester;
    double internal, external, total;
    string grade;

    string toCSV() const {
        return to_string(studentId) + "," + to_string(courseId) + "," +
               studentName + "," + courseName + "," + semester + "," +
               to_string(internal) + "," + to_string(external) + "," +
               to_string(total) + "," + grade;
    }
    static Result fromCSV(const string& line) {
        auto f = splitCSV(line);
        Result r{};
        if (f.size() < 9) return r;
        r.studentId = stoi(f[0]); r.courseId = stoi(f[1]);
        r.studentName = f[2]; r.courseName = f[3]; r.semester = f[4];
        r.internal = stod(f[5]); r.external = stod(f[6]);
        r.total = stod(f[7]); r.grade = f[8];
        return r;
    }
};

struct Fee {
    int studentId;
    string studentName, feeType, dueDate, paidDate, status;
    double amount;

    string toCSV() const {
        return to_string(studentId) + "," + studentName + "," + feeType + "," +
               to_string(amount) + "," + dueDate + "," + paidDate + "," + status;
    }
    static Fee fromCSV(const string& line) {
        auto f = splitCSV(line);
        Fee fe{};
        if (f.size() < 7) return fe;
        fe.studentId = stoi(f[0]); fe.studentName = f[1]; fe.feeType = f[2];
        fe.amount = stod(f[3]); fe.dueDate = f[4]; fe.paidDate = f[5]; fe.status = f[6];
        return fe;
    }
};

struct Notice {
    int    id;
    string title, content, date, postedBy, category;

    string toCSV() const {
        return to_string(id) + "," + title + "," + content + "," +
               date + "," + postedBy + "," + category;
    }
    static Notice fromCSV(const string& line) {
        auto f = splitCSV(line);
        Notice n{};
        if (f.size() < 6) return n;
        n.id = stoi(f[0]); n.title = f[1]; n.content = f[2];
        n.date = f[3]; n.postedBy = f[4]; n.category = f[5];
        return n;
    }
};

template<typename T>
void saveToFile(const string& filename, const vector<T>& data) {
    ofstream f(filename);
    for (auto& d : data) f << d.toCSV() << "\n";
}

template<typename T>
vector<T> loadFromFile(const string& filename) {
    vector<T> data;
    ifstream f(filename);
    string line;
    while (getline(f, line))
        if (!line.empty()) data.push_back(T::fromCSV(line));
    return data;
}

vector<Student>    students;
vector<Faculty>    faculties;
vector<Course>     courses;
vector<Enrollment> enrollments;
vector<Attendance> attendances;
vector<Result>     results;
vector<Fee>        fees;
vector<Notice>     notices;

void loadAll() {
    students    = loadFromFile<Student>("students.csv");
    faculties   = loadFromFile<Faculty>("faculty.csv");
    courses     = loadFromFile<Course>("courses.csv");
    enrollments = loadFromFile<Enrollment>("enrollments.csv");
    attendances = loadFromFile<Attendance>("attendance.csv");
    results     = loadFromFile<Result>("results.csv");
    fees        = loadFromFile<Fee>("fees.csv");
    notices     = loadFromFile<Notice>("notices.csv");
}

void saveAll() {
    saveToFile("students.csv",    students);
    saveToFile("faculty.csv",     faculties);
    saveToFile("courses.csv",     courses);
    saveToFile("enrollments.csv", enrollments);
    saveToFile("attendance.csv",  attendances);
    saveToFile("results.csv",     results);
    saveToFile("fees.csv",        fees);
    saveToFile("notices.csv",     notices);
}

int nextStudentId() {
    if (students.empty()) return 1001;
    return max_element(students.begin(), students.end(),
        [](const Student& a, const Student& b){ return a.id < b.id; })->id + 1;
}
int nextFacultyId() {
    if (faculties.empty()) return 2001;
    return max_element(faculties.begin(), faculties.end(),
        [](const Faculty& a, const Faculty& b){ return a.id < b.id; })->id + 1;
}
int nextCourseId() {
    if (courses.empty()) return 3001;
    return max_element(courses.begin(), courses.end(),
        [](const Course& a, const Course& b){ return a.id < b.id; })->id + 1;
}
int nextNoticeId() {
    if (notices.empty()) return 1;
    return max_element(notices.begin(), notices.end(),
        [](const Notice& a, const Notice& b){ return a.id < b.id; })->id + 1;
}

Student* findStudent(int id) {
    auto it = find_if(students.begin(), students.end(),
        [id](const Student& s){ return s.id == id; });
    return it != students.end() ? &*it : nullptr;
}
Faculty* findFaculty(int id) {
    auto it = find_if(faculties.begin(), faculties.end(),
        [id](const Faculty& f){ return f.id == id; });
    return it != faculties.end() ? &*it : nullptr;
}
Course* findCourse(int id) {
    auto it = find_if(courses.begin(), courses.end(),
        [id](const Course& c){ return c.id == id; });
    return it != courses.end() ? &*it : nullptr;
}

void printStudentRow(const Student& s) {
    cout << "  " << left
         << setw(6)  << s.id
         << setw(22) << s.name
         << setw(14) << s.department
         << setw(10) << s.batch
         << setw(8)  << fixed << setprecision(2) << s.cgpa
         << s.phone << "\n";
}
void printStudentHeader() {
    cout << GRN << "  " << left
         << setw(6)  << "ID"
         << setw(22) << "Name"
         << setw(14) << "Department"
         << setw(10) << "Batch"
         << setw(8)  << "CGPA"
         << "Phone" << RST << "\n";
    drawLine();
}

void printFacultyRow(const Faculty& f) {
    cout << "  " << left
         << setw(6)  << f.id
         << setw(22) << f.name
         << setw(14) << f.department
         << setw(18) << f.designation
         << f.phone << "\n";
}
void printFacultyHeader() {
    cout << GRN << "  " << left
         << setw(6)  << "ID"
         << setw(22) << "Name"
         << setw(14) << "Department"
         << setw(18) << "Designation"
         << "Phone" << RST << "\n";
    drawLine();
}

void addStudent() {
    printHeader("ADD NEW STUDENT");
    Student s;
    s.id         = nextStudentId();
    s.name       = getInput("Full Name          : ");
    s.email      = getInput("Email              : ");
    s.phone      = getInput("Phone              : ");
    s.address    = getInput("Address            : ");
    s.dob        = getInput("Date of Birth      : ");
    s.gender     = getInput("Gender (M/F/O)     : ");
    s.department = getInput("Department         : ");
    s.batch      = getInput("Batch (e.g. 2024)  : ");
    s.cgpa       = 0.0;
    s.enrollDate = currentDate();
    students.push_back(s);
    saveAll();
    cout << GRN << "\n  Student added successfully! ID: " << s.id << RST << "\n";
    pressEnter();
}

void viewAllStudents() {
    printHeader("ALL STUDENTS");
    if (students.empty()) {
        cout << RED << "  No students found.\n" << RST;
        pressEnter(); return;
    }
    printStudentHeader();
    for (auto& s : students) printStudentRow(s);
    cout << "\n  " << GRN << "Total Students: " << students.size() << RST << "\n";
    pressEnter();
}

void searchStudent() {
    printHeader("SEARCH STUDENT");
    cout << "  1. Search by ID\n  2. Search by Name\n  3. Search by Department\n";
    int ch = getInt("Choice (1-3): ", 1, 3);
    vector<Student*> found;
    if (ch == 1) {
        int id = getInt("Enter Student ID: ");
        Student* s = findStudent(id);
        if (s) found.push_back(s);
    } else if (ch == 2) {
        string name = getInput("Enter Name (partial): ");
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        for (auto& s : students) {
            string lower = s.name;
            transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            if (lower.find(name) != string::npos) found.push_back(&s);
        }
    } else {
        string dept = getInput("Enter Department: ");
        for (auto& s : students)
            if (s.department == dept) found.push_back(&s);
    }
    if (found.empty()) { cout << RED << "  No results found.\n" << RST; pressEnter(); return; }
    printStudentHeader();
    for (auto s : found) printStudentRow(*s);
    pressEnter();
}

void updateStudent() {
    printHeader("UPDATE STUDENT");
    int id = getInt("Enter Student ID: ");
    Student* s = findStudent(id);
    if (!s) { cout << RED << "  Student not found.\n" << RST; pressEnter(); return; }
    cout << "\n  Editing: " << BOLD << s->name << RST << "\n\n";
    cout << "  1. Name  2. Email  3. Phone  4. Address  5. Department  6. Batch\n";
    int field = getInt("Field to update (1-6): ", 1, 6);
    map<int, pair<string*, string>> fieldMap = {
        {1, {&s->name, "New Name: "}},
        {2, {&s->email, "New Email: "}},
        {3, {&s->phone, "New Phone: "}},
        {4, {&s->address, "New Address: "}},
        {5, {&s->department, "New Department: "}},
        {6, {&s->batch, "New Batch: "}}
    };
    *fieldMap[field].first = getInput(fieldMap[field].second);
    saveAll();
    cout << GRN << "  Updated successfully!\n" << RST;
    pressEnter();
}

void deleteStudent() {
    printHeader("DELETE STUDENT");
    int id = getInt("Enter Student ID: ");
    auto it = find_if(students.begin(), students.end(),
        [id](const Student& s){ return s.id == id; });
    if (it == students.end()) { cout << RED << "  Student not found.\n" << RST; pressEnter(); return; }
    cout << RED << "  Delete student: " << it->name << " ? (y/n): " << RST;
    string c; getline(cin, c);
    if (c == "y" || c == "Y") {
        enrollments.erase(remove_if(enrollments.begin(), enrollments.end(),
            [id](const Enrollment& e){ return e.studentId == id; }), enrollments.end());
        attendances.erase(remove_if(attendances.begin(), attendances.end(),
            [id](const Attendance& a){ return a.studentId == id; }), attendances.end());
        results.erase(remove_if(results.begin(), results.end(),
            [id](const Result& r){ return r.studentId == id; }), results.end());
        fees.erase(remove_if(fees.begin(), fees.end(),
            [id](const Fee& f){ return f.studentId == id; }), fees.end());
        students.erase(it);
        saveAll();
        cout << GRN << "  Student deleted.\n" << RST;
    }
    pressEnter();
}

void viewStudentProfile() {
    printHeader("STUDENT PROFILE");
    int id = getInt("Enter Student ID: ");
    Student* s = findStudent(id);
    if (!s) { cout << RED << "  Student not found.\n" << RST; pressEnter(); return; }
    drawLine('=');
    cout << BOLD << "  STUDENT DETAILS\n" << RST;
    drawLine();
    cout << "  ID          : " << s->id         << "\n"
         << "  Name        : " << s->name        << "\n"
         << "  Email       : " << s->email       << "\n"
         << "  Phone       : " << s->phone       << "\n"
         << "  Address     : " << s->address     << "\n"
         << "  Date of Birth: " << s->dob        << "\n"
         << "  Gender      : " << s->gender      << "\n"
         << "  Department  : " << s->department  << "\n"
         << "  Batch       : " << s->batch       << "\n"
         << "  Enroll Date : " << s->enrollDate  << "\n"
         << "  CGPA        : " << fixed << setprecision(2) << s->cgpa << "\n";
    drawLine();
    cout << BOLD << "  ENROLLED COURSES\n" << RST;
    drawLine();
    int count = 0;
    for (auto& e : enrollments)
        if (e.studentId == id) { cout << "  - " << e.courseName << " (Sem: " << e.semester << ")\n"; count++; }
    if (!count) cout << "  No courses enrolled.\n";
    drawLine();
    cout << BOLD << "  RECENT RESULTS\n" << RST;
    drawLine();
    count = 0;
    for (auto& r : results) {
        if (r.studentId == id) {
            cout << "  " << left << setw(25) << r.courseName
                 << "Total: " << setw(7) << r.total
                 << "Grade: " << r.grade << "\n";
            count++;
        }
    }
    if (!count) cout << "  No results found.\n";
    pressEnter();
}

void studentMenu() {
    while (true) {
        printHeader("STUDENT MANAGEMENT");
        cout << "  " << BOLD << "[1]" << RST << " Add Student\n"
             << "  " << BOLD << "[2]" << RST << " View All Students\n"
             << "  " << BOLD << "[3]" << RST << " Search Student\n"
             << "  " << BOLD << "[4]" << RST << " Update Student\n"
             << "  " << BOLD << "[5]" << RST << " Delete Student\n"
             << "  " << BOLD << "[6]" << RST << " View Student Profile\n"
             << "  " << BOLD << "[0]" << RST << " Back\n\n";
        int ch = getInt("Choice: ", 0, 6);
        if (ch == 0) break;
        if (ch == 1) addStudent();
        else if (ch == 2) viewAllStudents();
        else if (ch == 3) searchStudent();
        else if (ch == 4) updateStudent();
        else if (ch == 5) deleteStudent();
        else if (ch == 6) viewStudentProfile();
    }
}

void addFaculty() {
    printHeader("ADD NEW FACULTY");
    Faculty f;
    f.id            = nextFacultyId();
    f.name          = getInput("Full Name       : ");
    f.email         = getInput("Email           : ");
    f.phone         = getInput("Phone           : ");
    f.department    = getInput("Department      : ");
    f.designation   = getInput("Designation     : ");
    f.qualification = getInput("Qualification   : ");
    f.joinDate      = currentDate();
    f.salary        = getDouble("Salary          : ", 0, 9999999);
    faculties.push_back(f);
    saveAll();
    cout << GRN << "\n  Faculty added! ID: " << f.id << RST << "\n";
    pressEnter();
}

void viewAllFaculty() {
    printHeader("ALL FACULTY");
    if (faculties.empty()) { cout << RED << "  No faculty found.\n" << RST; pressEnter(); return; }
    printFacultyHeader();
    for (auto& f : faculties) printFacultyRow(f);
    cout << "\n  " << GRN << "Total Faculty: " << faculties.size() << RST << "\n";
    pressEnter();
}

void searchFaculty() {
    printHeader("SEARCH FACULTY");
    cout << "  1. By ID   2. By Name   3. By Department\n";
    int ch = getInt("Choice (1-3): ", 1, 3);
    vector<Faculty*> found;
    if (ch == 1) {
        int id = getInt("Enter Faculty ID: ");
        Faculty* f = findFaculty(id);
        if (f) found.push_back(f);
    } else if (ch == 2) {
        string name = getInput("Enter Name: ");
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        for (auto& f : faculties) {
            string lower = f.name;
            transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            if (lower.find(name) != string::npos) found.push_back(&f);
        }
    } else {
        string dept = getInput("Enter Department: ");
        for (auto& f : faculties)
            if (f.department == dept) found.push_back(&f);
    }
    if (found.empty()) { cout << RED << "  Not found.\n" << RST; pressEnter(); return; }
    printFacultyHeader();
    for (auto f : found) printFacultyRow(*f);
    pressEnter();
}

void updateFaculty() {
    printHeader("UPDATE FACULTY");
    int id = getInt("Enter Faculty ID: ");
    Faculty* f = findFaculty(id);
    if (!f) { cout << RED << "  Faculty not found.\n" << RST; pressEnter(); return; }
    cout << "\n  Editing: " << BOLD << f->name << RST << "\n\n";
    cout << "  1. Name  2. Email  3. Phone  4. Department  5. Designation  6. Salary\n";
    int field = getInt("Field (1-6): ", 1, 6);
    if (field == 1) f->name        = getInput("New Name: ");
    else if (field == 2) f->email  = getInput("New Email: ");
    else if (field == 3) f->phone  = getInput("New Phone: ");
    else if (field == 4) f->department = getInput("New Department: ");
    else if (field == 5) f->designation = getInput("New Designation: ");
    else f->salary = getDouble("New Salary: ", 0, 9999999);
    saveAll();
    cout << GRN << "  Updated!\n" << RST;
    pressEnter();
}

void deleteFaculty() {
    printHeader("DELETE FACULTY");
    int id = getInt("Enter Faculty ID: ");
    auto it = find_if(faculties.begin(), faculties.end(),
        [id](const Faculty& f){ return f.id == id; });
    if (it == faculties.end()) { cout << RED << "  Not found.\n" << RST; pressEnter(); return; }
    cout << RED << "  Delete " << it->name << "? (y/n): " << RST;
    string c; getline(cin, c);
    if (c == "y" || c == "Y") { faculties.erase(it); saveAll(); cout << GRN << "  Deleted.\n" << RST; }
    pressEnter();
}

void facultyMenu() {
    while (true) {
        printHeader("FACULTY MANAGEMENT");
        cout << "  " << BOLD << "[1]" << RST << " Add Faculty\n"
             << "  " << BOLD << "[2]" << RST << " View All Faculty\n"
             << "  " << BOLD << "[3]" << RST << " Search Faculty\n"
             << "  " << BOLD << "[4]" << RST << " Update Faculty\n"
             << "  " << BOLD << "[5]" << RST << " Delete Faculty\n"
             << "  " << BOLD << "[0]" << RST << " Back\n\n";
        int ch = getInt("Choice: ", 0, 5);
        if (ch == 0) break;
        if (ch == 1) addFaculty();
        else if (ch == 2) viewAllFaculty();
        else if (ch == 3) searchFaculty();
        else if (ch == 4) updateFaculty();
        else if (ch == 5) deleteFaculty();
    }
}

void addCourse() {
    printHeader("ADD NEW COURSE");
    Course c;
    c.id          = nextCourseId();
    c.code        = getInput("Course Code    : ");
    c.name        = getInput("Course Name    : ");
    c.department  = getInput("Department     : ");
    c.credits     = getInt("Credits (1-6)  : ", 1, 6);
    c.facultyName = getInput("Faculty Name   : ");
    courses.push_back(c);
    saveAll();
    cout << GRN << "\n  Course added! ID: " << c.id << RST << "\n";
    pressEnter();
}

void viewAllCourses() {
    printHeader("ALL COURSES");
    if (courses.empty()) { cout << RED << "  No courses found.\n" << RST; pressEnter(); return; }
    cout << GRN << "  " << left
         << setw(6) << "ID" << setw(10) << "Code" << setw(28) << "Name"
         << setw(16) << "Department" << setw(8) << "Credits" << "Faculty\n" << RST;
    drawLine();
    for (auto& c : courses)
        cout << "  " << left
             << setw(6) << c.id << setw(10) << c.code << setw(28) << c.name
             << setw(16) << c.department << setw(8) << c.credits << c.facultyName << "\n";
    cout << "\n  " << GRN << "Total Courses: " << courses.size() << RST << "\n";
    pressEnter();
}

void updateCourse() {
    printHeader("UPDATE COURSE");
    int id = getInt("Enter Course ID: ");
    Course* c = findCourse(id);
    if (!c) { cout << RED << "  Course not found.\n" << RST; pressEnter(); return; }
    cout << "\n  1. Code  2. Name  3. Department  4. Credits  5. Faculty\n";
    int field = getInt("Field (1-5): ", 1, 5);
    if (field == 1)      c->code        = getInput("New Code: ");
    else if (field == 2) c->name        = getInput("New Name: ");
    else if (field == 3) c->department  = getInput("New Department: ");
    else if (field == 4) c->credits     = getInt("New Credits: ", 1, 6);
    else                 c->facultyName = getInput("New Faculty: ");
    saveAll();
    cout << GRN << "  Updated!\n" << RST;
    pressEnter();
}

void deleteCourse() {
    printHeader("DELETE COURSE");
    int id = getInt("Enter Course ID: ");
    auto it = find_if(courses.begin(), courses.end(),
        [id](const Course& c){ return c.id == id; });
    if (it == courses.end()) { cout << RED << "  Not found.\n" << RST; pressEnter(); return; }
    cout << RED << "  Delete course: " << it->name << "? (y/n): " << RST;
    string c; getline(cin, c);
    if (c == "y" || c == "Y") {
        courses.erase(it);
        saveAll();
        cout << GRN << "  Deleted.\n" << RST;
    }
    pressEnter();
}

void courseMenu() {
    while (true) {
        printHeader("COURSE MANAGEMENT");
        cout << "  " << BOLD << "[1]" << RST << " Add Course\n"
             << "  " << BOLD << "[2]" << RST << " View All Courses\n"
             << "  " << BOLD << "[3]" << RST << " Update Course\n"
             << "  " << BOLD << "[4]" << RST << " Delete Course\n"
             << "  " << BOLD << "[0]" << RST << " Back\n\n";
        int ch = getInt("Choice: ", 0, 4);
        if (ch == 0) break;
        if (ch == 1) addCourse();
        else if (ch == 2) viewAllCourses();
        else if (ch == 3) updateCourse();
        else if (ch == 4) deleteCourse();
    }
}

void enrollStudent() {
    printHeader("ENROLL STUDENT IN COURSE");
    int sid = getInt("Student ID: ");
    Student* s = findStudent(sid);
    if (!s) { cout << RED << "  Student not found.\n" << RST; pressEnter(); return; }
    int cid = getInt("Course ID : ");
    Course* c = findCourse(cid);
    if (!c) { cout << RED << "  Course not found.\n" << RST; pressEnter(); return; }
    bool already = any_of(enrollments.begin(), enrollments.end(),
        [sid, cid](const Enrollment& e){ return e.studentId == sid && e.courseId == cid; });
    if (already) { cout << YLW << "  Already enrolled!\n" << RST; pressEnter(); return; }
    Enrollment e;
    e.studentId = sid; e.courseId = cid;
    e.studentName = s->name; e.courseName = c->name;
    e.date = currentDate();
    e.semester = getInput("Semester (e.g. 2024-Odd): ");
    enrollments.push_back(e);
    saveAll();
    cout << GRN << "  Enrollment successful!\n" << RST;
    pressEnter();
}

void viewEnrollments() {
    printHeader("ENROLLMENTS");
    cout << "  1. All   2. By Student   3. By Course\n";
    int ch = getInt("Choice (1-3): ", 1, 3);
    vector<Enrollment*> list;
    if (ch == 1)
        for (auto& e : enrollments) list.push_back(&e);
    else if (ch == 2) {
        int sid = getInt("Student ID: ");
        for (auto& e : enrollments) if (e.studentId == sid) list.push_back(&e);
    } else {
        int cid = getInt("Course ID: ");
        for (auto& e : enrollments) if (e.courseId == cid) list.push_back(&e);
    }
    if (list.empty()) { cout << RED << "  No records.\n" << RST; pressEnter(); return; }
    cout << "\n" << GRN << "  " << left
         << setw(8) << "Stu.ID" << setw(22) << "Student" << setw(28) << "Course"
         << setw(14) << "Semester" << "Date\n" << RST;
    drawLine();
    for (auto e : list)
        cout << "  " << left
             << setw(8) << e->studentId << setw(22) << e->studentName
             << setw(28) << e->courseName << setw(14) << e->semester << e->date << "\n";
    cout << "\n  " << GRN << "Total: " << list.size() << RST << "\n";
    pressEnter();
}

void dropEnrollment() {
    printHeader("DROP ENROLLMENT");
    int sid = getInt("Student ID: ");
    int cid = getInt("Course ID : ");
    auto it = find_if(enrollments.begin(), enrollments.end(),
        [sid, cid](const Enrollment& e){ return e.studentId == sid && e.courseId == cid; });
    if (it == enrollments.end()) { cout << RED << "  Enrollment not found.\n" << RST; pressEnter(); return; }
    cout << RED << "  Drop " << it->studentName << " from " << it->courseName << "? (y/n): " << RST;
    string c; getline(cin, c);
    if (c == "y" || c == "Y") { enrollments.erase(it); saveAll(); cout << GRN << "  Dropped.\n" << RST; }
    pressEnter();
}

void enrollmentMenu() {
    while (true) {
        printHeader("ENROLLMENT MANAGEMENT");
        cout << "  " << BOLD << "[1]" << RST << " Enroll Student\n"
             << "  " << BOLD << "[2]" << RST << " View Enrollments\n"
             << "  " << BOLD << "[3]" << RST << " Drop Enrollment\n"
             << "  " << BOLD << "[0]" << RST << " Back\n\n";
        int ch = getInt("Choice: ", 0, 3);
        if (ch == 0) break;
        if (ch == 1) enrollStudent();
        else if (ch == 2) viewEnrollments();
        else if (ch == 3) dropEnrollment();
    }
}

void markAttendance() {
    printHeader("MARK ATTENDANCE");
    int cid = getInt("Course ID: ");
    Course* c = findCourse(cid);
    if (!c) { cout << RED << "  Course not found.\n" << RST; pressEnter(); return; }
    string date = getInput("Date (YYYY-MM-DD) [blank=today]: ");
    if (date.empty()) date = currentDate();
    vector<Enrollment*> enrolled;
    for (auto& e : enrollments) if (e.courseId == cid) enrolled.push_back(&e);
    if (enrolled.empty()) { cout << RED << "  No students enrolled.\n" << RST; pressEnter(); return; }
    cout << "\n  Marking attendance for: " << BOLD << c->name << RST
         << " | Date: " << date << "\n\n";
    for (auto e : enrolled) {
        cout << YLW << "  " << e->studentName << " (P=Present A=Absent L=Leave): " << RST;
        string status; getline(cin, status);
        transform(status.begin(), status.end(), status.begin(), ::toupper);
        if (status != "P" && status != "A" && status != "L") status = "A";
        auto existing = find_if(attendances.begin(), attendances.end(),
            [&](const Attendance& a){
                return a.studentId == e->studentId && a.courseId == cid && a.date == date;
            });
        if (existing != attendances.end()) existing->status = status;
        else {
            Attendance a;
            a.studentId = e->studentId; a.courseId = cid;
            a.studentName = e->studentName; a.courseName = c->name;
            a.date = date; a.status = status;
            attendances.push_back(a);
        }
    }
    saveAll();
    cout << GRN << "\n  Attendance saved!\n" << RST;
    pressEnter();
}

void viewAttendance() {
    printHeader("VIEW ATTENDANCE");
    cout << "  1. By Student   2. By Course\n";
    int ch = getInt("Choice (1-2): ", 1, 2);
    if (ch == 1) {
        int sid = getInt("Student ID: ");
        Student* s = findStudent(sid);
        if (!s) { cout << RED << "  Not found.\n" << RST; pressEnter(); return; }
        map<int, pair<int,int>> stats;
        for (auto& a : attendances) {
            if (a.studentId == sid) {
                stats[a.courseId].second++;
                if (a.status == "P") stats[a.courseId].first++;
            }
        }
        cout << "\n  Attendance Report: " << BOLD << s->name << RST << "\n\n";
        cout << GRN << "  " << left << setw(30) << "Course" << setw(10) << "Present"
             << setw(10) << "Total" << "Percentage\n" << RST;
        drawLine();
        for (auto& cstat : stats) {
            auto cid=cstat.first;
            auto p=cstat.second;
            Course* c = findCourse(cid);
            string cname = c ? c->name : to_string(cid);
            double pct = p.second > 0 ? (p.first * 100.0 / p.second) : 0;
            string color = pct >= 75 ? GRN : (pct >= 60 ? YLW : RED);
            cout << "  " << left << setw(30) << cname
                 << setw(10) << p.first << setw(10) << p.second
                 << color << fixed << setprecision(1) << pct << "%" << RST << "\n";
        }
    } else {
        int cid = getInt("Course ID: ");
        map<int, pair<int,int>> stats;
        map<int, string> names;
        for (auto& a : attendances) {
            if (a.courseId == cid) {
                stats[a.studentId].second++;
                names[a.studentId] = a.studentName;
                if (a.status == "P") stats[a.studentId].first++;
            }
        }
        Course* c = findCourse(cid);
        cout << "\n  Course: " << BOLD << (c ? c->name : to_string(cid)) << RST << "\n\n";
        cout << GRN << "  " << left << setw(8) << "ID" << setw(25) << "Student"
             << setw(10) << "Present" << setw(10) << "Total" << "Percentage\n" << RST;
        drawLine();
        for (auto& stat : stats) {
            auto sid=stat.first;
            auto p=stat.second;
            double pct = p.second > 0 ? (p.first * 100.0 / p.second) : 0;
            string color = pct >= 75 ? GRN : (pct >= 60 ? YLW : RED);
            cout << "  " << left << setw(8) << sid << setw(25) << names[sid]
                 << setw(10) << p.first << setw(10) << p.second
                 << color << fixed << setprecision(1) << pct << "%" << RST << "\n";
        }
    }
    pressEnter();
}

void attendanceMenu() {
    while (true) {
        printHeader("ATTENDANCE MANAGEMENT");
        cout << "  " << BOLD << "[1]" << RST << " Mark Attendance\n"
             << "  " << BOLD << "[2]" << RST << " View Attendance Report\n"
             << "  " << BOLD << "[0]" << RST << " Back\n\n";
        int ch = getInt("Choice: ", 0, 2);
        if (ch == 0) break;
        if (ch == 1) markAttendance();
        else if (ch == 2) viewAttendance();
    }
}

void updateCGPA(int studentId) {
    map<int, double> courseCredits;
    for (auto& c : courses) courseCredits[c.id] = c.credits;
    double totalPoints = 0, totalCredits = 0;
    for (auto& r : results) {
        if (r.studentId == studentId) {
            double credits = courseCredits.count(r.courseId) ? courseCredits[r.courseId] : 3;
            totalPoints  += gradePoint(r.total) * credits;
            totalCredits += credits;
        }
    }
    Student* s = findStudent(studentId);
    if (s) s->cgpa = totalCredits > 0 ? totalPoints / totalCredits : 0.0;
}

void addResult() {
    printHeader("ADD / UPDATE RESULT");
    int sid = getInt("Student ID : ");
    Student* s = findStudent(sid);
    if (!s) { cout << RED << "  Student not found.\n" << RST; pressEnter(); return; }
    int cid = getInt("Course ID  : ");
    Course* c = findCourse(cid);
    if (!c) { cout << RED << "  Course not found.\n" << RST; pressEnter(); return; }
    string sem = getInput("Semester   : ");
    double intr = getDouble("Internal (0-40) : ", 0, 40);
    double extr = getDouble("External (0-60) : ", 0, 60);
    double total = intr + extr;
    string grade = gradeFromMarks(total);
    auto it = find_if(results.begin(), results.end(),
        [sid, cid, &sem](const Result& r){
            return r.studentId == sid && r.courseId == cid && r.semester == sem;
        });
    if (it != results.end()) {
        it->internal = intr; it->external = extr;
        it->total = total; it->grade = grade;
    } else {
        Result r;
        r.studentId = sid; r.courseId = cid;
        r.studentName = s->name; r.courseName = c->name;
        r.semester = sem; r.internal = intr;
        r.external = extr; r.total = total; r.grade = grade;
        results.push_back(r);
    }
    updateCGPA(sid);
    saveAll();
    cout << GRN << "\n  Result saved! Grade: " << grade << "\n" << RST;
    pressEnter();
}

void viewStudentResult() {
    printHeader("STUDENT RESULT");
    int sid = getInt("Student ID: ");
    Student* s = findStudent(sid);
    if (!s) { cout << RED << "  Not found.\n" << RST; pressEnter(); return; }
    vector<Result*> sResults;
    for (auto& r : results) if (r.studentId == sid) sResults.push_back(&r);
    if (sResults.empty()) { cout << RED << "  No results.\n" << RST; pressEnter(); return; }
    cout << "\n  Result Card: " << BOLD << s->name << RST
         << " (CGPA: " << fixed << setprecision(2) << s->cgpa << ")\n\n";
    map<string, vector<Result*>> bySem;
    for (auto r : sResults) bySem[r->semester].push_back(r);
    for (auto& sems : bySem) {
        auto sem=sems.first;
        auto semResults=sems.second;
        cout << MAG << "  Semester: " << sem << RST << "\n";
        drawLine();
        cout << GRN << "  " << left << setw(28) << "Course"
             << setw(12) << "Internal" << setw(12) << "External"
             << setw(10) << "Total" << "Grade\n" << RST;
        drawLine('-', 50);
        double semTotal = 0;
        for (auto r : semResults) {
            cout << "  " << left << setw(28) << r->courseName
                 << setw(12) << r->internal << setw(12) << r->external
                 << setw(10) << r->total << r->grade << "\n";
            semTotal += r->total;
        }
        cout << "\n  Semester Average: " << fixed << setprecision(2)
             << semTotal / semResults.size() << "\n\n";
    }
    pressEnter();
}

void classResult() {
    printHeader("CLASS RESULT");
    int cid = getInt("Course ID: ");
    Course* c = findCourse(cid);
    if (!c) { cout << RED << "  Course not found.\n" << RST; pressEnter(); return; }
    string sem = getInput("Semester: ");
    vector<Result*> list;
    for (auto& r : results)
        if (r.courseId == cid && r.semester == sem) list.push_back(&r);
    if (list.empty()) { cout << RED << "  No results.\n" << RST; pressEnter(); return; }
    sort(list.begin(), list.end(), [](const Result* a, const Result* b){ return a->total > b->total; });
    cout << "\n  Course: " << BOLD << c->name << RST << " | Semester: " << sem << "\n\n";
    cout << GRN << "  " << left << setw(5) << "Rank" << setw(25) << "Student"
         << setw(10) << "Internal" << setw(10) << "External"
         << setw(10) << "Total" << "Grade\n" << RST;
    drawLine();
    int rank = 1;
    double classAvg = 0;
    int pass = 0;
    for (auto r : list) {
        string color = r->total >= 40 ? GRN : RED;
        cout << color << "  " << left << setw(5) << rank++
             << setw(25) << r->studentName
             << setw(10) << r->internal << setw(10) << r->external
             << setw(10) << r->total << r->grade << RST << "\n";
        classAvg += r->total;
        if (r->total >= 40) pass++;
    }
    classAvg /= list.size();
    drawLine();
    cout << "  Class Average : " << fixed << setprecision(2) << classAvg << "\n"
         << "  Pass Rate     : " << pass << "/" << list.size()
         << " (" << (pass * 100.0 / list.size()) << "%)\n";
    pressEnter();
}

void resultMenu() {
    while (true) {
        printHeader("RESULTS MANAGEMENT");
        cout << "  " << BOLD << "[1]" << RST << " Add / Update Result\n"
             << "  " << BOLD << "[2]" << RST << " View Student Result\n"
             << "  " << BOLD << "[3]" << RST << " View Class Result\n"
             << "  " << BOLD << "[0]" << RST << " Back\n\n";
        int ch = getInt("Choice: ", 0, 3);
        if (ch == 0) break;
        if (ch == 1) addResult();
        else if (ch == 2) viewStudentResult();
        else if (ch == 3) classResult();
    }
}

void addFee() {
    printHeader("ADD FEE RECORD");
    int sid = getInt("Student ID: ");
    Student* s = findStudent(sid);
    if (!s) { cout << RED << "  Student not found.\n" << RST; pressEnter(); return; }
    Fee f;
    f.studentId   = sid;
    f.studentName = s->name;
    f.feeType     = getInput("Fee Type (Tuition/Exam/Hostel/Other): ");
    f.amount      = getDouble("Amount: ", 0, 9999999);
    f.dueDate     = getInput("Due Date (YYYY-MM-DD): ");
    f.paidDate    = "";
    f.status      = "Pending";
    fees.push_back(f);
    saveAll();
    cout << GRN << "  Fee record added!\n" << RST;
    pressEnter();
}

void payFee() {
    printHeader("MARK FEE AS PAID");
    int sid = getInt("Student ID: ");
    vector<Fee*> pending;
    for (auto& f : fees) if (f.studentId == sid && f.status == "Pending") pending.push_back(&f);
    if (pending.empty()) { cout << YLW << "  No pending fees.\n" << RST; pressEnter(); return; }
    cout << "\n  Pending Fees:\n\n";
    for (int i = 0; i < (int)pending.size(); i++)
        cout << "  [" << i+1 << "] " << pending[i]->feeType
             << " - Rs." << pending[i]->amount << " (Due: " << pending[i]->dueDate << ")\n";
    int idx = getInt("Select fee index: ", 1, (int)pending.size());
    pending[idx-1]->status   = "Paid";
    pending[idx-1]->paidDate = currentDate();
    saveAll();
    cout << GRN << "  Fee marked as paid!\n" << RST;
    pressEnter();
}

void viewFees() {
    printHeader("FEE RECORDS");
    cout << "  1. All   2. By Student   3. Pending Only\n";
    int ch = getInt("Choice (1-3): ", 1, 3);
    vector<Fee*> list;
    if (ch == 1) for (auto& f : fees) list.push_back(&f);
    else if (ch == 2) {
        int sid = getInt("Student ID: ");
        for (auto& f : fees) if (f.studentId == sid) list.push_back(&f);
    } else for (auto& f : fees) if (f.status == "Pending") list.push_back(&f);
    if (list.empty()) { cout << RED << "  No records.\n" << RST; pressEnter(); return; }
    cout << "\n" << GRN << "  " << left
         << setw(8) << "StuID" << setw(22) << "Student" << setw(14) << "Fee Type"
         << setw(12) << "Amount" << setw(14) << "Due Date" << "Status\n" << RST;
    drawLine();
    double total = 0, totalPaid = 0;
    for (auto f : list) {
        string color = f->status == "Paid" ? GRN : RED;
        cout << "  " << left
             << setw(8)  << f->studentId
             << setw(22) << f->studentName
             << setw(14) << f->feeType
             << setw(12) << f->amount
             << setw(14) << f->dueDate
             << color << f->status << RST << "\n";
        total += f->amount;
        if (f->status == "Paid") totalPaid += f->amount;
    }
    drawLine();
    cout << "  Total: Rs." << total << " | Paid: Rs." << totalPaid
         << " | Pending: Rs." << (total - totalPaid) << "\n";
    pressEnter();
}

void feeMenu() {
    while (true) {
        printHeader("FEE MANAGEMENT");
        cout << "  " << BOLD << "[1]" << RST << " Add Fee Record\n"
             << "  " << BOLD << "[2]" << RST << " Mark Fee as Paid\n"
             << "  " << BOLD << "[3]" << RST << " View Fee Records\n"
             << "  " << BOLD << "[0]" << RST << " Back\n\n";
        int ch = getInt("Choice: ", 0, 3);
        if (ch == 0) break;
        if (ch == 1) addFee();
        else if (ch == 2) payFee();
        else if (ch == 3) viewFees();
    }
}

void postNotice() {
    printHeader("POST NOTICE");
    Notice n;
    n.id       = nextNoticeId();
    n.title    = getInput("Title    : ");
    n.content  = getInput("Content  : ");
    n.date     = currentDate();
    n.postedBy = getInput("Posted By: ");
    n.category = getInput("Category (General/Exam/Event/Academic): ");
    notices.push_back(n);
    saveAll();
    cout << GRN << "  Notice posted!\n" << RST;
    pressEnter();
}

void viewNotices() {
    printHeader("NOTICE BOARD");
    if (notices.empty()) { cout << RED << "  No notices.\n" << RST; pressEnter(); return; }
    vector<Notice> sorted = notices;
    sort(sorted.begin(), sorted.end(), [](const Notice& a, const Notice& b){ return a.id > b.id; });
    for (auto& n : sorted) {
        drawLine('=');
        cout << BOLD << "  [" << n.id << "] " << n.title << RST
             << "  (" << MAG << n.category << RST << ")\n"
             << "  Date: " << n.date << " | Posted By: " << n.postedBy << "\n"
             << "  " << n.content << "\n";
    }
    drawLine('=');
    pressEnter();
}

void deleteNotice() {
    printHeader("DELETE NOTICE");
    viewNotices();
    int id = getInt("Enter Notice ID to delete: ");
    auto it = find_if(notices.begin(), notices.end(),
        [id](const Notice& n){ return n.id == id; });
    if (it == notices.end()) { cout << RED << "  Not found.\n" << RST; pressEnter(); return; }
    notices.erase(it);
    saveAll();
    cout << GRN << "  Notice deleted.\n" << RST;
    pressEnter();
}

void noticeMenu() {
    while (true) {
        printHeader("NOTICE BOARD");
        cout << "  " << BOLD << "[1]" << RST << " Post Notice\n"
             << "  " << BOLD << "[2]" << RST << " View Notices\n"
             << "  " << BOLD << "[3]" << RST << " Delete Notice\n"
             << "  " << BOLD << "[0]" << RST << " Back\n\n";
        int ch = getInt("Choice: ", 0, 3);
        if (ch == 0) break;
        if (ch == 1) postNotice();
        else if (ch == 2) viewNotices();
        else if (ch == 3) deleteNotice();
    }
}

void dashboardReport() {
    printHeader("DASHBOARD & REPORTS");

    int totalStudents = (int)students.size();
    int totalFaculty  = (int)faculties.size();
    int totalCourses  = (int)courses.size();

    map<string, int> deptStudentCount;
    for (auto& s : students) deptStudentCount[s.department]++;
    map<string, int> deptFacultyCount;
    for (auto& f : faculties) deptFacultyCount[f.department]++;

    double avgCGPA = 0;
    if (!students.empty())
        avgCGPA = accumulate(students.begin(), students.end(), 0.0,
            [](double sum, const Student& s){ return sum + s.cgpa; }) / students.size();

    int paidFees = (int)count_if(fees.begin(), fees.end(),
        [](const Fee& f){ return f.status == "Paid"; });
    double totalRevenue = accumulate(fees.begin(), fees.end(), 0.0,
        [](double sum, const Fee& f){ return f.status == "Paid" ? sum + f.amount : sum; });
    double totalPending = accumulate(fees.begin(), fees.end(), 0.0,
        [](double sum, const Fee& f){ return f.status == "Pending" ? sum + f.amount : sum; });

    drawLine('=');
    cout << BOLD << CYN << "  COLLEGE OVERVIEW\n" << RST;
    drawLine();
    cout << "  Total Students  : " << GRN << totalStudents << RST << "\n"
         << "  Total Faculty   : " << GRN << totalFaculty  << RST << "\n"
         << "  Total Courses   : " << GRN << totalCourses  << RST << "\n"
         << "  Enrollments     : " << GRN << enrollments.size()  << RST << "\n"
         << "  Attendance Rec. : " << GRN << attendances.size()  << RST << "\n"
         << "  Result Records  : " << GRN << results.size()      << RST << "\n"
         << "  Average CGPA    : " << GRN << fixed << setprecision(2) << avgCGPA << RST << "\n";

    drawLine('=');
    cout << BOLD << CYN << "  DEPARTMENT-WISE STUDENTS\n" << RST;
    drawLine();
    for (auto& dept : deptStudentCount) 
        cout << "  " << left << setw(25) << dept.first << ": " << dept.second << " students\n";

    drawLine('=');
    cout << BOLD << CYN << "  FEE SUMMARY\n" << RST;
    drawLine();
    cout << "  Fee Records     : " << fees.size() << "\n"
         << "  Paid            : " << GRN << paidFees << " | Rs." << totalRevenue << RST << "\n"
         << "  Pending         : " << RED << (fees.size() - paidFees) << " | Rs." << totalPending << RST << "\n";

    drawLine('=');
    cout << BOLD << CYN << "  TOP 5 STUDENTS BY CGPA\n" << RST;
    drawLine();
    vector<Student> sorted = students;
    sort(sorted.begin(), sorted.end(), [](const Student& a, const Student& b){ return a.cgpa > b.cgpa; });
    int n = min(5, (int)sorted.size());
    for (int i = 0; i < n; i++)
        cout << "  " << i+1 << ". " << left << setw(25) << sorted[i].name
             << "CGPA: " << fixed << setprecision(2) << sorted[i].cgpa << "\n";

    pressEnter();
}

void splashScreen() {
    clearScreen();

    cout << "****************************************************\n";
    cout << "           COLLEGE MANAGEMENT SYSTEM\n";
    cout << "****************************************************\n";

    pressEnter();
}

int main() {
    loadAll();
    splashScreen();
    while (true) {
        printHeader("COLLEGE MANAGEMENT SYSTEM - MAIN MENU");
        cout << "  " << BOLD << CYN << "[1]" << RST << " Student Management\n"
             << "  " << BOLD << CYN << "[2]" << RST << " Faculty Management\n"
             << "  " << BOLD << CYN << "[3]" << RST << " Course Management\n"
             << "  " << BOLD << CYN << "[4]" << RST << " Enrollment Management\n"
             << "  " << BOLD << CYN << "[5]" << RST << " Attendance Management\n"
             << "  " << BOLD << CYN << "[6]" << RST << " Results Management\n"
             << "  " << BOLD << CYN << "[7]" << RST << " Fee Management\n"
             << "  " << BOLD << CYN << "[8]" << RST << " Notice Board\n"
             << "  " << BOLD << CYN << "[9]" << RST << " Dashboard & Reports\n"
             << "  " << BOLD << RED  << "[0]" << RST << " Exit\n\n";
        int ch = getInt("Choice: ", 0, 9);
        if (ch == 0) {
            saveAll();
            cout << GRN << "\n  Data saved. Goodbye!\n\n" << RST;
            break;
        }
        if      (ch == 1) studentMenu();
        else if (ch == 2) facultyMenu();
        else if (ch == 3) courseMenu();
        else if (ch == 4) enrollmentMenu();
        else if (ch == 5) attendanceMenu();
        else if (ch == 6) resultMenu();
        else if (ch == 7) feeMenu();
        else if (ch == 8) noticeMenu();
        else if (ch == 9) dashboardReport();
    }
    return 0;
}
