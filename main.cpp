#include <iostream>
#include <fstream>
#include <filesystem> // For std::filesystem

namespace fs = std::filesystem;
using namespace std;

void menu();

void add_new_student();

void show_student_info();

void search_with_num();

void delete_student_data();

void add_course(const string &File_Name);

float gpa = 0, all_credits;

int main() {
    menu();

}

void menu() {
    string choose;
    cout << "1.Add new  student \n"
            "2.Show student info \n"
            "3.Search with student num\n "
            "4.Delete student data\n"
            "5.Exit\n";

    cout << "what you  want to do? ";
    cin >> choose;
    while (true) {
        if (choose == "1") {
            system("cls");
            add_new_student();
        } else if (choose == "2") {
            system("cls");
            show_student_info();
        } else if (choose == "3") {
            system("cls");
            search_with_num();
        } else if (choose == "4") {
            system("cls");
            delete_student_data();
        } else if (choose == "5") {
            system("cls");
            break;
        } else {
            system("cls");
            menu();
        }
        menu();
    }

}

void add_new_student() {
    string student_name, student_number, yes_no;
    cout << "student name: ";
    getline(cin >> ws, student_name);
    cout << "student number: ";
    getline(cin >> ws, student_number);

    ofstream myFile("ST_" + student_number + ".txt");
    myFile << "Student Number : " + student_number + "\nStudent Name : " + student_name;
    while (true) {
        cout << "\ndo you  want add course ?(y/n)";
        cin >> yes_no;
        if (yes_no == "y")
            add_course("ST_" + student_number + ".txt");
        else
            break;
    }
    cout << "data saved✅ ";

};

void show_student_info() {
    std::string path = "."; // Current directory
    std::string prefix = "ST_";

    for (const auto &entry: fs::directory_iterator(path)) {
        // Check if the file name starts with "ST_"
        if (entry.is_regular_file() && entry.path().filename().string().rfind(prefix, 0) == 0) {
            std::ifstream file(entry.path());
            if (file.is_open()) {
                std::cout << "Contents of file: " << entry.path().filename() << "\n";
                std::string line;
                while (std::getline(file, line)) {
                    std::cout << line << "\n";
                }
                std::cout << "----------------------------------\n";
                file.close();
            } else {
                std::cerr << "Error: Could not open file " << entry.path() << "\n";
            }
        }
    }

};

void search_with_num() {
    string student_number;
    cout << "student number: ";
    getline(cin >> ws, student_number);
    ifstream myFile("ST_" + student_number + ".txt");

    if (myFile) {
        string data;
        while (getline(myFile, data)) {

            cout << data;
        }
        myFile.close();
    } else {
        cout << student_number + " not exist! \n try again !!";
    }
};

void delete_student_data() {
    string student_num;
    cout << "student number: ";
    getline(cin >> ws, student_num);

    try {
        if (std::filesystem::remove(student_num))
            std::cout << "file " << student_num << " deleted.\n";
        else
            std::cout << "file " << student_num << " not found.\n";
    }
    catch (const std::filesystem::filesystem_error &err) {
        std::cout << "filesystem error: " << err.what() << '\n';
    }
};

void add_course(const string &File_Name) {

    ifstream myFile(File_Name);
    string text, all;
    while (getline(myFile, text)) {
        all += text;
    }
    string courseName;
    float credits, grade;

    cout << "course name :";
    getline(cin >> ws, courseName);
    cout << "credits :";
    cin >> credits;
    all_credits += credits;
    cout << "grade :";
    cin >> grade;
    gpa += (grade * credits);
    string temp;
    temp= "\nCourse : " + courseName + ", Credits: " + to_string(credits) + ", Grade:" + to_string(grade);
    all +=temp;
    ofstream file(File_Name);
    file<<all;
    file.close();
    myFile.close();


};