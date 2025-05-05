//main.cpp

/*
Library System

Course:  CMPE 126
Authors: Eden Reader, Jasmine Kurian

*/
#include <iostream>
#include <string>
#include "Book.h"
#include "LibraryManager.h"
#include "User.h"
#include "LibraryIO.h"

using namespace std;

// function: prompts user to select genre from list
//-----returns the string representing the chosen grenre
string getGenreChoice() {
    int genreChoice;
    
    while (true) {
        cout << "\nChoose genre by entering the corresponding number:\n";
        cout << "1. Fantasy\n2. Romance\n3. Mystery\n4. Horror\n5. Science Fiction\n6. RETURN TO MENU\n";
        cout << "\nEnter your choice (1-6): ";
        cin >> genreChoice;

        //input validation
        while(cin.fail()) {
            cout << "Invalid Choice! Enter an Integer!" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> genreChoice;
    }
        //input matching for the corresponding genre
        switch (genreChoice) {
            case 1: return "Fantasy";
            case 2: return "Romance";
            case 3: return "Mystery";
            case 4: return "Horror";
            case 5: return "Science Fiction";
            case 6: return "QUIT";
            default:
                cout << "\nInvalid choice!" << endl;
                cout << "\nEnter your choice (1-6): ";
                break;
        }
    }
}

//function: allows user to choose book from the list
// selects a book from a <vector<Book> (linear search through MENU!)
// returns a pointer to the chosen Book object (or nullptr is user returns to the menu)
Book* getBookChoice(vector<Book>& books) {
    int bookChoice;
    bool loop = true;
    int listSize = books.size();

    while(loop) {
        loop = false;
        cout << "\nSelect book by entering the corresponding number:\n";
        
        //linear travesal of vector for display
        //this displays all of the book options
        for(int i = 0; i < listSize; i++){
            cout << i+1 << ". " << books[i].getTitle() << " by " << books[i].getAuthor() << endl;
        }
        cout << listSize+1 << ". RETURN TO MENU";
        cout << "\n\nEnter your choice (1-" << listSize+1 << "): ";
        cin >> bookChoice;

        //choice validation , allows for retry
        while(cin.fail()) {
            cout << "Invalid Choice! Enter an Integer!" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> bookChoice;
    }
        // returns chosen book (or returns null)
        if (bookChoice < 1 || bookChoice > listSize+1) {
            cout << "\nInvalid choice!" << endl;
            loop = true;
        }
    }

    if (bookChoice == listSize+1)
        return nullptr;
    else
        return &books[bookChoice-1]; // pointer to the chosen book
}

