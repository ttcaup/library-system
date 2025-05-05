//LibraryManager.h
#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <string> 
#include <deque>
#include <map>
#include "Book.h"
#include "User.h"

using namespace std;


class LibraryManager {
    
private:
    map< string, Book> books;
    map< string , User* > inventory; //maps book to user
    map< string, string> hashPass; //username -> hashed password
    map< string , vector <Book> > sortGenre;//maps genre to a list of books 
    map< string, deque<User*>> bookWaitlist; //key=book is mapped to a value=waitlist of users
    vector<User*> userList; //user database for login, local variable

public:
   
    vector<Book> getBooksByGenre(const string& genre) {
        return sortGenre[genre];
    }

    //find and return a pointer to the book with given title 
    Book* getBook(const string& title) {
        auto it = books.find(title);
        if (it != books.end()) return &it->second;
        return nullptr;
    }

    const map<string, Book>& getAllBooksMap() const {
        return books;
    }
    
    vector<User*> getAllUsers(){
        return userList;
    }

    User* userInList(const string& userName) {
        for( User* userptr : userList ) {
            if (userName == userptr->getUsername())//need to add condition for password matching 
                return userptr;
        }
        return nullptr;
    }

    bool hashPassCheck(const string& userName, const string& password){
        return (User::hashFunction(password) == hashPass[userName]);
    }

    void AddUserToLibrary(User* userptr) {
        userList.push_back(userptr);
        hashPass[userptr -> getUsername()] = userptr -> getHashedPassword();
        
    }

    void PrintUserInfo(const User& user) {
        cout << "Name: " << user.getFirst() << endl;
        //print out list of books
        if (user.getUserBooks().empty()) {
            cout << "You currently have no books.\n\n";
        }
        else {
            cout << "Your Books: " << endl;
            for (const Book& book : user.getUserBooks()) {
                cout << book.getTitle() << endl;
            }
            cout << "\n\n";
        }
    }

    void AddBookToLibrary(const Book& book) {
        string title = book.getTitle();
        books[title] = book;
        string genre = book.getGenre(); // gets genre of book
        sortGenre[genre].push_back(book); // adds book to the specific genre's list

        inventory[title]=nullptr; //adds new book to inventory

    }

    bool checkOutBook(const string& title, User& user){
        if (books[title].getStatus() == 0){ //already in someone elses hands 
            bookWaitlist[title].push_back(&user);
            cout<<"you are position " << (checkWaitlist(user, title) + 1) << " in the waitlist for this book"<< endl;
            return false;
        }
        else {
            Book& book = books[title];
            user.addBook(book);
            inventory[title] = &user; //updated the inventory
            book.setStatus(false); // book is now not available
            return true;
        }
    }
    //
    // return a book from a user and make it available in invetory again
    bool returnBook(const string& title, User* user){
        Book& book = books[title];
        if(!user->bookCheck(book)) { //user doesn't have book (this is impossible)
            return false;
        }
        else {
            user->removeBook(book); //updates user list
            inventory[title] = nullptr; //updates inventory
            book.setStatus(true); //book is now available
            return true;
        }
    }
    //checks a user's position in the waitlist for a book
     int checkWaitlist(User& user, const string& title) {
        auto it = find(bookWaitlist[title].begin(), bookWaitlist[title].end(), &user);
        if (it == bookWaitlist[title].end()) return -1;  //if not in the waitlist, return -1!
        return distance(bookWaitlist[title].begin(), it);
     }

     //removing a user from the waitlist
     bool exitWaitlist(const string& title) {
        auto& it = bookWaitlist[title];
        if(!it.empty()) {
            it.pop_front();
            return true;
        }
        return false;
    }

    //acceptsw new book and adds it to the system
    void donateBook(const string& title, const string& author, const string& genre){
        Book donatedBook(title, author, genre, true); //available
        AddBookToLibrary(donatedBook);
    }
    
};


#endif
