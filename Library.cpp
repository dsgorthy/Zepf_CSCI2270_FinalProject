// Joshua Zepf
// CSCI 2270 Hoenigman
// Final Project
// Definitions for Library.h
// April 2015

#include "Library.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

Library::Library()
{
    User* root = new User;
    root->name = "empty";
    root->next = NULL;
    root->prev = NULL;
    setRoot(root);
}

Library::~Library()
{
}

/*
Function Prototype:
void Library::addUser(string)

Function Description:
This function takes the input string and creates a new user in the database.
It sets the diffScore, max1, max2, and movieHashTable elements to NULL

Example:
Library L;
L.addUser("Joshua");

Precondition: None
Post Condition: Creates a new user and puts it at the tail of the linked list of users
*/
void Library::addUser(string userName)
{
    if (userRoot->name == "empty")
    {
        User* root = new User;
        root->name = userName;
        root->next = NULL;
        root->prev = NULL;
        root->max1 = NULL;
        root->max2 = NULL;
        root->diffScore = 0;
        for (int i=0; i<10; i++)
            root->movieHashTable[i] = NULL;
        setRoot(root);
    }
    else
    {
        User* u = new User;
        u->name = userName;
        u->max1 = NULL;
        u->max2 = NULL;
        u->diffScore = 0;
        for (int i=0; i<10; i++)
            u->movieHashTable[i] = NULL;
        User* x = userRoot;
        while (x->next != NULL)
            x = x->next;
        x->next = u;
        u->prev = x;
    }
}

void Library::printUsers()
{
    User* u = userRoot;
    while (u != NULL)
    {
        cout << u->name << endl;
        u = u->next;
    }
}

void Library::setRoot(User* ur)
{
    userRoot = ur;
}

/*
Function Prototype:
void Library::addRating(string, string, int)

Function Description:
This function finds a user, finds the hash sum of a movie title, then adds the movie with a certain rating to the
user's hashtable

Example:
Library L;
L.addRating("Joshua", "Interstellar", 5);

Precondition: The username you input should match a user already added to the database. The first string should be
the username, the second string should be movie title, and the third string should be the rating of the movie
Post Condition: Rating given to movie and movie added to the user's hashtable.
*/
void Library::addRating(string userName, string movieTitle, int rating)
{
    User* u = userRoot;
    bool uFound = false;
    while (u != NULL)
    {
        if (u->name == userName)
        {
            uFound = true;
            break;
        }
        else
            u = u->next;
    }
    if (uFound == false)
        cout << "ERROR: User could not be found" << endl;
    else
    {
        Movie* m = new Movie;
        m->title = movieTitle;
        m->rating = rating;
        m->next = NULL;
        m->prev = NULL;
        int index = hashSum(movieTitle);
        if (u->movieHashTable[index] == NULL)
            u->movieHashTable[index] = m;
        else
            colResolve(u, m, index);
    }

}

/*
Basic hashSum function for a hashtable of size 10.
*/
int Library::hashSum(string movieTitle)
{
    int sum = 0;
    for (int i=0; i<movieTitle.length(); i++)
        sum = sum + movieTitle[i];
    sum = sum % 10;
    return sum;
}

/*
Function Prototype:
void Library::colResolve(User*, Movie*, int)

Function Description:
Only supposed to run through the addRating function. If there is a collision in the user's hashtable,
this will solve the collision by sorting the movies in that hashtable index in alphabetical order. Movies
that are chained are done so with a doubly linked list

Example:
Library L;
L.colResolve(user, movie, 5);

Precondition: User node, Movie node, and index in hashtable should already be found.
Post Condition: Collisions at hashTable[index] are sorted and returned in alphabetical order.
*/
void Library::colResolve(User* u, Movie* m, int index)
{
    Movie* x = u->movieHashTable[index];
    Movie* y;
    if (x->title > m->title)
    {
        m->next = x;
        x->prev = m;
        u->movieHashTable[index] = m;
        return;
    }
    while (x->next != NULL)
    {
        if (x->title > m->title)
        {
            y = x->prev;
            y->next = m;
            m->prev = y;
            m->next = x;
            x->prev = m;
            return;
        }
        x = x->next;
    }
    if (x->title > m->title)
    {
        y = x->prev;
        y->next = m;
        m->prev = y;
        m->next = x;
        x->prev = m;
    }
    else
    {
        x->next = m;
        m->prev = x;
    }
}

