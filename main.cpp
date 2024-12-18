#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

void menu();

void add_new_student();

void show_student_info();

void search_with_num();

void delete_student_data();

void addCourse();

float gpa = 0, all_credits;
int menuChoose;

int main() {
    menu();

}

void menu() {
    while (true) {
        cout << "1.Add new student \n"
                "2.Show student info \n"
                "3.Add course to a student\n"
                "4.Search with student num\n"
                "5.Delete student data\n"
                "6.Exit\n";
        cout << "What you want to do? ";
        cin >> menuChoose;
        if (menuChoose == 1) {
            add_new_student();
        } else if (menuChoose == 2) {
            show_student_info();
        } else if (menuChoose == 3) {
            addCourse();
        } else if (menuChoose == 4) {
            search_with_num();
        } else if (menuChoose == 5) {
            delete_student_data();
        } else if (menuChoose == 6) {
            cout << "Exited!";
            break;
        }
    }
}

void add_new_student() {
    string student_name, student_number, existing_numbers;
    string data;

    ifstream myF("ST_numbers.txt");
    if (myF.is_open()) {
        while (getline(myF, data)) {
            existing_numbers += data + '\n';  // Adding newline for proper matching
        }
        myF.close();
    }

    cout << "Student name: ";
    getline(cin >> ws, student_name);

    while (true) {
        cout << "Student number (8 digits): ";
        getline(cin >> ws, student_number);

        if (student_number.length() != 8 || !isdigit(student_number[0])) {
            cout << "Invalid student number. Please enter an 8-digit number.\n";
            continue;
        }
        if (existing_numbers.find(student_number + '\n') != string::npos) {
            cout << "Student number already exists. Please enter a unique number.\n";
            continue;
        }

        break;
    }
    ofstream studentNumbers("ST_numbers.txt", ios::app);
    if (studentNumbers.is_open()) {
        studentNumbers << student_number << '\n';
        studentNumbers.close();
    }
    ofstream myFile("ST_" + student_number + ".txt", ios::app);
    if (myFile.is_open()) {
        myFile << "Student Number: " << student_number << "\nStudent Name: " << student_name;
        myFile.close();
    }
    cout << "Data saved.\n";
}

void show_student_info() {
    for (const auto &item: filesystem::directory_iterator(".")) {
        if (item.is_regular_file() && item.path().filename().string().starts_with("ST_")) {
            ifstream file(item.path());
            if (file) {
                cout << "Contents of file: " << item.path().filename() << "\n";
                cout << file.rdbuf();
                cout << "----------------------------------\n";
            } else {
                cerr << "Error: Could not open file " << item.path() << "\n";
            }
        }
    }
}

void search_with_num() {
    string student_number;
    cout << "Student number: ";
    getline(cin >> ws, student_number);
    ifstream myFile("ST_" + student_number + ".txt");

    if (myFile) {
        string data;
        while (getline(myFile, data)) {
            cout << data << endl;
        }
        myFile.close();
    } else {
        cout << student_number + " does not exist! Try again!!\n";
    }
}

void delete_student_data() {
    string student_num;
    cout << "Student number: ";
    getline(cin >> ws, student_num);
    try {
        if (filesystem::remove("ST_" + student_num + ".txt")) {
            cout << "File " << student_num << " deleted.\n";
        } else {
            cout << "File " << student_num << " not found.\n";
        }
    } catch (const filesystem::filesystem_error &err) {
        cout << "Filesystem error: " << err.what() << '\n';
    }
}

void addCourse() {
    string student_num;
    cout << "Student Number: ";
    getline(cin >> ws, student_num);
    ofstream file("ST_" + student_num + ".txt", ios::app);
    string data, all_data;
    while (true) {
        char y_n;
        cout << "Do you want to add a course? (y/n): ";
        cin >> y_n;
        if (y_n == 'y') {
            if (file.is_open()) {
                all_data = "";
                string course;
                float grade, credits;
                cout << "Course name: ";
                getline(cin >> ws, course);
                cout << "Credits: ";
                cin >> credits;
                all_credits += credits;
                cout << "Grade: ";
                cin >> grade;
                gpa += (grade * credits);
                all_data += "\nCourse: " + course + ", Credits: " + to_string(credits) + ", Grade: " + to_string(grade);
                file << all_data;
            } else {
                cout << "Failed to open the file!" << endl;
            }
        } else {
            file << "\nGPA: " + to_string(gpa / all_credits);
            file.close();
            break;
        }
    }
}
