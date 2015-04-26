// Joshua Zepf
// CSCI 2270 Hoenigman
// Final Project
// Header File
// April 2015

#ifndef MOVIE_H
#define GRAPH_H

#include <string>

struct Movie
{
    std::string title; // Title of movie
    int rating; // Rating of movie
    Movie* next; // Pointer for collision linked list
    Movie* prev; // Pointer for collision linked list
};

struct User
{
    std::string name; // Name of user
    User* next; // Pointer for linked list
    User* prev; // Pointer for linked list
    User* max1; // Pointer to most similar user
    User* max2; // Pointer to second most similar user
    int diffScore; // Stores how different the user's ratings are to a comparing user
    Movie* movieHashTable[10]; // Hashtable that stores the user's ratings
};

class Library
{
    public:
        Library();
        ~Library();
        void addUser(std::string userName);
        void setRoot(User* ur);
        void printUsers();
        void addRating (std::string userName, std::string movieTitle, int rating);
        int hashSum(std::string movieTitle);
        void colResolve(User* u, Movie* m, int index);
        void printRatings(std::string userName);
        void findMatches(std::string userName);
        void findRecommendations(std::string userName);
        void autoFill();
    protected:
    private:
        User* userRoot; // Root of the linked list of Users.
};

#endif // MOVIE_H
