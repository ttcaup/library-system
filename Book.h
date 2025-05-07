//Book.h
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

    //constructor 1: default status is true, used for adding new books to library 
    Book (string title, string author, string genre) {
        this->title = title;
        this->author = author;
        this->genre = genre;
        status = true;
    }
    //constructor 2: default
    //used in persistance when a book already exists and is being loaded from file 
    Book() : title(""), author(""), genre(""), status(true){}

    //getter functions: 
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
  
    //Book object overloaded for title and author
    bool operator== (const Book& other) const {
        return this->title == other.getTitle() && this->author == other.getAuthor();
    }

};


#endif