#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

\
#include <string> 
#include <unordered_map>
#include "Book.h"
#include "User.h"

using namespace std;


class LibraryManager {
    unordered_map< Book , User > inventory; //maps book to user
    unordered_map< string , vector <Book> > sortGenre;//maps genre to a list of books 

    //print user info

    //add a book to the inventory and genre list

    //remove a book from the database and genre list

    //update the inventory - checkout(value=user) OR return(value = null), will need to update the books avail.

    //queue waitlist for a book

    //queue search alg for users position in waitlist

    
};


#endif