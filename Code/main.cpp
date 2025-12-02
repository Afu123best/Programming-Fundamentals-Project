#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;
/*
GLOBAL ARRAYS (Database stored in arrays)
-Maximum 100 students
-Data stored in parallel arrays so index i corresponds to same student
*/
char name[100][50]; //Student name max 50 characters
int roll_num[100]; //Roll Number
char section[100];  //Section: A, B or C
int quizzes[100][3]; //3 quiz marks
int assignments[100][2]; //2 assignment marks
int midterm[100]; //midterm marks
int final[100]; //final marks

int student_total[100]; //total marks for each student

double percentage[100]; //percentage calculation
char grade[100]; //Final grade (A-F)

//Global variables
int student_count = 0; //Total number of active students  
const int total_maximum_marks = (3*10) + (2*10) + 50 + 100; //=200

//INPUT VALIDATION FUNCTIONS START FROM HERE

//SAFE INTEGER FROM USER (letter input pr masla na karay)

void input_valid_name(char arr[], int size){
    while (true){
        cin.getline(arr,size);
        if (strlen(arr) == 0 || strspn(arr," ") == strlen(arr)){
            cout << "Invalid. Name cannot be empty. Enter again: ";
            continue;
        }
        bool valid = true;
        for (int i = 0; arr[i] != '\0'; i++){
            if (!isalpha(arr[i]) && arr[i] != ' '){
                valid = false;
                break;
            }
        }
        if (!valid){
            cout << "Invalid name. Only letters and spaces are allowed. Enter again: ";
            continue;
        }
        return;
    }
}

int input_int_safe(){
    int x;
    while (true){
        cin >> x;
        if (!cin.fail()){
            return x;
        }
        cout << "Invalid input! Please enter a number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

//INTEGER FROM USER WITH RANGE
int input_int_range(int low, int high){
    int x;
    while (true){
        cin >> x;
        if (!cin.fail() && x >= low && x <= high){
            return x;
        }
        cout << "Invalid! Enter a number between " << low << " and " << high << ": ";
        cin.clear();
        cin.ignore(10000,'\n');
    }
}

//ROLL NUMBER ALREADY EXISTS? (helper)
bool roll_number_exists(int r){
    for (int i = 0; i < student_count; i++){
        if (roll_num[i] == r){
            return true;
        }
    }
    return false;
}

//ROLL NUMBER VALID
int input_valid_roll(){
    int r;
    while (true){
        cin >> r;
        if (cin.fail()){
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "Invalid! Enter a valid number: ";
            continue;
        }
        if (r <= 0){
            cout << "Roll number must be positive: ";
            continue;
        }
        if (roll_number_exists(r)){
            cout << "Roll number already exists! Enter another: ";
            continue;
        }
        if (!(r >= 1000 && r <= 9999)){
            cout << "Roll number must be 4 digits: ";
            continue;
        }
        return r;
    }
}

//SECTION VALIDATION
char input_valid_section(){
    char s;
    while (true){
        cin >> s;
        s = toupper(s);
        if (s == 'A' || s == 'B' || s == 'C'){
            return s;
        }
        cout << "Invalid section! Enter A, B, or C: ";
    }
}

//INPUT VALIDATION FUNCTIONS END FROM HERE

//DISPLAY A SINGLE STUDENT RECORD
void display_student(int index) {
    cout << "Name: " << name[index] << "\n";
    cout << "Roll: " << roll_num[index] << "\n";
    cout << "Section: " << section[index] << "\n";

    cout << "Quiz1: " << quizzes[index][0] << "\n";
    cout << "Quiz2: " << quizzes[index][1] << "\n";
    cout << "Quiz3: " << quizzes[index][2] << "\n";
    cout << "Assignment1: " << assignments[index][0] << "\n";
    cout << "Assignment2: " << assignments[index][1] << "\n";
    
    cout << "Midterm: " << midterm[index] << "\n";
    cout << "Final: " << final[index] << "\n";

    cout << "Percentage: " << percentage[index] << "\n";
    cout << "Grade: " << grade[index] << "\n";
}

//DISPLAY ALL STUDENTS IN A TABULAR FORMAT
void display_all_students_tabular(){
    if (student_count == 0){
        cout << "No students available.\n";
        return;
    }
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "Name                 Roll  Sec  Q1  Q2  Q3  A1  A2  Mid  Final  Total  %       Grade\n";
    cout << "----------------------------------------------------------------------------------------------\n";
    
    for (int i = 0; i < student_count; i++){
        cout << left;

        cout << setw(20) << name[i]
        << setw(6) << roll_num[i] 
        << setw(5) << section[i] 
        << setw(4) << quizzes[i][0] 
        << setw(4) << quizzes[i][1] 
        << setw(4) << quizzes[i][2]
        << setw(4) << assignments[i][0]
        << setw(4) << assignments[i][1]
        << setw(6) << midterm[i]
        << setw(7) << final[i]
        << setw(7) << student_total[i]
        << setw(8) << fixed << setprecision(2) << percentage[i]
        << setw(6) << grade[i]
        << endl;
    }
    cout << "----------------------------------------------------------------------------------------------\n";
}

//BUBBLE SORT TO DESCENDING ORDER
void sort_by_percentage_desc() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if (percentage[j] < percentage[j + 1]) {   

                // swap everything for student j and j+1

                swap(name[j], name[j + 1]);
                swap(roll_num[j], roll_num[j + 1]);
                swap(section[j], section[j + 1]);

                for (int k = 0; k < 3; k++)
                    swap(quizzes[j][k], quizzes[j + 1][k]);

                for (int k = 0; k < 2; k++)
                    swap(assignments[j][k], assignments[j + 1][k]);

                swap(midterm[j], midterm[j + 1]);
                swap(final[j], final[j + 1]);
                swap(student_total[j], student_total[j + 1]);
                swap(percentage[j], percentage[j + 1]);
                swap(grade[j], grade[j + 1]);
            }
        }
    }

    cout << "Students sorted by percentage (highest to lowest).\n";
}

