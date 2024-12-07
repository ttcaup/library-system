#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Book.h"

using namespace std;


class User {
private:
    string userName;
    string firstName;
    int phoneNumber;
    string favGenre;
    vector<Book> books;
    
public:
    User(string username, string first, int phone, string genre) {
        userName = username;
        firstName = first;
        phoneNumber = phone;
        favGenre = genre;
        books = {};
    }

    string GetUsername(){
        return userName;
    }
    bool addBook(Book book) {
        books.push_back(book);
    }

    bool removeBook(Book book){
        books.erase(find(books.begin(), books.end(), book));
        return true;
    }

    string GetFirst() {
        return firstName;
    }
    int GetPhone() {
        return phoneNumber;
    }
    string GetGenre() {
        return favGenre;
    }

    void SetGenre(string genre){
        favGenre = genre;
    }
    bool bookCheck(Book book){
        auto it = find(books.begin(), books.end(), book);
        if (it == books.end()){
            return false;
        }
        else 
            return true;
    }
    vector<Book> getUserBooks(){
        return books;
    }
};


#endif