/*
Function Prototype:
void Library::printRatings(string)

Function Description:
Prints all the ratings that a given user has entered

Example:
Library L;
L.printRatings("Joshua");

Precondition: string userName must match the name of a user already added. Otherwise, it will return an error
Post Condition: Prints all the ratings the user has entered in the order they exist within the user's hashtable.
*/
void Library::printRatings(string userName)
{
    User* u = userRoot;
    bool uFound = false;
    while (u != NULL)
    {
        if (u->name == userName)
        {
            uFound = true;
            break;
        }
        else
            u = u->next;
    }
    if (uFound == false)
        cout << "ERROR: User could not be found" << endl;
    else
    {
        cout << u->name << "'s Ratings" << endl << "--------------------" << endl;
        Movie* m;
        for (int i=0; i<10; i++)
        {
            m = u->movieHashTable[i];
            if (m != NULL)
            {
                while (m != NULL)
                {
                    cout << m->title << ":" << m->rating << endl;
                    m = m->next;
                }
            }
        }
    }
}

/*
Function Prototype:
void Library::findMatches(string);

Function Description:
This function finds a user and compares all his ratings with the ratings of every other user. It calculates the
difference in ratings between all movies that both users have seen and then prints the two users that the original
user's ratings are most similar to. The function stores these two users in the max1 and max2 elements of the original
user's struct.

Example:
Library L;
L.findMatches("Joshua");

Precondition: Username input should match a user in the database. This function works better the more movies the user shares
in common with other users. If the original user's movies don't match any of the other user's movies, this function will return
two users, but they will not be similar.
Post Condition: Prints the two most similar users, and stores them in the user's struct;
*/
void Library::findMatches(string userName)
{
    User* u = userRoot; // u is target user
    User* uTrav; // uTrav will be used to move through the list of users
    Movie* m1; // m1 will be the target user's movie
    Movie* m2; // m2 will be uTrav's movie
    int diff; // diff will store the difference in rating in one movie
    while (u != NULL)
    {
        u->diffScore = 0; // Reset all the diffscores to 0 in case this function has already been run
        u = u->next;
    }
    u = userRoot;
    bool userFound = false;
    while (u != NULL)
    {
        if (u->name == userName)
        {
            userFound = true;
            break; // Sets u to the target user
        }
        u = u->next;
    }
    if (userFound == false)
    {
        cout << "ERROR: User could not be found" << endl;
        return;
    }
    for (int i=0; i<10; i++) // For every index in target user's movieHashTable
    {
        if (u->movieHashTable[i] != NULL) // If there is a movie in that index
        {
            m1 = u->movieHashTable[i];
            while (m1 != NULL) // Loops through all chained movies in that index
            {
                uTrav = userRoot;
                while (uTrav != NULL) // Loops through every user in the database and makes it uTrav
                {
                    for (int j=0; j<10; j++) // For every index in uTrav's movieHashTable
                    {
                        if (uTrav->movieHashTable[j] != NULL) // If there is a movie in that index
                        {
                            m2 = uTrav->movieHashTable[j];
                            while (m2 != NULL) // Loops through all chained movies in that index
                            {
                                if (m2->title == m1->title) // If uTrav's movie is the same as target user's movie
                                {
                                    diff = abs(m1->rating - m2->rating); // Calculates the absolute value between the difference in ratings
                                    uTrav->diffScore = uTrav->diffScore + diff;

                                }
                                m2 = m2->next;
                            }
                        }
                    }
                    uTrav = uTrav->next;
                }
                m1 = m1->next;
            }
        }
    }
    User* max1 = new User;
    User* max2 = new User;
    max1->diffScore = 1000000;
    max1->name = "empty";
    max1->next = NULL;
    max1->prev = NULL;
    max2->diffScore = 1000000;
    uTrav = userRoot;
    while (uTrav != NULL)
    {
        if (uTrav->name != u->name) // Makes sure the target user isn't matched with himself
        {
            if (uTrav->diffScore < max1->diffScore)
            {
                max2 = max1;
                max1 = uTrav;
            }
            else if (uTrav->diffScore < max2->diffScore)
                max2 = uTrav;
        }
        uTrav = uTrav->next;
    }
    u->max1 = max1;
    u->max2 = max2;
    cout << "Most similar user: " << u->max1->name << endl;
    cout << "Second most similar user: " << u->max2->name << endl;
}

