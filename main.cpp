//main.cpp
#include <iostream>
#include <string>
#include "Book.h"
#include "LibraryManager.h"
#include "User.h"

int main(int argc, char const *argv[])
{

    
    LibraryManager lib = LibraryManager();
    Book twilight = Book("Twilight", "idk", "Fantasy");
    lib.AddBookToLibrary(twilight);

    //populate books //J
    unordered_map<string, vector<string>> genreToTitles = {
        {"Mystery", {"M1", "M2", "M3", "M4", "M5"}}, {"Romance", {"R1", "R2", "R3", "R4", "R5"}},
        {"Fantasy", {"F1", "F2", "F3", "F4", "F5"}}, {"Horror", {"H1", "H2", "H3", "H4", "H5"}},
        {"Science Fiction", {"S1", "S2", "S3", "S4", "S5"}}
    };

    for (const auto& [genre, titles] : genreToTitles) { //looks through,iterates, thorugh genres and books
        for (const auto& title : titles) {
            // Create a new book with the current title and genre
            Book book(title, genre); 

            // Add the book to the library
            library.AddBookToLibrary(book);
        }
    }


    LibraryManager lib = LibraryManager();
    book1 twilight
    lib.addBookToInventory(book1)
    book2 twilight2
    book3 twilight3

    user eden
    user matt

    //and users //E

    
    //list genre recs based on selected genre 1-5 

    return 0;
}
