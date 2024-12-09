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
    map< string , vector <Book> > sortGenre;//maps genre to a list of books 
    deque<User> waitlist; 
    vector<User*> userList; //user database for login, local variable

public:

    /*void printUserList() {
    for (User &user : userList) {
        cout << user.getUsername() << " ";
     }
    }*/
   
    vector<Book> getBooksByGenre(string genre) {
        return sortGenre[genre];
    }

    User* userInList(string& userName) {
        for( User* userptr : userList ) {
            if (userName == userptr->getUsername())
                return userptr;
        }
        return nullptr;
    }

    void AddUserToLibrary(User* userptr) {
        userList.push_back(userptr);
    }

    void PrintUserInfo(const User& user) {
        cout << "Name: " << user.getFirst() << endl;
        //print out list of books
        cout << "Your Books: " << endl;
        cout << user.getUserBooks().size() << endl;
        for (const Book& book : user.getUserBooks()) {
            cout << "test" << endl;
            cout << book.getTitle() << endl;
        }

    }

    void AddBookToLibrary(const Book& book) {
        string genre = book.getGenre(); // gets genre of book
        sortGenre[genre].push_back(book); // adds book to the specific genre's list

        inventory[book]=nullptr; //adds new book to inventory
    }

    bool checkOutBook(Book& book, User& user){
        if (inventory[book] != nullptr){ //already in someone elses hands 
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
    //queue search alg for users position in waitlist //E
     int checkWaitlist(User& user) {
        auto it = find(waitlist.begin(), waitlist.end(), user);
        if (it == waitlist.end()) { //if not in the waitlist, return -1!
            return -1;//not in the list
        }
        return distance(waitlist.begin(), it);
     }

    //update waitlist? add to dequq push, remove from deque pop
     bool joinWaitlist(const User& user) {
         waitlist.push_back(user);
         return true;
     }
     bool exitWaitlist(){
        if(! waitlist.empty()) //only pop if not empty
            waitlist.pop_front();
            return true;
     }
    
};


#endif
