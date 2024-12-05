#ifndef BOOK_H
#define BOOK_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

class Book {
private:
    int isbn;
    string title;
    string author;
    string genre;
    bool status;
public:
    Book(int isbn, string title, string genre, bool status) {
        this->isbn = isbn;
        this->title = title;
        this->genre = genre;
        this->status = status;
    }
    Book(int isbn, string title, string genre) {
        this->isbn = isbn;
        this->title = title;
        this->genre = genre;
        status = true;
    }
    int GetIsbn() {
        return isbn;
    }
    string GetTitle() {
        return title;
    }
    string GetAuthor() {
        return author;
    }
    string GetGenre() {
        return genre;
    }
    int GetStatus() {
        return status;
    }
    void SetStatus(bool status) {
        this->status = status;
    }
    void PrintInfo() {
        cout << "Book Info" << endl;
    }

};


#endif