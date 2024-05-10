#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

#include	<cctype>
#include	<string>
#include	<iomanip>
using namespace std;

bool readFile(const char *, BST *);
int menu();

bool isNumeric(const string& ); // Function to check the input is valid or not.

int main() {

	// Variables definition
	BST t1;
	int choice = 0;
	int order = 0;
	int source = 0;
	bool done_inserted = false;

	do {
		system("cls");
		menu();
		cout << endl;
		cout << "Please key in the option -->  ";
		while (!(cin >> choice) || choice < 1 || choice > 7) {
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid option. Please enter an integer between 1 and 7 --> ";
		}

		switch (choice)
		{
		case 1:
			if (!done_inserted)
			{
				if (readFile("student.txt", &t1))
				{
					done_inserted = true;
					cout << "\nRead data to BST successfully !\n" << endl;
				}
				else
				{
					cout << "Failed to read data to BST" << endl;
				}
			}
			else
			{
				cout << "\nYou already inserted once\n" << endl;
			}
			system("pause");
			break;

		case 2:
			if (!t1.deepestNodes())
			{
				cout << endl;
				cout << "Failed to access to the deepest nodes." << endl;
				cout << endl;
			}
			system("pause");
			break;

		case 3:
		{
			bool validSource = false, validOrder = false;
			string sourceInput, orderInput;
			while (!validSource || !validOrder) {
				system("cls");

				// check the source is valid or not
				if (!validSource) {
					cout << "**************************" << endl;
					cout << "*          Source        *" << endl;
					cout << "**************************" << endl;
					cout << "* 1. Display on screen   *" << endl;
					cout << "* 2. Write to text file  *" << endl;
					cout << "**************************" << endl;
					cout << endl;
					cout << "Please enter the source --> ";
					cin >> sourceInput;

					if (isNumeric(sourceInput)) {
						int tempSource = atoi(sourceInput.c_str());
						if (tempSource == 1 || tempSource == 2) {		// Source = 1 to print to screen / source = 2 to print to a file name “student-info.txt”
							source = tempSource;
							validSource = true;
						}
						else{
							cout << "\nInvalid source. Please select either 1 or 2." << endl;
							system("pause");
						}
					}
					else {
						cout << "\nInvalid input. It must be a numeric value." << endl;
						system("pause");
					}
				}

				// check the order is valid or not
				if (validSource && !validOrder) {
					cout << endl;
					cout << "**************************" << endl;
					cout << "*          Order         *" << endl;
					cout << "**************************" << endl;
					cout << "* 1. Ascending           *" << endl;
					cout << "* 2. Descending          *" << endl;
					cout << "**************************" << endl;
					cout << endl;
					cout << "Please enter the order --> ";
					cin >> orderInput;

					if (isNumeric(orderInput)) {
						int tempOrder = atoi(orderInput.c_str());
						if (tempOrder == 1 || tempOrder == 2) {		// Order = 1 for ascending and order = 2 for descending
							order = tempOrder;
							validOrder = true;
						}
						else {
							cout << "\n Invalid Input. Please select either 1 or 2." << endl;
							system("pause");
						}
					}
					else {
						cout << "\n Invalid Input. It must be a numeric value" << endl;
						system("pause");
					}
				}
			}

			t1.display(source, order);
			system("pause");
			break;
		}
		case 4: 
		{
			Student s1;
			BST t2;
			bool valid_ID = false;
			string input;
			while (!valid_ID) {
				cout << "\nPlease key in the student id --> ";
				cin >> input;

				// Perform input validation on the string
				if (isNumeric(input)) {  // You need to implement isNumeric() function
					s1.id = stoi(input);  // Convert the string to an integer
					valid_ID = true;    // Input is valid, exit the loop
				}
				else 
					cout << "Invalid input. Please enter a valid student id." << endl;
			}

			if (t2.CloneSubtree(t1, s1)) {
				cout << "\nBST T1:" << endl;
				cout << "==========" << endl;
				t1.preOrderPrint();
				cout << "\nBST T2:" << endl;
				cout << "==========" << endl;
				t2.preOrderPrint();
			}
		}
			cout << endl;
			system("pause");
			break;

		case 5:
			t1.printLevelNodes();
			system("pause");
			break;

		case 6:
			t1.printPath();
			cout << endl;
			system("pause");
			break;

		case 7:
			cout << "\nThank you for using this program :) \n" << endl;
			break;

		default:
			cout << "Wrong option!" << endl;
		}
	} while (choice != 7);

	system("pause");
	return 0;
}


// Functions definition

bool readFile(const char* filename, BST* t1)
{
	ifstream infile(filename);
	Student student;
	char s[256];
	int i = 0;

	if (!infile.is_open())
	{
		cout << "Unable to open text file" << endl;
		return false;
	}

	// Modify the loop condition
	while (infile >> s)  // Starting the reading here
	{
		for (i = 1; i < 3; i++) // Adjusted loop count since we've already read the first string
		{
			infile >> s;
		}
		infile >> student.id;

		for (i = 0; i < 2; i++)
		{
			infile >> s;
		}
		infile >> student.name;
		infile.getline(s, 256);
		strcat_s(student.name, s);

		for (i = 0; i < 2; i++)
		{
			infile >> s;
		}
		infile >> student.address;
		infile.getline(s, 256);
		strcat_s(student.address, s);

		for (i = 0; i < 2; i++)
		{
			infile >> s;
		}
		infile >> student.DOB;

		for (i = 0; i < 3; i++)
		{
			infile >> s;
		}
		infile >> student.phone_no;

		for (i = 0; i < 2; i++)
		{
			infile >> s;
		}
		infile >> student.course;

		for (i = 0; i < 2; i++)
		{
			infile >> s;
		}
		infile >> student.cgpa;

		if (t1->empty())
		{
			if (t1->insert(student))
				cout << "Student ID:" << setw(6) << left << student.id << " Status: Inserted Success." << endl;
		}
		else
		{
			if (!t1->duplicateInsert(t1->root, student.id))
			{
				if (t1->insert(student))  // Check the insertion result for non-empty BST as well
					cout << "Student ID:" << setw(6) << left << student.id << " Status: Inserted Success." << endl;
			}
		}
	}

	cout << "There are " << t1->size() << " students recorded! " << endl;
	return true;
}

bool isNumeric(const string& str) {
	for (char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

int menu()
{

	cout << "\t\t\tMenu" << endl;
	cout << "    ____________________________________________" << endl;
	cout << "   /     |                                      \\" << endl;
	cout << "   | [1] | Read Data to BST                     |" << endl;
	cout << "   |-----|------------------------------------- |" << endl;
	cout << "   | [2] | Print Deepest Nodes                  |" << endl;
	cout << "   |-----|------------------------------------- |" << endl;
	cout << "   | [3] | Display Student                      |" << endl;
	cout << "   |-----|------------------------------------- |" << endl;
	cout << "   | [4] | Clone Subtree                        |" << endl;
	cout << "   |-----|------------------------------------- |" << endl;
	cout << "   | [5] | Print Level Nodes                    |" << endl;
	cout << "   |-----|------------------------------------- |" << endl;
	cout << "   | [6] | Print Path                           |" << endl;
	cout << "   |-----|------------------------------------- |" << endl;
	cout << "   | [7] | Exit                                 |" << endl;
	cout << "   \\____________________________________________/" << endl;

	return 0;
}