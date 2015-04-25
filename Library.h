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
    std::string title;
    int rating;
    Movie* next;
    Movie* prev;
};

struct User
{
    std::string name;
    User* next;
    User* prev;
    User* max1;
    User* max2;
    int diffScore;
    Movie* movieHashTable[10];
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
        User* userRoot;
};

#endif // MOVIE_H
