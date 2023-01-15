/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class node
{
    public:
    node* next;
    int idNumber, firstDay;
    double salary;
    int phoneNumber, workHours;
    string empName;
    string address;
};

//This is needed to use it at all method
node* head = NULL;

//-----------------------------------------------------------------CHECK METHOD
bool checkRecord (int idNumber)
{
    node* temp = head;
    //if the head equal to NULL this meaning that the the list is empty and no records
    if (temp == NULL)
    //false meaning this record is not exist in the list
        return false;
    //while the list in not empty and have records 
    while (temp != NULL) 
    {
    //check the ID number 
        if (temp->idNumber == idNumber)
    //if it's exist return true, meaning yes this record is exist in the list 
            return true;
    //otherwise, keep traversing
        temp = temp->next;
    }
    return false;
}

//-----------------------------------------------------------------INSERT METHOD
void createRecord(int idNumber, string empName, int phoneNumber,
    string address, int firstDay, double salary, int workHours)
{
    //based on the return value from checRecord method, if it's true this meaning the record is already exist 
    if (checkRecord(idNumber))
    {
        cout<< "This emplyee is already exist in the records!" << endl;
        return;
    }
    //otherwise, meaning the record with this ID number doesn't exist and it's allow to insert it
    node* newRecord = new node();
    newRecord->next = NULL;
    newRecord->idNumber = idNumber;
    newRecord->empName = empName;
    newRecord->phoneNumber = phoneNumber;
    newRecord->address = address;
    newRecord->firstDay = firstDay;
    newRecord->salary = salary;
    newRecord->workHours = workHours;
    //SORTED INSERTING PROCESS
    //When the list is empty or we want to insert id equal or smaller than the id exist already
    if (head == NULL || head->idNumber >= newRecord->idNumber)
    {
        newRecord->next = head;
        head = newRecord;
        cout << "Employee Record Is Inserted Successfuly ..\n" << endl;
        cout << "----------------------------------------------\n";
        return;
    }
    //inserting the node record in the middle or the end of the list 
    else
    {
        node* current = head;
        while (current->next != NULL && current->next->idNumber < newRecord->idNumber)
        {
        //while the list is NOT empty and the new exist id is smaller than the new one
        //keep traversing
            current = current->next;
        }
        //locate the new record after the above condition is broken
        newRecord->next = current->next;
        current->next = newRecord;
        cout << "Employee Record Is Inserted Successfuly ..\n" << endl;
        cout << "----------------------------------------------\n";
    }

}

//-----------------------------------------------------------------SEARCH METHOD
void searchRecord(int idNumber)
{
    node* record = head;
    //printing message to inform user that the record is not found
    if (record == NULL || record->idNumber != idNumber)
        cout << "Record NOT found !!" << endl;
    //while the head is not equal to NULL meaning there is a records to search 
    while (record != NULL)
    {
        //if the ID number is match, so we found the record
        if (record->idNumber == idNumber)
        {
            cout << "Record is FOUND ... " << endl;
            //printing record's informations 
            cout << "Employee ID Number : " << record->idNumber << endl;
            cout << "Employee Name : " << record->empName << endl;
            cout << "Employee Phone Number : " << record->phoneNumber << endl;
            cout << "Employee Address : " << record->address << endl;
            cout << "Employee First Work Day : " << record->firstDay << endl;
            cout << "Emplyee Salary : " << record->salary << endl;
            cout << "Employee Work Hours : " << record->workHours << endl;
        }
        //if the ID number is not match, keep traversing
        record = record->next;
    }
}

//----------------------------------------------------------------DELETE METHOD 
int deleteRecord(int idNumber)
{
    node* record2del;
    node* temp = head;
    //if the we found the record to delete at the beginning 
    if (temp != NULL && temp->idNumber == idNumber)
    {
        //head will point to the next of the temp
        head = temp->next;
        //delete temp from memory
        free(temp);
        cout << "Employee Record Is Deleted Successfuly ..\n" << endl;
        cout << "----------------------------------------------\n";
        return 0;
    }
    //if the record to delete is in the middle or in the end
    while (temp->next != NULL)
    {
        if (temp->next->idNumber == idNumber)
        {
            record2del = temp->next;
            temp->next = temp->next->next;
            free(record2del);
            cout << "Employee Record Is Deleted Successfuly ..\n" << endl;
            cout << "----------------------------------------------\n";
            return 0;
        }
        temp = temp->next;
    }
    //otherwise, ID number to delete is not found
        cout << "ID number to delete is not found" << endl;
        return -1;
}

