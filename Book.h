//Booh.h
#ifndef BOOK_H
#define BOOK_H

#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Book {
private:
    string title;
    string author;
    string genre;
    bool status;
public:
    Book(string title, string author, string genre, bool status) {
        this->title = title;
        this->genre = genre;
        this->author = author;
        this->status = status;
    }
    Book (string title, string author, string genre) {
        this->title = title;
        this->author = author;
        this->genre = genre;
        status = true;
    }
    string getTitle() const {
        return title;
    }
    string getAuthor() const {
        return author;
    }
    string getGenre() const{
        return genre;
    }
    int getStatus() const {
        return status;
    }
    void setStatus(const bool& status) {
        this->status = status;
    }
  
    // void printBookInfo(Book book) {
    //     cout << "Book Info" << endl;//need to do
    // }
    
    bool operator== (const Book& other) const {
        return this->title == other.getTitle() && this->author == other.getAuthor();
    }
    bool operator< (const Book& other) const {
        return this->title < other.getTitle();
    }

};


#endif