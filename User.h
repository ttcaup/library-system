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
    void addBook(Book book) {
        int left = 0;
        int right = books.size();

        // Perform binary search to find the correct position
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

    bool removeBook(Book book){
        books.erase(find(books.begin(), books.end(), book));
        return true;
    }

    string getFirst() {
        return firstName;
    }
    int getPhone() {
        return phoneNumber;
    }
    string getGenre() {
        return favGenre;
    }

    void setGenre(string genre){
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