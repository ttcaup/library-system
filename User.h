//User.h
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <algorithm>
#include "Book.h"

using namespace std;


class User {
private:
    string userName;
    string firstName;
    vector<Book> books; //each user has a list of books associated with it
    string passwordHash = ""; 

public:

    //Constructor
    User(string username, string first) {
        userName = username;
        firstName = first;
        books = {};
    }

    //basic getter functions:
    string getUsername() const {
        return userName;
    }

    string getFirst() const {
        return firstName;
    }
    
    //password things
    static string hashFunction(string input){
        int hash = 0;
        for (char c : input){
            hash = hash * 101 + c;
        }
        return to_string(hash); 
        //hash is an int so we convert
    }
    
    bool setPassword(string password) {
        if (passwordHash != "") {
            cout << "ERROR: password is already set!" << endl; //need this line for persistance 
            return false;  
            //prevents password from being hashed each time user data is loaded from file
        }
        passwordHash = hashFunction(password); //hashes if needed
        return true;
    }

    void authenticateFromFile(string passwordHash) {
        this->passwordHash = passwordHash; //setting the password 
    }

    string getHashedPassword() const {
        return passwordHash; //returns hashsed passwords for authentication
    }

    //User->book related funtions
    void addBook(const Book& book) {
        // Perform binary search to find the correct position, vector is in abc order
        int left = 0;
        int right = books.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (books[mid].getTitle() < book.getTitle()) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        books.insert(books.begin() + left, book);
    }

    bool removeBook(const Book& book) {
        auto it = find(books.begin(), books.end(), book); //using iterators, finds book in vector

        if (it == books.end()) {
            return false; //book not found
        } else {
            books.erase(it);
            return true; //book found, deleted 
        }
    }

    const vector<Book>& getUserBooks() const{
        return books; //gets de-referenced book objects
    }

    //checks if the user has the book
    bool bookCheck(const Book& book) const {
        auto it = find(books.begin(), books.end(), book);  // This uses operator== to compare books
        return it != books.end();
    }
    
    //User class is overloaded for username
    bool operator==(const User& other) const {
        return this->userName == other.getUsername();
    }

};

#endif