//----------------------------------------------------------------DISPLAY METHOD 
void showRecord()
{
    node* record = head;
    //if the record equal to NULL meaning that the list is empty 
    if (record == NULL)
        cout << "NO records is found" << endl;
    //otherwise, meaning that the list have records
    while (record != NULL)
    {
        cout << "Employee ID Number : " << record->idNumber << endl;
        cout << "Employee Name : " << record->empName << endl;
        cout << "Employee Phone Number : " << record->phoneNumber << endl;
        cout << "Employee Address : " << record->address << endl;
        cout << "Employee First Work Day : " << record->firstDay << endl;
        cout << "Emplyee Salary : " << record->salary << endl;
        cout << "Employee Work Hours : " << record->workHours << "\n" << endl;
        record = record->next;
    }
}

//----------------------------------------------------------SALARY UPDATE METHOD 
int updateSalary(int idNumber)
{
    node* record = head;
    //while the list have records and not empty
    while (record != NULL)
    {
        // check if there is match on idNumber
        if (record->idNumber==idNumber) 
        {
            //check the working hours, if it's less than 32 hours CANT update the salary
            if (record->workHours <= 32)
            {
                cout<<"Sorry CANT update salary for this employee\n"
                <<"Because the working hours are less than or equal 32 hours..\n"
                <<"So the salary is still : ";
                return record->salary;
            }
            //otherwise, meaning it's more that 32 hours, so do calculations
            else 
            {
                double salary, overTime, newSalary;
                int workHours;
                workHours = record->workHours - 32;
                overTime = workHours* (record->salary * 0.02);
                newSalary = record->salary + overTime;
                cout<<"Salary is updated Successfuly..\n";
                cout << "The new salary is : ";
                record->salary=newSalary;
                return newSalary;
            }
        }
        //Keep traversing until find the matchs ID
        record = record->next;
        //otherwise, meaning no matchs
        if (record->idNumber != idNumber)
        {
            cout<<"There is NO employee record for this ID !!"<<endl;
            return -1;
        }
    }
    return -1;
}

//--------------------------------------------------------------------------MAIN
int main()
{
    int idNumber, firstDay, salary, idNumber2del;
    int phoneNumber, workHours, choice = 1;
    string empName;
    string address;

    cout << "\n---------EMPLOYEE RECORD MANAGEMENT SYSTEM---------" << endl;
    //while the user choice is not equal to 6, beacuse 6 meaning Exit
    while (choice != 6)
    {
        //keep printing the options list 
        cout << "\n*********OPTIONS LIST*********\n" << endl;
        cout << "Please Choose Your Option : " << endl;
        cout << "1. Insert Employee Record \n2. Delete Employee Record \n"
            << "3. Show Employee Record \n4. Search Employee Record\n"
            << "5. Update Salary \n6. Exit \nYour choice : ";
        cin >> choice;
        
        //if the user choose 1 meaning he want to insert new record
        if (choice == 1)
        {
            cout << "Enter the ID of employee : ";
            cin >> idNumber;
            // calling checkRecord method to check the id number if it's exsit or not
            if (checkRecord(idNumber) == false) 
            {
                //if the method return false meaning the id number is not exsit
                //so keep taking the rest of information from user 
                cout<< "Enter the name of employee : ";
                cin>> empName;
                cout<< "Enter the phone number of the employee : ";
                cin>> phoneNumber;
                cout<< "Enter the address of the employee : ";
                cin>> address;
                cout<< "Enter the first day of the work : ";
                cin>> firstDay;
                cout<< "Enter the salary : ";
                cin>> salary;
                cout<< "Enter the work hours : ";
                cin>> workHours;
                createRecord(idNumber, empName, phoneNumber, address,
                    firstDay, salary, workHours);
            }
            //otherwise meaning the method returnd true so the id number is already exsist
            else 
            {
                cout<<"This emplyee is already exist in the records!\n";
            }
        }
        
        //if the user choose 2 meaning he want to delete a record
        if (choice == 2)
        {
            cout<< "Enter the ID of employee you want to delete : ";
            cin>> idNumber2del;
            deleteRecord(idNumber2del);
        }
        
        //if the user choose 3 meaning he want to display all records
        if (choice == 3)
        {
            showRecord();
        }
        
        //if the user choose 4 meaning he want to search for specfic record
        if (choice == 4)
        {
            cout<< "Enter the ID of employee you want to search : ";
            cin>> idNumber;
            searchRecord(idNumber);
        }
        
        //if the user choose 5 meaning he want to update the salary for specfic record
        if (choice == 5)
        {
            cout<<"Enter the ID of employee you want to update salary for : ";
            cin>>idNumber;
            cout<<updateSalary(idNumber)<<"\n";
        }
        
        //if the user choose 6 meaning he want to exist the program 
        if (choice == 6)
        {
            cout << "\nTHANK YOU, GOOD BYE !!";
            exit(0);
        }
        
        //otherwise, meaning the user choose wrong choice 
        if (choice != 1 && choice !=2 && choice != 3 && choice != 4 &&
            choice != 5 && choice != 6 )
            cout<<"WRONG CHOICE, TRY AGAIN !!"<<endl;
    }
    return 0;
}



