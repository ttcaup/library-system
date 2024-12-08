//Booh.h
#ifndef BOOK_H
#define BOOK_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

class Book {
private:
    string title;
    string author;
    string genre;
    bool status;
public:
    Book(string title, string genre, bool status) {
        this->title = title;
        this->genre = genre;
        this->status = status;
    }
    Book(string title, string genre) {
        this->title = title;
        this->genre = genre;
        status = true;
    }
    string getTitle() {
        return title;
    }
    string getAuthor() {
        return author;
    }
    string getGenre() {
        return genre;
    }
    int getStatus() {
        return status;
    }
    void setStatus(bool status) {
        this->status = status;
    }
    void printBookInfo() {
        cout << "Book Info" << endl;//need to do
    }

};


#endif