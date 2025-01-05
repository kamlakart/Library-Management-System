#include<bits/stdc++.h>
using namespace std;


class Book{
    string bookName;
    int isbnNumber, pages;
    public:
        Book(const string& bookName, const int& isbnNumber, const int& pages)
        : bookName(bookName), isbnNumber(isbnNumber), pages(pages) {}

        string getBookName() const
        {
            return bookName;
        }
        int getIsbnNumber() const 
        {
            return isbnNumber;
        }
        int getNumberOfPages() const
        {
            return pages;
        }
        void correctBookName(const string& newBookName)
        {
            if(bookName==newBookName)
            {
                cout<<"Previous Entry is same as requested Entry\n";
                return;
            }
            bookName=newBookName;
            cout<<"Book Name has been changed Successfully!!\n";
        }
        void correctBookPages(const int& newPages)
        {
            if(pages==newPages)
            {
                cout<<"Previous Entry is same as requested Entry\n";
                return;
            }
            pages=newPages;
            cout<<"Number of pages has been modified Successfully!!\n";
        }
        void correctIsbnNumber(const int& newIsbnNumber)
        {
            if(isbnNumber==newIsbnNumber)
            {
                cout<<"Previous Entry is same as requested Entry\n";
            }
            isbnNumber=newIsbnNumber;
            cout<<"ISBN number has been updated Successfully!!\n";
        }
};

class User{
    string userName;
    long long userId;
    unordered_map<int,Book> isbnNumberBookMap;
    vector<Book> borrowedBooks;
    public:
        User(const string& userName, const int& userId) : userName(userName), userId(userId) {}
        vector<Book> getBooks()
        {
            return borrowedBooks;
        }
};

class UserManagement{
    unordered_map<int, User> userIdUserMap;
    static long long currentUserIdCounter;
    public:
        int createUser(const string& userName)
        {
            ++currentUserIdCounter;
            User user1(userName, currentUserIdCounter);
            userIdUserMap[currentUserIdCounter]=user1;
            return currentUserIdCounter;
        }
        optional<User> getUser(const int& userId)
        {
            if(userIdUserMap.find(userId)!=userIdUserMap.end())
            {
                return userIdUserMap.at(userId);
            }
            return nullopt;
        }
        optional<vector<Book>> getBooks(const int& userId)
        {
            if(userIdUserMap.find(userId)!=userIdUserMap.end())
            {
                return userIdUserMap.at(userId).getBooks();
            }
            return nullopt;
        }
};

long long UserManagement::currentUserIdCounter=1000000000;

int main()
{

    return 0;
}