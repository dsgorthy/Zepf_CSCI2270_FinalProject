// Joshua Zepf
// CSCI 2270 Hoenigman
// Final Project
// Driver function
// April 2015

#include "Library.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    Library L;
    string command;
    while (command != "8")
    {
        cout << "======MAIN MENU======" << endl;
        cout << "1. Add User" << endl;
        cout << "2. Add Rating" << endl;
        cout << "3. Print Users" << endl;
        cout << "4. Print User's Ratings" << endl;
        cout << "5. Find Matches" << endl;
        cout << "6. Find Recommendations" << endl;
        cout << "7. AutoFill Library (Testing Purposes)" << endl;
        cout << "8. Quit" << endl;
        getline (cin, command);
        if (command == "1")
        {
            string userName;
            cout << "Enter name of new user:" << endl;
            getline (cin, userName);
            L.addUser(userName);
        }
        else if (command == "2")
        {
            string userName;
            string movieTitle;
            string ratingString;
            int rating;
            cout << "Enter user's name:" << endl;
            getline (cin, userName);
            cout << "Enter movie title:" << endl;
            getline (cin, movieTitle);
            cout << "Enter rating on a scale of 0 to 5:" << endl;
            getline (cin, ratingString);
            rating = stoi(ratingString);
            L.addRating(userName, movieTitle, rating);
        }
        else if (command == "3")
        {
            L.printUsers();
        }
        else if (command == "4")
        {
            string userName;
            cout << "Enter user's name:" << endl;
            getline(cin, userName);
            L.printRatings(userName);
        }
        else if (command == "5")
        {
            string userName;
            cout << "Enter user's name:" << endl;
            getline(cin, userName);
            L.findMatches(userName);
        }
        else if (command == "6")
        {
            string userName;
            cout << "Enter user's name:" << endl;
            getline (cin, userName);
            L.findRecommendations(userName);
        }
        else if (command == "7")
        {
            L.autoFill();
        }
    }
    cout << "Goodbye!" << endl;
}
