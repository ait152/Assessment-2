#include <iostream>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    string location;
    bool available;

    void setBookDetails(string t, string a, string i, string l, bool av) {
        title = t;
        author = a;
        isbn = i;
        location = l;
        available = av;
    }

    virtual void displayBookDetails() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Location: " << location << endl;
        cout << "Availability: " << (available ? "Available" : "Borrowed") << endl;
    }

    bool borrowBook() {
        if (available) {
            available = false;
            cout << "You have successfully borrowed \"" << title << "\".\n";
            return true;
        } else {
            cout << "Sorry, \"" << title << "\" is currently not available.\n";
            return false;
        }
    }

    void returnBook() {
        available = true;
        cout << "\"" << title << "\" has been returned.\n";
    }
};
// End of the main class
// HardcopyBook class 
class HardcopyBook : public Book {
public:
    string shelfNumber = "Shelf Area";

    void displayBookDetails() override {
        Book::displayBookDetails();
        cout << "Type: Hardcopy Book Shelf: " << shelfNumber << "\n";
    }
};

// EBook class
class EBook : public Book {
public:
    string licenseEndDate = "DIC 2025";

    void displayBookDetails() override {
        Book::displayBookDetails();
        cout << "Type: E-Book license ends: " << licenseEndDate << "\n";
    }
};

int main() {
    const int maxLength = 10;
    Book* library[maxLength];
    int length = 5;

    
    library[0] = new HardcopyBook();
    library[0]->setBookDetails("The Interpretation of Dreams", "Sigmund Freud", "11", "Shelf A1", true);

    library[1] = new HardcopyBook();
    library[1]->setBookDetails("Alice's Adventures in Wonderland", "Lewis Carroll", "22", "Shelf A2", true);

    library[2] = new HardcopyBook();
    library[2]->setBookDetails("The Odyssey", "Homer", "33", "Shelf A3", true);

    library[3] = new EBook();
    library[3]->setBookDetails("The Old Man and The Sea", "Ernest Hemingway", "44", "Online", true);

    library[4] = new EBook();
    library[4]->setBookDetails("The Truce", "Mario Benedetti", "55", "Online", true);

    int choice;

    do {
        cout << "\nWelcome, please select an option:\n";
        cout << "1 - List all Books\n";
        cout << "2 - Borrow a Book\n";
        cout << "3 - Return a Book\n";
        cout << "4 - Add a New Book\n";
        cout << "5 - Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
    

        if (choice == 1) {
            for (int i = 0; i < length; i++) {
                library[i]->displayBookDetails();
               
            }
        }
        else if (choice == 2) {
    string num;
    cout << "Enter ISBN to borrow: ";
    cin >> num; 
    bool found = false;
    for (int i = 0; i < length; i++) {
        if (library[i]->isbn == num) {
            library[i]->borrowBook();
            found = true;
            break;
        }
    }
    if (!found) cout << "Book with ISBN " << num << " not found.\n";
}
        else if (choice == 3) {
            string num;
            cout << "Enter ISBN to return: ";
             cin >> num; 
            bool found = false;
            for (int i = 0; i < length; i++) {
                if (library[i]->isbn == num) {
                    library[i]->returnBook();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Book with ISBN " << num << " not found.\n";
        }
        else if (choice == 4) {
            if (length >= maxLength) {
                cout << "Library is full, cannot add more books.\n";
                continue;
            }
            int type;
            string t, a, i, l;
            bool av;
            cout << "Is it a Hardcopy (1) or an EBook (2)?: ";
            cin >> type;
            cin.ignore();

            if (type == 1) {
                library[length] = new HardcopyBook();
            } else {
                library[length] = new EBook();
            }

            cout << "Enter title: ";
            getline(cin, t);
            cout << "Enter author: ";
            getline(cin, a);
            cout << "Enter ISBN: ";
            getline(cin, i);
            cout << "Enter location Shelf or Online: ";
            getline(cin, l);
            cout << "Is it available?1 for yes, 0 for no: ";
            cin >> av;
            cin.ignore();

            library[length]->setBookDetails(t, a, i, l, av);
            length++;
            cout << "Book added successfully.\n";
        }
        else if (choice == 5) {
            cout << "Exiting program.\n";
        }
        else {
            cout << "Invalid choice, please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
