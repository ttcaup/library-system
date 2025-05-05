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

    //this is called each time there is a modifiaction to the library or user data
    static void saveToFile(LibraryManager& lib) {
        // Save books to file
        ofstream booksFile("books.txt"); 

        if (!booksFile) {
            cerr << "Error opening books.txt for writing.\n";
            return; //--goes to menu
        }

        // Access all books directly from the map
        //for every book in the map...
        //each parameter of the book object is written into books.txt in the correct format
        for (const auto& [title, book] : lib.getAllBooksMap()) {
            booksFile << book.getTitle() << "|"
                      << book.getAuthor() << "|"
                      << book.getGenre() << "|"
                      << book.getStatus() << "\n";
        }
        booksFile.close(); //done

        // Save users to file
        ofstream userFile("users.txt");
        if (!userFile) {
            cerr << "Error opening users.txt for writing.\n";
            return;
        }

        //accesses the vector structure directly
        //for every user pointer in the vector...
        //write all the parameters to the user.txt file 
        for (User* user : lib.getAllUsers()) {
            userFile << user->getUsername() << "|"
                     << user->getFirst() << "|"
                     << user->getHashedPassword() << "|";

            const vector<Book>& userBooks = user->getUserBooks();
            //for every book in the user's bookList...
            //write to the user.txt file in the correct formatt
            for (size_t i = 0; i < userBooks.size(); ++i) {
                userFile << userBooks[i].getTitle();
                if (i != userBooks.size() - 1) userFile << ",";
            }
            userFile << "\n";
        }
        userFile.close(); //done
    }

    //This is called once at the begining of int main()
    //loads all data from both files
    static void loadFromFile(LibraryManager& lib) {
        // Load books first
        ifstream booksFile("books.txt");
        string line;

        //for every line in the file...
        while (getline(booksFile, line)) {
            stringstream ss(line);
            string title, author, genre, status; 

            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, genre, '|');
            getline(ss, status);

            Book book(title, author, genre); //create book object
            if (status == "0") book.setStatus(false);//check if available

            lib.AddBookToLibrary(book); //add book to library structure 
        }
        booksFile.close(); //close the book.txt file

        // Load users
        ifstream userFile("users.txt");

        //for every line in the file...
        while (getline(userFile, line)) {
            stringstream ss(line);
            string username, firstname, passwordHash, bookList;

            getline(ss, username, '|');
            getline(ss, firstname, '|');
            getline(ss, passwordHash, '|');
            getline(ss, bookList);

            User* user = new User(username, firstname); //create new user object
            user->authenticateFromFile(passwordHash); //setting the hashed password as entered in the file
            lib.AddUserToLibrary(user); //adds user  to library structure

            stringstream bl(bookList);
            string bookTitle;
            //for every line in the file
            while (getline(bl, bookTitle, ',')) {
                Book* book = lib.getBook(bookTitle); //gets the book object
                if (book) {
                    user->addBook(*book); //add the book to the user's list of book
                    book->setStatus(false);//sets the avail. as false
                }
            }
        }
        userFile.close();
    }
};

#endif
