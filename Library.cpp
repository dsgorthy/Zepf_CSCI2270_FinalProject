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

int Library::hashSum(string movieTitle)
{
    int sum = 0;
    for (int i=0; i<movieTitle.length(); i++)
        sum = sum + movieTitle[i];
    sum = sum % 10;
    return sum;
}

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

void Library:: printRatings(string userName)
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


void Library::findMatches(string userName)
{
    User* u = userRoot;
    User* uTrav;
    Movie* m1;
    Movie* m2;
    int diff;
    while (u != NULL)
    {
        u->diffScore = 0;
        u = u->next;
    }
    u = userRoot;
    while (u != NULL)
    {
        if (u->name == userName)
            break;
        u = u->next;
    }
    for (int i=0; i<10; i++)
    {
        if (u->movieHashTable[i] != NULL)
        {
            m1 = u->movieHashTable[i];
            while (m1 != NULL)
            {
                uTrav = userRoot;
                while (uTrav != NULL)
                {
                    for (int j=0; j<10; j++)
                    {
                        if (uTrav->movieHashTable[j] != NULL)
                        {
                            m2 = uTrav->movieHashTable[j];
                            while (m2 != NULL)
                            {
                                if (m2->title == m1->title)
                                {
                                    diff = abs(m1->rating - m2->rating);
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
    max1->diffScore = 10;
    max1->name = "empty";
    max1->next = NULL;
    max1->prev = NULL;
    max2->diffScore = 10;
    uTrav = userRoot;
    while (uTrav != NULL)
    {
        if (uTrav->name != u->name)
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

void Library::findRecommendations(string userName)
{
    vector<Movie*> recList;
    User* u = userRoot;
    Movie* m;
    while (u != NULL)
    {
        if (u->name == userName)
            break;
        u = u->next;
    }
    if (u->max1 == NULL)
    {
        cout << "ERROR: Please find matches before finding recommendations" << endl;
        return;
    }
    for (int i=0; i<10; i++)
    {
        m = u->max1->movieHashTable[i];
        while (m != NULL)
        {
            if (m->rating == 4 || m->rating == 5)
                recList.push_back(m);
            m = m->next;
        }
    }
    if (u->max2 != NULL)
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
    for (int i=0; i<recList.size(); i++)
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