//SEARCH BY ROLL NUMBER (RETURNS -1 IF NOT FOUND)
int search_student_by_roll() {
    if (student_count == 0){
        cout << "No students available.\n";
        return -1;
    }
    int entered_roll_num;
    cout << "Enter roll number: ";
    cin >> entered_roll_num;

    for (int i = 0; i < student_count; i++) {
        if (roll_num[i] == entered_roll_num) {
            return i;  
        }
    }

    return -1;   
}

//CALCULATE PERCENTAGE AND GRADE OF A STUDENT
void calculate_percentage_and_grade(int index){
    int total_obtained_marks = quizzes[index][0] + quizzes[index][1] + quizzes[index][2] + assignments[index][0] + assignments[index][1] + midterm[index] + final[index];
    percentage[index] = ((double)total_obtained_marks/total_maximum_marks) * 100; //important to do (double) because dividing that sometimes becomes 0. so 0.75 is 75% but without double it will be 0%

    if (percentage[index] >= 90){
        grade[index] = 'A';
    }
    else if (percentage[index] >= 80){
        grade[index] = 'B';
    }
    else if (percentage[index] >= 70){
        grade[index] = 'C';
    }
    else if (percentage[index] >= 60){
        grade[index] = 'D';
    }
    else{
        grade[index] = 'F';
    }
}

//ADD NEW STUDENT TO DATABASE
void add_student(){
    int index = student_count;
    
    cout << "Enter student name: ";
    cin.ignore(10000,'\n');
    input_valid_name(name[index], 50);
    
    cout << "Enter student roll number: ";
    roll_num[index] = input_valid_roll();
    
    cout << "Enter section(A,B,C): ";
    section[index] = input_valid_section();
    
    cout << "Enter quiz 1 marks(0-10): ";
    quizzes[index][0] = input_int_range(0, 10);
    cout << "Enter quiz 2 marks(0-10): ";
    quizzes[index][1] = input_int_range(0, 10);
    cout << "Enter quiz 3 marks(0-10): ";
    quizzes[index][2] = input_int_range(0, 10);

    cout << "Enter assignment 1 marks(0-10): ";
    assignments[index][0] = input_int_range(0, 10);
    cout << "Enter assignment 2 marks(0-10): ";
    assignments[index][1] = input_int_range(0, 10);

    cout << "Enter midterm marks(0-50): ";
    midterm[index] = input_int_range(0,50);

    cout << "Enter final marks(0-100): ";
    final[index] = input_int_range(0,100);

    student_total[index] = quizzes[index][0] + quizzes[index][1] + quizzes[index][2] + assignments[index][0] + assignments[index][1] + midterm[index] + final[index];

    calculate_percentage_and_grade(index);
    cout << "System | Successfully added student " << index << "\n"; 
    student_count++;
}

