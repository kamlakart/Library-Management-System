#include <bits/stdc++.h>

using namespace std;

class Book
{
    int bookId;
    string title;
    string author;
    bool isAvailable;

public:
    Book(int id, const string &title, const string &author)
        : bookId(id), title(title), author(author), isAvailable(true) {}

    int getBookId() const { return bookId; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool checkAvailability() const { return isAvailable; }

    void borrowBook() { isAvailable = false; }
    void returnBook() { isAvailable = true; }

    void display() const
    {
        cout << setw(5) << bookId << " | " << setw(20) << title
             << " | " << setw(15) << author
             << " | " << (isAvailable ? "Available" : "Not Available") << endl;
    }
};

class User
{
    int userId;
    string name;
    unordered_set<int> borrowedBooks; // Efficient storage for borrowed book IDs

public:
    User(int id, const string &name) : userId(id), name(name) {}

    int getUserId() const { return userId; }
    string getName() const { return name; }
    unordered_set<int> getBorrowedBooks() const { return borrowedBooks; }

    void borrowBook(int bookId) { borrowedBooks.insert(bookId); }
    void returnBook(int bookId) { borrowedBooks.erase(bookId); }

    void display() const
    {
        cout << "User ID: " << userId << ", Name: " << name << endl;
        if (borrowedBooks.empty())
        {
            cout << "No books borrowed." << endl;
        }
        else
        {
            cout << "Borrowed Books: ";
            for (int bookId : borrowedBooks)
            {
                cout << bookId << " ";
            }
            cout << endl;
        }
    }
};

class Library
{
    unordered_map<int, Book> books;
    unordered_map<int, User> users;

public:
    void addBook(int bookId, const string &title, const string &author)
    {
        if (books.find(bookId) != books.end())
        {
            cout << "Book with ID " << bookId << " already exists." << endl;
            return;
        }
        books[bookId] = Book(bookId, title, author);
        cout << "Book added successfully." << endl;
    }

    void addUser(int userId, const string &name)
    {
        if (users.find(userId) != users.end())
        {
            cout << "User with ID " << userId << " already exists." << endl;
            return;
        }
        users[userId] = User(userId, name);
        cout << "User added successfully." << endl;
    }

    optional<Book> getBook(int bookId)
    {
        if (books.find(bookId) != books.end())
        {
            return books[bookId];
        }
        return nullopt;
    }

    optional<User> getUser(int userId)
    {
        if (users.find(userId) != users.end())
        {
            return users[userId];
        }
        return nullopt;
    }

    void borrowBook(int userId, int bookId)
    {
        if (users.find(userId) == users.end())
        {
            cout << "User ID " << userId << " not found." << endl;
            return;
        }

        if (books.find(bookId) == books.end())
        {
            cout << "Book ID " << bookId << " not found." << endl;
            return;
        }

        Book &book = books[bookId];
        if (!book.checkAvailability())
        {
            cout << "Book " << book.getTitle() << " is currently not available." << endl;
            return;
        }

        users[userId].borrowBook(bookId);
        book.borrowBook();
        cout << "Book " << book.getTitle() << " borrowed successfully by " << users[userId].getName() << "." << endl;
    }

    void returnBook(int userId, int bookId)
    {
        if (users.find(userId) == users.end())
        {
            cout << "User ID " << userId << " not found." << endl;
            return;
        }

        if (books.find(bookId) == books.end())
        {
            cout << "Book ID " << bookId << " not found." << endl;
            return;
        }

        User &user = users[userId];
        if (user.getBorrowedBooks().find(bookId) == user.getBorrowedBooks().end())
        {
            cout << "Book " << bookId << " was not borrowed by " << user.getName() << "." << endl;
            return;
        }

        user.returnBook(bookId);
        books[bookId].returnBook();
        cout << "Book " << books[bookId].getTitle() << " returned successfully by " << user.getName() << "." << endl;
    }

    void displayAllBooks() const
    {
        cout << setw(5) << "ID" << " | " << setw(20) << "Title" << " | " << setw(15) << "Author" << " | " << "Status" << endl;
        cout << "-----------------------------------------------------------" << endl;
        for (const auto &[bookId, book] : books)
        {
            book.display();
        }
    }

    void displayAllUsers() const
    {
        for (const auto &[userId, user] : users)
        {
            user.display();
            cout << "-------------------------------" << endl;
        }
    }
};

int main()
{
    Library library;

    library.addBook(1, "C++ Primer", "Stanley Lippman");
    library.addBook(2, "Effective C++", "Scott Meyers");
    library.addBook(3, "Clean Code", "Robert Martin");

    library.addUser(1001, "Alice");
    library.addUser(1002, "Bob");

    library.displayAllBooks();
    cout << endl;

    library.borrowBook(1001, 1);
    library.borrowBook(1001, 2);
    library.borrowBook(1002, 3);

    library.displayAllUsers();
    cout << endl;

    library.returnBook(1001, 1);
    library.returnBook(1002, 3);

    library.displayAllBooks();
    library.displayAllUsers();

    return 0;
}
