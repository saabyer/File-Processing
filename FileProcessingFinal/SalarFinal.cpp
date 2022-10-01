#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>

struct student {
    std::string StudentID;
    std::string Surname;
    std::string FirstName;
    std::string BirthDate;
    std::string Sex;
};

//checks if a text file has no data
bool is_empty(std::ifstream &file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

//prints all the data inside a text file
void show(std::string filename) {
    filename.append(".txt");
    std::ifstream file;
    file.open(filename);
    if(file.is_open()) {
        std::cout << "Active File: " << filename << std::endl;
        std::cout << "-----------------------------------------------------------------------\n";
        std::cout << "Student ID\tSurname\tFirstname\tBirthDate\tSex\n";
        std::cout << "-----------------------------------------------------------------------\n";
        std::cout << file.rdbuf();
    }
}

//adds a student to the list of students
void add_student(std::vector<student> &students) {
    student temp;

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
}

//saves the data you want to add to the text file and exit
void save_exit(std::string filename, std::vector<student> &students) {
    filename.append(".txt");
    std::ofstream file(filename);
    if(file.is_open()) {
        for(int i = 0; i < students.size(); i++) {
            if(i < students.size() - 1) {
                file << students[i].StudentID << "\t";
                file << students[i].Surname << "\t";
                file << students[i].FirstName << "\t";
                file << students[i].BirthDate << "\t";
                file << students[i].Sex << "\n";
            }
            else if (i == students.size() - 1) {
                file << students[i].StudentID << "\t";
                file << students[i].Surname << "\t";
                file << students[i].FirstName << "\t";
                file << students[i].BirthDate << "\t";
                file << students[i].Sex;
            }
        }
        file.close();
        exit(0);
    }
    else {
        std::cout << "File not found.\n";
    }
}

//edits the data of a specific student inside the text file
void edit_record(std::string ID, std::vector<student> &students, std::string filename) {
    student temp;
    for(int i = 0; i < students.size(); i++) {
        if(ID == students[i].StudentID) {
            std::cin.ignore();
            std::cout << "New Student ID: ";
            std::getline(std::cin, temp.StudentID);
            std::cout << "New Surname: ";
            std::getline(std::cin, temp.Surname);
            std::cout << "New Firstname: ";
            std::getline(std::cin, temp.FirstName);
            std::cout << "New Birthdate: ";
            std::getline(std::cin, temp.BirthDate);
            std::cout << "New Sex: ";
            std::getline(std::cin, temp.Sex);

            students[i].StudentID = temp.StudentID;
            students[i].Surname = temp.Surname;
            students[i].FirstName = temp.FirstName;
            students[i].BirthDate = temp.BirthDate;
            students[i].Sex = temp.Sex;
        }
    }
    save_exit(filename, students);
}

//deletes the data of a specific student in the text file
void delete_record(std::string ID, std::vector<student> &students, std::string filename) {
    student temp;
    for(int i = 0; i < students.size(); i++) {
        if(ID == students[i].StudentID) {
            temp.FirstName = students[i].FirstName;
            temp.Surname = students[i].Surname;
            students.erase(students.begin() + i);
            std::cout << "Successfully deleted " << temp.Surname << ", " <<
            temp.FirstName << "'s record.\n";
        }
    }
    save_exit(filename, students);
}

//opens a text file
bool open_existing_file(std::string filename, std::vector<student> &students) {
    bool flag = false;
    std::string temp_string = filename;
    students.clear();
    student temp;
    filename.append(".txt");
    std::ifstream file(filename);
    if(file.is_open() && !is_empty(file)) {//check if the file is not empty
        flag = true;
        show(temp_string);
        while(!file.eof()) {
            std::getline(file, temp.StudentID, '\t');
            std::getline(file, temp.Surname, '\t');
            std::getline(file, temp.FirstName, '\t');
            std::getline(file, temp.BirthDate, '\t');
            std::getline(file, temp.Sex, '\n');
            students.push_back(temp);
        }
        file.close();
    }
    else if(file.is_open() && is_empty(file)) { // check if the files is empty
        flag = true;
        students.clear();
        std::cout << "No data currently.\n";
    }
    else {
        system("cls");
        std::cout << "File not found.\n";
    }
    return flag;
}

//creates a new text file
void create_new_file(std::string filename) {
    filename.append(".txt");
    std::ofstream file(filename);
    if(file.is_open()) {
        std::cout << "Successfully created a new file called " << filename << ".\n";
    }
    file.close();
}

int main() {
    system("CLS");
    int answer1;
    int answer2;
    std::string ID;
    std::string filename;
    std::vector<student> students;
    do {
        std::cout << "[1] Create New File [2] Open an Existing File [3] Exit\n";
        std::cout << "Answer: ";
        std::cin >> answer1;
        switch(answer1) {
        case 1:
            system("cls");
            std::cout << "Enter filename to create: ";
            std::cin >> filename;
            create_new_file(filename);
            break;
        case 2:
            std::cout << "Enter filename to open: ";
            std::cin >> filename;
            if(open_existing_file(filename, students)== true) {
                do {
                    std::cout << "\n[1] Add [2] Edit [3] Delete [4] Save and Exit [5] Exit Without Saving\n";
                    std::cout << "Answer: ";
                    std::cin >> answer2;
                    switch(answer2) {
                    case 1:
                        system("cls");
                        add_student(students);
                        break;

                    case 2:
                        std::cout << "Enter ID of the student you want to edit: ";
                        std::cin >> ID;
                        edit_record(ID,students, filename);
                        break;

                    case 3:
                        std::cout << "Enter ID of the student you want to delete: ";
                        std::cin >> ID;
                        delete_record(ID, students, filename);
                        break;

                    case 4:
                        save_exit(filename, students);
                        break;

                    case 5:
                        exit(0);
                        break;

                    default:
                        system("CLS");
                        std::cout << "Invalid Option";
                        break;
                    }
                } while(answer2 != 4 || answer2 != 5);
            break;
        }
        break;
        case 3:
            exit(0);
            break;
        default:
            system("CLS");
            std::cout << "Invalid Option!\n";
            break;
        }
    }while(answer1 != 3);

    return 0;
}
