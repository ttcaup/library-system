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
    string favGenre;
    vector<Book> books;


public:
    User(string username, string first, string genre) {
        userName = username;
        firstName = first;
        favGenre = genre;
        books = {};
    }

    void addBook(const Book& book) {
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

bool removeBook(const Book& book) {
    auto it = find(books.begin(), books.end(), book);

    if (it == books.end()) {
        return false;
    } else {
        books.erase(it);
        return true;
    }
}

    string getUsername() const {
        return userName;
    }

    string getFirst() const {
        return firstName;
    }

    string getGenre() const {
        return favGenre;
    }

    // void setGenre(string genre){
    //     favGenre = genre;
    // }
    bool bookCheck(const Book& book) const {
        auto it = find(books.begin(), books.end(), book);  // This uses operator== to compare books
        return it != books.end();
    }

    const vector<Book>& getUserBooks() const {
        return books;
    }
    bool operator==(const User& other) const {
        return this->userName == other.getUsername();
    }
};


#endif