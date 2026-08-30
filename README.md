# Student Record and Course Management System

A high-performance command-line application built in Modern C++17 utilizing Object-Oriented Programming (OOP), file persistence, multi-criteria sorting algorithms, credit-weighted SGPA calculation, and institutional CSV reporting.

---

## Executive Summary and Description

The Student Record and Course Management System is an academic administration tool designed to handle student data management, performance analytics, and institutional records with speed and reliability. Built in modern C++17, it utilizes delimited file streams (fstream) for persistence, eliminating external database dependencies.

The system features multi-criteria sorting algorithms (Merit Rank, Alphabetical, Student ID), institutional statistical analytics (Mean CGPA, Standard Deviation, Toppers), credit-weighted Semester GPA (SGPA) calculation, and a one-click CSV report exporter formatted for spreadsheet software like Microsoft Excel and Google Sheets.

---

## System Architecture and Workflow

```
[Application Startup]
        |
        v
[Load File Stream: students_db.txt] --(Parse Delimited Strings)--> [std::vector<Student> Memory Bank]
                                                                                |
   +----------------------------------------------------------------------------+---------------------------+
   |                                            |                               |                           |
   v                                            v                               v                           v
[Enroll Student]                        [Sort Records]                 [Analytics Engine]          [CSV Report Exporter]
- Validate ID                            - CGPA Merit Rank              - Class Mean CGPA           - students_report.csv
- Update std::vector                     - Alphabetical Name            - Standard Deviation (s)    - Excel Compatible
- Save students_db.txt                   - Student ID                   - Class Toppers
```

---

## Key Features

- Object-Oriented Design (OOP): Clean encapsulation with Student and StudentManagementSystem classes.
- File Persistence: Auto-saves and loads records from students_db.txt via pipe-delimited file streams.
- Institutional Statistical Analytics: Computes class average CGPA, standard deviation, top performers, and lowest GPAs.
- Credit-Weighted SGPA Calculator: Computes exact semester GPAs based on course credits and grade points.
- Multi-Criteria Sorting: Custom lambda comparators for ranking by Merit, Alphabetical Name, or ID.
- CSV Spreadsheet Exporter: Exports student directories into standard students_report.csv files.
- Robust Input Sanitization: Prevents duplicate IDs and handles malformed CLI inputs.

---

## Tech Stack and Prerequisites

- Language: Modern C++17
- Compiler: GCC / MinGW-w64 (g++) or MSVC
- Storage: Pipe-delimited flat-file storage (fstream)
- Prerequisites: A C++17 compatible compiler installed (g++ --version)

---

## Installation and Quickstart Guide

### 1. Navigate to Directory
```bash
cd "C:\Users\shiva\OneDrive\Documents\projects\03-student-management-system"
```

### 2. Compile the Source Code
Compile with g++ using the C++17 standard:
```bash
g++ -std=c++17 main.cpp -o student_system.exe
```

### 3. Execute the Application
```bash
.\student_system.exe
```

---

## Usage Instructions and Examples

When launched, the application displays an interactive terminal menu:

```
============================================================
  STUDENT ACADEMIC AND COURSE MANAGEMENT SYSTEM
============================================================
1. Enroll New Student Record
2. Display Full Directory Table
3. Calculate Semester SGPA (Credit-Weighted)
4. Sort Directory (by Merit Rank or Alphabetical)
5. Institutional Academic Analytics and Class Metrics
6. Export Student Directory to CSV (Excel Format)
7. Exit Application
Enter Selection (1-7):
```

---

## Verification and Sample Directory Table

```
===============================================================================================
ID      NAME                ROLL NO         DEPARTMENT    SEM   CGPA    ACADEMIC STATUS             
-----------------------------------------------------------------------------------------------
101     Shivam Patil        CSE-2025-001    AI-ML         3     9.65    First Class with Distinction (Honors)
105     Ananya Verma        CSE-2025-052    CSE           3     9.40    First Class with Distinction (Honors)
103     Priya Nair          CSE-2025-029    Data Science  3     9.25    First Class with Distinction (Honors)
102     Aarav Sharma        CSE-2025-014    CSE           3     8.90    First Class with Distinction
104     Rohan Deshmukh      CSE-2025-045    AI-ML         3     7.80    First Class                 
===============================================================================================
Total Active Records: 5
```

---

## Author and Attribution

- Developer: Shivam Patil
- Designation: Aspiring Software Engineer | CSE Undergraduate
- Portfolio: [https://shivam.dev](https://shivampatilck-1010.github.io/portfolio-website/)

---

## License and Copyright

Copyright (c) 2026 Shivam Patil (shivam.dev). All rights reserved.
