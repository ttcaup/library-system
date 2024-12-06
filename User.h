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
    void CheckOutBook(Book book) {
        books.push_back(book);
    }

    bool ReturnBook(Book book){
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
};


#endif