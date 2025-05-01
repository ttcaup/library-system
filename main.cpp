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

string getGenreChoice() {
    int genreChoice;
    
    while (true) {
        cout << "\nChoose genre by entering the corresponding number:\n";
        cout << "1. Fantasy\n2. Romance\n3. Mystery\n4. Horror\n5. Science Fiction\n6. RETURN TO MENU\n";
        cout << "\nEnter your choice (1-6): ";
        cin >> genreChoice;
        while(cin.fail()) {
            cout << "Invalid Choice! Enter an Integer!" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> genreChoice;
    }
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

Book* getBookChoice(vector<Book>& books) {
    int bookChoice;
    bool loop = true;
    int listSize = books.size();

    while(loop) {
        loop = false;
        cout << "\nSelect book by entering the corresponding number:\n";
        
        for(int i = 0; i < listSize; i++){
            cout << i+1 << ". " << books[i].getTitle() << " by " << books[i].getAuthor() << endl;
        }
        cout << listSize+1 << ". RETURN TO MENU";
        cout << "\n\nEnter your choice (1-" << listSize+1 << "): ";
        cin >> bookChoice;
        while(cin.fail()) {
            cout << "Invalid Choice! Enter an Integer!" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> bookChoice;
    }
        
        if (bookChoice < 1 || bookChoice > listSize+1) {
            cout << "\nInvalid choice!" << endl;
            loop = true;
        }
    }

    if (bookChoice == listSize+1)
        return nullptr;
    else
        return &books[bookChoice-1];
}

bool mainMenu(LibraryManager& lib, User& selectedUser) {
//------------------Main Menu------------------------//

    int menuOpt;
    cout << "\n-----------Menu----------" << endl;
    cout << "\nWhat would you like to do?" << endl;;
    cout << "1. Checkout a book\n2. Return a book\n3. Enter/Check Waitlist \n4. Account Info\n5. Log Out" << endl;
    cout << "\nEnter your choice (1-5): ";
    cin >> menuOpt;
    while(cin.fail()) {
            cout << "Invalid Choice! Enter an Integer!" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> menuOpt;
    }

    //checkout book
    if(menuOpt == 1) {
        string genre = getGenreChoice();

        if (genre == "QUIT")
            return true;
        // get books by genre
        vector<Book> selectedBooks = lib.getBooksByGenre(genre);
        // prompt user to pick book, or go back to main menu
        Book* chosenOne = getBookChoice(selectedBooks);
        cout<< chosenOne->getStatus() <<endl;
        if (chosenOne == nullptr)
            return true;
        //calls book title 
        lib.checkOutBook(chosenOne->getTitle(), selectedUser);
        LibraryIO::saveToFile(lib);
        
    }
    
    else if(menuOpt == 2) {
        // get vector of user books
        vector<Book> usersBook = selectedUser.getUserBooks();
        if(usersBook.size() == 0) {
            cout << "\nYou have no books. :((()" << endl;
            return true;
        }

        // prompt user to pick book, or go back to main menu
        Book* chosenOne = getBookChoice(usersBook);
        if (chosenOne == nullptr)
            return true;
        
        if(! lib.returnBook(chosenOne->getTitle(), &selectedUser)){
            cout<<"\nLooks like you do not have this book...\n"<<endl;
        }
        else{
            cout<< "\nYour book was successfully returned!\n"<<endl;
        }
        
    }
    // check waitlist
    else if (menuOpt == 3){
        cout<<"\nCheck waitlist "<< endl;
        string bookTitle;
        cout<< "enter a book title"<<endl;
        cin.ignore();
        getline(cin, bookTitle);
        Book* chosenBook = lib.getBook(bookTitle);
        
        if(!chosenBook){
            cout<< "Book not found"<< endl;
            return true;
        }
        if(lib.checkWaitlist(selectedUser, bookTitle) == -1){
           cout<<"You are not on a waitlist for this book"<<endl;
        }
        else {
            cout<< "You are Position #" << (lib.checkWaitlist(selectedUser, bookTitle) + 1) ;
            cout<<" in the waitlist!--"<<endl;
            if(lib.checkWaitlist(selectedUser, bookTitle) == 0 && chosenBook->getStatus() == 1){
                cout<<"We checked out this book for you!"<<endl;
                lib.exitWaitlist(bookTitle);
                lib.checkOutBook(bookTitle, selectedUser);
                LibraryIO::saveToFile(lib);
            }
        }
        
    }
    //account info
    else if (menuOpt == 4)
    {
        cout << "\n-----Your Account Info-----"<< endl;
        
        lib.PrintUserInfo(selectedUser);
    }

    //logout
    else if (menuOpt == 5)
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