//UPDATE EXISTING STUDENT RECORD
void update_student(){
    if (student_count == 0){
        cout << "No student available.\n";
        return;
    }
    int index = search_student_by_roll();

    if (index == -1) {
        cout << "System | Roll number not found!\n";
        return;
    }
    else{

        cout << "Enter student name: ";
        cin.ignore(10000,'\n');
        input_valid_name(name[index], 50);
    
        cout << "Enter section(A,B,C): ";
        section[index] = input_valid_section();
    
        cout << "Enter quiz 1 marks(0-10): ";
        quizzes[index][0] = input_int_range(0, 10);
        cout << "Enter quiz 2 marks(0-10): ";
        quizzes[index][1] = input_int_range(0, 10);
        cout << "Enter quiz 3 marks(0-10): ";
        quizzes[index][2] = input_int_range(0, 10);

        cout << "Enter assignment 1 marks(0-10): ";
        assignments[index][0] = input_int_range(0, 10);
        cout << "Enter assignment 2 marks(0-10): ";
        assignments[index][1] = input_int_range(0, 10);

        cout << "Enter midterm marks(0-50): ";
        midterm[index] = input_int_range(0,50);

        cout << "Enter final marks(0-100): ";
        final[index] = input_int_range(0,100);

        student_total[index] = quizzes[index][0] + quizzes[index][1] + quizzes[index][2] + assignments[index][0] + assignments[index][1] + midterm[index] + final[index];

        calculate_percentage_and_grade(index);
        cout << "System | Successfully updated student " << index << "\n"; 
    }
}

//DELETE A STUDENT RECORD AND SHIFT LEFT
void delete_student(){
    int index = search_student_by_roll();

    if (index == -1) {
        cout << "System | Roll number not found!\n";
        return;
    }
    else{
        //shift all the records left from index
        for (int i = index; i < student_count-1; i++){
            strcpy(name[i],name[i+1]);
            roll_num[i] = roll_num[i+1];
            section[i] = section[i+1];
            quizzes[i][0] = quizzes[i+1][0];
            quizzes[i][1] = quizzes[i+1][1];
            quizzes[i][2] = quizzes[i+1][2];
            assignments[i][0] = assignments[i+1][0];
            assignments[i][1] = assignments[i+1][1];
            midterm[i] = midterm[i+1];
            final[i] = final[i+1];
            student_total[i] = student_total[i+1];
            percentage[i] = percentage[i+1];
            grade[i] = grade[i+1];
        }
        student_count--;
        cout << "System | Student deleted successfully.";
    }
}

//SEARCH & DISPLAY A STUDENT
void search_and_display(){
    int index = search_student_by_roll();
    if (index == -1){
        cout << "System | Roll number not found!\n";
        return;
    }
    else{
        display_student(index);
    }
}

//DISPLAY CLASS AVERAGE PERCENTAGE
void display_average(){
    if (student_count == 0){
        cout << "No students available\n";
        return;
    }
    double avg_percentage = 0;
    for (int i = 0; i < student_count; i++){
        avg_percentage += percentage[i];
    }
    avg_percentage /= student_count;

    cout << "Class Average Percentage: " << avg_percentage << "\n";
}

//DISPLAY STUDENT WITH HIGHEST MARKS
void display_highest(){
    if (student_count == 0){
        cout << "No students available.\n";
        return;
    }
    int highest = -1;
    int highest_index = 0;
    for (int index = 0; index < student_count; index++){
        if (student_total[index] > highest){
            highest = student_total[index];
            highest_index = index;
        }
    }
    cout << "Highest total marks in class: " << highest << "\n";
    display_student(highest_index);
}

