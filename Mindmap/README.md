This is the first time I am making a README.md file.

Overview:
The Student Performance Management System (SPMS) is a console-based C++ application
that allows storing, managing, and analyzing students’ academic performance data (marks of
quizzes, assignments, and exams).

Functional Requirements (Features):
1. Student Record Management
● Add a new student (Name, Roll Number, Section)
● Store marks for at least 3 quizzes, 2 assignments, Midterm and Final exam.
● Update or delete existing student record
2. Data storage and retrieval 
● Store records in arrays during runtime.​
● Save records to a text file for persistence.​
● Load records from file at program start.​
3. Performance Calculations
● Calculate total marks and percentage.​
● Assign a grade (A, B, C, D, F) based on percentage.​
● Identify topper(s) of the class.​
4. Reports
●Display all student records in a tabular format.​
● Search student by Roll No.​
● Show class average, highest, and lowest scores.​

Additional Features:
● Sort students by percentage (descending order).​
●​ Generate subject-wise statistics (e.g., average quiz score).​
● Export report to a text file.​


Things to submit:
1. Project Report (PDF) including:
○ Cover page (Project title, team members, roll numbers).​
○​ Problem description.​
○​ Features implemented.​
○​ Sample input/output screenshots.​
○​ Known limitations (if any).​

2.​ Source Code Files (.cpp files + input data file).​


Mind map:
Lets try to save data on a .text file. That text file can be our primary memory. Since we cant use records, we will use arrays with the same universal unique index for a unique student. that means marks[1] will be the marks of students[1] parallel arrays basically