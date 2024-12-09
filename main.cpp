//main.cpp

/*
Library System

Course:  CMPE 126
Authors: Eden Reader
         Jasmine Kurian

*/
#include <iostream>
#include <string>
#include "Book.h"
#include "LibraryManager.h"
#include "User.h"

#include <iostream>
#include <string>
using namespace std;

string getGenreChoice() {
    int genreChoice;
    cout << "\nChoose genre by entering the corresponding number:\n";
    cout << "1. Fantasy\n2. Romance\n3. Mystery\n4. Horror\n5. Science Fiction\n\n6. Go back to menu\n";
    cout << "\nEnter your choice (1-6): ";
    while (true) {
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
    cout << "Select book by entering the corresponding number:\n";
    
    for(int i = 0; i < books.size(); i++){
        cout << i+1 << ") " << books[i].getTitle() << " by " << books[i].getAuthor() << endl;
    }
    cout << "\n6) Go back to menu";
    cout << "\nEnter your choice (1-6): ";
    cin >> bookChoice;
    
    while (bookChoice < 1 && bookChoice > 6) {
        cout << "\nInvalid choice!" << endl;
        cout << "\nEnter your choice (1-5): ";
        cin >> bookChoice;
    }

    if (bookChoice == 6)
        return nullptr;
    else
        return &books[bookChoice-1];
}

int main(int argc, char const *argv[])
{
    LibraryManager lib = LibraryManager();

    //Fantasy
    lib.AddBookToLibrary(Book("Harry Potter", "J.K. Rowling", "Fantasy"));
    lib.AddBookToLibrary(Book("Eldest", "Christopher Paolini", "Fantasy"));
    lib.AddBookToLibrary(Book("Uprooted", "Naomi Novik", "Fantasy"));
    lib.AddBookToLibrary(Book("Eragon", "Christopher Paolini", "Fantasy"));
    lib.AddBookToLibrary(Book("Mistborn", "Brandon Sanderson", "Fantasy"));

    //Romance
    lib.AddBookToLibrary(Book("Twilight", "Stephenie Meyer", "Romance"));
    lib.AddBookToLibrary(Book("Eleanor", "Rainbow Rowell", "Romance"));
    lib.AddBookToLibrary(Book("Outlander", "Diana Gabaldon", "Romance"));
    lib.AddBookToLibrary(Book("After", "Anna Todd", "Romance"));
    lib.AddBookToLibrary(Book("Fifty Shades of Grey", "E.L. James", "Romance"));

    //Mystery
    lib.AddBookToLibrary(Book("Sherlock", "Arthur Conan Doyle", "Mystery"));
    lib.AddBookToLibrary(Book("Gone", "Gillian Flynn", "Mystery"));
    lib.AddBookToLibrary(Book("Innocent", "Scott Turow", "Mystery"));
    lib.AddBookToLibrary(Book("Sharp", "Gillian Flynn", "Mystery"));
    lib.AddBookToLibrary(Book("Rogue", "Ruth Ware", "Mystery"));

    //Science Fiction
    Book dune("Dune", "Frank Herbert", "Science Fiction"); 
    Book ender("Ender's Game", "Orson Scott Card", "Science Fiction"); 
    Book neuromancer("Neuromancer", "William Gibson", "Science Fiction"); 
    Book foundation("Foundation", "Isaac Asimov", "Science Fiction"); 
    Book hyperion("Hyperion", "Dan Simmons", "Science Fiction"); 

    //Add books to library
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

    //Add books to library
    lib.AddBookToLibrary(carrie);
    lib.AddBookToLibrary(it);
    lib.AddBookToLibrary(dracula);
    lib.AddBookToLibrary(birdbox);
    lib.AddBookToLibrary(frankenstein);

    //and users 
    User Eden("eread", "Eden", "Romance" );
    User Jasmine("jamontoast", "Jasmine", "Fantasy");
    User Matthew("loco4cocoa", "Matthew", "Science Fiction");

    lib.AddUserToLibrary(Eden);
    lib.AddUserToLibrary(Jasmine);
    lib.AddUserToLibrary(Matthew);
    
    //lib.printUserList();

   
    while (true)
    {
        //----------------opening scene-------------------//
        cout << "-------------------------------------" << endl;
        cout << "Welcome to Reader & Kurian's Emporium"<< endl;
        cout << "-------------------------------------" << endl;
        cout << "\nEnter Username: "<<endl;
        string userName;
        cin >> userName;
        User* selectedUser = lib.userInList(userName);
        
        if (selectedUser == nullptr) {
            cout << "\nLet's make you an account!\n" <<endl;
            cout << "What is your first name: " <<endl;
            string firstName;
            cin >> firstName;
            
            cout << "\nLet's find your favorite genre!" << endl;
            string favGenre = getGenreChoice(); //gets their fav genre! 
            selectedUser = new User(userName, firstName, favGenre);
            lib.AddUserToLibrary(*selectedUser);
        }
        else {
            cout << "\nWelcome back " << selectedUser->getFirst() << "!" <<endl;
        }
        //-------------end opening scene-------------------//

        //---------------------Menu------------------------//
        while(true) {
            int menuOpt;
            cout << "\n\n----dhfjsdhf-------Menu----------" << endl;
            cout << "\nWhat would you like to do?" << endl;;
            cout << "1. Checkout a book\n2. Return a book\n3. Enter/Check Waitlist \n4. Account Info\n5. Log Out" << endl;
            cout << "\nEnter your choice (1-5): ";
            cin >> menuOpt;

            //checkout book
            if(menuOpt == 1){
                string genre = getGenreChoice();

                if (genre == "QUIT")
                    break;

                vector<Book> selectedBooks = lib.getBooksByGenre(genre);
                
                if (getBookChoice(selectedBooks) == nullptr)
                    break;

                Book chosenOne = *getBookChoice(selectedBooks);
                if (!lib.checkOutBook(chosenOne,selectedUser)) {
                    cout << "\nBook Unavailable, checked out by another human.\n" << endl << endl;
                }
            }
            
            else if(menuOpt == 2){
                vector <Book> usersBook = selectedUser->getUserBooks();
                if (getBookChoice(usersBook) == nullptr)
                    break;
                
                Book chosenOne = *getBookChoice(usersBook);
                if(! lib.returnBook(chosenOne, selectedUser)){
                    cout<<"\nLooks like you do not have this book...\n"<<endl;
                }
                else{
                    cout<< "\nYour book was successfully returned!\n"<<endl;
                }
                
            }
            else if (menuOpt == 3)// Enter/check waitlist
            {
                cout<<"Join OR Check waitlist "<< endl;
                
                if(lib.checkWaitlist(*selectedUser)== -1){
                    lib.joinWaitlist(*selectedUser);
                    cout << "\nYou have joined the waitlist to meet" << endl;
                    cout << "Professor Mortezie and Edward Cullen!\n" << endl;
                    cout<< "You are Position #"<<lib.checkWaitlist(*selectedUser);
                    cout<<" in the waitlist!"<<endl;
                }
                
                else{
                    cout<< "You are Position #"<<lib.checkWaitlist(*selectedUser);
                    cout<<" in the waitlist!"<<endl;
                }
            }
            //account info
            else if (menuOpt == 4)
            {
                cout << "Your Account Info: "<< endl;
                lib.PrintUserInfo(*selectedUser);
            }
            //logout
            else if (menuOpt == 5)
            {
                //log out
                break;
                
            }
            else {
                cout << "\nInvalid choice. Please enter a number between 1 and 4.";
            }
        }
        
        //------------------end Menu------------------------//
    }

    //list genre recs based on selected genre 1-5 

    return 0;
}


