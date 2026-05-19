#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

struct Book {
    int id;
    char title[50];
    char author[50];
    char genre[30];
    char status[20];
};

const string fileName = "library.dat";

// Function Declarations
void addBook();
void searchBook();
void updateBook();
void deleteBook();
void displayAll();
bool isDuplicateID(int);

int main() {
    int choice;

    while (true) {
        cout << "\n====================================";
        cout << "\n     LIBRARY MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Book";
        cout << "\n2. Search Book by ID";
        cout << "\n3. Update Book Information";
        cout << "\n4. Delete Book";
        cout << "\n5. Display All Books";
        cout << "\n6. Exit";
        cout << "\n------------------------------------";
        cout << "\nEnter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addBook();
                break;

            case 2:
                searchBook();
                break;

            case 3:
                updateBook();
                break;

            case 4:
                deleteBook();
                break;

            case 5:
                displayAll();
                break;

            case 6:
                cout << "Exiting Program...\n";
                return 0;

            default:
                cout << "Invalid Choice!\n";
        }
    }

    return 0;
}

// Check Duplicate Book ID
bool isDuplicateID(int id) {
    ifstream inFile(fileName, ios::binary);

    Book b;

    while (inFile.read(reinterpret_cast<char*>(&b), sizeof(Book))) {
        if (b.id == id) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

// Add Book
void addBook() {
    ofstream outFile(fileName, ios::binary | ios::app);

    if (!outFile) {
        cout << "Error opening file!\n";
        return;
    }

    Book b;

    cout << "\nEnter Book ID: ";
    cin >> b.id;

    if (isDuplicateID(b.id)) {
        cout << "Book ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Title: ";
    cin.getline(b.title, 50);

    cout << "Enter Author: ";
    cin.getline(b.author, 50);

    cout << "Enter Genre: ";
    cin.getline(b.genre, 30);

    cout << "Enter Status (Available/Issued): ";
    cin.getline(b.status, 20);

    outFile.write(reinterpret_cast<char*>(&b), sizeof(Book));

    outFile.close();

    cout << "Book record added successfully.\n";
}

// Search Book
void searchBook() {
    ifstream inFile(fileName, ios::binary);

    if (!inFile) {
        cout << "File does not exist!\n";
        return;
    }

    int id;
    bool found = false;
    Book b;

    cout << "\nEnter Book ID to search: ";
    cin >> id;

    while (inFile.read(reinterpret_cast<char*>(&b), sizeof(Book))) {
        if (b.id == id) {
            cout << "\n========== BOOK FOUND ==========\n";
            cout << "Book ID : " << b.id << endl;
            cout << "Title   : " << b.title << endl;
            cout << "Author  : " << b.author << endl;
            cout << "Genre   : " << b.genre << endl;
            cout << "Status  : " << b.status << endl;

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book with ID " << id << " not found.\n";
    }

    inFile.close();
}

// Update Book
void updateBook() {
    fstream file(fileName, ios::binary | ios::in | ios::out);

    if (!file) {
        cout << "File does not exist!\n";
        return;
    }

    int id;
    bool found = false;
    Book b;

    cout << "\nEnter Book ID to update: ";
    cin >> id;

    while (file.read(reinterpret_cast<char*>(&b), sizeof(Book))) {

        if (b.id == id) {

            found = true;

            cin.ignore();

            cout << "Enter New Title: ";
            cin.getline(b.title, 50);

            cout << "Enter New Author: ";
            cin.getline(b.author, 50);

            cout << "Enter New Genre: ";
            cin.getline(b.genre, 30);

            cout << "Enter New Status: ";
            cin.getline(b.status, 20);

            file.seekp(-static_cast<int>(sizeof(Book)), ios::cur);

            file.write(reinterpret_cast<char*>(&b), sizeof(Book));

            cout << "Record updated successfully.\n";

            break;
        }
    }

    if (!found) {
        cout << "Record not found.\n";
    }

    file.close();
}

// Delete Book
void deleteBook() {

    ifstream inFile(fileName, ios::binary);

    if (!inFile) {
        cout << "File does not exist!\n";
        return;
    }

    ofstream outFile("temp.dat", ios::binary);

    int id;
    bool found = false;
    Book b;

    cout << "\nEnter Book ID to delete: ";
    cin >> id;

    while (inFile.read(reinterpret_cast<char*>(&b), sizeof(Book))) {

        if (b.id != id) {
            outFile.write(reinterpret_cast<char*>(&b), sizeof(Book));
        }
        else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove(fileName.c_str());
    rename("temp.dat", fileName.c_str());

    if (found)
        cout << "Book deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

// Display All Books
void displayAll() {

    ifstream inFile(fileName, ios::binary);

    if (!inFile) {
        cout << "No records found!\n";
        return;
    }

    Book b;

    cout << "\n================ BOOK RECORDS ================\n";

    cout << left
         << setw(10) << "ID"
         << setw(25) << "Title"
         << setw(25) << "Author"
         << setw(20) << "Genre"
         << setw(15) << "Status" << endl;

    cout << "---------------------------------------------------------------"
         << "----------------\n";

    bool empty = true;

    while (inFile.read(reinterpret_cast<char*>(&b), sizeof(Book))) {

        empty = false;

        cout << left
             << setw(10) << b.id
             << setw(25) << b.title
             << setw(25) << b.author
             << setw(20) << b.genre
             << setw(15) << b.status
             << endl;
    }

    if (empty) {
        cout << "No records available.\n";
    }

    inFile.close();
}