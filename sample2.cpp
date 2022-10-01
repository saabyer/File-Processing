#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<conio.h>

struct student {
    int Rec;
    std::string StudentID;
    std::string Surname;
    std::string FirstName;
    std::string BirthDate;
    std::string Sex;
};

void create_new_file();
void open_an_existing_file();
void manage_data();
void get_answer1();
void get_answer2(std::vector<student> &students, std::ofstream &file);
//bool is_empty(std::ifstream &file);

//bool is_empty(std::ifstream &file) {
//    return file.peek() == std::ifstream::traits_type::eof();
//}

void create_new_file() {
    std::ofstream file;
    std::string filename;
    std::cout << "Enter a file name: ";
    std::cin >> filename;
    filename.append(".txt");
    file.open(filename);
    std::cout << "Successfully created a file called " << filename << ".\n";
}

void open_an_existing_file() {
    std::fstream file;
    std::string filename;
    std::cout << "Enter file name: ";
    std::cin >> filename;
    filename.append(".txt");
    file.open(filename);
    if(file.is_open()) {
        std::cout << "Active File: " << filename << std::endl;
        std::cout << "-----------------------------------------------------------------------\n";
        std::cout << "Rec\tStudent ID\tSurname\tFirstname\tBirthDate\tSex\n";
        std::cout << "-----------------------------------------------------------------------\n";
        std::cout << file.rdbuf() << "\n";
    }
}

void manage_data() {
    char answer;
    std::ofstream file;
    std::vector<student> students;
    get_answer2(students, file);
}

void get_answer2(std::vector<student> &students, std::ofstream &file) {
    char answer;
    student temp;
    std::cout << "[A]dd [E]dit [D]elete [S]ort [F]ilter sa[V]e e[X]it\n";
    answer = toupper(getch());
    if(answer == 'A') {
        temp.Rec = students.size() + 1;
        std::cin.ignore();
        std::cout << "Student ID: ";
        std::getline(std::cin, temp.StudentID);
        std::cout << "Surname: ";
        std::getline(std::cin, temp.Surname);
        std::cout << "Firstname: ";
        std::getline(std::cin, temp.FirstName);
        std::cout << "Birthdate: ";
        std::getline(std::cin, temp.BirthDate);
        std::cout << "Sex: ";
        std::getline(std::cin, temp.Sex);
        students.push_back(temp);
        get_answer2(students, file);
    }
    else if (answer == 'E') {

    }
    else if (answer == 'D') {

    }
    else if (answer == 'S') {

    }
    else if (answer == 'F') {

    }
    else if (answer == 'V') {
        if (file.is_open()) {
            file << temp.Rec << "\t";
            file << temp.StudentID << "\t";
            file << temp.Surname << "\t";
            file << temp.FirstName << "\t";
            file << temp.BirthDate << "\t";
            file << temp.Sex << "\n";
            get_answer2(students, file);

        }
    }
    else if (answer == 'X') {
        exit(0);
    }
    else {
        std::cout << "Invalide Choice!\n";
        get_answer2(students, file);
    }
}

void get_answer1() {
    std::cout << "\n[1] Create New File [2] Open an Existing File [3] Manage Data [4] Exit\n";
    char answer = getch();
    if(answer == '1') {
        create_new_file();
        get_answer1();
    }
    else if (answer == '2') {
        open_an_existing_file();
        get_answer1();
    }
    else if (answer == '3') {
        manage_data();
    }
    else if (answer == '4') {
        exit(0);
    }
    else {
        std::cout << "Invalid choice!\n";
        get_answer1();
    }
}

void interface() {
    get_answer1();
}

int main() {
    std::fstream file;
    interface();
}
