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

using namespace std;

string getGenreChoice() {
    int genreChoice;
    
    while (true) {
        cout << "\nChoose genre by entering the corresponding number:\n";
        cout << "1. Fantasy\n2. Romance\n3. Mystery\n4. Horror\n5. Science Fiction\n6. RETURN TO MENU\n";
        cout << "\nEnter your choice (1-6): ";
        cin >> genreChoice;
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

    //checkout book
    if(menuOpt == 1) {
        string genre = getGenreChoice();

        if (genre == "QUIT")
            return true;
        
        // get books by genre
        vector<Book> selectedBooks = lib.getBooksByGenre(genre);
        
        // prompt user to pick book, or go back to main menu
        Book* chosenOne = getBookChoice(selectedBooks);
        if (chosenOne == nullptr)
            return true;

        if (!lib.checkOutBook(*chosenOne, selectedUser)) {
            cout << "\nBook Unavailable, checked out by another human.\n" << endl << endl;
        }
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
        
        if(! lib.returnBook(*chosenOne, &selectedUser)){
            cout<<"\nLooks like you do not have this book...\n"<<endl;
        }
        else{
            cout<< "\nYour book was successfully returned!\n"<<endl;
        }
        
    }
    else if (menuOpt == 3)// Enter/check waitlist
    {
        cout<<"\nJoin OR Check waitlist "<< endl;
        if(lib.checkWaitlist(selectedUser) == -1){
            lib.joinWaitlist(selectedUser);
            cout << "\nYou have joined the waitlist to meet" << endl;
            cout << "Professor Mortezie and Edward Cullen!\n" << endl;
            cout<< "--You are Position #"<<lib.checkWaitlist(selectedUser);
            cout<<" in the waitlist!--"<<endl;
        }
        else
        {
            cout<< "--You are Position #" << lib.checkWaitlist(selectedUser);
            cout<<" in the waitlist!--"<<endl;
            if(lib.checkWaitlist(selectedUser) == 0){
                cout<<"It's time to meet Professor Mortezie and Edward Cullen!!!" << endl;
                cout <<"We are so excited for you <3"<<endl;
                lib.exitWaitlist();
            }
        }
    }
    //account info
    else if (menuOpt == 4)
    {
        cout << "\n- - - - Your Account Info - - - -"<< endl;
        
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
        cout << "\nInvalid choice! Please enter a number between 1 and 5.\n";
    }
    return true;
//------------------end Menu------------------------//
}

int main(int argc, char const *argv[])
{
    // ------------------- initialize and fill the library with presets! ------------------------- //
    LibraryManager lib = LibraryManager();

    //Fantasy
    Book harry("Harry Potter", "J.K. Rowling", "Fantasy");
    Book eldest("Eldest", "Christopher Paolini", "Fantasy");
    Book uprooted("Uprooted", "Naomi Novik", "Fantasy");
    Book eragon("Eragon", "Christopher Paolini", "Fantasy");
    Book mistborn("Mistborn", "Brandon Sanderson", "Fantasy");
    lib.AddBookToLibrary(harry);
    lib.AddBookToLibrary(eldest);
    lib.AddBookToLibrary(uprooted);
    lib.AddBookToLibrary(eragon);
    lib.AddBookToLibrary(mistborn);

    //Romance
    Book Twilight("Twilight", "Stephenie Meyer", "Romance");
    Book Eleanor("Eleanor", "Rainbow Rowell", "Romance");
    Book Outlander("Outlander", "Diana Gabaldon", "Romance");
    Book fifty("Fifty Shades of Grey", "E.L. James", "Romance");
    Book After("After", "Anna Todd", "Romance");
    lib.AddBookToLibrary(Twilight);
    lib.AddBookToLibrary(Eleanor);
    lib.AddBookToLibrary(Outlander);
    lib.AddBookToLibrary(After);
    lib.AddBookToLibrary(fifty);

    //Mystery
    Book Sherlock("Sherlock", "Arthur Conan Doyle", "Mystery");
    Book Gone("Gone", "Gillian Flynn", "Mystery");
    Book Innocent("Innocent", "Scott Turow", "Mystery");
    Book Sharp("Sharp", "Gillian Flynn", "Mystery");
    Book Rogue("Rogue", "Ruth Ware", "Mystery");
    lib.AddBookToLibrary(Sherlock);
    lib.AddBookToLibrary(Gone);
    lib.AddBookToLibrary(Innocent);
    lib.AddBookToLibrary(Sharp);
    lib.AddBookToLibrary(Rogue);
    
    //Science Fiction
    Book dune("Dune", "Frank Herbert", "Science Fiction"); 
    Book ender("Ender's Game", "Orson Scott Card", "Science Fiction"); 
    Book neuromancer("Neuromancer", "William Gibson", "Science Fiction"); 
    Book foundation("Foundation", "Isaac Asimov", "Science Fiction"); 
    Book hyperion("Hyperion", "Dan Simmons", "Science Fiction"); 

    lib.AddBookToLibrary(dune);
    lib.AddBookToLibrary(ender);
    lib.AddBookToLibrary(neuromancer);
    lib.AddBookToLibrary(foundation);
    lib.AddBookToLibrary(hyperion);

    //Horror
    Book carrie("Carrie", "Stephen King", "Horror"); 
    Book it("It", "Stephen King", "Horror"); 
    Book dracula("Dracula", "Bram Stoker", "Horror"); 
    Book birdbox("Birdbox", "Josh Malerman", "Horror"); 
    Book frankenstein("Frankenstein", "Mary Shelley", "Horror"); 

    lib.AddBookToLibrary(carrie);
    lib.AddBookToLibrary(it);
    lib.AddBookToLibrary(dracula);
    lib.AddBookToLibrary(birdbox);
    lib.AddBookToLibrary(frankenstein);

    //and users 
    User Eden("eread", "Eden");
    User Jasmine("jamontoast", "Jasmine");
    User Matthew("loco4cocoa", "Matthew");
    
    //add users to library
    lib.AddUserToLibrary(&Eden);
    lib.AddUserToLibrary(&Jasmine);
    lib.AddUserToLibrary(&Matthew);

    //adding users to waitlist
    lib.joinWaitlist(Eden);
    lib.joinWaitlist(Jasmine);
    lib.joinWaitlist(Matthew);

    //adding books to users
    lib.checkOutBook(Twilight, Matthew);
    lib.checkOutBook(dracula, Jasmine);
    lib.checkOutBook(Rogue, Jasmine);
    lib.checkOutBook(dune, Eden);
    lib.checkOutBook(Outlander, Eden);
    
    bool isUserNew = false;
    User* selectedUser;
    
    while (true)
    {
        //----------------opening scene-------------------//
        cout << "---------------------------------------------" << endl;
        cout << "Welcome to Reader & Kurian's Library Emporium"<< endl;
        cout << "---------------------------------------------" << endl;
        cout << "\nEnter (or create a new) username: "<< endl;
        string userName;
        cin >> userName;
        selectedUser = lib.userInList(userName);
        
        if (selectedUser == nullptr) {
            cout << "\nLet's make you an account!\n" <<endl;
            cout << "What is your first name: " <<endl;
            string firstName;
            cin >> firstName;
            selectedUser = new User(userName, firstName);
            lib.AddUserToLibrary(selectedUser);
            isUserNew = true;
        }
        else {
            cout << "\nWelcome back " << selectedUser->getFirst() << "!" <<endl;
        }
        //-------------end opening scene-------------------//

        //---------------------Menu------------------------//
        bool opt = true;
        while(opt) {
            opt = mainMenu(lib, *selectedUser);
        }
    }
    
    if(isUserNew) delete selectedUser;
    return 0;
}


