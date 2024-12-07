//LibraryManager.h
#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

\
#include <string> 
#include <unordered_map>
#include "Book.h"
#include "User.h"

using namespace std;


class LibraryManager {
    unordered_map< Book , User > inventory; //maps book to user
    unordered_map< string , vector <Book> > sortGenre;//maps genre to a list of books 
    
    //print user info //J
    void PrintUserInfo(const User& user) const {
        cout << "Name: " << user.GetFirst() << endl;
        cout << "Phone Number: " << user.GetPhone() << endl;
        cout << "Favorite Genre: " << user.GetGenre() << endl;
    }

    //add a book to the inventory and genre list //J
    //remove a book from the database and genre list  //J
    public:
    //puts book in library and assigns with genre
    void AddBookToLibrary(const Book& book) {
        string genre = book.GetGenre(); // gets genre of book
        sortGenre[genre].push_back(book); // adds book to the specific genre's list
    }
    //removes book from both libray and genre list
    bool RemoveBookFromLibrary(const string& title, const string& genre) {
        //this gets the vector of books for the specidic genre
        vector<Book>& booksInGenre = sortGenre[genre];

        //finds the book (by title) in vector
        //CHECK THIS
        auto it = find_if(booksInGenre.begin(),booksInGenre.end(),
        [&title](const Book& b) { return b.GetTitle() == title; });

        if (it != booksInGenre.end()) {
            booksInGenre.erase(it);   //removes book is found
            return true;
        }
        return false;                  //fails
    }
    

    //update the inventory - checkout(value=user) OR return(value = null), will need to update the books avail. //E

    //queue waitlist for a book //E

    //queue search alg for users position in waitlist //E

    
};


#endif
