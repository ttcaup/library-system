#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <string> 
#include <deque>
#include <unordered_map>
#include "Book.h"
#include "User.h"
#include <thread>
#include <chrono>
#include <functional>

using namespace std;


class LibraryManager {
    unordered_map< Book , User* > inventory; //maps book to user
    unordered_map< string , vector <Book> > sortGenre;//maps genre to a list of books 
    deque<User> waitlist; //wailist to meet edward from twighlight 
    vector<User> userList;  //we will need this for main logic, to create a selected user variable 

    LibraryManager(){

    }
    //print user info //J

    //add a book to the inventory  //J

    // add  a book to genre list //J

    

    //remove a book from the database and genre list  //J


    bool checkOutBook(Book book, User* user){
        if(inventory.find(book) == inventory.end()){
            return false;//returns false if the book is not found in inventory
        }
        else if (inventory[book] != nullptr){ //already in someone elses hands 
            return false;
        }
        else {
            user->addBook(book);
            inventory[book] = user; //updated the inventory
            return true;
        }
    }
    
    bool returnBook(Book book, User* user){
        if(! user->bookCheck(book)){
            return false;
        }
        else {
            user->removeBook(book);//updates user list
            inventory[book] = nullptr;//updates inventory
            return true;
        }
    }

    //queue search alg for users position in waitlist //E
    int checkWaitlist(User user){
        auto it = find(waitlist.begin(), waitlist.end(), user);
        return distance(waitlist.begin(), it);
    }

    //update waitlist? add to dequq push, remove from deque pop
    bool joinWaitlist(User user){
        waitlist.push_back(user);
        return true;
    }
    bool exitWaitlist(){
    if(! waitlist.empty()) //only pop if not empty
        waitlist.pop_front();
        return true;
    }
    
    void executeAfterDelay(int seconds, const std::function<void()>& exitWaitlist) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    exitWaitlist();
    }
    
};


#endif