/*
Function Prototype:
void Library::findRecommendations(string)

Function Description:
Finds the target user. Creates a vector of every movie that the two most similar users have rated a 4 or 5.
The vector is then compared to every movie the target user has rated and deletes the movie from the vector if the
target user has already seen the movie. It then prints every movie in the vector.

Example:
Library L;
L.findRecommendations("Joshua")

Precondition: Username input should match a user in the database. Matches must be found for the target user before
this function can be used.
Post Condition: Prints movies that the two similar users have rated a 4 or 5 that the target user has not seen.
*/
void Library::findRecommendations(string userName)
{
    vector<Movie*> recList; // Vector to store recommended movies
    User* u = userRoot;
    Movie* m;
    bool userFound = false;
    while (u != NULL)
    {
        if (u->name == userName)
        {
            userFound = true;
            break;
        }
        u = u->next;
    }
    if (userFound == false)
    {
        cout << "ERROR: User could not be found" << endl;
        return;
    }
    if (u->max1 == NULL) // Matches have not been found yet
    {
        cout << "ERROR: Please find matches before finding recommendations" << endl;
        return;
    }
    for (int i=0; i<10; i++) // For every index in movieHashTable
    {
        m = u->max1->movieHashTable[i];
        while (m != NULL)
        {
            if (m->rating == 4 || m->rating == 5) // If movie is rated a 4 or 5 add it to the vector
                recList.push_back(m);
            m = m->next;
        }
    }
    if (u->max2 != NULL) // If there is a second most similar user
    {
        for (int i=0; i<10; i++)
        {
            m = u->max2->movieHashTable[i];
            while (m != NULL)
            {
                if (m->rating == 4 || m->rating == 5)
                {
                    bool inList = false;
                    for (int j=0; j<recList.size(); j++)
                    {
                        if (recList[j]->title == m->title)
                            inList = true;
                    }
                    if (inList == false)
                        recList.push_back(m);
                }
                m = m->next;
            }
        }
    }
    for (int i=0; i<recList.size(); i++) // Loops through the vector and takes out the movie if the target user has already rated it
    {
        for (int j=0; j<10; j++)
        {
            m = u->movieHashTable[j];
            while (m != NULL)
            {
                if (m->title == recList[i]->title)
                    recList.erase(recList.begin()+i);
                m = m->next;
            }
        }
    }

    cout << "Recommended for " << u->name << ":" << endl;
    cout << "--------------------------" << endl;
    for (int i=0; i<recList.size(); i++)
    {
        cout << recList[i]->title << endl;
    }
}


/*
Function Prototype:
void Library::autoFill()

Function Description:
Fills the database with 5 users who have each rated 5 movies. This function is mainly for testing purposes
so that every time you run the program you don't have to add a bunch of users and ratings manually. This starting
database is relatively small.

Example:
Library L;
L.autoFill();

Precondition: No preconditions. This function can be run as soon as a Library has been created.
Post Condition: Adds 5 users and 25 ratings to the database.
*/
void Library::autoFill()
{
    string userName;
    userName = "Joshua";
    addUser(userName);
    addRating(userName, "Interstellar", 5);
    addRating(userName, "Clockwork Orange", 0);
    addRating(userName, "Mud", 3);
    addRating(userName, "Batman", 4);
    addRating(userName, "Inception", 4);
    userName = "Max";
    addUser(userName);
    addRating(userName, "Batman", 5);
    addRating(userName, "Inception", 3);
    addRating(userName, "Field of Dreams", 5);
    addRating(userName, "Dear John", 1);
    addRating(userName, "Moneyball", 5);
    userName = "Chase";
    addUser(userName);
    addRating(userName, "Interstellar", 5);
    addRating(userName, "Inception", 3);
    addRating(userName, "Field of Dreams", 4);
    addRating(userName, "Moneyball", 4);
    addRating(userName, "50 Shades of Grey", 5);
    userName = "Rachel";
    addUser(userName);
    addRating(userName, "Interstellar", 2);
    addRating(userName, "Mud", 3);
    addRating(userName, "50 Shades of Grey", 3);
    addRating(userName, "Batman", 3);
    addRating(userName, "Leon the Professional", 5);
    userName = "Karin";
    addUser(userName);
    addRating(userName, "Batman", 3);
    addRating(userName, "Inception", 5);
    addRating(userName, "Dear John", 4);
    addRating(userName, "Bridesmaids", 4);
    addRating(userName, "The Avengers", 3);
}
