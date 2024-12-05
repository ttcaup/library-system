#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <string> 
#include <unordered_map>
#include "Book.h"
#include "User.h"

using namespace std;


class LibraryManager {
    unordered_map< Book , User > database;

    //print user info

    //add a book to the database

    //remove a book from the database

    //search for a book, does it exist? is it available? when will it be available?

    //quque waitlist for a book

    //search for genre recs
};


#endif