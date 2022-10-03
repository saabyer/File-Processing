/***FOR THE SAKE OF SIMPLICITY, THIS CODE HAS BEEN
    CONSTRAINT TO WORK ONLY WITH VALID INPUTS
    PLEASE AVOID USING INVALID INPUTS. THANK YOU***/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

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

//saves the data you want to add to the text file and exits the program
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
        //exit(0);
    }
    else {
        std::cout << "File not found.\n";
    }
}

//adds a student to the list of students
void add_student(std::string filename, std::vector<student> &students) {
    student temp;       //temporarily stores the data in this variable

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

    students.push_back(temp); //pushes temp to the vector
    save_exit(filename, students);
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

//deletes all the data of a specific student in the text file
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

/*FOR DEBUGGING PURPOSES ONLY
void print_vector(std::vector<student> &students) {
    for (int i = 0; i < students.size(); i++) {
        std::cout << students[i].StudentID << "\t";
        std::cout << students[i].Surname << "\t";
        std::cout << students[i].FirstName << "\t";
        std::cout << students[i].BirthDate << "\t";
        std::cout << students[i].Sex << "\n";
    }
}*/

//sort by lastname
void sort_by_lastname(std::string sort_by, std::string filename, std::vector<student> &students) {
    student temp;
    std::string temp_name;
    std::string temp_name2;
    if(toupper(sort_by[0]) == 'A') {//sort in ascending order using bubble sort
        for(int i = 0; i < students.size(); i++) {
            for(int j = i+ 1; j < students.size(); j++) {
                temp_name = students[j].Surname;
                temp_name2 = students[i].Surname;
                std::transform(temp_name.begin(),temp_name.end(), temp_name.begin(),::toupper);
                std::transform(temp_name2.begin(),temp_name2.end(), temp_name2.begin(),::toupper);
                if(temp_name < temp_name2) {
                    //std::cout << "Check Ascending" << std::endl; FOR DEBUGGING PURPOSES
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
    }
    else if(toupper(sort_by[0]) == 'D') {//sort in descending order using bubble sort
        for(int i = 0; i < students.size(); i++) {
            for(int j = i+ 1; j < students.size(); j++) {
                temp_name = students[j].Surname;
                temp_name2 = students[i].Surname;
                std::transform(temp_name.begin(),temp_name.end(), temp_name.begin(),::toupper);
                std::transform(temp_name2.begin(),temp_name2.end(), temp_name2.begin(),::toupper);
                if(temp_name > temp_name2) {
                    //std::cout << "Check Descending" << std::endl; FOR DEBUGGING PURPOSES
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
    }
    //print_vector(students);
    save_exit(filename, students);
}

//sort by firstname
void sort_by_firstname(std::string sort_by, std::string filename, std::vector<student> &students) {
    student temp;
    std::string temp_name;
    std::string temp_name2;
    if(toupper(sort_by[0]) == 'A') {//sort in ascending order using bubble sort
        for(int i = 0; i < students.size(); i++) {
            for(int j = i+ 1; j < students.size(); j++) {
                temp_name = students[j].FirstName;
                temp_name2 = students[i].FirstName;
                std::transform(temp_name.begin(),temp_name.end(), temp_name.begin(),::toupper);
                std::transform(temp_name2.begin(),temp_name2.end(), temp_name2.begin(),::toupper);
                if(temp_name < temp_name2) {
                    //std::cout << "Check Ascending" << std::endl; FOR DEBUGGING PURPOSES
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
    }
    else if(toupper(sort_by[0]) == 'D') {//sort in descending order using bubble sort
        for(int i = 0; i < students.size(); i++) {
            for(int j = i+ 1; j < students.size(); j++) {
                temp_name = students[j].FirstName;
                temp_name2 = students[i].FirstName;
                std::transform(temp_name.begin(),temp_name.end(), temp_name.begin(),::toupper);
                std::transform(temp_name2.begin(),temp_name2.end(), temp_name2.begin(),::toupper);
                if(temp_name > temp_name2) {
                    //std::cout << "Check Descending" << std::endl; FOR DEBUGGING PURPOSES
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
    }
    //print_vector(students);
    save_exit(filename, students);
}

//sort by ID
void sort_by_id(std::string sort_by, std::string filename, std::vector<student> &students) {
    student temp;
    std::string temp_name;
    std::string temp_name2;
    if(toupper(sort_by[0]) == 'A') {//sort in ascending order using bubble sort
        for(int i = 0; i < students.size(); i++) {
            for(int j = i+ 1; j < students.size(); j++) {
                temp_name = students[j].StudentID;
                temp_name2 = students[i].StudentID;
                std::transform(temp_name.begin(),temp_name.end(), temp_name.begin(),::toupper);
                std::transform(temp_name2.begin(),temp_name2.end(), temp_name2.begin(),::toupper);
                if(temp_name < temp_name2) {
                    //std::cout << "Check Ascending" << std::endl; FOR DEBUGGING PURPOSES
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
    }
    else if(toupper(sort_by[0]) == 'D') {//sort in descending order using bubble sort
        for(int i = 0; i < students.size(); i++) {
            for(int j = i+ 1; j < students.size(); j++) {
                temp_name = students[j].StudentID;
                temp_name2 = students[i].StudentID;
                std::transform(temp_name.begin(),temp_name.end(), temp_name.begin(),::toupper);
                std::transform(temp_name2.begin(),temp_name2.end(), temp_name2.begin(),::toupper);
                if(temp_name > temp_name2) {
                    //std::cout << "Check Descending" << std::endl; FOR DEBUGGING PURPOSES
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
    }
    //print_vector(students);
    save_exit(filename, students);
}

//sort by birthdate
void sort_by_birthdate(std::string sort_by, std::string filename, std::vector<student> &students) {
    student temp;
    std::string temp_name;
    std::string temp_name2;
    if(toupper(sort_by[0]) == 'A') {//sort in ascending order using bubble sort
        for(int i = 0; i < students.size(); i++) {
            for(int j = i+ 1; j < students.size(); j++) {
                temp_name = students[j].BirthDate;
                temp_name2 = students[i].BirthDate;
                std::transform(temp_name.begin(),temp_name.end(), temp_name.begin(),::toupper);
                std::transform(temp_name2.begin(),temp_name2.end(), temp_name2.begin(),::toupper);
                if(temp_name < temp_name2) {
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                    //std::cout << "Check Ascending" << std::endl; FOR DEBUGGING PURPOSES
                    /*temp.StudentID = students[i].StudentID;
                    temp.Surname = students[i].Surname;
                    temp.FirstName = students[i].FirstName;
                    temp.BirthDate = students[i].BirthDate;
                    temp.Sex = students[i].Sex;

                    students[i].StudentID = students[j].StudentID;
                    students[i].Surname = students[j].Surname;
                    students[i].FirstName = students[j].FirstName;
                    students[i].BirthDate = students[j].BirthDate;
                    students[i].Sex = students[j].Sex;

                    students[j].StudentID = temp.StudentID;
                    students[j].Surname = temp.Surname;
                    students[j].FirstName = temp.FirstName;
                    students[j].BirthDate = temp.BirthDate;
                    students[j].Sex = temp.Sex; */
                }
            }
        }
    }
    else if(toupper(sort_by[0]) == 'D') {//sort in descending order using bubble sort
        for(int i = 0; i < students.size(); i++) {
            for(int j = i+ 1; j < students.size(); j++) {
                temp_name = students[j].BirthDate;
                temp_name2 = students[i].BirthDate;
                std::transform(temp_name.begin(),temp_name.end(), temp_name.begin(),::toupper);
                std::transform(temp_name2.begin(),temp_name2.end(), temp_name2.begin(),::toupper);
                if(temp_name > temp_name2) {
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
    }
    //print_vector(students);
    save_exit(filename, students);
}

//sort by sex
void sort_by_sex(std::string sort_by, std::string filename, std::vector<student> &students) {
    student temp;
    char temp_answer;
    char temp_answer2;
    if(toupper(sort_by[0]) == 'F') {//sorting with females first
        for(int i = 0; i < students.size(); i++) {
            for(int j = i+ 1; j < students.size(); j++) {
                temp_answer = toupper(students[j].Sex[0]);
                temp_answer2 = toupper(students[i].Sex[0]);
                if(temp_answer < temp_answer2) {
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
    }
    else if(toupper(sort_by[0]) == 'M') {//sorting with males first
        for(int i = 0; i < students.size(); i++) {
            for(int j = i+ 1; j < students.size(); j++) {
                temp_answer = toupper(students[j].Sex[0]);
                temp_answer2 = toupper(students[i].Sex[0]);
                if(temp_answer != temp_answer2) { // temp -> j; j -> i; i -> temp
                    temp = students[j];
                    students[j] = students[i];
                    students[i] = temp;
                }
            }
        }
    }
    //print_vector(students);
    save_exit(filename, students);
}

int main() {
    bool flag = false;
    bool flag2 = true;
    system("CLS");
    int answer1;
    int answer2;
    std::string sort_by;
    std::string sort_by2;
    std::string ID;
    std::string filename;
    std::vector<student> students;
    do {
        system("cls");
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
                    std::cout << "\n[1] Add [2] Edit [3] Delete [4] Sort [5] Save [6] Exit Without Saving\n";
                    std::cout << "Answer: ";
                    std::cin >> answer2;
                    switch(answer2) {
                    case 1:
                        system("cls");
                        add_student(filename, students);
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
                        std::cout << "Sort by [S]urname [F]irstname [I]D [B]irthdate Se[X]: ";
                        std::cin >> sort_by;
                        do {
                            if(toupper(sort_by[0])== 'S') {
                                std::cout <<"Sorting Surname in [A]scending or [D]esceding order: ";
                                std::cin >> sort_by2;
                                sort_by_lastname(sort_by2, filename, students);
                                break;

                            }
                            else if(toupper(sort_by[0])== 'F') {
                                std::cout <<"Sorting First Name in [A]scending or [D]esceding order: ";
                                std::cin >> sort_by2;
                                sort_by_firstname(sort_by2, filename, students);
                            }
                            else if (toupper(sort_by[0])== 'I'){
                                std::cout <<"Sorting Student ID in [A]scending or [D]esceding order: ";
                                std::cin >> sort_by2;
                                sort_by_id(sort_by2, filename, students);
                            }
                            else if (toupper(sort_by[0])== 'B'){
                                std::cout <<"Sorting Birth Date in [A]scending or [D]esceding order: ";
                                std::cin >> sort_by2;
                                sort_by_birthdate(sort_by2, filename, students);
                            }
                            else if (toupper(sort_by[0])== 'X'){
                                std::cout <<"Sorting Sex in [M]ale first or [F]emale first: ";
                                std::cin >> sort_by2;
                                sort_by_sex(sort_by2, filename, students);
                            }
                            else {
                                std::cout <<"Invalid Option!\n";
                                flag = true;
                            }
                        }while(flag);
                        break;

                    case 5:
                        save_exit(filename, students);
                        flag = false;
                        break;

                    case 6:
                        exit(0);
                        break;

                    default:
                        system("CLS");
                        std::cout << "Invalid Option";
                        break;
                    }
                } while(flag);
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
