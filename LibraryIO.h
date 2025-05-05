//LibraryIO.h
#ifndef LIBRARYIO_H
#define LIBRARYIO_H

#include "LibraryManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class LibraryIO {
public:
    static void saveToFile(LibraryManager& lib) {
        // Save books to file
        ofstream booksFile("books.txt"); 

        if (!booksFile) {
            cerr << "Error opening books.txt for writing.\n";
            return; //--goes to menu
        }

        // Access all books directly from the map
        for (const auto& [title, book] : lib.getAllBooksMap()) {
            booksFile << book.getTitle() << "|"
                      << book.getAuthor() << "|"
                      << book.getGenre() << "|"
                      << book.getStatus() << "\n";
        }
        booksFile.close();

        // Save users to file
        ofstream userFile("users.txt");
        if (!userFile) {
            cerr << "Error opening users.txt for writing.\n";
            return;
        }

        for (User* user : lib.getAllUsers()) {
            userFile << user->getUsername() << "|"
                     << user->getFirst() << "|"
                     << user->getHashedPassword() << "|";

            const vector<Book>& userBooks = user->getUserBooks();
            for (size_t i = 0; i < userBooks.size(); ++i) {
                userFile << userBooks[i].getTitle();
                if (i != userBooks.size() - 1) userFile << ",";
            }
            userFile << "\n";
        }
        userFile.close();
    }

    static void loadFromFile(LibraryManager& lib) {
        // Load books
        ifstream booksFile("books.txt");
        string line;

        while (getline(booksFile, line)) {
            stringstream ss(line);
            string title, author, genre, status;

            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, genre, '|');
            getline(ss, status);

            Book book(title, author, genre);
            if (status == "0") book.setStatus(false);

            lib.AddBookToLibrary(book);
        }
        booksFile.close();

        // Load users
        ifstream userFile("users.txt");

        while (getline(userFile, line)) {
            stringstream ss(line);
            string username, firstname, passwordHash, bookList;

            getline(ss, username, '|');
            getline(ss, firstname, '|');
            getline(ss, passwordHash, '|');
            getline(ss, bookList);

            User* user = new User(username, firstname);
            user->authenticateFromFile(passwordHash);
            lib.AddUserToLibrary(user);

            stringstream bl(bookList);
            string bookTitle;
            while (getline(bl, bookTitle, ',')) {
                Book* book = lib.getBook(bookTitle);
                if (book) {
                    user->addBook(*book);
                    book->setStatus(false);
                }
            }
        }
        userFile.close();
    }
};

#endif
