//LibraryManage categories by https://destiny.pcsb.org/
//Got help for my file code from the File handling-MO PowerPoint
//Case Switch based on https://www.youtube.com/watch?v=wS7kpyw6Nkc
//How to remove content from the file https://stackoverflow.com/questions/48085781/what-is-the-difference-among-iosapp-out-and-trunc-in-c & https://www.sololearn.com/en/Discuss/275877/clear-data-inside-text-file-in-c
#include <iostream>  // Included Library
#include <fstream>  // File Library


using namespace std;

class LibraryManage {
    int id; //Defining id as an integer
    char author[100]; //Defining author as a character value
    char title[100];  //Defining title as a character value
    char gradelevel[100]; //Defining gradelevel as a character value
    double price; //Defining price as a double integer value
    int pages;  //Defining pages as an integer
    int quantity; //Defining quantity as an integer

public:
    //Allows users to input book details
    void libraryInput() {
        cout << "Enter Book ID" << endl;
        cin >> id;
        cout << "Enter Book Author" << endl;
        cin.ignore();
        cin.getline(author, 100); //Allows for spaces in input
        cout << "Enter Book Title" << endl;
        cin.getline(title, 100); //Allows for spaces in input
        cout << "Enter Book Grade Level" << endl;
        cin >> gradelevel;
        cout << "Enter Book Price" << endl;
        cin >> price;
        cout << "Enter Book Pages" << endl;
        cin >> pages;
        cout << "Enter Book Quantity" << endl;
        cin >> quantity;
    }

    void displayDetails() {
        //Code for displaying details the user previously inputted
        cout << "Book ID: " << id << endl;
        cout << "Book Author: " << author << endl;
        cout << "Book Title: " << title << endl;
        cout << "Book Grade Level: " << gradelevel << endl;
        cout << "Book Price: " << price << endl;
        cout << "Book Pages: " << pages << endl;
        cout << "Book Quantity: " << quantity << endl;
    }

    void writetoFile(ofstream &file) { //Writing the book details from user into a file
        file << id << "," << author << "," << title << "," << gradelevel << "," << price << "," << pages << "," << quantity << endl;

    }

    void readFromFile(ifstream &file) { //Read book details from file
        file >> id;
        file.ignore(); //separates different line of data
        file.getline(author, 100, ','); //Read data until comma in file
        file.getline(title, 100, ',');
        file.getline(gradelevel, 100, ',');
        file >> price;
        file.ignore();
        file >> pages;
        file.ignore();
        file >> quantity;
    }
};

int main() {
    LibraryManage lib[20]; //Array to store objects
    int input = 0; //Keep user input
    int count = 0; //Keep count of number of books

    ifstream inFile("librarymanage3_data.txt"); //Opens file and allows reading
//Reading the data
    if (inFile.is_open()) {
        while (!inFile.eof() && count < 20) { //If both things are true, loop continues
            lib[count].readFromFile(inFile); //Reading book details
            count++; //Count of books
        }
        inFile.close();
    }
//Allows user to choose any of the 6 options in the menu
    while (input != 6) {
        cout << "Enter 1 to input details" << endl;
        cout << "Enter 2 to display details" << endl;
        cout << "Enter 3 to save details" << endl;
        cout << "Enter 4 to clear history" << endl;
        cout << "Enter 5 to view past details" <<endl;
        cout << "Enter 6 to quit" << endl;
        cin >> input;

        switch (input) {
            case 1: //Input details
                if (count < 20) {
                    lib[count].libraryInput(); //Inputting data for each book
                    count++; //Count of books
                } else {
                    cout << "Library is full" << endl; //Error is given if over 20
                }
                break;
            case 2: //Display Details
                for (int i = 0; i < count; i++) {
                    lib[i].displayDetails();
                }
                break;
            case 3: { //Save details
                ofstream outFile("librarymanage3_data.txt");
                if (!outFile.is_open()) {
                    cerr << "Error" << endl; //Error given when file can't be saved and returns 1
                    return 1;
                }
                for (int i = 0; i < count; i++) {
                    lib[i].writetoFile(outFile); //Writing data for each book
                }
                outFile.close(); //Close file
                cout << "Details saved" << endl; //Given when file is successfully saved
                break;
            }
            case 4: { //Clear file history
                ofstream outFile("librarymanage3_data.txt", ios::trunc);
                outFile.close();
                cout << "File cleared" << endl; //Given when file is successfully cleared
                count = 0; //Clearing count
                for (int i = 0; i < 20; ++i) {
                    lib[i] = LibraryManage(); //Reinitializing object
                }
            }
                break;
            case 5: { // View past data
                ifstream inFile("librarymanage3_data.txt"); //Input file for reading
                if (inFile.is_open()) {
                    for (int i = 0; i < count; ++i) {
                        lib[i].readFromFile(inFile); //Read book details from file
                        lib[i].displayDetails(); //Display book details
                    }
                    inFile.close(); //close file
                } else {
                    cerr << "Can't open file!" << endl; // Error given when file can't be open
                }
                break;
            }
            case 6: //Quit and exit
                cout << "Exited" << endl; //Given when code is successfully exited
                break;
            default:
                cout << "Invalid. Try Again" << endl; //Given when an invalid entry is given by user

        }
    }
    return 0;
}
