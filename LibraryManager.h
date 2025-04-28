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
    map< Book , User* > inventory; //maps book to user
    map< string, string> hashPass; //username -> hashed password
    map< string , vector <Book> > sortGenre;//maps genre to a list of books 
    map< Book, deque<User*>> bookWaitlist; //key=book is mapped to a value=waitlist of users
    vector<User*> userList; //user database for login, local variable

public:
   
    vector<Book> getBooksByGenre(string genre) {
        return sortGenre[genre];
    }

    Book getBook(const string& title) {
        for (auto& book : inventory) {
            if (book.first.getTitle() == title) {
                return book.first;  // Return a copy of the found book
            }
        }
        // Return a default book if not found
        return Book("not found", "", "", false);
    }
    

    User* userInList(string& userName) {
        for( User* userptr : userList ) {
            if (userName == userptr->getUsername())//need to add condition for password matching 
                return userptr;
        }
        return nullptr;
    }

    bool hashPassCheck(string userName, string password){
        return (User::hashFunction(password) == hashPass[userName]);
    }

    void AddUserToLibrary(User* userptr) {
        userList.push_back(userptr);
        hashPass[userptr -> getUsername()] = userptr -> getHashedPassword(); 
    }

    void PrintUserInfo(const User& user) {
        cout << "Name: " << user.getFirst() << endl;
        //print out list of books
        if (user.getUserBooks().size() == 0) {
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
        string genre = book.getGenre(); // gets genre of book
        sortGenre[genre].push_back(book); // adds book to the specific genre's list

        inventory[book]=nullptr; //adds new book to inventory
    }

    bool checkOutBook(Book& book, User& user){
        if (inventory[book] != nullptr){ //already in someone elses hands 
            bookWaitlist[book].push_back(&user);
            cout<<"you are position " << (checkWaitlist(user, book) + 1) << " in the waitlist for this book"<< endl;
            return false;
        }
        else {
            user.addBook(book);
            inventory[book] = &user; //updated the inventory
            book.setStatus(false); // book is now not available
            return true;
        }
    }
    
    bool returnBook(Book& book, User* user){
        if(! user->bookCheck(book)) { //user doesn't have book (this is impossible)
            return false;
        }
        else {
            user->removeBook(book); //updates user list
            inventory[book] = nullptr; //updates inventory
            book.setStatus(true); //book is now available
            return true;
        }
    }
    //queue search alg for users position in waitlist //
     int checkWaitlist(User& user, const Book& book) {
        auto it = find(bookWaitlist[book].begin(), bookWaitlist[book].end(), &user);
        if (it == bookWaitlist[book].end()) { //if not in the waitlist, return -1!
            return -1;//not in the list
        }
        return distance(bookWaitlist[book].begin(), it);
     }

    //adding a user to the waitlist
    //bool joinWaitlist(const User& user) {
    //     bookWaitlist.push_back(&user);
    //      return true;
    //}

     //removing a user from the waitlist
     bool exitWaitlist(const Book& book){
        if(! bookWaitlist.empty()) {
        bookWaitlist[book].pop_front();
            return true;}
     }
    
};


#endif
