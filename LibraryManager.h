//LibraryManager.h
#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <string> 
#include <deque>
#include <unordered_map>
#include "Book.h"
#include "User.h"
#include <thread>
#include <chrono>
#include <functional>

using namespace std;


class LibraryManager 
{
private:
    unordered_map< Book , User* > inventory; //maps book to user
    unordered_map< string , vector <Book> > sortGenre;//maps genre to a list of books 
    deque <User*> waitlist; //
    vector<User> userList; //user database for login, local variable

public:

    vector<Book> getBooksByGenre(string genre) {
        return sortGenre[genre];
    }

    User* userInList(string userName) {
        for( User user : userList ) {
            if ( userName == user.getUsername())
                return &user;
        }
        return nullptr;
    }

    void AddUserToLibrary(User& user){
        userList.push_back(user);
    }
    //print user info //J
    void PrintUserInfo( User& user) const {
        cout << "Name: " << user.getFirst() << endl;
        cout << "Favorite Genre: " << user.getGenre() << endl;
    }

    //add a book to the inventory and genre list //J

    //remove a book from the database and genre list  //J
    //puts book in library and assigns with genre
    void AddBookToLibrary(Book& book) {
        string genre = book.getGenre(); // gets genre of book
        sortGenre[genre].push_back(book); // adds book to the specific genre's list

        inventory[book]=nullptr; //adds new book to inventory
    }
    //removes book from both libray and genre list
    bool RemoveBookFromLibrary(const string& title, const string& genre) {
        //this gets the vector of books for the specidic genre
        vector<Book>& booksInGenre = sortGenre[genre];

        //finds the book (by title) in vector
        //CHECK THIS
        auto it = find_if(booksInGenre.begin(),booksInGenre.end(),
        [&title](Book& b) { return b.getTitle() == title; });

        if (it != booksInGenre.end()) {
            booksInGenre.erase(it);   //removes book is found
            return true;
        }
        return false;//fails
    }

    bool checkOutBook(Book book, User* user){
        if (inventory[book] != nullptr || book.getStatus() == false){ //already in someone elses hands 
            return false;
        }
        else {
            user->addBook(book);
            inventory[book] = user; //updated the inventory
            book.setStatus(false); // book is now not available
            return true;
        }
    }
    
    bool returnBook(Book book, User* user){
        if(! user->bookCheck(book)){ //user doesn't have book (this is impossible)
            return false;
        }
        else {
            user->removeBook(book);//updates user list
            inventory[book] = nullptr;//updates inventory
            book.setStatus(true); //book is now available
            return true;
        }
    }

    //queue search alg for users position in waitlist //E
    int checkWaitlist(User user){
        auto it = find(waitlist.begin(), waitlist.end(), user);
        return distance(waitlist.begin(), it);
    }

    //update waitlist? add to dequq push, remove from deque pop
    bool joinWaitlist(User* user){
        waitlist.push_back(user);
        return true;
    }
    bool exitWaitlist(){
    if(! waitlist.empty()) //only pop if not empty
        waitlist.pop_front();
        return true;
    }
    
    void executeAfterDelay(int seconds, const std::function<void()>& exitWaitlist) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    exitWaitlist();
    }
    
};


#endif