//DISPLAY STUDENT WITH LOWEST MARKS
void display_lowest(){
    if (student_count == 0){
        cout << "No students available.\n";
        return;
    }
    int lowest = 10000;
    int lowest_index = 0; 
    for (int index = 0; index < student_count; index++){
        if (student_total[index] < lowest){
            lowest = student_total[index];
            lowest_index = index;
        }
    }
    cout << "Lowest total marks in class: " << lowest << "\n";
    display_student(lowest_index);
}

//DISPLAY CLASS TOPPER(s) (handles more than 1)
void display_topper(){
    if (student_count == 0){
        cout << "No students available.\n";
        return;
    }
    
    int highest = -1;
    for (int i = 0; i < student_count; i++){
        if (student_total[i] > highest){
            highest = student_total[i];
        }
    }
    cout << "Topper(s) with " << highest << " marks\n";
    for (int i = 0; i < student_count; i++){
        if (student_total[i] == highest){
            display_student(i);
            cout << "\n";
        }
    }
}

//PRINT STATISTICS FOR ANY ARRAY (HELPER FUNCTION)
void print_stats(string label, int arr[], int n) {
    int highest = arr[0];
    int lowest = arr[0];
    int sum = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > highest){
            highest = arr[i];
        } 
        if (arr[i] < lowest){
            lowest = arr[i];
        } 
        sum += arr[i];
    }

    double average = (double)sum / n;

    cout << label << ":\n";
    cout << "   Highest: " << highest << "\n";
    cout << "   Lowest : " << lowest << "\n";
    cout << "   Average: " << average << "\n\n";
}

//GENERATE SUBJECT WISE STATISTICS
void generate_statistics(){
    if (student_count == 0) {
        cout << "No students available.\n";
        return;
    }
    cout << "System | Generating Subject Wise Statistics . . . \n";
    int tq1[100], tq2[100], tq3[100];
    int ta1[100], ta2[100];
    int tmid[100], tfin[100];

    for (int i = 0; i < student_count; i++) {
        tq1[i] = quizzes[i][0];
        tq2[i] = quizzes[i][1];
        tq3[i] = quizzes[i][2];

        ta1[i] = assignments[i][0];
        ta2[i] = assignments[i][1];

        tmid[i] = midterm[i];
        tfin[i] = final[i];
    }

    print_stats("Quiz 1", tq1, student_count);
    print_stats("Quiz 2", tq2, student_count);
    print_stats("Quiz 3", tq3, student_count);

    print_stats("Assignment 1", ta1, student_count);
    print_stats("Assignment 2", ta2, student_count);

    print_stats("Midterm", tmid, student_count);
    print_stats("Final", tfin, student_count);
}  

//EXPORT FULL REPORT TO A TXT FILE
void export_report(){
    ofstream file("report.txt");
    if (!file){
        cout << "System | Error creating file\n";
        return;
    }

    file << "STUDENT REPORT\n\n";
    for (int i = 0; i < student_count; i++){
        file << "Student " << i+1 << "\n";
        file << "Name: " << name[i] << "\n";
        file << "Roll Number: " << roll_num[i] << "\n";
        file << "Section: " << section[i] << "\n";

        file << "Quiz1: " << quizzes[i][0] << "\n";
        file << "Quiz2: " << quizzes[i][1] << "\n";
        file << "Quiz3: " << quizzes[i][2] << "\n";

        file << "Assignment1: " << assignments[i][0] << "\n";
        file << "Assignment2: " << assignments[i][1] << "\n";

        file << "Midterm: " << midterm[i] << "\n";
        file << "Final: " << final[i] << "\n";

        file << "Total: " << student_total[i] << "\n";
        file << "Percentage: " << percentage[i] << "\n";
        file << "Grade: " << grade[i] << "\n";
        
        file << "-----------------------------------" << "\n";
    }

    file.close();
    cout << "System | Report exported to report.txt successfully!\n";
}

//SAVE DATABASE TO FILE
void save_to_file(){
    ofstream file("students.txt");

    if (!file){
        cout << "System | Error saving file!\n";
        return;
    }
    file << student_count << "\n";
    for (int i = 0; i < student_count; i++){
        file << name[i] << "\n";
        file << roll_num[i] << "\n";
        file << section[i] << "\n";

        file << quizzes[i][0] << " " << quizzes[i][1] << " " << quizzes[i][2] << "\n";
        file << assignments[i][0] << " " << assignments[i][1] << "\n";

        file << midterm[i] << " " << final[i] << "\n";
        
        file << student_total[i] << " " << percentage[i] << " " << grade[i] << "\n";

        file << "-\n"; //separator
    }
    file.close();
    cout << "System | Saved to students.txt successfully!\n";
}