bool mainMenu(LibraryManager& lib, User& selectedUser) {
//------------------Main Menu------------------------//
    //menu display
    int menuOpt;
    cout << "\n-----------Menu----------" << endl;
    cout << "\nWhat would you like to do?" << endl;;
    cout << "1. Checkout a book\n2. Return a book\n3. Enter/Check Waitlist \n4. Account Info\n5.Donate Book\n6. Log Out" << endl;
    cout << "\nEnter your choice (1-6): ";
    cin >> menuOpt;
    //input validation
    while(cin.fail()) {
            cout << "Invalid Choice! Enter an Integer!" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> menuOpt;
    }

    //OPTION 1: checkout book
    if(menuOpt == 1) {
        string genre = getGenreChoice();

        if (genre == "QUIT")
            return true;
        // get books by genre
        // SEARCHES by genre (uses map<string, vector<Book>>)
        vector<Book> selectedBooks = lib.getBooksByGenre(genre);
        // prompt user to pick book, or go back to main menu
        // LINEAR SEARCHES through the genre list for book selection
        Book* chosenOne = getBookChoice(selectedBooks);
        cout<< chosenOne->getStatus() <<endl;
        if (chosenOne == nullptr)
            return true;
        //calls book title 
        //---------map searches??? O(log n) using red-black tree
        lib.checkOutBook(chosenOne->getTitle(), selectedUser);
        LibraryIO::saveToFile(lib);
        
    }
    //OPTION 2: Returns a book
    else if(menuOpt == 2) {
        // get vector of user books
        //LINEAR SEARCH: checks user's book list
        vector<Book> usersBook = selectedUser.getUserBooks();
        if(usersBook.size() == 0) {
            cout << "\nYou have no books. :((()" << endl;
            return true;
        }

        // prompt user to pick book, or go back to main menu
        Book* chosenOne = getBookChoice(usersBook);
        if (chosenOne == nullptr)
            return true;
        
        //returns book (if it exists)
        if(! lib.returnBook(chosenOne->getTitle(), &selectedUser)){
            cout<<"\nLooks like you do not have this book...\n"<<endl;
        }
        else{
            cout<< "\nYour book was successfully returned!\n"<<endl;
        }
        
    }
    //OPTION 3: Check waitlist or enters waitlist
    else if (menuOpt == 3){
        cout<<"\nCheck waitlist "<< endl;
        string bookTitle;
        cout<< "enter a book title"<<endl;
        cin.ignore();
        getline(cin, bookTitle); //this allowes multi-word titles

        //searches for book using its title
        // MAP LOOKUP: lib.getBook uses map<string,Book>
        Book* chosenBook = lib.getBook(bookTitle);
        
        //if book not found in the library catalog
        if(!chosenBook){
            cout<< "Book not found"<< endl;
            return true; //returns to main menu
        }

        //if user IS NOT on the waitlist for chosen book
        //LINEAR SEARCH: in deque<User*> checkWaitlist
        if(lib.checkWaitlist(selectedUser, bookTitle) == -1){
           cout<<"You are not on a waitlist for this book"<<endl;
        }
        else {
            //USER ON WAITLIST - shows position
            cout<< "You are Position #" << (lib.checkWaitlist(selectedUser, bookTitle) + 1) ;
            cout<<" in the waitlist!--"<<endl;

            //if user is first in line and book is available, the book is automaticcally checked out
            if(lib.checkWaitlist(selectedUser, bookTitle) == 0 && chosenBook->getStatus() == 1){
                cout<<"We checked out this book for you!"<<endl;
                // removes user form the waitlist (deque pop_front_)
                lib.exitWaitlist(bookTitle);
                //book is added to user's "checked out" list, so status is unavailable
                lib.checkOutBook(bookTitle, selectedUser);
                //saves updated library info to books.txt and users.txt
                LibraryIO::saveToFile(lib);
            }
        }
        
    }
    //account info
    else if (menuOpt == 4)
    {
        cout << "\n-----Your Account Info-----"<< endl;
        //VECTOR TRANSVERAL: transeverses user books
        lib.PrintUserInfo(selectedUser);
    }

    else if (menuOpt == 5) {
        cin.ignore();
        string title, author, genre;
        cout << "\nEnter the title of the book: ";
        getline(cin, title);
        cout << "Enter the author the the book";
        getline(cin, author);
        genre = getGenreChoice();
        if (genre == "QUIT") {
            cout << "Donation cancelled. \n";
            return true;
        }
        //donating a book ->>> added to map<string, Book> and vector<Book> by genre
        lib.donateBook(title, author, genre);
        LibraryIO::saveToFile(lib);
        cout << "\nThe Kureader Library thanks you for your donation!\n";
    }
    //logout
    else if (menuOpt == 6)
    {
        //log out
        return false;
    }
    else
    {
        cout << "\nInvalid choice. Please enter a number between 1 and 5.\n";
    }
    return true;
//------------------end Menu------------------------//
}

int main()
{
    LibraryManager lib;
    LibraryIO::loadFromFile(lib);
   
    
    bool isUserNew = false;
    User* selectedUser;
    
    while (true)
    {
        //----------------opening scene-------------------//
        cout << "---------------------------------------------" << endl;
        cout << "Welcome to Reader & Kurian's Library Emporium"<< endl;
        cout << "---------------------------------------------" << endl;
        cout << "\nEnter Username: "<< endl;
        string userName;
        cin >> userName;
        if(lib.userInList(userName)){
            int i;
            for(i = 0; i < 3; i++){
                cout << "\nEnter Password: "<< endl;
                string password;
                cin >> password;
                if(lib.hashPassCheck(userName, password)){ 
                    selectedUser = lib.userInList(userName);
                    cout << "\nWelcome back " << selectedUser->getFirst() << "!" <<endl;
                    break;
                }  
            }
            if(i == 3) continue;
        }
        else{
            cout << "\nLet's make you an account!\n" <<endl;
            cout << "What is your first name: " <<endl;
            string firstName;
            cin >> firstName;
            cout << "Enter Password: " <<endl;
            string password;
            cin >> password;
            selectedUser = new User(userName, firstName);
            selectedUser->setPassword(password);
            lib.AddUserToLibrary(selectedUser);
            LibraryIO::saveToFile(lib);
            isUserNew = true;
        }
        //-------------end opening scene-------------------//

        //---------------------Menu------------------------//
        bool opt = true;
        while(opt) {
            opt = mainMenu(lib, *selectedUser);
        }
    }
    
    if(isUserNew) delete selectedUser;

    LibraryIO::saveToFile(lib);
    return 0;
}


