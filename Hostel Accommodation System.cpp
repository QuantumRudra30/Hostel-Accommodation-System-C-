#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>

using namespace std;

class Hostel
{
private:
    string Name;
    int Rent, Bed;

public:
    Hostel(string name, int rent, int bed)
    {
        Name = name;
        Rent = rent;
        Bed = bed;
    }

    string getName()
    {
        return Name;
    }

    int getRent()
    {
        return Rent;
    }

    int getBed()
    {
        return Bed;
    }

    void reserve()   // corrected function name + return type
    {
        ifstream in("D:/Hostel.txt");
        ofstream out("D:/HostelTemp.txt");

        string line;
        while (getline(in, line))
        {
            int pos = line.find(Name);
            if (pos != string::npos)
            {
                Bed--;

                stringstream ss;
                ss << Bed;
                string strBed = ss.str();

                int bedPos = line.find_last_of(':');
                line.replace(bedPos + 1, string::npos, " " + strBed);
            }
            out << line << endl;
        }

        in.close();
        out.close();

        remove("D:/Hostel.txt");
        rename("D:/HostelTemp.txt", "D:/Hostel.txt");

        cout << "\tBed Reserved Successfully!" << endl;
    }
};

class Student
{
private:
    string Name, RollNo, Address;

public:
    Student()
    {
        Name = "";
        RollNo = "";
        Address = "";
    }

    void setName(string name)
    {
        Name = name;
    }

    void setRollNo(string rollNo)
    {
        RollNo = rollNo;
    }

    void setAddress(string address)
    {
        Address = address;
    }

    string getName()
    {
        return Name;
    }

    string getRollNo()
    {
        return RollNo;
    }

    string getAddress()
    {
        return Address;
    }
};

int main()
{
    Hostel h("3star", 5000, 2);

    ofstream out("D:/Hostel.txt");
    out << "\t" << h.getName() << " : " << h.getRent() << " : " << h.getBed() << endl << endl;
    out.close();

    cout << "Hostel Data Saved" << endl;

    Student s;
    bool exit = false;

    while (!exit)
    {
        system("cls");

        int val;
        cout << "\tWelcome To Hostel Accommodation System" << endl;
        cout << "\t*******************" << endl;
        cout << "\t1. Reserve A Bed" << endl;
        cout << "\t2. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1)
        {
            system("cls");

            string name, rollNo, address;

            cout << "\tEnter Name of Student: ";
            cin >> name;
            s.setName(name);

            cout << "\tEnter Roll No: ";
            cin >> rollNo;
            s.setRollNo(rollNo);

            cout << "\tEnter Address: ";
            cin >> address;
            s.setAddress(address);

            if (h.getBed() > 0)
            {
                h.reserve();
            }
            else
            {
                cout << "\tSorry, Bed Not Available!" << endl;
            }

            ofstream outFile("D:/Student.txt", ios::app);
            outFile << "\t" << s.getName() << " : " << s.getRollNo()
                    << " : " << s.getAddress() << endl << endl;
            outFile.close();

            Sleep(5000);
        }
        else if (val == 2)
        {
            exit = true;
            system("cls");
            cout << "Good Luck!" << endl;
            Sleep(3000);
        }
    }
    return 0;
}
