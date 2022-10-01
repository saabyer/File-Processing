#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int maxrow = 10;

string studentID[maxrow] = {};
string surName[maxrow] = {};
string firstName[maxrow] = {};
string birthDate[maxrow] = {};
string sex[maxrow] = {};

void Add()
{
    char studentID2[50];
    char surName2[20];
    char firstName2[20];
    char birthDate2[50];
    char sex2[5];

    cin.ignore();
    system("CLS");

    //student input
    cout<<"Student ID: ";
    cin.getline(studentID2, 50);
    cout<<"Student's Last Name: ";
    cin.getline(surName2, 20);
    cout<<"Student's First Name: ";
    cin.getline(firstName2, 20);
    cout<<"Student's Birth Date: ";
    cin.getline(birthDate2, 50);
    cout<<"[M]ale | [F]emale: ";
    cin.getline(sex2, 5);

    for(int x=0; x < maxrow; x++)
    {
        if(studentID[x] == "\0")
        {
            studentID[x] = studentID2;
            surName[x] = surName2;
            firstName[x] = firstName2;
            birthDate[x] = birthDate2;
            sex[x] = sex2;

            break;
        }
    }
}

void Update(string search)
{
    char studentID2[50];
    char surName2[20];
    char firstName2[20];
    char birthDate2[50];
    char sex2[5];

    int counter = 0;

    for(int x=0; x < maxrow; x++)
    {
       if(studentID[x] == search)
       {
            counter++;

            cout<<"Student ID: ";
            cin.getline(studentID2, 50);
            cout<<"Student's Last Name: ";
            cin.getline(surName2, 20);
            cout<<"Student's First Name: ";
            cin.getline(firstName2, 20);
            cout<<"Student's Birth Date: ";
            cin.getline(birthDate2, 50);
            cout<<"[M]ale | [F]emale: ";
            cin.getline(sex2, 5);

            studentID[x] = studentID2;
            surName[x] = surName2;
            firstName[x] = firstName2;
            birthDate[x] = birthDate2;
            sex[x] = sex2;

            cout<<"Update Successful."<<endl;

            break;
       }
    }

    if(counter == 0)
    {
        cout<<"ID Not Found, Please Try Again."<<endl;
    }
}

void Delete(string search)
{
    int counter = 0;
    for(int x=0; x < maxrow; x++)
    {
        if(studentID[x] == search)
        {
            counter ++;

            studentID[x] = "";
            surName[x] = "";
            firstName[x] = "";
            birthDate[x] = "";
            sex[x] = "";

            cout<<"Successfully Deleted."<<endl;
            break;
        }
    }

    if(counter == 0)
    {
        cout<<"ID Not Found, Please Try Again."<<endl;
    }
}

void Search(string search)
{
    system("CLS");
    cout<<"[CURRENT LIST]"<<endl;
    //cout<<" No. |     ID     | Last Name | First Name | Birth Date | Sex "<<endl;
    cout<<"=============================================================="<<endl;

    int counter = 0;
    for(int x=0; x < maxrow; x++)
    {
        if(studentID[x] == search)
        {
            counter++;
            cout<<" | "<<counter<<" | "<<studentID[x]<<" | "<<surName[x]<<" | "<<firstName[x]<<" | "<<birthDate[x]<<" | "<<sex[x]<<endl;
            break;
        }
    }

    if(counter == 0)
    {
        cout<<"ID Not Found, Please Try Again."<<endl;
    }

    cout<<"=============================================================="<<endl;
}

void Show()
{
    system("CLS");
    cout<<"[CURRENT LIST]"<<endl;

    int counter = 0;
    cout<<"=============================================================="<<endl;
    cout<<" No. |     ID     | Last Name | First Name | Birth Date | Sex "<<endl;
    cout<<"--------------------------------------------------------------"<<endl;

    for(int x=0; x < maxrow; x++)
    {
        if(studentID[x] != "\0")
        {
            counter++;
            cout<<" | "<<counter<<" | "<<studentID[x]<<" | "<<surName[x]<<" | "<<firstName[x]<<" | "<<birthDate[x]<<" | "<<sex[x]<<endl;
        }
    }
    cout<<"=============================================================="<<endl;

}

void OpenFile()
{
    string line;
    ifstream myfile("Sample.txt");
    if(myfile.is_open())
    {
        int x = 0;
        while(getline(myfile, line))
        {
            int l = line.length();
            studentID[x] = line.substr(0, 3);
            surName[x] = line.substr(4, 1 - 4);
            firstName[x] = line.substr(5, 1 - 5);
            birthDate[x] = line.substr(6, 1 - 6);
            sex[x] = line.substr(7, 1 - 7);
            x++;
        }
    }else{
        cout<<"Enable to open the file."<<endl;
    }
}

void SaveToFile()
{
    ofstream myfile;
    myfile.open("Sample.txt");

    myfile<<"========================================================"<<endl;
    myfile<<"     ID     | Last Name | First Name | Birth Date | Sex "<<endl;
    myfile<<"--------------------------------------------------------"<<endl;
    for(int x=0; x < maxrow; x++)
    {
        if(studentID[x] == "\0")
        {
            break;
        }else{
            myfile<<studentID[x]<<" | "<<surName[x]<<" | "<<firstName[x]<<" | "<<birthDate[x]<<" | "<<sex[x]<<endl;
        }
    }
    myfile<<"========================================================"<<endl;

}

int main()
{
    std::cout<<"MENU\n";
    int option;
    string studentID;

    system("CLS");

    do{
        cout<<"[1] ADD"<<endl;
        cout<<"[2] UPDATE"<<endl;
        cout<<"[3] DELETE"<<endl;
        cout<<"[4] SEARCH"<<endl;
        cout<<"[5] SHOW CONTENT"<<endl;
        cout<<"[6] SAVE & EXIT"<<endl;
        cout<<" "<<endl;
        cout<<"[0] CLEAR"<<endl;
        cout<<"==================="<<endl;

        cout<<"Choose Option: ";
        cin>>option;

        switch(option)
        {
        case 0:
            system("CLS");
            break;

        case 1: Add();
            system("CLS");
            break;

        case 2:
            cin.ignore();
            cout<<"Search ID: ";
            getline(cin, studentID);
            Update(studentID);
            break;

        case 3:
            cin.ignore();
            cout<<"Delete Student Profile(By ID): ";
            getline(cin, studentID);
            Delete(studentID);
            break;

        case 4:
            cin.ignore();
            system("CLS");
            cout<<"Search ID: ";
            getline(cin, studentID);
            Search(studentID);
            break;

        case 5: Show();
            break;

       case 6:
            SaveToFile();
            cout<<" "<<endl;
            cout<<"File Saved, Please Open The File Through File Explorer or any File Manager."<<endl;
            cout<<" "<<endl;
            break;

        default:
            cout<<"Invalid Output"<<endl;
        }
    }while(option != 6);

    return 0;
}
