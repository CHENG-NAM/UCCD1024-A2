#include <iostream>
#include <fstream> // read or write the text file

#include "Student.h"


using namespace std;


Student::Student()
{
	strcpy_s(name, " ");
	id = 0;
	strcpy_s(address, " ");
	strcpy_s(DOB, " ");
	strcpy_s(course, " ");
	strcpy_s(phone_no, " ");
	cgpa = 0.0;

}


void Student::print(ostream &out)
{
	out << "\nName: " << name;
	out << "\nID: " << id;
	out << "\nAddress: " << address;
	out << "\nDate of Birth: " << DOB;
	out << "\nPhone No: " << phone_no;
	out << "\nCourse: " << course;
	out << "\nCGPA: " << cgpa;
	out << "\n";

}


bool Student::compare1(Student p2)
{
	if (id > p2.id)
		return true;
	return false;

}


bool Student::compare2(Student p2)
{
	if (id == p2.id)
		return true;
	return false;
}



bool Student::compare3(int id2)
{
	if (id == id2)
		return true;
	return false;
}

// read in the text file
void Student::printstudent()
{
	ofstream outputfile("student-info.txt", ios::app);

	if (!outputfile.is_open())
	{
		cout << "Unable open text file" << endl;
		return;
	}

	outputfile << "\nName: " << name;
	outputfile << "\nID: " << id;
	outputfile << "\nAddress: " << address;
	outputfile << "\nDate of Birth: " << DOB;
	outputfile << "\nPhone No: " << phone_no;
	outputfile << "\nCourse: " << course;
	outputfile << "\nCGPA: " << cgpa;
	outputfile << "\n";

	outputfile.close();
}