#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Book {
    string author;
    string title;
    string category;
};

struct Magazine {
    string title;
    int year;
};

struct Newspaper {
    string title;
    int year;
};

void addBook(vector<Book*>& books) {
    string author, title, category;
    cout << "Enter author: ";
    cin.ignore();
    getline(cin, author);
    cout << "Enter title: ";
    getline(cin, title);
    cout << "Enter category: ";
    getline(cin, category);
    books.push_back(new Book{ author, title, category });
    cout << "Book added successfully.\n";
}

void addMagazine(vector<Magazine*>& magazines) {
    string title;
    int year;
    cout << "Enter title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter year: ";
    cin >> year;
    magazines.push_back(new Magazine{ title, year });
    cout << "Magazine added successfully.\n";
}

void addNewspaper(vector<Newspaper*>& newspapers) {
    string title;
    int year;
    cout << "Enter title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter year: ";
    cin >> year;
    newspapers.push_back(new Newspaper{ title, year });
    cout << "Newspaper added successfully.\n";
}

void viewAll(const vector<Book*>& books, const vector<Magazine*>& magazines, const vector<Newspaper*>& newspapers) {
    cout << "Books:\n";
    for (const auto& book : books) {
        cout << "Author: " << book->author << ", Title: " << book->title << ", Category: " << book->category << endl;
    }

    cout << "\nMagazines:\n";
    for (const auto& magazine : magazines) {
        cout << "Title: " << magazine->title << ", Year: " << magazine->year << endl;
    }

    cout << "\nNewspapers:\n";
    for (const auto& newspaper : newspapers) {
        cout << "Title: " << newspaper->title << ", Year: " << newspaper->year << endl;
    }
}

void removeBook(vector<Book*>& books) {
    string title;
    cout << "Enter the title of the book to remove: ";
    cin.ignore();
    getline(cin, title);
    books.erase(remove_if(books.begin(), books.end(), [&](Book* book) {
        if (book->title == title) {
            delete book;
            return true;
        }
        return false;
        }), books.end());
    cout << "Book removed successfully.\n";
}

void searchBook(const vector<Book*>& books) {
    string author, title;
    cout << "Enter author: ";
    cin.ignore();
    getline(cin, author);
    cout << "Enter title: ";
    getline(cin, title);
    bool found = false;
    for (const auto& book : books) {
        if (book->author == author && book->title == title) {
            cout << "Found book - Author: " << book->author << ", Title: " << book->title << ", Category: " << book->category << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Book not found.\n";
    }
}

void sortByTypeAndTitle(vector<Book*>& books, vector<Magazine*>& magazines, vector<Newspaper*>& newspapers) {
    sort(books.begin(), books.end(), [](Book* a, Book* b) {
        return a->title < b->title;
        });

    sort(magazines.begin(), magazines.end(), [](Magazine* a, Magazine* b) {
        return a->title < b->title;
        });

    sort(newspapers.begin(), newspapers.end(), [](Newspaper* a, Newspaper* b) {
        return a->title < b->title;
        });

    cout << "Data sorted by title.\n";
}

void saveToFile(const vector<Book*>& books, const vector<Magazine*>& magazines, const vector<Newspaper*>& newspapers) {
    ofstream outFile("library_data.txt");
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    outFile << "Books:\n";
    for (const auto& book : books) {
        outFile << "Author: " << book->author << ", Title: " << book->title << ", Category: " << book->category << endl;
    }

    outFile << "\nMagazines:\n";
    for (const auto& magazine : magazines) {
        outFile << "Title: " << magazine->title << ", Year: " << magazine->year << endl;
    }

    outFile << "\nNewspapers:\n";
    for (const auto& newspaper : newspapers) {
        outFile << "Title: " << newspaper->title << ", Year: " << newspaper->year << endl;
    }

    outFile.close();
    cout << "Data saved to library_data.txt\n";
}

void Ascii() {
    cout << R"(
 .-.    .-. .----.  .---.    .--.   .---.  .-.  .-.
 } |    { | | {_} } } }}_}  / {} \  } }}_}  \ \/ /
 } '--. | } | {_} } | } \  /  /\  \ | } \    `-\ }
 `----' `-' `----'  `-'-'  `-'  `-' `-'-'      `-'
    )" << endl;
}

int main() {
    vector<Book*> books;
    vector<Magazine*> magazines;
    vector<Newspaper*> newspapers;

    int choice;

    do {
        Ascii();
        cout << "1. Add Book\n";
        cout << "2. Add Magazine\n";
        cout << "3. Add Newspaper\n";
        cout << "4. View All Records\n";
        cout << "5. Search Book\n";
        cout << "6. Remove Book\n";
        cout << "7. Sort by Title\n";
        cout << "8. Save to File\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook(books);
            break;
        case 2:
            addMagazine(magazines);
            break;
        case 3:
            addNewspaper(newspapers);
            break;
        case 4:
            viewAll(books, magazines, newspapers);
            break;
        case 5:
            searchBook(books);
            break;
        case 6:
            removeBook(books);
            break;
        case 7:
            sortByTypeAndTitle(books, magazines, newspapers);
            break;
        case 8:
            saveToFile(books, magazines, newspapers);
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    for (auto& book : books) delete book;
    for (auto& magazine : magazines) delete magazine;
    for (auto& newspaper : newspapers) delete newspaper;

    return 0;
}
