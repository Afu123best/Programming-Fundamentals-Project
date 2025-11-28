Student Database Management System

AFNAN MAJEED — 25L-0706
HASHIM KHAN NIAZI — 25L-0703
2025

Table of Contents

Problem Description

Features Implemented

Sample Input/Outputs

Known Limitations (if any)

Problem Description

Often teachers struggle to keep track of a students’ yearly report as it is messy and difficult to do. Keeping track of continuously changing conditions like calculating averages, and total is a tedious part of a teachers’ already jampacked schedule. Without a structured and actively updating system, retrieving individual student records, determining grades and identifying toppers becomes a difficult task.

Therefore, the Student Performance Management System (SPMS) is a solution to the problem teachers’ face. SPMS is a console-based program that actively calculates all the tedious and repeatable calculations with every input. It uses global arrays to keep track of the records of each individual student. It also supports permanent memory as the records of students need to be saved permanently and accessed at the convenience of the user.

By ensuring accurate data handling, validation, and persistence through file storage, the SPMS enables instructors to maintain organized records and quickly evaluate students’ academic progress.

Features Implemented
1) Student Record Management System

Functionality to create individual student record with name, roll number etc.

Ability to update a record in the system

Ability to delete a record in the system

2) File Handling and Storing Data

Functionality of loading file for persistent data.

Functionality for saving file for updated persistent data.

3) Performance Calculations

Calculates class highest, lowest, average.

Calculates total and percentage

Grade assignment on student performance

Identifies class topper(s).

4) Reports and Display

Displays all students

Displays average, highest, total, topper(s).

5) Additional Enhancements

Sorts students by percentage (descending order)

Subject wise statistics for individual coursework performance

Option to export report to a text file

Sample Input/Output Screenshots

File: Input/output:

Input/output:

Known Limitations

Data capacity limited to 100:
The system can only handle 100 students.

Input Validation Lacking For Certain Cases
If user enters an empty input for name or roll number, the program will crash. (Easy fix for this)
If user enters a string longer than 49

Limited Updating Options
The system makes the user change the entire fields of a student so its a bit tedious when user wants to updates only a single field
The system does not update the roll number of a student. This limitation was set by me as I believe ID shouldn’t change for a student. And for simplicity

File Handling is Basic:
Anyone can access private records easily due to lack of encryption.
No automatic formatting of file when in the case of corruption or manual edition.

Majority Calculations in Int:
For simplicity, total, highest, lowest etc was calculated in int.

No Undo or Recovery Options:
If user deletes a record on accident, there is no undo option.
