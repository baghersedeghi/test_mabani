#include <iostream>

using namespace std;

void  menu();
void  add_new_student ();
void  show_student_info();
void  search_with_num();
void  delete_student_data();
void  add_course();
int main() {
    menu();

}
void  menu(){
string choose;
    cout<< "1.add new  student \n"
       "2.show student info \n"
       "3.search with student num\n "
       "4.delete student data";

    cout<< "what you  whant to do?";
    cin>> choose;
if (choose=="1"){
    system("cls");
    add_new_student();
} else if(choose=="2"){
    system("cls");
    show_student_info();
} else if (choose=="3"){
    system("cls");
    search_with_num();
}else if (choose=="4"){
    system("cls");
    delete_student_data();
}else{    system("cls");
    menu();
}


}
void  add_new_student() {
    string student_name , student_number,yes_no;
    cout<<"student name: ";
    cin>> student_name;
    cout<<"student number: ";
    cin>> student_number;
cout<< "do you  want add course ?(y/n)";
cin >> yes_no;
    if (yes_no=="y")
        add_course();

};