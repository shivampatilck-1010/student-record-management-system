/**
 * Student Record & Course Management System (v2.2 Enterprise)
 * Author: Shivam Patil (shivam.dev)
 * Tech: Modern C++17, OOP, Binary Search, Merge Sort, Course Credits SGPA, CSV Report Exporter
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

class Student {
private:
    int id;
    string name;
    string rollNo;
    string department;
    int semester;
    double cgpa;

public:
    Student() : id(0), name(""), rollNo(""), department(""), semester(1), cgpa(0.0) {}
    Student(int i, string n, string r, string d, int sem, double g) 
        : id(i), name(n), rollNo(r), department(d), semester(sem), cgpa(g) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getRollNo() const { return rollNo; }
    string getDepartment() const { return department; }
    int getSemester() const { return semester; }
    double getCgpa() const { return cgpa; }

    void setCgpa(double g) { cgpa = g; }
    void setName(string n) { name = n; }
    void setDepartment(string d) { department = d; }
    void setSemester(int sem) { semester = sem; }

    string getHonorsStatus() const {
        if (cgpa >= 9.0) return "First Class with Distinction (Honors)";
        if (cgpa >= 8.0) return "First Class with Distinction";
        if (cgpa >= 7.0) return "First Class";
        if (cgpa >= 6.0) return "Second Class";
        if (cgpa >= 5.0) return "Pass Class";
        return "Academic Probation";
    }

    void displayRow() const {
        cout << left << setw(8) << id 
             << setw(20) << name 
             << setw(16) << rollNo 
             << setw(14) << department 
             << setw(6) << semester 
             << setw(8) << fixed << setprecision(2) << cgpa 
             << setw(28) << getHonorsStatus() << "\n";
    }
};

class StudentManagementSystem {
private:
    vector<Student> students;
    const string dbFileName = "students_db.txt";

public:
    StudentManagementSystem() {
        loadFromFile();
    }

    void addStudent() {
        int id, sem;
        string name, rollNo, dept;
        double gpa;

        cout << "\n--- Enroll New Student Record ---\n";
        cout << "Enter Student ID (e.g. 106): ";
        if (!(cin >> id)) { cin.clear(); cin.ignore(1000, '\n'); return; }

        for (const auto& s : students) {
            if (s.getId() == id) {
                cout << "[!] Error: Student ID " << id << " already exists!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Full Name: "; getline(cin, name);
        cout << "Enter Roll Number: "; getline(cin, rollNo);
        cout << "Enter Department (CSE, AI-ML, IT, ECE): "; getline(cin, dept);
        cout << "Enter Semester (1-8): "; cin >> sem;
        cout << "Enter CGPA (0.0 - 10.0): "; cin >> gpa;

        students.push_back(Student(id, name, rollNo, dept, sem, gpa));
        saveToFile();
        cout << "[OK] Student record registered successfully!\n";
    }

    void displayAll() const {
        if (students.empty()) {
            cout << "\n[!] No records found in database.\n";
            return;
        }

        cout << "\n" << string(95, '=') << "\n";
        cout << left << setw(8) << "ID" 
             << setw(20) << "NAME" 
             << setw(16) << "ROLL NO" 
             << setw(14) << "DEPARTMENT" 
             << setw(6) << "SEM" 
             << setw(8) << "CGPA" 
             << setw(28) << "ACADEMIC STATUS" << "\n";
        cout << string(95, '-') << "\n";

        for (const auto& s : students) {
            s.displayRow();
        }
        cout << string(95, '=') << "\n";
        cout << "Total Active Records: " << students.size() << "\n";
    }

    void calculateCourseGPA() {
        cout << "\n--- Calculate Credit-Weighted Semester SGPA ---\n";
        int numCourses;
        cout << "Enter number of enrolled semester courses (e.g. 5): ";
        cin >> numCourses;

        double totalGradePoints = 0.0;
        int totalCredits = 0;

        for (int i = 1; i <= numCourses; i++) {
            string courseName;
            int credits;
            double gradePoint;

            cin.ignore();
            cout << "\nCourse #" << i << " Name: "; getline(cin, courseName);
            cout << "Course Credits (e.g. 3 or 4): "; cin >> credits;
            cout << "Grade Points Earned (0.0 - 10.0): "; cin >> gradePoint;

            totalGradePoints += (credits * gradePoint);
            totalCredits += credits;
        }

        if (totalCredits > 0) {
            double sgpa = totalGradePoints / totalCredits;
            cout << "\n" << string(50, '-') << "\n";
            cout << "Calculated SGPA: " << fixed << setprecision(2) << sgpa << " / 10.0\n";
            cout << "Total Course Credits Registered: " << totalCredits << "\n";
            cout << string(50, '-') << "\n";
        }
    }

    void exportToCSV() const {
        string filename = "students_report.csv";
        ofstream out(filename);
        if (!out) {
            cout << "[!] Error creating CSV file.\n";
            return;
        }

        out << "ID,Name,RollNo,Department,Semester,CGPA,Status\n";
        for (const auto& s : students) {
            out << s.getId() << ",\"" << s.getName() << "\"," << s.getRollNo() << "," 
                << s.getDepartment() << "," << s.getSemester() << "," << s.getCgpa() << ",\"" 
                << s.getHonorsStatus() << "\"\n";
        }
        cout << "\n[OK] Institutional record exported to '" << filename << "' (Ready for Excel / Sheets)\n";
    }

    void displayStatistics() const {
        if (students.empty()) return;
        
        double totalGpa = 0.0;
        double maxGpa = students[0].getCgpa();
        double minGpa = students[0].getCgpa();
        string topper = students[0].getName();

        vector<double> gpas;
        for (const auto& s : students) {
            double g = s.getCgpa();
            gpas.push_back(g);
            totalGpa += g;
            if (g > maxGpa) { maxGpa = g; topper = s.getName(); }
            if (g < minGpa) { minGpa = g; }
        }

        double mean = totalGpa / students.size();
        double var = 0.0;
        for (double g : gpas) var += pow(g - mean, 2);
        double stdDev = sqrt(var / students.size());

        cout << "\n" << string(60, '=') << "\n";
        cout << "INSTITUTIONAL ACADEMIC ANALYTICS & CGPA METRICS\n";
        cout << string(60, '=') << "\n";
        cout << "  * Class Average CGPA:     " << fixed << setprecision(2) << mean << " / 10.0\n";
        cout << "  * Standard Deviation (s):  " << setprecision(2) << stdDev << "\n";
        cout << "  * Highest CGPA (Topper):   " << maxGpa << " (" << topper << ")\n";
        cout << "  * Lowest CGPA Recorded:   " << minGpa << "\n";
        cout << string(60, '=') << "\n";
    }

    void sortStudents() {
        int opt;
        cout << "\nSort By: 1. CGPA Merit Rank  2. Student Name  3. ID: ";
        cin >> opt;

        if (opt == 1) {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.getCgpa() > b.getCgpa();
            });
            cout << "[OK] Sorted by CGPA Merit Rank.\n";
        } else if (opt == 2) {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.getName() < b.getName();
            });
            cout << "[OK] Sorted Alphabetically by Name.\n";
        } else {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.getId() < b.getId();
            });
            cout << "[OK] Sorted by Student ID.\n";
        }
        displayAll();
        saveToFile();
    }

    void saveToFile() const {
        ofstream out(dbFileName);
        if (!out) return;
        for (const auto& s : students) {
            out << s.getId() << "|" << s.getName() << "|" << s.getRollNo() << "|" 
                << s.getDepartment() << "|" << s.getSemester() << "|" << s.getCgpa() << "\n";
        }
    }

    void loadFromFile() {
        students.clear();
        ifstream in(dbFileName);
        if (!in) {
            students.push_back(Student(101, "Shivam Patil", "CSE-2025-001", "AI-ML", 3, 9.65));
            students.push_back(Student(102, "Aarav Sharma", "CSE-2025-014", "CSE", 3, 8.90));
            students.push_back(Student(103, "Priya Nair", "CSE-2025-029", "Data Science", 3, 9.25));
            students.push_back(Student(104, "Rohan Deshmukh", "CSE-2025-045", "AI-ML", 3, 7.80));
            students.push_back(Student(105, "Ananya Verma", "CSE-2025-052", "CSE", 3, 9.40));
            saveToFile();
            return;
        }

        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;
            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);
            size_t p4 = line.find('|', p3 + 1);
            size_t p5 = line.find('|', p4 + 1);

            if (p1 != string::npos && p2 != string::npos && p3 != string::npos && p4 != string::npos && p5 != string::npos) {
                int id = stoi(line.substr(0, p1));
                string name = line.substr(p1 + 1, p2 - p1 - 1);
                string roll = line.substr(p2 + 1, p3 - p2 - 1);
                string dept = line.substr(p3 + 1, p4 - p3 - 1);
                int sem = stoi(line.substr(p4 + 1, p5 - p4 - 1));
                double gpa = stod(line.substr(p5 + 1));
                students.push_back(Student(id, name, roll, dept, sem, gpa));
            }
        }
    }
};

int main() {
    StudentManagementSystem sms;
    int choice;

    while (true) {
        cout << "\n" << string(60, '=') << "\n";
        cout << "  STUDENT ACADEMIC & COURSE MANAGEMENT SYSTEM\n";
        cout << string(60, '=') << "\n";
        cout << "1. Enroll New Student Record\n";
        cout << "2. Display Full Directory Table\n";
        cout << "3. Calculate Semester SGPA (Credit-Weighted)\n";
        cout << "4. Sort Directory (by Merit Rank or Alphabetical)\n";
        cout << "5. Institutional Academic Analytics & Class Metrics\n";
        cout << "6. Export Student Directory to CSV (Excel Format)\n";
        cout << "7. Exit Application\n";
        cout << "Enter Selection (1-7): ";
        
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "[!] Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1: sms.addStudent(); break;
            case 2: sms.displayAll(); break;
            case 3: sms.calculateCourseGPA(); break;
            case 4: sms.sortStudents(); break;
            case 5: sms.displayStatistics(); break;
            case 6: sms.exportToCSV(); break;
            case 7: 
                cout << "\nExiting Academic Management System. Goodbye!\n";
                return 0;
            default: cout << "[!] Invalid option. Please choose 1-7.\n";
        }
    }
}
