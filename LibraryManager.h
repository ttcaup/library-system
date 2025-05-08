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
    map< string, Book> books; //maps title to a book object
    map< string , User* > inventory; //maps title to user
    map< string, string> hashPass; //username -> hashed password
    map< string , vector <Book> > sortGenre;//maps genre to a list of books 
    map< string, deque<User*>> bookWaitlist; //title of book is mapped to a deque of User pointers
    vector<User*> userList; //user database for login, local variable

public:

//User associated functions:

    vector<User*> getAllUsers(){
        return userList; //returns vector of user pointers
    }

    //function returns a pointer to a user object
    //that pointer is used throughout the users'
    // expereince to update their information
    User* userInList(const string& userName) {
        for( User* userptr : userList ) {
            if (userName == userptr->getUsername())
                return userptr; //user found
        }
        return nullptr; //user not found
    }

    void AddUserToLibrary(User* userptr) {
        userList.push_back(userptr);//adds the user pointer to userList
        hashPass[userptr -> getUsername()] = userptr -> getHashedPassword(); 
        //maps the userName to the hashed password
    }

    bool hashPassCheck(const string& userName, const string& password){
        return (User::hashFunction(password) == hashPass[userName]); 
        //applies hash function to plaintext "password" 
        //then compares it to the stored hashPass
    }

    //checks a user's position in the waitlist for a book
    int checkWaitlist(User& user, const string& title) {
        auto it = find(bookWaitlist[title].begin(), bookWaitlist[title].end(), &user);
        //iterator refrences each value if the deque until it finds the correct user
        if (it == bookWaitlist[title].end()) return -1;  //if not in the waitlist, return -1!
        return distance(bookWaitlist[title].begin(), it); //returns position
     }

     //removing a user from the waitlist
    bool exitWaitlist(const string& title) {
        auto& it = bookWaitlist[title]; //finds the key
        if(!it.empty()) {
            it.pop_front();
            return true;//books found, user popped from deque
        }
        return false; //book not found
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

//Book associated functions: 

    vector<Book> getBooksByGenre(const string& genre) {
        return sortGenre[genre]; 
        //returns value = list of books in key = genre
    }

    //find and return a pointer to the book with given title 
    Book* getBook(const string& title) {
        auto it = books.find(title); //iterator finds key = title 
        if (it != books.end()) return &it->second; //accesses the value and returns it 
        return nullptr; //book not found
    }

    const map<string, Book>& getAllBooksMap() const {
        return books; //retunrs de-referenced book values from the books map
    }

    void AddBookToLibrary(const Book& book) {
        string title = book.getTitle();
        books[title] = book;
        string genre = book.getGenre(); // gets genre of book
        sortGenre[genre].push_back(book); // adds book to the specific genre's list
        inventory[title]=nullptr; //adds new book to inventory
    }

    //accepts new book and adds it to the system
    void donateBook(const string& title, const string& author, const string& genre){
        Book donatedBook(title, author, genre); //available
        AddBookToLibrary(donatedBook);
    }

    bool checkOutBook(const string& title, User& user){
        if (books[title].getStatus() == 0){ //already in someone elses hands 
            bookWaitlist[title].push_back(&user); //adds user to book waitlist
            cout<<"\n--You are position #" << (checkWaitlist(user, title) + 1) << " in the waitlist for this book--"<< endl;
            return false;
        }
        else {
            Book& chosenBook = books[title]; //accesses the value (Book object) in the books map 
            user.addBook(chosenBook); //adds it to user list of books
            inventory[title] = &user; //updated the inventory
            chosenBook.setStatus(false); // book is now not available
            return true;
        }
    }

    // return a book from a user and make it available in invetory again
    bool returnBook(const string& title, User* user){
        Book& book = books[title];
        if(!user->bookCheck(book)) { 
            return false; //book is not in list
        }
        else {
            user->removeBook(book); //updates user list
            inventory[title] = nullptr; //updates inventory
            book.setStatus(true); //book is now available
            return true;
        }
    }
    
};


#endif
