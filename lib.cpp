#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable = true;
    int dueDays = 0; // Days until due (0 if available)
};

vector<Book> books;

void addBook() {
    Book book;
    cout << "Enter title: ";
    getline(cin, book.title);
    cout << "Enter author: ";
    getline(cin, book.author);
    cout << "Enter ISBN: ";
    getline(cin, book.ISBN);
    book.isAvailable = true;
    book.dueDays = 0;
    books.push_back(book);
    cout << "Book added successfully.\n";
}

void searchBook() {
    string keyword;
    cout << "Search by title, author, or ISBN: ";
    getline(cin, keyword);

    bool found = false;
    for (const auto& book : books) {
        if (book.title == keyword || book.author == keyword || book.ISBN == keyword) {
            cout << "Title: " << book.title
                 << ", Author: " << book.author
                 << ", ISBN: " << book.ISBN
                 << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No book found.\n";
}

void checkoutBook() {
    string isbn;
    cout << "Enter ISBN of the book to check out: ";
    getline(cin, isbn);

    for (auto& book : books) {
        if (book.ISBN == isbn) {
            if (book.isAvailable) {
                book.isAvailable = false;
                book.dueDays = 14;
                cout << "Book checked out successfully. Due in 14 days.\n";
            } else {
                cout << "Book is already checked out.\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

void returnBook() {
    string isbn;
    int daysLate;
    cout << "Enter ISBN of the book to return: ";
    getline(cin, isbn);

    for (auto& book : books) {
        if (book.ISBN == isbn) {
            if (!book.isAvailable) {
                cout << "Enter number of days late (0 if on time): ";
                cin >> daysLate;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                book.isAvailable = true;
                book.dueDays = 0;

                if (daysLate > 0) {
                    int fine = daysLate * 5;
                    cout << "Book returned late. Fine: Rs. " << fine << endl;
                } else {
                    cout << "Book returned on time. No fine.\n";
                }
            } else {
                cout << "Book is not checked out.\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

void menu() {
    int choice;
    do {
        cout << "\n--- Library Menu ---\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Check Out Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To clear newline character

        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: checkoutBook(); break;
            case 4: returnBook(); break;
            case 5: cout << "Exiting..."; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}