//LOAD DATABASE FROM FILE
void load_from_file(){
    ifstream file("students.txt");
    if (!file){
        cout << "System | No existing file found. Starting fresh\n";
        return;
    }
    
    file >> student_count;
    file.ignore();
    for (int i = 0; i < student_count; i++){
        
        file.getline(name[i], 50);

        file >> roll_num[i];
        file >> section[i];

        file >> quizzes[i][0] >> quizzes[i][1] >> quizzes[i][2];
        file >> assignments[i][0] >> assignments[i][1];

        file >> midterm[i] >> final[i];

        file >> student_total[i] >> percentage[i] >> grade[i];
        file.ignore();
        file.ignore(1000, '\n');
    }
    file.close();
    cout << "System | File loaded successfully!\n";
}

//MAIN MENU
void show_menu(){
    int choice = 0;
    while (choice != 12){
        cout << "1.Add New Student\n";
        cout << "2.Update Student\n";
        cout << "3.Delete Student\n";
        cout << "4.Search by roll number and display\n";
        cout << "5.Display Class Average\n";
        cout << "6.Display Class Highest\n";
        cout << "7.Display Class Lowest\n";
        cout << "8.Display topper(s)\n";
        cout << "9.Generate Subject Wise Statistics\n";
        cout << "10.Export Report To Text File\n";
        cout << "11. Display All Students\n";
        cout << "\n12.Exit\n";

        cout << "\n Enter your choice: ";
        cin >> choice;
        
        if (choice == 1){
            add_student();
        }
        else if (choice == 2){
            update_student();
        }
        else if (choice == 3){
            delete_student();
        }
        else if (choice == 4){
            search_and_display();
        }
        else if (choice == 5){
            display_average();
        }
        else if (choice == 6){
            display_highest();
        }
        else if (choice == 7){
            display_lowest();
        }
        else if (choice == 8){
            display_topper();
        }
        else if (choice == 9){
            generate_statistics();
        }
        else if (choice == 10){
            export_report();
        }
        else if (choice == 11){
            sort_by_percentage_desc();
            display_all_students_tabular();
        }
        else if (choice == 12){
            cout << "Saving and Exiting . . .\n";
        }
        else{
            cout << "Invalid choice! Try again\n";
        }
    }
}


int main(){
    cout << "System | Loading from file . . .\n";
    load_from_file();
    cout << "System | File loaded successfully!\n";
    
    show_menu();

    cout << "System | Saving to file . . . \n";
    save_to_file();
    cout << "System | Saved to file successfully!\n";

    return 0;
}

//limitation list that i think of while coding (please remove in final version)
//1. so the arrays are hardcoded to 100 total students. that means this database system can only handle 100 students dynamically
//2. Each student can have a name with up to 50 characters so if a student is arabic and has a name: Saad Ibn Abdelaziz Ibn Ali Ismael Shik Shak Shok Balla Thein Shawarma Wala bebsi Zyadeh Batata Bdoon Salata Ma3 Ganeenet Bebsi Bardeh Bdoon Thalj Wallak
//3. all calculations are done in integer for simplicity. so someone can have 89.9999% and still get a B. well too bad lol


//what to think about:
//automatic saving or manual saving (maybe save automatically before returning 0 in the main function and givng the option to save manually too)
//the pdf says to "Handle input validation and edge cases.​" so lets make a function that does that.
//quizzes marks range 0-10, assignments marks range 0-10, midterms marks range 0-50, finals marks range 0-100
//when updating a student, you cannot CANNOT change his/her roll number. since roll numbers cannot change in most ID systems. yes :)

//percentage - grade
//>= 90% - A
//>= 80% - B
//>= 70% - C
//>= 60% - D
//<= 60% - F
//roll number will be 1234

/*Format of my file:
student_count
name
roll
section
quiz1 quiz2 quiz3
ass1 ass2
mid final
total percentage grade
(repeat for each student)
*/
