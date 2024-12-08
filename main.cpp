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
    cout << "Choose genre by entering the corresponding number:\n";
    cout << "1. Fantasy\n2. Romance\n3. Mystery\n4. Horror\n5. Science Fiction\n";
    cout << "Enter your choice (1-5): ";
    while (true) {
        cin >> genreChoice;
        switch (genreChoice) {
            case 1: return "Fantasy";
            case 2: return "Romance";
            case 3: return "Mystery";
            case 4: return "Horror";
            case 5: return "Science Fiction";
            default:
                cout << "Invalid choice!" << endl;
                cout << "Enter your choice (1-5): ";
                break;
        }
    }
}

Book getBookChoice(vector<Book>& books) {
    int bookChoice;
    cout << "Select book by entering the corresponding number:\n";

    for(int i = 0; i < books.size(); i++){
        cout << i+1 << ") " << books[i].getTitle() << " by " << books[i].getAuthor() <<endl;
    }
    cout << "Enter your choice (1-5): ";
    cin >> bookChoice;
    
    while (bookChoice < 1 && bookChoice > 5) {
        cout << "Invalid choice!" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> bookChoice;
    }

    return books[bookChoice-1];
}

int main(int argc, char const *argv[])
{
    LibraryManager lib = LibraryManager();

    //Fantasy
    Book eldest("Eldest", "Christopher Paolini", "Fantasy"); 
    Book uprooted("Uprooted", "Naomi Novik", "Fantasy"); 
    Book eragon("Eragon", "Christopher Paolini", "Fantasy"); 
    Book mistborn("Mistborn", "Brandon Sanderson", "Fantasy"); 

    //Add books to library
    lib.AddBookToLibrary(eldest);
    lib.AddBookToLibrary(uprooted);
    lib.AddBookToLibrary(eragon);
    lib.AddBookToLibrary(mistborn);

    //Romance
    Book twilight("Twilight", "Stephenie Meyer", "Romance"); 
    Book eleanor("Eleanor", "Rainbow Rowell", "Romance"); 
    Book outlander("Outlander", "Diana Gabaldon", "Romance"); 
    Book after("After", "Anna Todd", "Romance"); 
    Book fiftyShades("Fifty Shades of Grey", "E.L. James", "Romance"); 

    //Add books to library
    lib.AddBookToLibrary(twilight);
    lib.AddBookToLibrary(eleanor);
    lib.AddBookToLibrary(outlander);
    lib.AddBookToLibrary(after);
    lib.AddBookToLibrary(fiftyShades);

    //Mystery
    Book sherlock("Sherlock", "Arthur Conan Doyle", "Mystery"); 
    Book gone("Gone", "Gillian Flynn", "Mystery"); 
    Book innocent("Innocent", "Scott Turow", "Mystery"); 
    Book sharp("Sharp", "Gillian Flynn", "Mystery"); 
    Book rogue("Rogue", "Ruth Ware", "Mystery"); 

    //Add books to library
    lib.AddBookToLibrary(sherlock);
    lib.AddBookToLibrary(gone);
    lib.AddBookToLibrary(innocent);
    lib.AddBookToLibrary(sharp);
    lib.AddBookToLibrary(rogue);

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
   
    while (true)
    {
        //----------------opening scene-------------------//
        cout << "Welcome to Reader & Kurian's Emporium"<<endl;
        cout << "Enter Username: "<<endl;
        string userName;
        cin >> userName;
        User* selectedUser = lib.userInList(userName);
        
        if (selectedUser == nullptr){
            cout << "Let's make you an account!" <<endl;
            cout << "What is your first name: " <<endl;
            string firstName;
            cin >> firstName;
            
            cout << "Let's find your favorite genre!" << endl;
            string favGenre = getGenreChoice(); //gets their fav genre! 
            selectedUser = new User(userName, firstName, favGenre);
            lib.AddUserToLibrary(*selectedUser);
        }
        else {
            cout << "Welcome back " << selectedUser->getFirst() << "!" <<endl;
        }
        //-------------end opening scene-------------------//

        //---------------------Menu------------------------//
        while(true) {
            int menuOpt;
            cout << "--------Menu-------" << endl << endl;
            cout << "What would you like to do?" << endl;;
            cout << "1. Checkout a book\n2. Return a book\n3. Enter/Check Waitlist \n4. Account Info\n5. Log Out" << endl;
            cout << "Enter your choice (1-5): ";
            cin >> menuOpt;

            //checkout book
            if(menuOpt == 1){
                string genre = getGenreChoice();
                vector<Book> selectedBooks = lib.getBooksByGenre(genre);
                Book chosenOne = getBookChoice(selectedBooks);
                if (!lib.checkOutBook(chosenOne,selectedUser)) {
                    cout << "Book Unavailable, checked out by another human." << endl << endl;
                }
            }
            
            else if(menuOpt == 2){
                vector <Book> usersBook = selectedUser->getUserBooks();
                Book chosenOne = getBookChoice(usersBook);
                if(! lib.returnBook(chosenOne, selectedUser)){
                    cout<<"Looks like you do not have this book..."<<endl;
                }
                else{
                    cout<< "Your book was successfully returned!"<<endl;
                }
                
            }
            else if (menuOpt == 3)
            {
                //waitlist
                
            }
            //account info
            else if (menuOpt == 4)
            {
                cout << "Username: " << selectedUser->getUsername() << endl; 
                cout << "Name: " << selectedUser->getFirst() << endl; 
                cout << "Favorite Genre: " << selectedUser->getGenre() << endl; 
                
            }
            //logout
            else if (menuOpt == 5)
            {
                //log out
                break;
                
            }
            else{
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            }
        }
        
        //------------------end Menu------------------------//
    }
    

    //list genre recs based on selected genre 1-5 

    return 0;
}


